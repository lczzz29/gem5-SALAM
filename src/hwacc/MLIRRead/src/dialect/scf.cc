#include "scf.hh"

namespace MULA {

namespace scf {

ConditionOp::ConditionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void ConditionOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ConditionOp::compute()
{
    // Compute code
}

void ConditionOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createConditionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::ConditionOp>(id, owner, dbg, OpCode, cycles, fu);
}

ExecuteRegionOp::ExecuteRegionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void ExecuteRegionOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ExecuteRegionOp::compute()
{
    // Compute code
}

void ExecuteRegionOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createExecuteRegionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::ExecuteRegionOp>(id, owner, dbg, OpCode, cycles, fu);
}

ForOp::ForOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void ForOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
    mlir::scf::ForOp *forOp = mlir::dyn_cast<mlir::scf::ForOp*>(op);
    assert(forOp && "Operation must be a scf.for");

    // // Get loop body region
    // bodyRegion = irmap->findRegion(&forOp->getLoopBody());
    // if (bodyRegion == nullptr) {
    //     if (dbg) DPRINTFS(Runtime, owner, "ERROR: Could not find body region for scf.for in IR map.");
    //     assert(0);
    // }

    // Capture mandatory loop operands (lb, ub, step)
    mlir::Value *lbOperand = &forOp->getLowerBound();
    mlir::Value *ubOperand = &forOp->getUpperBound();
    mlir::Value *stepOperand = &forOp->getStep();

    staticDependencies.push_back(irmap->findValue(lbOperand));
    staticDependencies.push_back(irmap->findValue(ubOperand));
    staticDependencies.push_back(irmap->findValue(stepOperand));

    // Check for iteration arguments
    hasIterArgs = forOp->getNumIterOperands() > 0;
    if (hasIterArgs) {
        // Capture all iteration arguments
        for (mlir::Value iterArg : forOp->getIterOperands()) {
            staticDependencies.push_back(irmap->findValue(&iterArg));
        }
    }

    // Check for results
    hasResult = forOp->getNumResults() > 0;
    if (hasResult) {
        // Capture all results
        for (mlir::Value result : forOp->getResults()) {
            staticDependencies.push_back(irmap->findValue(&result));
        }
    }

    // Debug output
    if (dbg) {
        DPRINTFS(Runtime, owner, "Initialized scf.for with:");
        DPRINTFS(Runtime, owner, "  - %d static dependencies", staticDependencies.size());
        DPRINTFS(Runtime, owner, "  - Has iteration args: %s", hasIterArgs ? "true" : "false");
        DPRINTFS(Runtime, owner, "  - Has results: %s", hasResult ? "true" : "false");
    }
}

void ForOp::compute()
{
    // Compute code
}

void ForOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createForOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::ForOp>(id, owner, dbg, OpCode, cycles, fu);
}

ForallOp::ForallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void ForallOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ForallOp::compute()
{
    // Compute code
}

void ForallOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createForallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::ForallOp>(id, owner, dbg, OpCode, cycles, fu);
}

InParallelOp::InParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void InParallelOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void InParallelOp::compute()
{
    // Compute code
}

void InParallelOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createInParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::InParallelOp>(id, owner, dbg, OpCode, cycles, fu);
}

IfOp::IfOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void IfOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
    mlir::scf::IfOp *ifOp = mlir::dyn_cast<mlir::scf::IfOp *>(op);
    assert(ifOp);

    thenRegion = irmap->findRegion(&ifOp->getBodyRegion());
    if(thenRegion == nullptr) {
        if (dbg) DPRINTFS(Runtime, owner, "ERROR. Could not find then region for scf.if in IR map.");
        assert(0);
    }

    mlir::Value *condOperand = &ifOp->getOperand();

    staticDependencies.push_back(irmap->findValue(condOperand));
    condition = std::dynamic_pointer_cast<MULA::Operand>(irmap->findValue(condOperand));

    hasElse = !ifOp->getElseRegion().empty();
    if(hasElse) {
        elseRegion = irmap->findRegion(&ifOp->getElseRegion());
    }
}

void IfOp::compute()
{
    // Compute code
}

void IfOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Region> 
IfOp::getTarget() 
{
    if (dbg) DPRINTFS(RuntimeCompute, owner, "|| Evaluating scf.if condition\n");
   
    if (condition->getUIntRegValue()) {
        // Condition is true - return then target
        if (dbg) DPRINTFS(RuntimeCompute, owner, "|| Condition: TRUE, Fetching then block\n");
        return thenRegion; // Assuming you have a conversion function
    }
    else {
        // Condition is false - check for else region
        if (!hasElse) {
            if (dbg) DPRINTFS(RuntimeCompute, owner, "|| Condition: FALSE, No else region - returning nullptr\n");
            return nullptr;
        }
        else {
            if (dbg) DPRINTFS(RuntimeCompute, owner, "|| Condition: FALSE, Fetching else region\n");
            return elseRegion; // Assuming you have a conversion function
        }
    }
}

std::shared_ptr<MULA::Operation>
createIfOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::IfOp>(id, owner, dbg, OpCode, cycles, fu);
}

IndexSwitchOp::IndexSwitchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void IndexSwitchOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void IndexSwitchOp::compute()
{
    // Compute code
}

void IndexSwitchOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createIndexSwitchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::IndexSwitchOp>(id, owner, dbg, OpCode, cycles, fu);
}

ParallelOp::ParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void ParallelOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ParallelOp::compute()
{
    // Compute code
}

void ParallelOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::ParallelOp>(id, owner, dbg, OpCode, cycles, fu);
}

ReduceOp::ReduceOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void ReduceOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ReduceOp::compute()
{
    // Compute code
}

void ReduceOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createReduceOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::ReduceOp>(id, owner, dbg, OpCode, cycles, fu);
}

ReduceReturnOp::ReduceReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void ReduceReturnOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ReduceReturnOp::compute()
{
    // Compute code
}

void ReduceReturnOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createReduceReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::ReduceReturnOp>(id, owner, dbg, OpCode, cycles, fu);
}

WhileOp::WhileOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void WhileOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void WhileOp::compute()
{
    // Compute code
}

void WhileOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createWhileOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::WhileOp>(id, owner, dbg, OpCode, cycles, fu);
}

YieldOp::YieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
    : Operation(id, owner, dbg, OpCode, cycles, fu)
{
    std::vector<uint64_t> base_params;
    base_params.push_back(id);
    base_params.push_back(OpCode);
    base_params.push_back(cycles);
    conditions.push_back(base_params);
}

void YieldOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void YieldOp::compute()
{
    // Compute code
}

void YieldOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createYieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::scf::YieldOp>(id, owner, dbg, OpCode, cycles, fu);
}

} // namespace scf

} // namespace MULA
