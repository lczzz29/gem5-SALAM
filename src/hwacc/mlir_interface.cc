// MLIRInterface Includes
#include "hwacc/mlir_interface.hh"

MLIRInterface::MLIRInterface(const MLIRInterfaceParams &p):
    ComputeUnit(p),
    filename(p.in_file),
    topName(p.top_name),
    scheduling_threshold(p.sched_threshold),
    clock_period(p.clock_period),
    lockstep(p.lockstep_mode) {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    clock_period = clock_period * 1000;
    dbg = comm->debug();
}

std::shared_ptr<MULA::Operation> createClone(const std::shared_ptr<MULA::Operation>& b)
{
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    std::shared_ptr<MULA::Operation> clone = b->clone();
    return clone;
}

void
MLIRInterface::ActiveFunc::scheduleBlock(std::shared_ptr<MULA::Block> block)
{
    auto schedulingStart = std::chrono::high_resolution_clock::now();
    if (dbg) DPRINTFS(Runtime, owner, "|---[Schedule MLIR Block - UID:%i ]\n", block->getUID());
    bool needToScheduleSuccessor = false;
    std::shared_ptr<MULA::Block> nextBlock;
    auto operation_list = *(block->Operations());
    for (auto op : operation_list) {
        std::shared_ptr<MULA::Operation> clone_op = op->clone();
        if (dbg) DPRINTFS(Runtime, owner,  "\t\t Operation Cloned [UID: %d] \n", op->getUID());
        
        findDynamicDeps(clone_op);
        reservation.push_back(clone_op);
        
        // Currently supports only arith, scf, memref and func dialects
        // thus should not check whether there is an unconditional branch cf.br
        // TODO: if supporting other dialects in the future, need to modify

        // // Handle MLIR terminator operations that control flow
        // if (clone_op->isTerminator()) {
        //     if (dbg) DPRINTFS(Runtime, owner, "\t\t Terminator Operation Found\n");
            
        //     // Handle MLIR cf.br operation (unconditional branch)
        //     if (clone_op->isCFBranch()) {
        //         if (dbg) DPRINTFS(Runtime, owner, "\t\t CF Branch Operation Found\n");
        //         auto cfBranch = mlir::dyn_cast_or_null<MULA::cf::BranchOp>(clone_op.get());
        //         if (cfBranch && !cfBranch->isConditional()) {
        //             if (dbg) DPRINTFS(Runtime, owner, "\t\t Unconditional Branch, Scheduling Next Block\n");
        //             nextBlock = cfBranch->getSuccessor();
        //             if (dbg) DPRINTFS(RuntimeCompute, owner, "\t\t Branching to %s from %s\n", 
        //                             nextBlock->getIRStub(), block->getIRStub());
        //             needToScheduleSuccessor = true;
        //         } else {
        //             // Conditional branch - add to reservation so it can be evaluated at runtime
        //             findDynamicDeps(clone_op);
        //             reservation.push_back(clone_op);
        //         }
        //     }
        //     // All other terminator operations get added to the reservation queue
        //     else {
        //         findDynamicDeps(clone_op);
        //         reservation.push_back(clone_op);
        //     }
        // }
        // // Handle all other operations (including SCF operations)
        // else {
        //     findDynamicDeps(clone_op);
        //     reservation.push_back(clone_op);
        // }
    }
    previousBlock = block;
    auto schedulingStop = std::chrono::high_resolution_clock::now();
    owner->addSchedulingTime(schedulingStop - schedulingStart);
    if (needToScheduleSuccessor) scheduleBlock(nextBlock);
}

// Add a new method to schedule MLIR regions
void
MLIRInterface::ActiveFunc::scheduleRegion(std::shared_ptr<MULA::Region> region)
{
    if (!region) return;
    
    auto schedulingStart = std::chrono::high_resolution_clock::now();
    if (dbg) DPRINTFS(Runtime, owner, "|---[Schedule MLIR Region]\n");
    
    // Schedule entry block in the region
    auto blocks = region->Blocks();
    if (!blocks || blocks->empty()) {
        if (dbg) DPRINTFS(Runtime, owner, "\t\t Region has no blocks\n");
        auto schedulingStop = std::chrono::high_resolution_clock::now();
        owner->addSchedulingTime(schedulingStop - schedulingStart);
        return;
    }
    
    // Schedule the entry block
    auto entryBlock = blocks->front();
    scheduleBlock(entryBlock);
    
    auto schedulingStop = std::chrono::high_resolution_clock::now();
    owner->addSchedulingTime(schedulingStop - schedulingStart);
}

void
MLIRInterface::ActiveFunc::processQueues() {
    auto queueStart = std::chrono::high_resolution_clock::now();

    if (owner->hw->hw_statistics->use_cycle_tracking()) {
        auto hwStart = std::chrono::high_resolution_clock::now();
        hw_cycle_stats.reset();
        owner->hw->hw_statistics->updateHWStatsCycleStart();

        // Update Params
        hw_cycle_stats.cycle = owner->cycle;
        hw_cycle_stats.resInFlight = reservation.size();
        hw_cycle_stats.loadInFlight = readQueue.size();
        hw_cycle_stats.storeInFlight = writeQueue.size();
        hw_cycle_stats.compInFlight = computeQueue.size();


        //
        auto hwStop = std::chrono::high_resolution_clock::now();
        owner->addHWTime(hwStop-hwStart);
    }
    
    if (dbg) {
        DPRINTFS(Runtime, owner, "\t\t  |-[Process Queues]--------\n");
        DPRINTFS(RuntimeQueues, owner, "\t\t[Runtime Queue Status] Reservation:%d, Compute:%d, Read:%d, Write:%d\n",
             reservation.size(), computeQueue.size(), readQueue.size(), writeQueue.size());
    }
    // First pass, computeQueue is empty
    for (auto queue_iter = computeQueue.begin(); queue_iter != computeQueue.end();) {
        if (dbg) DPRINTFS(Runtime, owner,  "\n\t\t %s \n\t\t %s%s%s%d%s \n",
        " |-[Compute Queue]--------------",
        " | Operation: ", queue_iter->second->getOpName(),
        " | UID[", (queue_iter->first), "]"
        );

        if((queue_iter->second)->commit()) {
            (queue_iter->second)->reset();
            queue_iter = computeQueue.erase(queue_iter);
            hw_cycle_stats.compCommited++;
        } else {
            ++queue_iter;
            hw_cycle_stats.compFUStall++;
        }
    }
    if (canReturn()) {
        // Handle function return
        if (dbg) DPRINTFS(Runtime, owner,  "[[Function Return]]\n\n");
        if (caller != nullptr) {
            // Signal the calling operation
            if (caller->hasResult) {
                auto retOp = reservation.front();
                for (auto it = retOp->getOperands()->begin(); it != retOp->getOperands()->end(); ++it) {
                    auto operand = *it;
                    auto callResultIt = caller->getResults()->begin();
                    callResultIt->setRegisterValue(operand.getOpRegister());
                    ++callResultIt;
                }
            }
            func->removeInstance();
            caller->commit();
        }
        returned = true;
        return;
    } else if (lockstepReady()) {
        // TODO: Look into for_each here
        for (auto queue_iter = reservation.begin(); queue_iter != reservation.end();) {
            if (owner->debug())
                if (dbg) DPRINTFS(Runtime, owner,  "Debug Breakpoint");
            auto op = *queue_iter;
            if (dbg) DPRINTFS(Runtime, owner,  "\n\t\t %s \n\t\t %s%s%s%d%s \n",
                " |-[Reserve Queue]--------------",
                " | Operation: ", op->getOpName(),
                " | UID[", (op)->getUID(), "]"
                );
            if ((op)->isReturn() == false) {
                if ((op)->isTerminator() && reservation.size() >= scheduling_threshold) {
                    ++queue_iter;
                } else if (((op)->ready()) && !uidActive((op)->getUID())) {
                    if ((op)->isLoad()) {
                        // RAW protection to ensure a writeback finishes before reading that location
                        if (op->isLoadingInternal()) {
                            launchRead(op);
                            if (dbg) DPRINTFS(Runtime, owner,  "\t\t  |-Erase From Queue: %s - UID[%i]\n", op->getOpName(), op->getUID());
                            queue_iter = reservation.erase(queue_iter);
                            hw_cycle_stats.loadInternal++;
                        } else if (!writeActive(op->getPtrOperandValue(0))) {
                            launchRead(op);
                            if (dbg) DPRINTFS(Runtime, owner,  "\t\t  |-Erase From Queue: %s - UID[%i]\n", op->getOpName(), op->getUID());
                            queue_iter = reservation.erase(queue_iter);
                            hw_cycle_stats.loadAcitve++;
                        } else {
                            auto activeWrite = getActiveWrite(op->getPtrOperandValue(0));
                            op->addRuntimeDependency(activeWrite);
                            activeWrite->addRuntimeUser(op);
                            ++queue_iter;
                            hw_cycle_stats.loadRawStall++;
                        }
                    } else if ((op)->isStore()) {
                        // WAR Protection to insure reading finishes before a write
                        // if (!readActive(op->getPtrOperandValue(1))) {
                        launchWrite(op);
                        if (dbg) DPRINTFS(Runtime, owner,  "\t\t  |-Erase From Queue: %s - UID[%i]\n", op->getOpName(), op->getUID());
                        queue_iter = reservation.erase(queue_iter);
                        hw_cycle_stats.storeActive++;
                        // } else {
                        //     auto activeRead = getActiveRead(op->getPtrOperandValue(1));
                        //     op->addRuntimeDependency(activeRead);
                        //     activeRead->addRuntimeUser(op);
                        //     ++queue_iter;c
                        // }
                    } else if ((op)->isLatchingBrExiting() && ((reservation.size() > 1) || !queuesClear())) {
                        ++queue_iter;
                    } else if ((op)->isRegionBrOp()) {
                        if (auto scfForOp = std::dynamic_pointer_cast<MULA::scf::ForOp>(op)) {
                            // launch sets the lower bound to induction variable,
                            // and sets the iteration arguments to initial arguments.
                            scfForOp->launch();
                            // default: enter the for region.
                            // return condition is judged when executing scf.yield
                            // the dependency between the definition of induction variable, iteration arguments
                            // and the use of them in region should be resolved.
                            // the dependency between the final result and the use of it in following op
                            // should not be resolved
                            // enter an op with region body is similar to call another function
                            auto nextRegion = scfForOp->getRegion();
                            if (dbg) DPRINTFS(RuntimeCompute, owner, "\t\t Branching to region %s from region %s\n",
                                nextRegion->getIRStub(), previousRegion->getIRStub());
                            }
                        if (auto scfIfOp = std::dynamic_pointer_cast<MULA::scf::IfOp>(op)) {

                        }
                    } else if ((op)->isTerminator()) {
                        (op)->launch();
                        auto nextRegion = op->getTarget();
                        if (dbg) DPRINTFS(RuntimeCompute, owner, "\t\t Branching to %s from %s\n",
                            nextBB->getIRStub(), previousBlock->getIRStub());
                        scheduleRegion(nextRegion);
                        if (dbg) DPRINTFS(Runtime, owner,  "\t\t  | Branch Scheduled: %s - UID[%i]\n", mlir::Operation::getOpcodeName((op)->getOpode()), (op)->getUID());
                        (op)->commit();
                        if (dbg) DPRINTFS(Runtime, owner,  "\t\t  |-Erase From Queue: %s - UID[%i]\n", mlir::Operation::getOpcodeName((*queue_iter)->getOpode()), (*queue_iter)->getUID());
                        queue_iter = reservation.erase(queue_iter);
                    } else if ((*queue_iter)->isCall()) {
                        auto callInst = std::dynamic_pointer_cast<MULA::func::CallOp>(op);
                        assert(callInst);
                        auto calleeValue = callInst->getCalleeValue();
                        auto callee = std::dynamic_pointer_cast<MULA::func::FuncOp>(calleeValue);
                        assert(callee);
                        if (callee->canLaunch()) {
                            owner->launchFunction(callee, callInst);
                            computeQueue.insert({(op)->getUID(), op});
                            if (dbg) DPRINTFS(Runtime, owner,  "\t\t  |-Erase From Queue: %s - UID[%i]\n", mlir::Operation::getOpcodeName((*queue_iter)->getOpode()), (*queue_iter)->getUID());
                            queue_iter = reservation.erase(queue_iter);
                        } else {
                            ++queue_iter;
                        }
                    } else {
                        auto computeStart = std::chrono::high_resolution_clock::now();
                        if (!(op)->launch()) {
                            if (dbg) DPRINTFS(Runtime, owner,  "\t\t  | Added to Compute Queue: %s - UID[%i]\n", mlir::Operation::getOpcodeName((op)->getOpode()), (op)->getUID());
                            computeQueue.insert({(op)->getUID(), op});
                            hw_cycle_stats.compLaunched++;
                        }
                        auto computeStop = std::chrono::high_resolution_clock::now();
                        owner->addComputeTime(computeStop-computeStart);
                        if (dbg) DPRINTFS(Runtime, owner,  "\t\t  |-Erase From Queue: %s - UID[%i]\n", mlir::Operation::getOpcodeName((*queue_iter)->getOpode()), (*queue_iter)->getUID());
                        queue_iter = reservation.erase(queue_iter);
                        hw_cycle_stats.compActive++;
                    }
                } else {
                    ++queue_iter;
                }
            } else {
                ++queue_iter;
            }
        }
    }

    if (owner->hw->hw_statistics->use_cycle_tracking()) {
        auto hwStart = std::chrono::high_resolution_clock::now();
        for (auto fu : hw->functional_units->functional_unit_list) {
            std::cout << fu->get_alias() << " - " << fu->get_in_use() << "\n";
        }



        owner->hw->hw_statistics->updateHWStatsCycleEnd(owner->cycle);
        auto hwStop = std::chrono::high_resolution_clock::now();
        owner->addHWTime(hwStop-hwStart);
    }
    auto queueStop = std::chrono::high_resolution_clock::now();
    owner->addQueueTime(queueStop-queueStart);
}



/*********************************************************************************************
 CN Scheduling

 As CNs are scheduled they are added to an in-flight queue depending on operation type.
 Loads and Stores are maintained in separate queues, and are committed by the comm_interface.
 Branch and phi opructions evaluate and commit immediately. All other CN types are added to
 an in-flight compute queue.

 Each tick we must first check our in-flight compute queue. Each node should have its cycle
 count incremented, and should commit if max cycle is reached.

 New CNs are added to the reservation table whenever a new BB is encountered. This may occur
 during device init, or when a br op commits. For each CN in a BB we reset the CN, evaluate
 if it is a phi or uncond br, and add it to our reservation table otherwise.
*********************************************************************************************/
void
MLIRInterface::tick()
{
    auto tickStart = std::chrono::high_resolution_clock::now();

    if (dbg) DPRINTF(MLIRInterface, "\n%s\n%s %d\n%s\n",
        "********************************************************************************",
        "   Cycle", cycle,
        "********************************************************************************");
    cycle++;

    // Process Queues in Active Functions
    for (auto func_iter = activeFuncs.begin(); func_iter != activeFuncs.end();) {
        func_iter->processQueues();
        if (!(func_iter->hasReturned())) {
            func_iter++;
        } else {
            func_iter = activeFuncs.erase(func_iter);
        }
    }
    if (activeFuncs.empty()) {
        // We are finished executing all functions. Signal completion to the CommInterface
        running = false;
        finalize();
        return;
    }
    //////////////// Schedule Next Cycle ////////////////////////
    if (running && !tickEvent.scheduled()) {
        schedule(tickEvent, curTick() + clock_period);// * process_delay);
    }
    auto tickStop = std::chrono::high_resolution_clock::now();
    simTime = simTime + (tickStop - tickStart);
}


/*********************************************************************************************
- findDynamicDeps(std::list<std::shared_ptr<MULA::Operations>, std::shared_ptr<MULA::Operation>)
- only parse queue once for each opruction until all dependencies are found
- include self in dependency list
- Register dynamicUser/dynamicDependencies std::deque<std::shared_ptr<SALAM::Instructon> >
*********************************************************************************************/
void // Add third argument, previous BB
MLIRInterface::ActiveFunc::findDynamicDeps(std::shared_ptr<MULA::Operation> op)
{
    // if (DTRACE(Trace)) if (dbg) DPRINTFS(Runtime, owner,  "Trace: %s \n", __PRETTY_FUNCTION__);
    if (dbg) DPRINTFS(Runtime, owner,  "Linking Dynamic Dependencies [%s]\n", mlir::Operation::getOpcodeName(op->getOpode()));
    // The list of UIDs for any dependencies we want to find
    //std::deque<uint64_t> dep_uids = op->runtimeInitialize();
    std::vector<uint64_t> dep_uids = op->runtimeInitialize();

    // assert(op->getDependencyCount() == 0);

    // // An opruction is a runtime dependency for itself since multiple
    // // opances of the same opruction shouldn't execute simultaneously
    // // dep_uids.push_back(op->getUID());

    // Find dependencies currently in queues

    // Reverse search the reservation queue because we want to link only the last opance of each dep
    auto queue_iter = reservation.rbegin();
    while ((queue_iter != reservation.rend()) && !dep_uids.empty()) {
        auto queued_op = *queue_iter;
        // Look at each opruction in runtime queue once
        for (auto dep_it = dep_uids.begin(); dep_it != dep_uids.end();) {
            // Check if any of the opruction to be scheduled dependencies match the current opruction from queue
            if (queued_op->getUID() == *dep_it) {
                // If dependency found, create two way link
                op->addRuntimeDependency(queued_op);
                queued_op->addRuntimeUser(op);
                dep_it = dep_uids.erase(dep_it);
            } else {
                dep_it++;
            }
        }
        queue_iter++;
    }

    // The other queues do not need to be reverse-searched since only 1 opance of any opruction can exist in them
    // Check the compute queue
    for (auto dep_it = dep_uids.begin(); dep_it != dep_uids.end();) {
        auto queue_iter = computeQueue.find(*dep_it);
        if (queue_iter != computeQueue.end()) {
            auto queued_op = queue_iter->second;
            op->addRuntimeDependency(queued_op);
            queued_op->addRuntimeUser(op);
            dep_it = dep_uids.erase(dep_it);
        } else {
            dep_it++;
        }
    }
    // Check the memory read queue
    for (auto dep_it = dep_uids.begin(); dep_it != dep_uids.end();) {
        auto queue_iter = readQueue.find(*dep_it);
        if (queue_iter != readQueue.end()) {
            auto queued_op = queue_iter->second;
            op->addRuntimeDependency(queued_op);
            queued_op->addRuntimeUser(op);
            dep_it = dep_uids.erase(dep_it);
        } else {
            dep_it++;
        }
    }

    // if (!dep_uids.empty()) {
    //     // Check the memory read queue
    //     // for (auto queued_read : readQueue) {
    //     for (auto rq_it = readQueue.begin(); rq_it != readQueue.end(); rq_it++) {
    //         auto queued_read = *rq_it;
    //         auto queued_op = queued_read.second;
    //         // Look at each opruction in runtime queue once
    //         for (auto dep_it = dep_uids.begin(); dep_it != dep_uids.end();) {
    //             // Check if any of the opruction to be scheduled dependencies match the current opruction from queue
    //             if (queued_op->getUID() == *dep_it) {
    //                 // If dependency found, create two way link
    //                 op->addRuntimeDependency(queued_op);
    //                 queued_op->addRuntimeUser(op);
    //                 dep_it = dep_uids.erase(dep_it);
    //             } else {
    //                 dep_it++;
    //             }
    //         }
    //         if (dep_uids.empty()) break;
    //     }
    // }
    // Check the memory write queue
    for (auto dep_it = dep_uids.begin(); dep_it != dep_uids.end();) {
        auto queue_iter = writeQueue.find(*dep_it);
        if (queue_iter != writeQueue.end()) {
            auto queued_op = queue_iter->second;
            op->addRuntimeDependency(queued_op);
            queued_op->addRuntimeUser(op);
            dep_it = dep_uids.erase(dep_it);
        } else {
            dep_it++;
        }
    }

    // if (!dep_uids.empty()) {
    //     // Check the memory write queue
    //     // for (auto queued_write : writeQueue) {
    //     for (auto wq_it = writeQueue.begin(); wq_it != writeQueue.end(); wq_it++) {
    //         auto queued_write = *wq_it;
    //         auto queued_op = queued_write.second;
    //         // Look at each opruction in runtime queue once
    //         for (auto dep_it = dep_uids.begin(); dep_it != dep_uids.end();) {
    //             // Check if any of the opruction to be scheduled dependencies match the current opruction from queue
    //             if (queued_op->getUID() == *dep_it) {
    //                 // If dependency found, create two way link
    //                 op->addRuntimeDependency(queued_op);
    //                 queued_op->addRuntimeUser(op);
    //                 dep_it = dep_uids.erase(dep_it);
    //             } else {
    //                 dep_it++;
    //             }
    //         }
    //         if (dep_uids.empty()) break;
    //     }
    // }

    // Fetch values for resolved dependencies, static elements, and immediate values
    if (!dep_uids.empty()) {
        for (auto resolved : dep_uids) {
            // If this dependency exists, then lock value into operand
            op->setOperandValue(resolved);
        }
    }
}

void
MLIRInterface::dumpModule(mlir::ModuleOp *M) {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    M->print(llvm::outs(), nullptr);
    for (const llvm::Function &F : *M) {
        for (const llvm::BasicBlock &BB : F) {
            for (const mlir::Operation &I : BB) {
                I.print(llvm::outs());
            }
        }
    }
}



void
MLIRInterface::constructStaticGraph() {
/*********************************************************************************************
 Constructing the Static CDFG

 Parses LLVM file and creates the CDFG passed to our runtime simulation engine.
*********************************************************************************************/
    auto parseStart = std::chrono::high_resolution_clock::now();

    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    if (dbg) DPRINTF(MLIRInterface, "Constructing Static Dependency Graph\n");

    llvm::StringRef file = filename;
    std::unique_ptr<llvm::LLVMContext> context(new llvm::LLVMContext());
    std::unique_ptr<llvm::SMDiagnostic> error(new llvm::SMDiagnostic());
    std::unique_ptr<mlir::ModuleOp> m;
    std::unique_ptr<llvm::DominatorTree> dt(new llvm::DominatorTree());
    std::unique_ptr<llvm::LoopInfoBase<llvm::BasicBlock, llvm::Loop>> loopInfo(new llvm::LoopInfoBase<llvm::BasicBlock, llvm::Loop>());

    m = llvm::parseIRFile(file, *error, *context);
    if(!m) panic("Error reading Module");

    // Construct the LLVM::Value to MULA::Value map
    uint64_t valueID = 0;
    SALAM::irvmap vmap;
    // Generate MULA::Values for llvm::GlobalVariables
    DPRINTF(LLVMParse, "Instantiate SALAM::GlobalConstants\n");
    for (auto glob_iter = m->global_begin(); glob_iter != m->global_end(); glob_iter++) {
        llvm::GlobalVariable &glb = *glob_iter;
        std::shared_ptr<SALAM::GlobalConstant> sglb = std::make_shared<SALAM::GlobalConstant>(valueID, this, debug());
        values.push_back(sglb);
        vmap.insert(SALAM::irvmaptype(&glb, sglb));
        valueID++;
    }
    // Generate MULA::func::FuncOps
    DPRINTF(LLVMParse, "Instantiate MULA::func::FuncOps\n");
    for (auto func_iter = m->begin(); func_iter != m->end(); func_iter++) {
        llvm::Function &func = *func_iter;
        std::shared_ptr<MULA::func::FuncOp> sfunc = std::make_shared<MULA::func::FuncOp>(valueID, this, debug());
        values.push_back(sfunc);
        functions.push_back(sfunc);
        vmap.insert(SALAM::irvmaptype(&func, sfunc));
        valueID++;
        // Generate args for SALAM:Functions
        DPRINTF(LLVMParse, "Instantiate MULA::func::FuncOps::Arguments\n");
        for (auto arg_iter = func.arg_begin(); arg_iter != func.arg_end(); arg_iter++) {
            llvm::Argument &arg = *arg_iter;
            std::shared_ptr<SALAM::Argument> sarg = std::make_shared<SALAM::Argument>(valueID, this, debug());
            values.push_back(sarg);
            vmap.insert(SALAM::irvmaptype(&arg, sarg));
            valueID++;
        }
        // Generate MULA::Blocks
        DPRINTF(LLVMParse, "Instantiate MULA::func::FuncOps::BasicBlocks\n");
        for (auto block_iter = func.begin(); block_iter != func.end(); block_iter++) {
            llvm::BasicBlock &block = *block_iter;
            std::shared_ptr<MULA::Block> sblock = std::make_shared<MULA::Block>(valueID, this, debug());
            values.push_back(sblock);
            vmap.insert(SALAM::irvmaptype(&block, sblock));
            valueID++;
            //Generate MULA::Operations
            DPRINTF(LLVMParse, "Instantiate MULA::func::FuncOps::BasicBlocks::Instructions\n");
            for (auto op_iter = block.begin(); op_iter != block.end(); op_iter++) {
                mlir::Operation &op = *op_iter;
                std::shared_ptr<MULA::Operation> sop = createOp(&op, valueID);
                values.push_back(sop);
                vmap.insert(SALAM::irvmaptype(&op, sop));
                valueID++;
            }
        }
    }

    // Use value map to initialize MULA::Values
    DPRINTF(LLVMParse, "Initialize SALAM::GlobalConstants\n");
    for (auto glob_iter = m->global_begin(); glob_iter != m->global_end(); glob_iter++) {
        llvm::GlobalVariable &glb = *glob_iter;
        std::shared_ptr<MULA::Value> glbval = vmap.find(&glb)->second;
        assert(glbval);
        std::shared_ptr<SALAM::GlobalConstant> sglb = std::dynamic_pointer_cast<SALAM::GlobalConstant>(glbval);
        assert(sglb);
        sglb->initialize(&glb, &vmap, &values);
    }
    // Functions will initialize BasicBlocks, which will initialize Instructions
    DPRINTF(LLVMParse, "Initialize MULA::func::FuncOps\n");
    for (auto func_iter = m->begin(); func_iter != m->end(); func_iter++) {
        llvm::Function &func = *func_iter;
        std::shared_ptr<MULA::Value> funcval = vmap.find(&func)->second;
        assert(funcval);
        std::shared_ptr<MULA::func::FuncOp> sfunc = std::dynamic_pointer_cast<MULA::func::FuncOp>(funcval);
        assert(sfunc);
        sfunc->initialize(&func, &vmap, &values, topName);
    }
    if (functions.size() == 1) functions.front()->setTop(true);

    // Detect Loop Latches
    for (auto func_iter = m->begin(); func_iter != m->end(); func_iter++) {
        llvm::Function &func = *func_iter;
        dt->recalculate(func);
        loopInfo->releaseMemory();
        loopInfo->analyze(*dt);
        for (auto loop=loopInfo->begin(); loop!=loopInfo->end(); ++loop) {
            if (llvm::BasicBlock *exBB = (*loop)->getExitingBlock()) {
                auto latchingBr = exBB->getTerminator();
                auto mapIt = vmap.find(latchingBr);
                if (mapIt != vmap.end()) {
                    auto salamValue = mapIt->second;
                    if (std::shared_ptr<SALAM::Br> sBr =
                        std::dynamic_pointer_cast<SALAM::Br>(salamValue)) {
                            sBr->setLatching(true);
                        }
                }
            }
        }
    }
    auto parseStop = std::chrono::high_resolution_clock::now();
    setupTime = parseStop - parseStart;
}

void
MLIRInterface::launchRead(MemoryRequest * memReq, ActiveFunc * func) {
    globalReadQueue.insert({memReq, func});
    comm->enqueueRead(memReq);
}

void
MLIRInterface::ActiveFunc::launchRead(std::shared_ptr<MULA::Operation> readOp) {
    auto rdOp = std::dynamic_pointer_cast<MULA::memref::LoadOp>(readOp);
    if (rdOp->isLoadingInternal()) {
        rdOp->loadInternal();
    } else {
        auto memReq = (readOp)->createMemoryRequest();
        auto rd_uid = readOp->getUID();
        readQueue.insert({rd_uid, (readOp)});
        readQueueMap.insert({memReq, rd_uid});
        owner->launchRead(memReq, this);
    }
}

void
MLIRInterface::launchWrite(MemoryRequest * memReq, ActiveFunc * func) {
    globalWriteQueue.insert({memReq, func});
    comm->enqueueWrite(memReq);
}

void
MLIRInterface::ActiveFunc::launchWrite(std::shared_ptr<MULA::Operation> writeOp) {
    auto memReq = (writeOp)->createMemoryRequest();
    trackWrite(memReq->getAddress(), writeOp);
    auto wr_uid = writeOp->getUID();
    writeQueue.insert({wr_uid, (writeOp)});
    writeQueueMap.insert({memReq, wr_uid});
    owner->launchWrite(memReq, this);
}

void
MLIRInterface::readCommit(MemoryRequest * req) {
/*********************************************************************************************
 Commit Memory Read Request
*********************************************************************************************/
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    auto queue_iter = globalReadQueue.find(req);
    if (queue_iter != globalReadQueue.end()) {
        queue_iter->second->readCommit(req);
        DPRINTF(Runtime, "Global Read Commit\n");
        // delete queue_iter->first; // The CommInterface will ultimately delete this memory request
        globalReadQueue.erase(queue_iter);
    } else {
        panic("Could not find memory request in global read queue!");
    }
}

void
MLIRInterface::ActiveFunc::readCommit(MemoryRequest * req) {
/*********************************************************************************************
 Commit Memory Read Request
*********************************************************************************************/
    // if (DTRACE(Trace)) if (dbg) DPRINTFS(Runtime, owner,  "Trace: %s \n", __PRETTY_FUNCTION__);
    auto map_iter = readQueueMap.find(req);
    if (map_iter != readQueueMap.end()) {
        auto queue_iter = readQueue.find(map_iter->second);
        if (queue_iter != readQueue.end()) {
            auto load_op = queue_iter->second;
            uint8_t * readBuff = req->getBuffer();
            load_op->setRegisterValue(readBuff);
            load_op->compute();
            if (dbg) DPRINTFS(Runtime, owner,  "Local Read Commit\n");
            load_op->commit();
            readQueue.erase(queue_iter);
            readQueueMap.erase(map_iter);
        } else {
            panic("Could not find memory request in read queue for function %u!", func->getUID());
        }
    } else {
        panic("Could not find memory request in read queue for function %u!", func->getUID());
    }
}

void
MLIRInterface::writeCommit(MemoryRequest * req) {
/*********************************************************************************************
 Commit Memory Write Request
*********************************************************************************************/
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    auto queue_iter = globalWriteQueue.find(req);
    if (queue_iter != globalWriteQueue.end()) {
        queue_iter->second->writeCommit(req);
        // delete queue_iter->first; // The CommInterface will ultimately delete this memory request
        globalWriteQueue.erase(queue_iter);
    } else {
        panic("Could not find memory request in global write queue!");
    }
}

void
MLIRInterface::ActiveFunc::writeCommit(MemoryRequest * req) {
/*********************************************************************************************
 Commit Memory Write Request
*********************************************************************************************/
    // if (DTRACE(Trace)) if (dbg) DPRINTFS(Runtime, owner,  "Trace: %s \n", __PRETTY_FUNCTION__);
    auto map_iter = writeQueueMap.find(req);
    if (map_iter != writeQueueMap.end()) {
        auto queue_iter = writeQueue.find(map_iter->second);
        if (queue_iter != writeQueue.end()) {
            queue_iter->second->commit();
            Addr addressWritten = map_iter->first->getAddress();
            untrackWrite(addressWritten);
            writeQueue.erase(queue_iter);
            writeQueueMap.erase(map_iter);
        } else {
            panic("Could not find memory request in write queue for function %u!", func->getUID());
        }
    } else {
        panic("Could not find memory request in write queue for function %u!", func->getUID());
    }
}

void
MLIRInterface::initialize() {
/*********************************************************************************************
 Initialize the Runtime Engine

 Calls function that constructs the basic block list, initializes the reservation table and
 read, write, and compute queues. Set all data collection variables to zero.
*********************************************************************************************/
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    if (dbg) DPRINTF(MLIRInterface, "Initializing LLVM Runtime Engine!\n");
    setupTime = std::chrono::seconds(0);
    simTime = std::chrono::seconds(0);
    schedulingTime = std::chrono::seconds(0);
    queueProcessTime = std::chrono::seconds(0);
    computeTime = std::chrono::seconds(0);
    hwTime = std::chrono::seconds(0);
    constructStaticGraph();
    timeStart = std::chrono::high_resolution_clock::now();
    if (dbg) DPRINTF(MLIRInterface, "================================================================\n");
    launchTopFunc();

    // panic("Kill Simulation");
    //if (debug()) DPRINTF(MLIRInterface, "Initializing Reservation Table!\n");
    //if (debug()) DPRINTF(MLIRInterface, "Initializing readQueue Queue!\n");
    //if (debug()) DPRINTF(MLIRInterface, "Initializing writeQueue Queue!\n");
    //if (debug()) DPRINTF(MLIRInterface, "Initializing computeQueue List!\n");
    if (dbg) DPRINTF(MLIRInterface, "\n%s\n%s\n%s\n",
           "*******************************************************************************",
           "*                 Begin Runtime Simulation Computation Engine                 *",
           "*******************************************************************************");
    running = true;
    cycle = 0;
    stalls = 0;
    tick();
}

void
MLIRInterface::debug(uint64_t flags) {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    // Dump
    for (auto func_iter = functions.begin(); func_iter != functions.end(); func_iter++) {
        // Function Level
        // (*func_iter)->dump();
        for (auto block_iter = (*func_iter)->getBBList()->begin(); block_iter != (*func_iter)->getBBList()->end(); block_iter++) {
            // Basic Block Level
            (*block_iter)->dump();
            for (auto op_iter = (*block_iter)->Operations()->begin(); op_iter != (*block_iter)->Operations()->end(); op_iter++) {
                // Instruction Level
                (*op_iter)->dump();
            }
        }
    }
    // Dump
    // SALAM::Operand test;
    // test.setOp()
}

void
MLIRInterface::startup() {
/*********************************************************************************************
 Initialize communications between gem5 interface and simulator
*********************************************************************************************/
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    comm->registerCompUnit(this);
}

// MLIRInterface*
// MLIRInterfaceParams::create() {
// /*********************************************************************************************
//  Create new interface between the llvm IR and our simulation engine
// *********************************************************************************************/
//     // if (DTRACE(Trace)) if (dbg) DPRINTFS(Runtime, owner,  "Trace: %s \n", __PRETTY_FUNCTION__);
//     return new MLIRInterface(this);
// }

void
MLIRInterface::finalize() {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    // Simulation Times
    simStop = std::chrono::high_resolution_clock::now();
    simTotal = simStop - timeStart;
    printResults();
    functions.clear();
    values.clear();
    comm->finish();
}

void
MLIRInterface::printResults() {


    std::map<uint64_t, uint64_t> totals_reads;
    std::map<uint64_t, uint64_t> totals_writes;

    std::cout << "********************************************************************************" << std::endl;
    std::cout << name() << std::endl;

    for (auto it : values) {
        if (it->isInstruction()) {
            //std::cout << "Instruction: " << mlir::Operation::getOpcodeName(it->getOpode()) << "\n";
            if (it->getReg()) {
                totals_reads[it->getOpode()] += it->getReg()->getReads();
                totals_writes[it->getOpode()] += it->getReg()->getWrites();
            }
        }
    }

    /*
    for(const auto& count : hw->opcodes->usage) {
        if (count.second) std::cout << "\nInstruction: " << mlir::Operation::getOpcodeName(count.first) << "\n\tIR Count: " << count.second << "\n\tTotal Reads: " << totals_reads[count.first] << "\n\tTotal Writes: " << totals_writes[count.first];
    }
    std::cout << "\n";
    */

   //hw->hw_statistics->print();


    double adder_area = (hw->opcodes->get_usage(13) + hw->opcodes->get_usage(20) + hw->opcodes->get_usage(15)) *  1.794430e+02;
    double adder_reads = (totals_reads[13] + totals_reads[15]);
    double adder_writes = (totals_writes[13] + totals_writes[15]);
    double adder_power_static = adder_reads*2.380803e-03;
    double adder_power_dynamic =  adder_writes*(8.115300e-03+6.162853e-03);

    double bitwise_area = (hw->opcodes->get_usage(29) + hw->opcodes->get_usage(30) + hw->opcodes->get_usage(25) + hw->opcodes->get_usage(26) + hw->opcodes->get_usage(27) + hw->opcodes->get_usage(28)) * 5.036996e+01;
    double bitwise_reads = (totals_reads[25] + totals_reads[26] + totals_reads[27] + totals_reads[28] + totals_reads[29] + totals_reads[30]);
    double bitwise_writes = (totals_writes[25] + totals_writes[26] + totals_writes[27] + totals_writes[28] + totals_writes[29] + totals_writes[30]);
    double bitwise_power_static = bitwise_reads*6.111633e-04;
    double bitwise_power_dynamic = bitwise_writes*(1.680942e-03+1.322420e-03);

    double multiplier_area = (hw->opcodes->get_usage(17) + hw->opcodes->get_usage(19) + hw->opcodes->get_usage(20))*4.595000e+03;
    double multiplier_reads = totals_reads[17] + totals_reads[19] + totals_reads[20];
    double multiplier_writes = totals_writes[17] + totals_writes[19] + totals_writes[20];
    double multiplier_power_static = multiplier_reads*4.817683e-02;
    double multiplier_power_dynamic = multiplier_writes*(5.725752e-01+8.662890e-01);

    double reg_area = hw->opcodes->get_usage(34)*32*5.981433e+00;
    double reg_reads = totals_reads[34]*32;
    double reg_writes = totals_writes[34]*32;
    double register_power_static = reg_reads*7.395312e-05;
    double register_power_dynamic = reg_writes*(1.322600e-03+1.792126e-04);

    double total_area = adder_area + bitwise_area + multiplier_area + reg_area;
    double total_power_static = adder_power_static + bitwise_power_static + multiplier_power_static + register_power_static;
    double total_power_dynamic = adder_power_dynamic + bitwise_power_dynamic + multiplier_power_dynamic + register_power_dynamic;

    std::cout << "Total Area: " << total_area;
    std::cout << "\nTotal Power Static: " << total_power_static << "\n";
    std::cout << "\nTotal Power Dynamic: " << total_power_dynamic << "\n";

    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    Tick cycle_time = clock_period/1000;

    auto hwTimingMS = std::chrono::duration_cast<std::chrono::milliseconds>(hwTime);
    auto hwHours = std::chrono::duration_cast<std::chrono::hours>(hwTimingMS);
    hwTimingMS -= std::chrono::duration_cast<std::chrono::seconds>(hwHours);
    auto hwMins = std::chrono::duration_cast<std::chrono::minutes>(hwTimingMS);
    hwTimingMS -= std::chrono::duration_cast<std::chrono::seconds>(hwMins);
    auto hwSecs = std::chrono::duration_cast<std::chrono::seconds>(hwTimingMS);
    hwTimingMS -= std::chrono::duration_cast<std::chrono::seconds>(hwSecs);

    //auto setupMS = std::chrono::duration_cast<std::chrono::milliseconds>(setupTime);

    //auto setupHours = std::chrono::duration_cast<std::chrono::hours>(setupMS);
    //setupMS -= std::chrono::duration_cast<std::chrono::seconds>(setupHours);
    //auto setupMins = std::chrono::duration_cast<std::chrono::minutes>(setupMS);
    //setupMS -= std::chrono::duration_cast<std::chrono::seconds>(setupMins);
    //auto setupSecs = std::chrono::duration_cast<std::chrono::seconds>(setupMS);
    //setupMS -= std::chrono::duration_cast<std::chrono::seconds>(setupSecs);

    auto setupUS = std::chrono::duration_cast<std::chrono::microseconds>(setupTime);
    auto setupHours = std::chrono::duration_cast<std::chrono::hours>(setupUS);
    setupUS -= std::chrono::duration_cast<std::chrono::seconds>(setupHours);
    auto setupMins = std::chrono::duration_cast<std::chrono::minutes>(setupUS);
    setupUS -= std::chrono::duration_cast<std::chrono::seconds>(setupMins);
    auto setupSecs = std::chrono::duration_cast<std::chrono::seconds>(setupUS);
    setupUS -= std::chrono::duration_cast<std::chrono::seconds>(setupSecs);

    auto setupMS = std::chrono::duration_cast<std::chrono::milliseconds>(setupUS);

    setupUS -= std::chrono::duration_cast<std::chrono::milliseconds>(setupMS);

    auto totalMS = std::chrono::duration_cast<std::chrono::milliseconds>(simTotal);
    auto totalHours = std::chrono::duration_cast<std::chrono::hours>(totalMS);
    totalMS -= std::chrono::duration_cast<std::chrono::seconds>(totalHours);
    auto totalMins = std::chrono::duration_cast<std::chrono::minutes>(totalMS);
    totalMS -= std::chrono::duration_cast<std::chrono::seconds>(totalMins);
    auto totalSecs = std::chrono::duration_cast<std::chrono::seconds>(totalMS);
    totalMS -= std::chrono::duration_cast<std::chrono::seconds>(totalSecs);

    auto simMS = std::chrono::duration_cast<std::chrono::milliseconds>(simTime);
    auto simHours = std::chrono::duration_cast<std::chrono::hours>(simMS);
    simMS -= std::chrono::duration_cast<std::chrono::seconds>(simHours);
    auto simMins = std::chrono::duration_cast<std::chrono::minutes>(simMS);
    simMS -= std::chrono::duration_cast<std::chrono::seconds>(simMins);
    auto simSecs = std::chrono::duration_cast<std::chrono::seconds>(simMS);
    simMS -= std::chrono::duration_cast<std::chrono::seconds>(simSecs);

    auto queueMS = std::chrono::duration_cast<std::chrono::milliseconds>(queueProcessTime);
    auto queueHours = std::chrono::duration_cast<std::chrono::hours>(queueMS);
    queueMS -= std::chrono::duration_cast<std::chrono::seconds>(queueHours);
    auto queueMins = std::chrono::duration_cast<std::chrono::minutes>(queueMS);
    queueMS -= std::chrono::duration_cast<std::chrono::seconds>(queueMins);
    auto queueSecs = std::chrono::duration_cast<std::chrono::seconds>(queueMS);
    queueMS -= std::chrono::duration_cast<std::chrono::seconds>(queueSecs);

    auto schedMS = std::chrono::duration_cast<std::chrono::milliseconds>(schedulingTime);
    auto schedHours = std::chrono::duration_cast<std::chrono::hours>(schedMS);
    schedMS -= std::chrono::duration_cast<std::chrono::seconds>(schedHours);
    auto schedMins = std::chrono::duration_cast<std::chrono::minutes>(schedMS);
    schedMS -= std::chrono::duration_cast<std::chrono::seconds>(schedMins);
    auto schedSecs = std::chrono::duration_cast<std::chrono::seconds>(schedMS);
    schedMS -= std::chrono::duration_cast<std::chrono::seconds>(schedSecs);

    auto computeMS = std::chrono::duration_cast<std::chrono::milliseconds>(computeTime);
    auto computeHours = std::chrono::duration_cast<std::chrono::hours>(computeMS);
    computeMS -= std::chrono::duration_cast<std::chrono::seconds>(computeHours);
    auto computeMins = std::chrono::duration_cast<std::chrono::minutes>(computeMS);
    computeMS -= std::chrono::duration_cast<std::chrono::seconds>(computeMins);
    auto computeSecs = std::chrono::duration_cast<std::chrono::seconds>(computeMS);
    computeMS -= std::chrono::duration_cast<std::chrono::seconds>(computeSecs);

/*********************************************************************************************
 Prints usage statistics of how many times each opruction was accessed during runtime
*********************************************************************************************/

    std::cout << "   ========= Performance Analysis =============" << std::endl;
    std::cout << "   Setup Time:                      " << setupHours.count() << "h " << setupMins.count() << "m " << setupSecs.count() << "s " << setupMS.count() << "ms " << setupUS.count() << "us" << std::endl;
    std::cout << "   Simulation Time (Total):         " << totalHours.count() << "h " << totalMins.count() << "m " << totalSecs.count() << "s " << totalMS.count() << "ms" << std::endl;
    std::cout << "   Simulation Time (Active):        " << simHours.count() << "h " << simMins.count() << "m " << simSecs.count() << "s " << simMS.count() << "ms" << std::endl;
    std::cout << "        Queue Processing Time:      " << queueHours.count() << "h " << queueMins.count() << "m " << queueSecs.count() << "s " << queueMS.count() << "ms" << std::endl;
    std::cout << "             Scheduling Time:       " << schedHours.count() << "h " << schedMins.count() << "m " << schedSecs.count() << "s " << schedMS.count() << "ms" << std::endl;
    std::cout << "             Computation Time:      " << computeHours.count() << "h " << computeMins.count() << "m " << computeSecs.count() << "s " << computeMS.count() << "ms" << std::endl;
    std::cout << "   System Clock:                    " << 1.0/(cycle_time) << "GHz" << std::endl;
    std::cout << "   Runtime:                         " << cycle << " cycles" << std::endl;
    std::cout << "   Runtime:                         " << (cycle*cycle_time*(1e-3)) << " us" << std::endl;
    std::cout << "   Stalls:                          " << stalls << " cycles" << std::endl;
    std::cout << "   Executed Nodes:                  " << (cycle-stalls-1) << " cycles" << std::endl;
    std::cout << std::endl;
}

void
MLIRInterface::dumpQueues() {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    // std::cout << "*********************************************************\n"
    //           << "Compute Queue\n"
    //           << "*********************************************************\n";
    // for (auto compute : computeQueue) {
    //     std::cout << compute->_LLVMLine << std::endl;
    // }
    // std::cout << "*********************************************************\n"
    //           << "Read Queue\n"
    //           << "*********************************************************\n";
    // for (auto read : readQueue) {
    //     std::cout << read->_LLVMLine << std::endl;
    // }
    // std::cout << "*********************************************************\n"
    //           << "Write Queue\n"
    //           << "*********************************************************\n";
    // for (auto write : writeQueue) {
    //     std::cout << write->_LLVMLine << std::endl;
    // }
    // std::cout << "*********************************************************\n"
    //           << "Reservation Queue\n"
    //           << "*********************************************************\n";
    // for (auto reserved : reservation) {
    //     std::cout << reserved->_LLVMLine << std::endl;
    // }
    // std::cout << "*********************************************************\n"
    //           << "End of queue dump\n"
    //           << "*********************************************************\n";
}

void
MLIRInterface::launchFunc(std::shared_ptr<MULA::func::FuncOp> callee,
                          std::shared_ptr<MULA::Operation> caller) {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    // Add the callee to our list of active functions
    activeFuncs.push_back(ActiveFunc(this, callee, caller));
    activeFuncs.back().launch();
}

void
MLIRInterface::launchTopFunc() {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    for (auto it = functions.begin(); it != functions.end(); it++) {
        if ((*it)->isTop()) {
            // Launch the top level function
            launchFunc((*it), nullptr);
            return;
        }
    }
    // Fallback if no function was marked as the top-level
    panic("No function marked as top-level. Set the top_name parameter for your MLIRInterface to the name of the top-level function\n");
}

void MLIRInterface::ActiveFunc::launch() {
    // if (DTRACE(Trace)) if (dbg) DPRINTFS(Runtime, owner,  "Trace: %s \n", __PRETTY_FUNCTION__);
    if (dbg) DPRINTFS(MLIRInterface, owner, "Launching Function: %s\n", func->getIRStub());
    // func->value_dump();
    // Fetch the arguments
    std::vector<std::shared_ptr<MULA::Value>> funcArgs = *(func->getArguments());
    if (func->isTop()) {
        // We need to fetch argument values from the memory mapped registers
        if (dbg) DPRINTFS(MLIRInterface, owner, "Connecting CommInterface\n");
        CommInterface * comm = owner->getCommInterface();
        if (dbg) DPRINTFS(MLIRInterface, owner, "Connecting HWInterface\n");
        hw = owner->getHWInterface();

        unsigned argOffset = 0;
        for (auto arg : funcArgs) {
            uint64_t argSizeInBytes = arg->getSizeInBytes();
            uint64_t regValue = comm->getGlobalVar(argOffset, argSizeInBytes);
            arg->setRegisterValue(regValue);
            argOffset += argSizeInBytes;
        }
    } else {
        // We need to fetch argument values from the calling function
        //std::deque<SALAM::Operand> callerArgs = *caller->getOperands();
        std::vector<SALAM::Operand> callerArgs = *caller->getOperands();
        if (funcArgs.size() != callerArgs.size())
            panic("Function expects %d args. Got %d args.", funcArgs.size(), callerArgs.size());
        for (auto i = 0; i < callerArgs.size(); i++) {
            funcArgs.at(i)->setRegisterValue(callerArgs.at(i).getOpRegister());
        }
    }
    func->addInstance();
    // Schedule the first BB
    scheduleBlock(func->entry());
}

std::shared_ptr<MULA::Operation>
MLIRInterface::createOp(mlir::Operation * op, uint64_t id) {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    uint64_t OpCode = op->Instruction::getOpcode();
    // if (DTRACE(Trace)) DPRINTF(MLIRInterface, "Switch OpCode [%d]\n", OpCode);
    // HW
    hw->opcodes->update_usage(OpCode);

    uint64_t functional_unit = 0;
    for (auto hw_op : hw->op_config->op_list) {
        //std::cout << "\n\n\nTest 7 OpCode[" << OpCode << "] | Compare: ["<< hw_op->get_opcode_num() << "]\n\n\n";
        if(OpCode == hw_op->get_opcode_num()) {
            //std::cout << "\n\n\nTest 4\n\n\n";
            functional_unit = hw_op->get_functional_unit();
            for (auto hw_fu : hw->functional_units->functional_unit_list) {
                //std::cout << "\n\n\nTest 5\n\n\n";
                if(hw_fu->get_enum_value() == functional_unit) {
                    //std::cout << "\n\n\nTest 6\n\n\n";
                    hw_fu->inc_functional_unit_limit();
                    break;
                }
            }
            break;
        }
    }

    switch(OpCode) {
        case llvm::Instruction::Ret : return SALAM::createRetInst(id, this, debug(), OpCode, hw->cycle_counts->ret_op, functional_unit); break;
        case llvm::Instruction::Br: return SALAM::createBrInst(id, this, debug(), OpCode, hw->cycle_counts->br_op, functional_unit); break;
        case llvm::Instruction::Switch: return SALAM::createSwitchInst(id, this, debug(), OpCode, hw->cycle_counts->switch_op, functional_unit); break;
        case llvm::Instruction::Add: return SALAM::createAddInst(id, this, debug(), OpCode, hw->cycle_counts->add_op, functional_unit); break;
        case llvm::Instruction::FAdd: return SALAM::createFAddInst(id, this, debug(), OpCode, hw->cycle_counts->fadd_op, functional_unit); break;
        case llvm::Instruction::Sub: return SALAM::createSubInst(id, this, debug(), OpCode, hw->cycle_counts->sub_op, functional_unit); break;
        case llvm::Instruction::FSub: return SALAM::createFSubInst(id, this, debug(), OpCode, hw->cycle_counts->fsub_op, functional_unit); break;
        case llvm::Instruction::Mul: return SALAM::createMulInst(id, this, debug(), OpCode, hw->cycle_counts->mul_op, functional_unit); break;
        case llvm::Instruction::FMul: return SALAM::createFMulInst(id, this, debug(), OpCode, hw->cycle_counts->fmul_op, functional_unit); break;
        case llvm::Instruction::UDiv: return SALAM::createUDivInst(id, this, debug(), OpCode, hw->cycle_counts->udiv_op, functional_unit); break;
        case llvm::Instruction::SDiv: return SALAM::createSDivInst(id, this, debug(), OpCode, hw->cycle_counts->sdiv_op, functional_unit); break;
        case llvm::Instruction::FDiv: return SALAM::createFDivInst(id, this, debug(), OpCode, hw->cycle_counts->fdiv_op, functional_unit); break;
        case llvm::Instruction::URem: return SALAM::createURemInst(id, this, debug(), OpCode, hw->cycle_counts->urem_op, functional_unit); break;
        case llvm::Instruction::SRem: return SALAM::createSRemInst(id, this, debug(), OpCode, hw->cycle_counts->srem_op, functional_unit); break;
        case llvm::Instruction::FRem: return SALAM::createFRemInst(id, this, debug(), OpCode, hw->cycle_counts->frem_op, functional_unit); break;
        case llvm::Instruction::Shl: return SALAM::createShlInst(id, this, debug(), OpCode, hw->cycle_counts->shl_op, functional_unit); break;
        case llvm::Instruction::LShr: return SALAM::createLShrInst(id, this, debug(), OpCode, hw->cycle_counts->lshr_op, functional_unit); break;
        case llvm::Instruction::AShr: return SALAM::createAShrInst(id, this, debug(), OpCode, hw->cycle_counts->ashr_op, functional_unit); break;
        case llvm::Instruction::And: return SALAM::createAndInst(id, this, debug(), OpCode, hw->cycle_counts->and_op, functional_unit); break;
        case llvm::Instruction::Or: return SALAM::createOrInst(id, this, debug(), OpCode, hw->cycle_counts->or_op, functional_unit); break;
        case llvm::Instruction::Xor: return SALAM::createXorInst(id, this, debug(), OpCode, hw->cycle_counts->xor_op, functional_unit); break;
        case llvm::Instruction::Load: return SALAM::createLoadInst(id, this, debug(), OpCode, hw->cycle_counts->load_op, functional_unit); break;
        case llvm::Instruction::Store: return SALAM::createStoreInst(id, this, debug(), OpCode, hw->cycle_counts->store_op, functional_unit); break;
        case llvm::Instruction::GetElementPtr : return SALAM::createGetElementPtrInst(id, this, debug(), OpCode, hw->cycle_counts->gep_op, functional_unit); break;
        case llvm::Instruction::Trunc: return SALAM::createTruncInst(id, this, debug(), OpCode, hw->cycle_counts->trunc_op, functional_unit); break;
        case llvm::Instruction::ZExt: return SALAM::createZExtInst(id, this, debug(), OpCode, hw->cycle_counts->zext_op, functional_unit); break;
        case llvm::Instruction::SExt: return SALAM::createSExtInst(id, this, debug(), OpCode, hw->cycle_counts->sext_op, functional_unit); break;
        case llvm::Instruction::FPToUI: return SALAM::createFPToUIInst(id, this, debug(), OpCode, hw->cycle_counts->fptoui_op, functional_unit); break;
        case llvm::Instruction::FPToSI: return SALAM::createFPToSIInst(id, this, debug(), OpCode, hw->cycle_counts->fptosi_op, functional_unit); break;
        case llvm::Instruction::UIToFP: return SALAM::createUIToFPInst(id, this, debug(), OpCode, hw->cycle_counts->uitofp_op, functional_unit); break;
        case llvm::Instruction::SIToFP: return SALAM::createSIToFPInst(id, this, debug(), OpCode, hw->cycle_counts->sitofp_op, functional_unit); break;
        case llvm::Instruction::FPTrunc: return SALAM::createFPTruncInst(id, this, debug(), OpCode, hw->cycle_counts->fptrunc_op, functional_unit); break;
        case llvm::Instruction::FPExt: return SALAM::createFPExtInst(id, this, debug(), OpCode, hw->cycle_counts->fpext_op, functional_unit); break;
        case llvm::Instruction::PtrToInt: return SALAM::createPtrToIntInst(id, this, debug(), OpCode, hw->cycle_counts->ptrtoint_op, functional_unit); break;
        case llvm::Instruction::IntToPtr: return SALAM::createIntToPtrInst(id, this, debug(), OpCode, hw->cycle_counts->inttoptr_op, functional_unit); break;
        case llvm::Instruction::ICmp: return SALAM::createICmpInst(id, this, debug(), OpCode, hw->cycle_counts->icmp_op, functional_unit); break;
        case llvm::Instruction::FCmp: return SALAM::createFCmpInst(id, this, debug(), OpCode, hw->cycle_counts->fcmp_op, functional_unit); break;
        case llvm::Instruction::PHI: return SALAM::createPHIInst(id, this, debug(), OpCode, hw->cycle_counts->phi_op, functional_unit); break;
        case llvm::Instruction::Call: return SALAM::createCallInst(id, this, debug(), OpCode, hw->cycle_counts->call_op, functional_unit); break;
        case llvm::Instruction::Select: return SALAM::createSelectInst(id, this, debug(), OpCode, hw->cycle_counts->select_op, functional_unit); break;
        default: {
            warn("Tried to create opance of undefined opruction type!");
            return SALAM::createBadInst(id, this, dbg, OpCode, 0, 0); break;
        }
    }
}
