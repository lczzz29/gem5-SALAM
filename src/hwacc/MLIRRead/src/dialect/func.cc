#include "func.hh"

namespace MULA {

namespace func {

CallIndirectOp::CallIndirectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CallIndirectOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CallIndirectOp::compute()
{
    // Compute code
}

void CallIndirectOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCallIndirectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::func::CallIndirectOp>(id, owner, dbg, OpCode, cycles, fu);
}

CallOp::CallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CallOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
    if (auto callOp = mlir::dyn_cast<mlir::func::CallOp>(op)) {
        bool hasResults = !callOp.getResultTypes().empty();
    }
}

void CallOp::compute()
{
    // Compute code
}

void CallOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::func::CallOp>(id, owner, dbg, OpCode, cycles, fu);
}

ConstantOp::ConstantOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ConstantOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ConstantOp::compute()
{
    // Compute code
}

void ConstantOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createConstantOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::func::ConstantOp>(id, owner, dbg, OpCode, cycles, fu);
}

FuncOp::FuncOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void FuncOp::initialize(mlir::Operation *op, MULA::IRMap *irMap)
{
    MULA::Operation::initialize(op, irMap);
}

void FuncOp::initialize(mlir::Operation *op, IRMap *irMap, std::string topName)
{
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    if (dbg) DPRINTFS(MLIRParse, owner, "Initialize Values - Function::initialize\n");
    MULA::Operation::initialize(op, irMap);

	//Parse irval for function params
	mlir::func::FuncOp func = mlir::dyn_cast<mlir::func::FuncOp>(op);
	assert(func); //panic("Invalid llvm::Value type used to initialize function. Failed cast to llvm::Function.");
    if (func.getName() == topName) top = true;
    else top = false;
	// Fill arguments
    if (dbg) DPRINTFS(MLIRParse, owner, "Initialize Function Arguments\n");
	for (auto arg : func.getArguments()) {
        std::shared_ptr<MULA::Value> argval = irMap->findValue(&arg);
        assert(argval);
        std::shared_ptr<MULA::Argument> argum = std::dynamic_pointer_cast<MULA::Argument>(argval);
        assert(argum);
        arguments.push_back(argum);
        argum->initialize(&arg, irMap);
    }

    // Fill bbList
    if (dbg) DPRINTFS(MLIRParse, owner, "Initialize Blocks\n");
    for (auto block = func.getFunctionBody().begin(); block != func.getFunctionBody().end(); block++) {
        mlir::Block &bb = *block;
        std::shared_ptr<MULA::Block> mappedBlock = irMap->findBlock(&bb);
        assert(mappedBlock);
        blockList.push_back(mappedBlock);
        mappedBlock->initialize(&bb, irMap);
    }
}


void FuncOp::compute()
{
    // Compute code
}

void FuncOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createFuncOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::func::FuncOp>(id, owner, dbg, OpCode, cycles, fu);
}

ReturnOp::ReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ReturnOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ReturnOp::compute()
{
    // Compute code
}

void ReturnOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::func::ReturnOp>(id, owner, dbg, OpCode, cycles, fu);
}

} // namespace func

} // namespace MULA
