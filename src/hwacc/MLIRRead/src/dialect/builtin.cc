#include "builtin.hh"

namespace MULA {

namespace builtin {

ModuleOp::ModuleOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ModuleOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ModuleOp::compute()
{
    // Compute code
}

void ModuleOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createModuleOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::builtin::ModuleOp>(id, owner, dbg, OpCode, cycles, fu);
}

} // namespace builtin

} // namespace MULA
