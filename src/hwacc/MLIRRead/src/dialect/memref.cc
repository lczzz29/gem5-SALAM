#include "memref.hh"

namespace MULA {

namespace memref {

AssumeAlignmentOp::AssumeAlignmentOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AssumeAlignmentOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AssumeAlignmentOp::compute()
{
    // Compute code
}

void AssumeAlignmentOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAssumeAlignmentOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::AssumeAlignmentOp>(id, owner, dbg, OpCode, cycles, fu);
}

AtomicRMWOp::AtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AtomicRMWOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AtomicRMWOp::compute()
{
    // Compute code
}

void AtomicRMWOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::AtomicRMWOp>(id, owner, dbg, OpCode, cycles, fu);
}

AtomicYieldOp::AtomicYieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AtomicYieldOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AtomicYieldOp::compute()
{
    // Compute code
}

void AtomicYieldOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAtomicYieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::AtomicYieldOp>(id, owner, dbg, OpCode, cycles, fu);
}

CopyOp::CopyOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CopyOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CopyOp::compute()
{
    // Compute code
}

void CopyOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCopyOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::CopyOp>(id, owner, dbg, OpCode, cycles, fu);
}

GenericAtomicRMWOp::GenericAtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void GenericAtomicRMWOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void GenericAtomicRMWOp::compute()
{
    // Compute code
}

void GenericAtomicRMWOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createGenericAtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::GenericAtomicRMWOp>(id, owner, dbg, OpCode, cycles, fu);
}

LoadOp::LoadOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void LoadOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
    if (staticDependencies.front()->isGlobalConstant()) loadingInternal = true;
}

void LoadOp::compute()
{
    // Compute code
}

void LoadOp::dumper()
{
    // Dump code
}

// loadInternal() used when the data to be loaded is a global constant
void LoadOp::loadInternal() {
    if (dbg) DPRINTFS(RuntimeCompute, owner, "|| Launching %s\n", getOpName());
    
    // Get the memref register
    auto memrefReg = std::static_pointer_cast<LocalMemrefRegister>(operands.front().getRegister());
    
    // Collect indices (assuming they're constant)
    std::vector<uint64_t> indices;
    for (unsigned i = 0; i < memrefReg->getRank(); ++i) {
        indices.push_back(operands[1+i].getPtrRegValue());
    }
    
    // Get the raw element value
    uint64_t rawValue = memrefReg->getElementValue(indices);
    
    if (dbg) {
        DPRINTFS(RuntimeCompute, owner, "|| Loading constant element at indices [");
        // for (auto idx : indices) DPRINTFR(" %d", idx);
        // DPRINTFR(" ] => value %llu\n", rawValue);
    }
    
    // Create a new register with the raw value (type will be handled by setRegisterValue)
    auto resultReg = std::make_shared<Register>(rawValue);
    results.front().setRegisterValue(resultReg);
    
    commit();
}

MemoryRequest* LoadOp::createMemoryRequest() {
    // Get the memref register and verify cast
    auto memrefReg = std::static_pointer_cast<MemrefRegister>(operands.front().getRegister());
    
    // Calculate linear offset using memref's strides
    Addr finalOffset = 0;
    for (unsigned i = 0; i < memrefReg->getRank(); ++i) {
        finalOffset += operands[1+i].getPtrRegValue() * memrefReg->getStrides()[i];
    }
    
    // Final address calculation
    Addr memAddr = memrefReg->getBaseAddress() + finalOffset;
    
    // Get element size using the new method (replaces getSizeInBytes())
    size_t reqLen = memrefReg->getElementSizeInBytes();
    
    // For vector types: multiply by number of elements
    if (auto vectorType = memrefReg->getElementType().dyn_cast<mlir::VectorType>()) {
        reqLen *= vectorType.getNumElements();
    }
    
    if (dbg) {
        DPRINTFS(RuntimeCompute, owner, "|| Loading %d bytes from 0x%x\n", reqLen, memAddr);
    }
    
    return new MemoryRequest(memAddr, reqLen);
}

std::shared_ptr<MULA::Operation>
createLoadOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::LoadOp>(id, owner, dbg, OpCode, cycles, fu);
}

AllocOp::AllocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AllocOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AllocOp::compute()
{
    // Compute code
}

void AllocOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAllocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::AllocOp>(id, owner, dbg, OpCode, cycles, fu);
}

AllocaOp::AllocaOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AllocaOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AllocaOp::compute()
{
    // Compute code
}

void AllocaOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAllocaOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::AllocaOp>(id, owner, dbg, OpCode, cycles, fu);
}

AllocaScopeOp::AllocaScopeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AllocaScopeOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AllocaScopeOp::compute()
{
    // Compute code
}

void AllocaScopeOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAllocaScopeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::AllocaScopeOp>(id, owner, dbg, OpCode, cycles, fu);
}

AllocaScopeReturnOp::AllocaScopeReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void AllocaScopeReturnOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void AllocaScopeReturnOp::compute()
{
    // Compute code
}

void AllocaScopeReturnOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createAllocaScopeReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::AllocaScopeReturnOp>(id, owner, dbg, OpCode, cycles, fu);
}

CastOp::CastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CastOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CastOp::compute()
{
    // Compute code
}

void CastOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::CastOp>(id, owner, dbg, OpCode, cycles, fu);
}

CollapseShapeOp::CollapseShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void CollapseShapeOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void CollapseShapeOp::compute()
{
    // Compute code
}

void CollapseShapeOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createCollapseShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::CollapseShapeOp>(id, owner, dbg, OpCode, cycles, fu);
}

DeallocOp::DeallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void DeallocOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void DeallocOp::compute()
{
    // Compute code
}

void DeallocOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createDeallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::DeallocOp>(id, owner, dbg, OpCode, cycles, fu);
}

DimOp::DimOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void DimOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void DimOp::compute()
{
    // Compute code
}

void DimOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createDimOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::DimOp>(id, owner, dbg, OpCode, cycles, fu);
}

DmaStartOp::DmaStartOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void DmaStartOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void DmaStartOp::compute()
{
    // Compute code
}

void DmaStartOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createDmaStartOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::DmaStartOp>(id, owner, dbg, OpCode, cycles, fu);
}

DmaWaitOp::DmaWaitOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void DmaWaitOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void DmaWaitOp::compute()
{
    // Compute code
}

void DmaWaitOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createDmaWaitOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::DmaWaitOp>(id, owner, dbg, OpCode, cycles, fu);
}

ExpandShapeOp::ExpandShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ExpandShapeOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ExpandShapeOp::compute()
{
    // Compute code
}

void ExpandShapeOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createExpandShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::ExpandShapeOp>(id, owner, dbg, OpCode, cycles, fu);
}

ExtractAlignedPointerAsIndexOp::ExtractAlignedPointerAsIndexOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ExtractAlignedPointerAsIndexOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ExtractAlignedPointerAsIndexOp::compute()
{
    // Compute code
}

void ExtractAlignedPointerAsIndexOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createExtractAlignedPointerAsIndexOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::ExtractAlignedPointerAsIndexOp>(id, owner, dbg, OpCode, cycles, fu);
}

ExtractStridedMetadataOp::ExtractStridedMetadataOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ExtractStridedMetadataOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ExtractStridedMetadataOp::compute()
{
    // Compute code
}

void ExtractStridedMetadataOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createExtractStridedMetadataOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::ExtractStridedMetadataOp>(id, owner, dbg, OpCode, cycles, fu);
}

GetGlobalOp::GetGlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void GetGlobalOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void GetGlobalOp::compute()
{
    // Compute code
}

void GetGlobalOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createGetGlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::GetGlobalOp>(id, owner, dbg, OpCode, cycles, fu);
}

GlobalOp::GlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void GlobalOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void GlobalOp::compute()
{
    // Compute code
}

void GlobalOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createGlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::GlobalOp>(id, owner, dbg, OpCode, cycles, fu);
}

MemorySpaceCastOp::MemorySpaceCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void MemorySpaceCastOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void MemorySpaceCastOp::compute()
{
    // Compute code
}

void MemorySpaceCastOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createMemorySpaceCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::MemorySpaceCastOp>(id, owner, dbg, OpCode, cycles, fu);
}

PrefetchOp::PrefetchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void PrefetchOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void PrefetchOp::compute()
{
    // Compute code
}

void PrefetchOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createPrefetchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::PrefetchOp>(id, owner, dbg, OpCode, cycles, fu);
}

RankOp::RankOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void RankOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void RankOp::compute()
{
    // Compute code
}

void RankOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createRankOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::RankOp>(id, owner, dbg, OpCode, cycles, fu);
}

ReallocOp::ReallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ReallocOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ReallocOp::compute()
{
    // Compute code
}

void ReallocOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createReallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::ReallocOp>(id, owner, dbg, OpCode, cycles, fu);
}

ReinterpretCastOp::ReinterpretCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ReinterpretCastOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ReinterpretCastOp::compute()
{
    // Compute code
}

void ReinterpretCastOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createReinterpretCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::ReinterpretCastOp>(id, owner, dbg, OpCode, cycles, fu);
}

ReshapeOp::ReshapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ReshapeOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ReshapeOp::compute()
{
    // Compute code
}

void ReshapeOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createReshapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::ReshapeOp>(id, owner, dbg, OpCode, cycles, fu);
}

StoreOp::StoreOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void StoreOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void StoreOp::compute()
{
    // Compute code
}

void StoreOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createStoreOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::StoreOp>(id, owner, dbg, OpCode, cycles, fu);
}

TransposeOp::TransposeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void TransposeOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void TransposeOp::compute()
{
    // Compute code
}

void TransposeOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createTransposeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::TransposeOp>(id, owner, dbg, OpCode, cycles, fu);
}

ViewOp::ViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void ViewOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void ViewOp::compute()
{
    // Compute code
}

void ViewOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::ViewOp>(id, owner, dbg, OpCode, cycles, fu);
}

SubViewOp::SubViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
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

void SubViewOp::initialize(mlir::Operation *op, MULA::IRMap *irmap)
{
    MULA::Operation::initialize(op, irmap);
}

void SubViewOp::compute()
{
    // Compute code
}

void SubViewOp::dumper()
{
    // Dump code
}

std::shared_ptr<MULA::Operation>
createSubViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu)
{
    return std::make_shared<MULA::memref::SubViewOp>(id, owner, dbg, OpCode, cycles, fu);
}

} // namespace memref

} // namespace MULA
