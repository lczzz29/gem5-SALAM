#include "operation.hh"
// #include "llvm/IR/GetElementPtrTypeIterator.h"
// #include "llvm/IR/DataLayout.h"
#include "sim/sim_object.hh"

#include <cmath>

namespace MULA
{

//---------------------------------------------------------------------------//
//--------- Operation Base Class ------------------------------------------//
//---------------------------------------------------------------------------//


MULA::Operation::Operation(uint64_t id, gem5::SimObject * owner, bool dbg)
{
    currentCycle = 0;
    uid = id;
    owner = owner;
    dbg = dbg;
}

MULA::Operation::Operation(uint64_t id, gem5::SimObject * owner, bool dbg,
                         uint64_t OpCode) :
                         mlirOpCode(OpCode)
{
    currentCycle = 0;
    uid = id;
    owner = owner;
    dbg = dbg;
}

MULA::Operation::Operation(uint64_t id, gem5::SimObject * owner, bool dbg,
                         uint64_t OpCode,
                         uint64_t cycles) :
                         mlirOpCode(OpCode),
                         cycleCount(cycles)
{
    currentCycle = 0;
    uid = id;
    owner = owner;
    dbg = dbg;
}

MULA::Operation::Operation(uint64_t id, gem5::SimObject * owner, bool dbg,
                         uint64_t OpCode,
                         uint64_t cycles,
                         uint64_t fu) :
                         mlirOpCode(OpCode),
                         cycleCount(cycles),
                         functional_unit(fu)
{
    currentCycle = 0;
    uid = id;
    owner = owner;
    dbg = dbg;
}

MULA::Operation::~Operation()
{
}

MULA::Operation::Operation_Debugger::Operation_Debugger()
{
}

void
MULA::Operation::Operation_Debugger::dumper(Operation *inst)
{
}

void
MULA::Operation::initialize(mlir::Operation *op,
                         IRMap * irmap
                         )
{
    if (dbg) DPRINTFS(MLIRParse, owner, "Initialize Value - Operation::initialize\n");
    // MULA::Value::initialize(irval, irmap);
    opName = op->getName().getStringRef().str();
    dialectName = op->getDialect()->getNamespace().str();

    // // Fetch the operands of the Operation
    // llvm::User * iruser = llvm::dyn_cast<llvm::User>(irval);
    // llvm::Instruction * inst = llvm::dyn_cast<llvm::Instruction>(irval);
    
    // uint64_t phiBB = 0;
    for (mlir::OpOperand &operand : op->getOpOperands()) {
        mlir::Value *oprndValue = &operand.get();
        auto mapit = irmap->findValue(oprndValue);
        std::shared_ptr<MULA::Value> opval;
        // Note: There is no case that one opoperand has no defining op in irmap.
        // i.e. no direct use of constant in an operation
        //
        // if(mapit == irmap->end()) {
        //     // TODO: Handle constant data and constant expressions
        //     if (dbg) DPRINTFS(MLIRParse, owner, "Instantiate Operand as Constant Data/Expression\n");
        //     uint64_t id = valueList->back()->getUID() + 1;
        //     std::shared_ptr<MULA::Constant> con = std::make_shared<MULA::Constant>(id, owner, dbg);
        //     valueList->push_back(con);
        //     irmap->insert(MULA::IRMaptype(oprndValue, con));
        //     con->initialize(oprndValue, irmap, valueList);
        //     opval = con;
        // } else {
        if (dbg) DPRINTFS(MLIRParse, owner, "Instantiate Operands on Value List\n");
        opval = mapit;
        // }
        if (dbg) DPRINTFS(MLIRParse, owner, "Link Operand to Static Operands List\n");
        staticDependencies.push_back(opval);
    }
}

void
MULA::Operation::signalUsers()
{
    uint64_t count = 0;
    for (auto user : dynamicUsers) {
        if (dbg) DPRINTFS(Runtime, owner, "|| User[%i] =============\n", count);
        user->setOperandValue(uid);
        count++;
    }
    if (dbg) DPRINTFS(Runtime, owner, "||==signalUsers==========\n");
}

void
MULA::Operation::removeDynamicDependency(uint64_t opuid)
{
    auto end = dynamicDependencies.end();
    auto it = dynamicDependencies.find(opuid);
    if (it != end) dynamicDependencies.erase(it);
}

bool
MULA::Operation::ready()
{
    if (dbg) DPRINTFS(Runtime, owner, "|| Remaining Dependencies: %i \n", getDependencyCount());
    if (getDependencyCount() == 0) {
        isready = true;
        if (dbg) DPRINTFS(Runtime, owner, "||==Return: %s\n", isready ? "true" : "false");
        if (dbg) DPRINTFS(Runtime, owner, "||==ready=================\n");
        return true;
    } else {

    }
    if (dbg) DPRINTFS(Runtime, owner, "||==Return: %s\n", isready ? "true" : "false");
    if (dbg) DPRINTFS(Runtime, owner, "||==ready=================\n");
    return false;
}

bool
MULA::Operation::launch()
{
    if (hasFunctionalUnit()) {
        if(!hw_interface->availableFunctionalUnit(getFunctionalUnit())) {
            return false;
            std::cout << "Waiting on next available FU\n"; 
        } else {
            
        }
    }
    launched = true;
    if (getCycleCount() == 0) { // Operation ready to be committed
        if (dbg) DPRINTFS(Runtime, owner, "||  0 Cycle Operation\n");
        compute();
        commit();
    } else {
        currentCycle++;
        compute();
    }
    if (dbg) DPRINTFS(Runtime, owner, "||==Return: %s\n", isCommitted() ? "true" : "false");
    if (dbg) DPRINTFS(Runtime, owner, "||==launch================\n");
    return isCommitted();
}

bool
MULA::Operation::commit()
{
    if (dbg) DPRINTFS(Runtime, owner, "||  Current Cycle: %i\n", getCurrentCycle());
    if (getCurrentCycle() == getCycleCount()) { // Operation ready to be committed
        signalUsers();
        committed = true;
        if (dbg) DPRINTFS(Runtime, owner, "||==Return: %s\n", committed ? "true" : "false");
        if (dbg) DPRINTFS(Runtime, owner, "||==commit================\n");
        //std::cout << "\n\n\nTest 3 - FU[" << getFunctionalUnit() << "]\n\n\n";
        if (hasFunctionalUnit()) {
            //std::cout << "\n\n\nTest 2\n\n\n";
            hw_interface->clearFunctionalUnit(getFunctionalUnit());
           // hw_interface->functional_units->
        } else {
            // 
        }
        return true;
    } else {
        if (dbg) DPRINTFS(Runtime, owner, "||  Remaining Cycles: %i\n", getCycleCount() - getCurrentCycle());
        currentCycle++;
    }
    if (dbg) DPRINTFS(Runtime, owner, "||==Return: %s\n", committed ? "true" : "false");
    if (dbg) DPRINTFS(Runtime, owner, "||==commit================\n");
    return false;
}

void
MULA::Operation::setOperandValue(uint64_t opuid)
{
    uint64_t count = 0;
    for (auto it = operands.begin(); it != operands.end(); ++it) {
        auto operand = *it;
        if (operand.getUID() == opuid) {
            if (dbg) DPRINTFS(Runtime, owner, "|| Storing Value in Operand[%i]\n", count++);
            operand.updateOperandRegister();
            //break;
        } else count++;
    }
    removeDynamicDependency(opuid);
}

void
MULA::Operation::reset() {
    isready = false;
    launched = false;
    committed = false;
    currentCycle = 0;
    if (dbg) DPRINTFS(Runtime, owner, "||==reset=================\n");
}

void
MULA::Operation::linkOperands(const MULA::Operand &newOp)
{
    MULA::Operand op_copy = newOp;
    operands.push_back(op_copy);
}

//std::deque<uint64_t>
std::vector<uint64_t>
MULA::Operation::runtimeInitialize() {
    assert(getDependencyCount() == 0);
    //std::deque<uint64_t> dep_uids;
    std::vector<uint64_t> dep_uids;

    for (auto it = staticDependencies.begin(); it != staticDependencies.end(); ++it) {
        std::shared_ptr<MULA::Value> static_dependency = *it;
        auto dep_uid = static_dependency->getUID();
        operands.push_back(MULA::Operand(static_dependency));
        if ((static_dependency->isConstant()) || (static_dependency->isArgument())) {
            operands.back().updateOperandRegister();
        } else {
            dep_uids.push_back(dep_uid);
        }
    }
    // dep_uids.push_back(uid);

    return dep_uids;
}

} // namespace MULA

//---------------------------------------------------------------------------//