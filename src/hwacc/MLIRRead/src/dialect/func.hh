#ifndef __HWACC_MLIR_FUNC_HH__
#define __HWACC_MLIR_FUNC_HH__

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "../operation.hh"
#include "../irmap.hh"
#include "../block.hh"

namespace MULA {

namespace func {

// MULA-FUNC-CALLINDIRECT // -------------------------------------------------------------//
class CallIndirectOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        CallIndirectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CallIndirectOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::func::CallIndirectOp> clone() const { return std::static_pointer_cast<MULA::func::CallIndirectOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::func::CallIndirectOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCallIndirectOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-FUNC-CALL // -------------------------------------------------------------//
class CallOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;
        std::shared_ptr<MULA::func::FuncOp> callee;

    protected:
    public:
        CallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~CallOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        bool isCall() override { return true; }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::func::FuncOp> getCalleeValue() { return callee; }
        bool hasResult;
        std::shared_ptr<MULA::func::CallOp> clone() const { return std::static_pointer_cast<MULA::func::CallOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::func::CallOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createCallOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-FUNC-CONSTANT // -------------------------------------------------------------//
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
        std::shared_ptr<MULA::func::ConstantOp> clone() const { return std::static_pointer_cast<MULA::func::ConstantOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::func::ConstantOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createConstantOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-FUNC-FUNC // -------------------------------------------------------------//
class FuncOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

        /**
         * migrated from @file function.hh
         *  
        */ 
		std::vector<std::shared_ptr<MULA::Block>> blockList;
		std::vector<std::shared_ptr<MULA::Argument>> arguments;
		bool top;
		unsigned activeInstances = 0;
		unsigned instanceLimit = 1;

    protected:
    public:
        FuncOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~FuncOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        /**
         * migrated from @file function.hh
         */
		void initialize(mlir::Operation *op, IRMap *irMap, std::string topName);
		bool isTop() { return top; }
		void setTop(bool isTop) { top = isTop; }
		virtual bool isFunction() { return true; }
		std::vector<std::shared_ptr<MULA::Block>> * getBlockList() { return &blockList; }
		std::vector<std::shared_ptr<MULA::Argument>> * getArguments() { return &arguments; }
		std::shared_ptr<MULA::Block> entry() { return blockList.front(); }
		void addInstance() { activeInstances++; }
		void removeInstance() { if (activeInstances>0) activeInstances--; }
		bool canLaunch() { return activeInstances < instanceLimit; }
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::func::FuncOp> clone() const { return std::static_pointer_cast<MULA::func::FuncOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::func::FuncOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createFuncOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

// MULA-FUNC-RETURN // -------------------------------------------------------------//
class ReturnOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ReturnOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        bool isReturn() override { return true; }
        std::shared_ptr<MULA::func::ReturnOp> clone() const { return std::static_pointer_cast<MULA::func::ReturnOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::func::ReturnOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createReturnOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

} // namespace func

} // namespace MULA
#endif // __HWACC_MLIR_FUNC_HH__
