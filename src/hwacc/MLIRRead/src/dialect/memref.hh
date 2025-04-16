#ifndef __HWACC_MLIR_MEMREF_HH__
#define __HWACC_MLIR_MEMREF_HH__

#include "llvm/ADT/SmallVector.h"
#include "../operation.hh"
#include "../irmap.hh"
namespace MULA {

namespace memref {

// MULA-MEMREF-ASSUMEALIGNMENT // -------------------------------------------------------------//
class AssumeAlignmentOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AssumeAlignmentOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AssumeAlignmentOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::AssumeAlignmentOp> clone() const { return std::static_pointer_cast<MULA::memref::AssumeAlignmentOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::AssumeAlignmentOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAssumeAlignmentOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-ATOMICRMW // -------------------------------------------------------------//
class AtomicRMWOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AtomicRMWOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::AtomicRMWOp> clone() const { return std::static_pointer_cast<MULA::memref::AtomicRMWOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::AtomicRMWOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-ATOMICYIELD // -------------------------------------------------------------//
class AtomicYieldOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AtomicYieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AtomicYieldOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::AtomicYieldOp> clone() const { return std::static_pointer_cast<MULA::memref::AtomicYieldOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::AtomicYieldOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAtomicYieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-COPY // -------------------------------------------------------------//
class CopyOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CopyOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CopyOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::CopyOp> clone() const { return std::static_pointer_cast<MULA::memref::CopyOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::CopyOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCopyOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-GENERICATOMICRMW // -------------------------------------------------------------//
class GenericAtomicRMWOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        GenericAtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~GenericAtomicRMWOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::GenericAtomicRMWOp> clone() const { return std::static_pointer_cast<MULA::memref::GenericAtomicRMWOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::GenericAtomicRMWOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createGenericAtomicRMWOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-LOAD // -------------------------------------------------------------//
class LoadOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;
        bool loadingInternal = false;

    protected:
    public:
        LoadOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~LoadOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        void loadInternal();
        bool isLoadingInternal() { return loadingInternal; }
        bool isLoad() override { return true; }
        std::shared_ptr<MULA::memref::LoadOp> clone() const { return std::static_pointer_cast<MULA::memref::LoadOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::LoadOp(*this)); }
        MemoryRequest * createMemoryRequest() override;
};

std::shared_ptr<MULA::Operation>
createLoadOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-ALLOC // -------------------------------------------------------------//
class AllocOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AllocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AllocOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::AllocOp> clone() const { return std::static_pointer_cast<MULA::memref::AllocOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::AllocOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAllocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-ALLOCA // -------------------------------------------------------------//
class AllocaOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AllocaOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AllocaOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::AllocaOp> clone() const { return std::static_pointer_cast<MULA::memref::AllocaOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::AllocaOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAllocaOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-ALLOCASCOPE // -------------------------------------------------------------//
class AllocaScopeOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AllocaScopeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AllocaScopeOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::AllocaScopeOp> clone() const { return std::static_pointer_cast<MULA::memref::AllocaScopeOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::AllocaScopeOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAllocaScopeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-ALLOCASCOPERETURN // -------------------------------------------------------------//
class AllocaScopeReturnOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AllocaScopeReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AllocaScopeReturnOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::AllocaScopeReturnOp> clone() const { return std::static_pointer_cast<MULA::memref::AllocaScopeReturnOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::AllocaScopeReturnOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAllocaScopeReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-CAST // -------------------------------------------------------------//
class CastOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CastOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::CastOp> clone() const { return std::static_pointer_cast<MULA::memref::CastOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::CastOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-COLLAPSESHAPE // -------------------------------------------------------------//
class CollapseShapeOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CollapseShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CollapseShapeOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::CollapseShapeOp> clone() const { return std::static_pointer_cast<MULA::memref::CollapseShapeOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::CollapseShapeOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCollapseShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-DEALLOC // -------------------------------------------------------------//
class DeallocOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        DeallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~DeallocOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::DeallocOp> clone() const { return std::static_pointer_cast<MULA::memref::DeallocOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::DeallocOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createDeallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-DIM // -------------------------------------------------------------//
class DimOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        DimOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~DimOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::DimOp> clone() const { return std::static_pointer_cast<MULA::memref::DimOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::DimOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createDimOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-DMASTART // -------------------------------------------------------------//
class DmaStartOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        DmaStartOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~DmaStartOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::DmaStartOp> clone() const { return std::static_pointer_cast<MULA::memref::DmaStartOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::DmaStartOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createDmaStartOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-DMAWAIT // -------------------------------------------------------------//
class DmaWaitOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        DmaWaitOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~DmaWaitOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::DmaWaitOp> clone() const { return std::static_pointer_cast<MULA::memref::DmaWaitOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::DmaWaitOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createDmaWaitOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-EXPANDSHAPE // -------------------------------------------------------------//
class ExpandShapeOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ExpandShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ExpandShapeOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::ExpandShapeOp> clone() const { return std::static_pointer_cast<MULA::memref::ExpandShapeOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::ExpandShapeOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createExpandShapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-EXTRACTALIGNEDPOINTERASINDEX // -------------------------------------------------------------//
class ExtractAlignedPointerAsIndexOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ExtractAlignedPointerAsIndexOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ExtractAlignedPointerAsIndexOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::ExtractAlignedPointerAsIndexOp> clone() const { return std::static_pointer_cast<MULA::memref::ExtractAlignedPointerAsIndexOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::ExtractAlignedPointerAsIndexOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createExtractAlignedPointerAsIndexOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-EXTRACTSTRIDEDMETADATA // -------------------------------------------------------------//
class ExtractStridedMetadataOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ExtractStridedMetadataOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ExtractStridedMetadataOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::ExtractStridedMetadataOp> clone() const { return std::static_pointer_cast<MULA::memref::ExtractStridedMetadataOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::ExtractStridedMetadataOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createExtractStridedMetadataOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-GETGLOBAL // -------------------------------------------------------------//
class GetGlobalOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        GetGlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~GetGlobalOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::GetGlobalOp> clone() const { return std::static_pointer_cast<MULA::memref::GetGlobalOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::GetGlobalOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createGetGlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-GLOBAL // -------------------------------------------------------------//
class GlobalOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        GlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~GlobalOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::GlobalOp> clone() const { return std::static_pointer_cast<MULA::memref::GlobalOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::GlobalOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createGlobalOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-MEMORYSPACECAST // -------------------------------------------------------------//
class MemorySpaceCastOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MemorySpaceCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MemorySpaceCastOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::MemorySpaceCastOp> clone() const { return std::static_pointer_cast<MULA::memref::MemorySpaceCastOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::MemorySpaceCastOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMemorySpaceCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-PREFETCH // -------------------------------------------------------------//
class PrefetchOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        PrefetchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~PrefetchOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::PrefetchOp> clone() const { return std::static_pointer_cast<MULA::memref::PrefetchOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::PrefetchOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createPrefetchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-RANK // -------------------------------------------------------------//
class RankOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        RankOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~RankOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::RankOp> clone() const { return std::static_pointer_cast<MULA::memref::RankOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::RankOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createRankOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-REALLOC // -------------------------------------------------------------//
class ReallocOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ReallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ReallocOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::ReallocOp> clone() const { return std::static_pointer_cast<MULA::memref::ReallocOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::ReallocOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createReallocOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-REINTERPRETCAST // -------------------------------------------------------------//
class ReinterpretCastOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ReinterpretCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ReinterpretCastOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::ReinterpretCastOp> clone() const { return std::static_pointer_cast<MULA::memref::ReinterpretCastOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::ReinterpretCastOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createReinterpretCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-RESHAPE // -------------------------------------------------------------//
class ReshapeOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ReshapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ReshapeOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::ReshapeOp> clone() const { return std::static_pointer_cast<MULA::memref::ReshapeOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::ReshapeOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createReshapeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-STORE // -------------------------------------------------------------//
class StoreOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        StoreOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~StoreOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::StoreOp> clone() const { return std::static_pointer_cast<MULA::memref::StoreOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::StoreOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createStoreOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-TRANSPOSE // -------------------------------------------------------------//
class TransposeOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        TransposeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~TransposeOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::TransposeOp> clone() const { return std::static_pointer_cast<MULA::memref::TransposeOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::TransposeOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createTransposeOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-VIEW // -------------------------------------------------------------//
class ViewOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ViewOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::ViewOp> clone() const { return std::static_pointer_cast<MULA::memref::ViewOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::ViewOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-MEMREF-SUBVIEW // -------------------------------------------------------------//
class SubViewOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        SubViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~SubViewOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::memref::SubViewOp> clone() const { return std::static_pointer_cast<MULA::memref::SubViewOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::memref::SubViewOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createSubViewOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

} // namespace memref

} // namespace MULA
#endif // __HWACC_MLIR_MEMREF_HH__
