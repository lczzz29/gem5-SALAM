#ifndef __HWACC_MLIR_ARITH_HH__
#define __HWACC_MLIR_ARITH_HH__

#include "../operation.hh"
#include "../irmap.hh"
namespace MULA {

namespace arith {

// MULA-ARITH-ADDF // -------------------------------------------------------------//
class AddFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AddFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AddFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::AddFOp> clone() const { return std::static_pointer_cast<MULA::arith::AddFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::AddFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAddFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-ADDI // -------------------------------------------------------------//
class AddIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AddIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AddIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::AddIOp> clone() const { return std::static_pointer_cast<MULA::arith::AddIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::AddIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAddIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-ADDUIEXTENDED // -------------------------------------------------------------//
class AddUIExtendedOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AddUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AddUIExtendedOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::AddUIExtendedOp> clone() const { return std::static_pointer_cast<MULA::arith::AddUIExtendedOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::AddUIExtendedOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAddUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-ANDI // -------------------------------------------------------------//
class AndIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        AndIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~AndIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::AndIOp> clone() const { return std::static_pointer_cast<MULA::arith::AndIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::AndIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createAndIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-BITCAST // -------------------------------------------------------------//
class BitcastOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        BitcastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~BitcastOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::BitcastOp> clone() const { return std::static_pointer_cast<MULA::arith::BitcastOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::BitcastOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createBitcastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-CEILDIVSI // -------------------------------------------------------------//
class CeilDivSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CeilDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CeilDivSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::CeilDivSIOp> clone() const { return std::static_pointer_cast<MULA::arith::CeilDivSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::CeilDivSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCeilDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-CEILDIVUI // -------------------------------------------------------------//
class CeilDivUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CeilDivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CeilDivUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::CeilDivUIOp> clone() const { return std::static_pointer_cast<MULA::arith::CeilDivUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::CeilDivUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCeilDivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-CMPF // -------------------------------------------------------------//
class CmpFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CmpFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CmpFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::CmpFOp> clone() const { return std::static_pointer_cast<MULA::arith::CmpFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::CmpFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCmpFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-CMPI // -------------------------------------------------------------//
class CmpIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CmpIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CmpIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::CmpIOp> clone() const { return std::static_pointer_cast<MULA::arith::CmpIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::CmpIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCmpIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-CONSTANT // -------------------------------------------------------------//
class ConstantOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ConstantOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ConstantOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::ConstantOp> clone() const { return std::static_pointer_cast<MULA::arith::ConstantOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::ConstantOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createConstantOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-DIVF // -------------------------------------------------------------//
class DivFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        DivFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~DivFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::DivFOp> clone() const { return std::static_pointer_cast<MULA::arith::DivFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::DivFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createDivFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-DIVSI // -------------------------------------------------------------//
class DivSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        DivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~DivSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::DivSIOp> clone() const { return std::static_pointer_cast<MULA::arith::DivSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::DivSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-DIVUI // -------------------------------------------------------------//
class DivUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        DivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~DivUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::DivUIOp> clone() const { return std::static_pointer_cast<MULA::arith::DivUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::DivUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createDivUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-EXTF // -------------------------------------------------------------//
class ExtFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ExtFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ExtFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::ExtFOp> clone() const { return std::static_pointer_cast<MULA::arith::ExtFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::ExtFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createExtFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-EXTSI // -------------------------------------------------------------//
class ExtSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ExtSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ExtSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::ExtSIOp> clone() const { return std::static_pointer_cast<MULA::arith::ExtSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::ExtSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createExtSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-EXTUI // -------------------------------------------------------------//
class ExtUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ExtUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ExtUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::ExtUIOp> clone() const { return std::static_pointer_cast<MULA::arith::ExtUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::ExtUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createExtUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-FLOORDIVSI // -------------------------------------------------------------//
class FloorDivSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        FloorDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~FloorDivSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::FloorDivSIOp> clone() const { return std::static_pointer_cast<MULA::arith::FloorDivSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::FloorDivSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createFloorDivSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-FPTOSI // -------------------------------------------------------------//
class FPToSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        FPToSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~FPToSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::FPToSIOp> clone() const { return std::static_pointer_cast<MULA::arith::FPToSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::FPToSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createFPToSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-FPTOUI // -------------------------------------------------------------//
class FPToUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        FPToUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~FPToUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::FPToUIOp> clone() const { return std::static_pointer_cast<MULA::arith::FPToUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::FPToUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createFPToUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-INDEXCAST // -------------------------------------------------------------//
class IndexCastOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        IndexCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~IndexCastOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::IndexCastOp> clone() const { return std::static_pointer_cast<MULA::arith::IndexCastOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::IndexCastOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createIndexCastOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-INDEXCASTUI // -------------------------------------------------------------//
class IndexCastUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        IndexCastUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~IndexCastUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::IndexCastUIOp> clone() const { return std::static_pointer_cast<MULA::arith::IndexCastUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::IndexCastUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createIndexCastUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MAXIMUMF // -------------------------------------------------------------//
class MaximumFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MaximumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MaximumFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MaximumFOp> clone() const { return std::static_pointer_cast<MULA::arith::MaximumFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MaximumFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMaximumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MAXNUMF // -------------------------------------------------------------//
class MaxNumFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MaxNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MaxNumFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MaxNumFOp> clone() const { return std::static_pointer_cast<MULA::arith::MaxNumFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MaxNumFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMaxNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MAXSI // -------------------------------------------------------------//
class MaxSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MaxSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MaxSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MaxSIOp> clone() const { return std::static_pointer_cast<MULA::arith::MaxSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MaxSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMaxSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MAXUI // -------------------------------------------------------------//
class MaxUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MaxUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MaxUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MaxUIOp> clone() const { return std::static_pointer_cast<MULA::arith::MaxUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MaxUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMaxUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MINIMUMF // -------------------------------------------------------------//
class MinimumFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MinimumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MinimumFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MinimumFOp> clone() const { return std::static_pointer_cast<MULA::arith::MinimumFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MinimumFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMinimumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MINNUMF // -------------------------------------------------------------//
class MinNumFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MinNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MinNumFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MinNumFOp> clone() const { return std::static_pointer_cast<MULA::arith::MinNumFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MinNumFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMinNumFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MINSI // -------------------------------------------------------------//
class MinSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MinSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MinSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MinSIOp> clone() const { return std::static_pointer_cast<MULA::arith::MinSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MinSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMinSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MINUI // -------------------------------------------------------------//
class MinUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MinUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MinUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MinUIOp> clone() const { return std::static_pointer_cast<MULA::arith::MinUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MinUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMinUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MULF // -------------------------------------------------------------//
class MulFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MulFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MulFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MulFOp> clone() const { return std::static_pointer_cast<MULA::arith::MulFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MulFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMulFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MULI // -------------------------------------------------------------//
class MulIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MulIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MulIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MulIOp> clone() const { return std::static_pointer_cast<MULA::arith::MulIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MulIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMulIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MULSIEXTENDED // -------------------------------------------------------------//
class MulSIExtendedOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MulSIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MulSIExtendedOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MulSIExtendedOp> clone() const { return std::static_pointer_cast<MULA::arith::MulSIExtendedOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MulSIExtendedOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMulSIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-MULUIEXTENDED // -------------------------------------------------------------//
class MulUIExtendedOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        MulUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~MulUIExtendedOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::MulUIExtendedOp> clone() const { return std::static_pointer_cast<MULA::arith::MulUIExtendedOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::MulUIExtendedOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createMulUIExtendedOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-NEGF // -------------------------------------------------------------//
class NegFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        NegFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~NegFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::NegFOp> clone() const { return std::static_pointer_cast<MULA::arith::NegFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::NegFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createNegFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-ORI // -------------------------------------------------------------//
class OrIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        OrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~OrIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::OrIOp> clone() const { return std::static_pointer_cast<MULA::arith::OrIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::OrIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createOrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-REMF // -------------------------------------------------------------//
class RemFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        RemFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~RemFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::RemFOp> clone() const { return std::static_pointer_cast<MULA::arith::RemFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::RemFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createRemFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-REMSI // -------------------------------------------------------------//
class RemSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        RemSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~RemSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::RemSIOp> clone() const { return std::static_pointer_cast<MULA::arith::RemSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::RemSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createRemSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-REMUI // -------------------------------------------------------------//
class RemUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        RemUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~RemUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::RemUIOp> clone() const { return std::static_pointer_cast<MULA::arith::RemUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::RemUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createRemUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-SELECT // -------------------------------------------------------------//
class SelectOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        SelectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~SelectOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::SelectOp> clone() const { return std::static_pointer_cast<MULA::arith::SelectOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::SelectOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createSelectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-SHLI // -------------------------------------------------------------//
class ShLIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ShLIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ShLIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::ShLIOp> clone() const { return std::static_pointer_cast<MULA::arith::ShLIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::ShLIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createShLIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-SHRSI // -------------------------------------------------------------//
class ShRSIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ShRSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ShRSIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::ShRSIOp> clone() const { return std::static_pointer_cast<MULA::arith::ShRSIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::ShRSIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createShRSIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-SHRUI // -------------------------------------------------------------//
class ShRUIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ShRUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ShRUIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::ShRUIOp> clone() const { return std::static_pointer_cast<MULA::arith::ShRUIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::ShRUIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createShRUIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-SITOFP // -------------------------------------------------------------//
class SIToFPOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        SIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~SIToFPOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::SIToFPOp> clone() const { return std::static_pointer_cast<MULA::arith::SIToFPOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::SIToFPOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createSIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-SUBF // -------------------------------------------------------------//
class SubFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        SubFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~SubFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::SubFOp> clone() const { return std::static_pointer_cast<MULA::arith::SubFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::SubFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createSubFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-SUBI // -------------------------------------------------------------//
class SubIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        SubIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~SubIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::SubIOp> clone() const { return std::static_pointer_cast<MULA::arith::SubIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::SubIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createSubIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-TRUNCF // -------------------------------------------------------------//
class TruncFOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        TruncFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~TruncFOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::TruncFOp> clone() const { return std::static_pointer_cast<MULA::arith::TruncFOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::TruncFOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createTruncFOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-TRUNCI // -------------------------------------------------------------//
class TruncIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        TruncIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~TruncIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::TruncIOp> clone() const { return std::static_pointer_cast<MULA::arith::TruncIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::TruncIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createTruncIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-UITOFP // -------------------------------------------------------------//
class UIToFPOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        UIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~UIToFPOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::UIToFPOp> clone() const { return std::static_pointer_cast<MULA::arith::UIToFPOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::UIToFPOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createUIToFPOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-ARITH-XORI // -------------------------------------------------------------//
class XOrIOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        XOrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~XOrIOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::arith::XOrIOp> clone() const { return std::static_pointer_cast<MULA::arith::XOrIOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::arith::XOrIOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createXOrIOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

} // namespace arith

} // namespace MULA
#endif // __HWACC_MLIR_ARITH_HH__
