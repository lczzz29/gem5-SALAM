#include "arith.hh"

namespace MULA {

namespace arith {

AddFOp::AddFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AddFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AddFOp::compute()
{
    // Compute code
}

void AddFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAddFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::AddFOp>(id, owner, dbg, OpCode, cycles, fu);
}

AddIOp::AddIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AddIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AddIOp::compute()
{
    // Compute code
}

void AddIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAddIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::AddIOp>(id, owner, dbg, OpCode, cycles, fu);
}

AddUIExtendedOp::AddUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AddUIExtendedOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AddUIExtendedOp::compute()
{
    // Compute code
}

void AddUIExtendedOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAddUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::AddUIExtendedOp>(id, owner, dbg, OpCode, cycles, fu);
}

AndIOp::AndIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AndIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AndIOp::compute()
{
    // Compute code
}

void AndIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAndIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::AndIOp>(id, owner, dbg, OpCode, cycles, fu);
}

BitcastOp::BitcastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void BitcastOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void BitcastOp::compute()
{
    // Compute code
}

void BitcastOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createBitcastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::BitcastOp>(id, owner, dbg, OpCode, cycles, fu);
}

CeilDivSIOp::CeilDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CeilDivSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CeilDivSIOp::compute()
{
    // Compute code
}

void CeilDivSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCeilDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::CeilDivSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

CeilDivUIOp::CeilDivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CeilDivUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CeilDivUIOp::compute()
{
    // Compute code
}

void CeilDivUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCeilDivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::CeilDivUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

CmpFOp::CmpFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CmpFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CmpFOp::compute()
{
    // Compute code
}

void CmpFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCmpFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::CmpFOp>(id, owner, dbg, OpCode, cycles, fu);
}

CmpIOp::CmpIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CmpIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CmpIOp::compute()
{
    // Compute code
}

void CmpIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCmpIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::CmpIOp>(id, owner, dbg, OpCode, cycles, fu);
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
    return std::make_shared<MULA::arith::ConstantOp>(id, owner, dbg, OpCode, cycles, fu);
}

DivFOp::DivFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void DivFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void DivFOp::compute()
{
    // Compute code
}

void DivFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createDivFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::DivFOp>(id, owner, dbg, OpCode, cycles, fu);
}

DivSIOp::DivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void DivSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void DivSIOp::compute()
{
    // Compute code
}

void DivSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::DivSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

DivUIOp::DivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void DivUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void DivUIOp::compute()
{
    // Compute code
}

void DivUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createDivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::DivUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

ExtFOp::ExtFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ExtFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ExtFOp::compute()
{
    // Compute code
}

void ExtFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createExtFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::ExtFOp>(id, owner, dbg, OpCode, cycles, fu);
}

ExtSIOp::ExtSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ExtSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ExtSIOp::compute()
{
    // Compute code
}

void ExtSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createExtSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::ExtSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

ExtUIOp::ExtUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ExtUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ExtUIOp::compute()
{
    // Compute code
}

void ExtUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createExtUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::ExtUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

FloorDivSIOp::FloorDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void FloorDivSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void FloorDivSIOp::compute()
{
    // Compute code
}

void FloorDivSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createFloorDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::FloorDivSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

FPToSIOp::FPToSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void FPToSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void FPToSIOp::compute()
{
    // Compute code
}

void FPToSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createFPToSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::FPToSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

FPToUIOp::FPToUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void FPToUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void FPToUIOp::compute()
{
    // Compute code
}

void FPToUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createFPToUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::FPToUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

IndexCastOp::IndexCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void IndexCastOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void IndexCastOp::compute()
{
    // Compute code
}

void IndexCastOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createIndexCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::IndexCastOp>(id, owner, dbg, OpCode, cycles, fu);
}

IndexCastUIOp::IndexCastUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void IndexCastUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void IndexCastUIOp::compute()
{
    // Compute code
}

void IndexCastUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createIndexCastUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::IndexCastUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

MaximumFOp::MaximumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MaximumFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MaximumFOp::compute()
{
    // Compute code
}

void MaximumFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMaximumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MaximumFOp>(id, owner, dbg, OpCode, cycles, fu);
}

MaxNumFOp::MaxNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MaxNumFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MaxNumFOp::compute()
{
    // Compute code
}

void MaxNumFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMaxNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MaxNumFOp>(id, owner, dbg, OpCode, cycles, fu);
}

MaxSIOp::MaxSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MaxSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MaxSIOp::compute()
{
    // Compute code
}

void MaxSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMaxSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MaxSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

MaxUIOp::MaxUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MaxUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MaxUIOp::compute()
{
    // Compute code
}

void MaxUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMaxUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MaxUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

MinimumFOp::MinimumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MinimumFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MinimumFOp::compute()
{
    // Compute code
}

void MinimumFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMinimumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MinimumFOp>(id, owner, dbg, OpCode, cycles, fu);
}

MinNumFOp::MinNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MinNumFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MinNumFOp::compute()
{
    // Compute code
}

void MinNumFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMinNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MinNumFOp>(id, owner, dbg, OpCode, cycles, fu);
}

MinSIOp::MinSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MinSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MinSIOp::compute()
{
    // Compute code
}

void MinSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMinSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MinSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

MinUIOp::MinUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MinUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MinUIOp::compute()
{
    // Compute code
}

void MinUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMinUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MinUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

MulFOp::MulFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MulFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MulFOp::compute()
{
    // Compute code
}

void MulFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMulFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MulFOp>(id, owner, dbg, OpCode, cycles, fu);
}

MulIOp::MulIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MulIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MulIOp::compute()
{
    // Compute code
}

void MulIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMulIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MulIOp>(id, owner, dbg, OpCode, cycles, fu);
}

MulSIExtendedOp::MulSIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MulSIExtendedOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MulSIExtendedOp::compute()
{
    // Compute code
}

void MulSIExtendedOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMulSIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MulSIExtendedOp>(id, owner, dbg, OpCode, cycles, fu);
}

MulUIExtendedOp::MulUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MulUIExtendedOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MulUIExtendedOp::compute()
{
    // Compute code
}

void MulUIExtendedOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMulUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::MulUIExtendedOp>(id, owner, dbg, OpCode, cycles, fu);
}

NegFOp::NegFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void NegFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void NegFOp::compute()
{
    // Compute code
}

void NegFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createNegFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::NegFOp>(id, owner, dbg, OpCode, cycles, fu);
}

OrIOp::OrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void OrIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void OrIOp::compute()
{
    // Compute code
}

void OrIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createOrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::OrIOp>(id, owner, dbg, OpCode, cycles, fu);
}

RemFOp::RemFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void RemFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void RemFOp::compute()
{
    // Compute code
}

void RemFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createRemFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::RemFOp>(id, owner, dbg, OpCode, cycles, fu);
}

RemSIOp::RemSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void RemSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void RemSIOp::compute()
{
    // Compute code
}

void RemSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createRemSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::RemSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

RemUIOp::RemUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void RemUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void RemUIOp::compute()
{
    // Compute code
}

void RemUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createRemUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::RemUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

SelectOp::SelectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void SelectOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void SelectOp::compute()
{
    // Compute code
}

void SelectOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createSelectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::SelectOp>(id, owner, dbg, OpCode, cycles, fu);
}

ShLIOp::ShLIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ShLIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ShLIOp::compute()
{
    // Compute code
}

void ShLIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createShLIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::ShLIOp>(id, owner, dbg, OpCode, cycles, fu);
}

ShRSIOp::ShRSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ShRSIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ShRSIOp::compute()
{
    // Compute code
}

void ShRSIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createShRSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::ShRSIOp>(id, owner, dbg, OpCode, cycles, fu);
}

ShRUIOp::ShRUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ShRUIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ShRUIOp::compute()
{
    // Compute code
}

void ShRUIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createShRUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::ShRUIOp>(id, owner, dbg, OpCode, cycles, fu);
}

SIToFPOp::SIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void SIToFPOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void SIToFPOp::compute()
{
    // Compute code
}

void SIToFPOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createSIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::SIToFPOp>(id, owner, dbg, OpCode, cycles, fu);
}

SubFOp::SubFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void SubFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void SubFOp::compute()
{
    // Compute code
}

void SubFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createSubFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::SubFOp>(id, owner, dbg, OpCode, cycles, fu);
}

SubIOp::SubIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void SubIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void SubIOp::compute()
{
    // Compute code
}

void SubIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createSubIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::SubIOp>(id, owner, dbg, OpCode, cycles, fu);
}

TruncFOp::TruncFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void TruncFOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void TruncFOp::compute()
{
    // Compute code
}

void TruncFOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createTruncFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::TruncFOp>(id, owner, dbg, OpCode, cycles, fu);
}

TruncIOp::TruncIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void TruncIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void TruncIOp::compute()
{
    // Compute code
}

void TruncIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createTruncIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::TruncIOp>(id, owner, dbg, OpCode, cycles, fu);
}

UIToFPOp::UIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void UIToFPOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void UIToFPOp::compute()
{
    // Compute code
}

void UIToFPOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createUIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::UIToFPOp>(id, owner, dbg, OpCode, cycles, fu);
}

XOrIOp::XOrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void XOrIOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void XOrIOp::compute()
{
    // Compute code
}

void XOrIOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createXOrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::arith::XOrIOp>(id, owner, dbg, OpCode, cycles, fu);
}

} // namespace arith

} // namespace MULA
