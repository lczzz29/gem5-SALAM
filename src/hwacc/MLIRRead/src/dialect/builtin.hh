#ifndef __HWACC_MLIR_BUILTIN_HH__
#define __HWACC_MLIR_BUILTIN_HH__

#include "../operation.hh"
#include "../irmap.hh"
namespace MULA {

namespace builtin {

// MULA-BUILTIN-MODULE // -------------------------------------------------------------//
class ModuleOp : public Operation
{
    private:
        std::vector< std::vector<uint64_t> > conditions;
        MULA::Debugger *dbgr;
        uint64_t currentCycle;

    protected:
    public:
        ModuleOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);
        ~ModuleOp() = default;
        void initialize(mlir::Operation *op,
                        MULA::IRMap *irMap
                        ) override;
        uint64_t getCycleCount() { return conditions.at(0).at(2); }
        void compute();
        void dump() { if (dbgr->enabled()) { dumper(); op_dbg->dumper(static_cast<MULA::Operation*>(this));}}
        void dumper();
        std::shared_ptr<MULA::builtin::ModuleOp> clone() const { return std::static_pointer_cast<MULA::builtin::ModuleOp>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const override { return std::shared_ptr<MULA::Operation>(new MULA::builtin::ModuleOp(*this)); }
};

std::shared_ptr<MULA::Operation>
createModuleOp(uint64_t id, gem5::SimObject * owner, bool dbg,
              uint64_t OpCode,
              uint64_t cycles,
              uint64_t fu);

} // namespace builtin

} // namespace MULA
#endif // __HWACC_MLIR_BUILTIN_HH__
