#ifndef __HWACC_MLIR_SCF_HH__
#define __HWACC_MLIR_SCF_HH__

#include "../operation.hh"
#include "../irmap.hh"
namespace MULA {

namespace scf {

// MULA-SCF-CONDITION // -------------------------------------------------------------//
class ConditionOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ConditionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ConditionOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        bool isTerminator() override { return true; }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::ConditionOp> clone() const { return std::static_pointer_cast<MULA::scf::ConditionOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::ConditionOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createConditionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-EXECUTEREGION // -------------------------------------------------------------//
class ExecuteRegionOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ExecuteRegionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ExecuteRegionOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::ExecuteRegionOp> clone() const { return std::static_pointer_cast<MULA::scf::ExecuteRegionOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::ExecuteRegionOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createExecuteRegionOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-FOR // -------------------------------------------------------------//
class ForOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;
        bool hasIterArgs;
        bool hasResult;

    protected:
    public:
        ForOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ForOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::ForOp> clone() const { return std::static_pointer_cast<MULA::scf::ForOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::ForOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createForOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-FORALL // -------------------------------------------------------------//
class ForallOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ForallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ForallOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::ForallOp> clone() const { return std::static_pointer_cast<MULA::scf::ForallOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::ForallOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createForallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-INPARALLEL // -------------------------------------------------------------//
class InParallelOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        InParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~InParallelOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::InParallelOp> clone() const { return std::static_pointer_cast<MULA::scf::InParallelOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::InParallelOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createInParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-IF // -------------------------------------------------------------//
class IfOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        std::shared_ptr<MULA::Operand> condition;
        std::shared_ptr<MULA::Region> thenRegion;
        std::shared_ptr<MULA::Region> elseRegion = nullptr;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;
        bool hasElse;
        bool hasResult;

    protected:
    public:
        IfOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~IfOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        std::shared_ptr<MULA::Region> getTarget() override;
        void dumper();
        std::shared_ptr<MULA::scf::IfOp> clone() const { return std::static_pointer_cast<MULA::scf::IfOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::IfOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createIfOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-INDEXSWITCH // -------------------------------------------------------------//
class IndexSwitchOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        IndexSwitchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~IndexSwitchOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::IndexSwitchOp> clone() const { return std::static_pointer_cast<MULA::scf::IndexSwitchOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::IndexSwitchOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createIndexSwitchOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-PARALLEL // -------------------------------------------------------------//
class ParallelOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ParallelOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::ParallelOp> clone() const { return std::static_pointer_cast<MULA::scf::ParallelOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::ParallelOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createParallelOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-REDUCE // -------------------------------------------------------------//
class ReduceOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ReduceOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ReduceOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::ReduceOp> clone() const { return std::static_pointer_cast<MULA::scf::ReduceOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::ReduceOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createReduceOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-REDUCERETURN // -------------------------------------------------------------//
class ReduceReturnOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ReduceReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ReduceReturnOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::ReduceReturnOp> clone() const { return std::static_pointer_cast<MULA::scf::ReduceReturnOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::ReduceReturnOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createReduceReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-WHILE // -------------------------------------------------------------//
class WhileOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        WhileOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~WhileOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::WhileOp> clone() const { return std::static_pointer_cast<MULA::scf::WhileOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::WhileOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createWhileOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-SCF-YIELD // -------------------------------------------------------------//
class YieldOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        YieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~YieldOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        bool isTerminator() override { return true; }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::scf::YieldOp> clone() const { return std::static_pointer_cast<MULA::scf::YieldOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::scf::YieldOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createYieldOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

} // namespace scf

} // namespace MULA
#endif // __HWACC_MLIR_SCF_HH__
