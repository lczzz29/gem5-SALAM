#ifndef __HWACC_MLIR_OPERATION_HH__
#define __HWACC_MLIR_OPERATION_HH__

#include <cstdlib>
#include <iostream>
// #include <llvm/IR/Value.h>
// #include <llvm/IR/Instruction.h>
// #include <llvm/IR/Instructions.h>
#include "mlir/IR/Operation.h"
#include "mlir/IR/Value.h"
#include "mlir/IR/Block.h"
#include "mlir/IR/Region.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/Dialect/SCF/IR/SCF.h"
// dialect includes
#include "dialect/memref.hh"
#include "dialect/arith.hh"
#include "dialect/func.hh"
#include "dialect/scf.hh"
#include "dialect/builtin.hh"
#include "irmap.hh"
#include "basic_block.hh"
#include "operand.hh"
#include "debug_flags.hh"
#include "value.hh"
#include "mem_request.hh"
#include "../../HWModeling/src/hw_interface.hh"

namespace MULA {

class Region; // Required Declaration
class Block; // Required Declaration



//---------------------------------------------------------------------------//
//--------- Operation Base Class ------------------------------------------//
//---------------------------------------------------------------------------//


class Operation
{
    private:
        std::map<uint64_t, std::shared_ptr<MULA::Operation>> dynamicDependencies;
        std::vector<std::shared_ptr<MULA::Operation>> dynamicUsers;
        std::vector<std::shared_ptr<MULA::Region>> regionList;
        uint64_t mlirOpCode;
        uint64_t cycleCount;
        uint64_t currentCycle;
        uint64_t functional_unit = 0;
        uint64_t uid = 0;
        std::string opName;
        std::string dialectName;
        HWInterface* hw_interface;

    protected:
        gem5::SimObject * owner;
        ValueListType staticDependencies;
        // Operands
        std::vector<MULA::Operand> operands;
        std::vector<MULA::Value> results;

        bool dbg = false;
        bool running = false;
        class Operation_Debugger: public Debugger
        {
            public:
                Operation_Debugger();
                ~Operation_Debugger() = default;
                virtual void dumper(MULA::Operation *op);
        };
        Operation_Debugger* op_dbg;
        bool launched = false;
        bool committed = false;
        bool isready = false;
    public:
        Operation(uint64_t id, gem5::SimObject * owner, bool dbg); //
        Operation(uint64_t id, gem5::SimObject * owner, bool dbg, uint64_t OpCode); //
        Operation(uint64_t id, gem5::SimObject * owner, bool dbg, uint64_t OpCode, uint64_t cycles); //
        Operation(uint64_t id, gem5::SimObject * owner, bool dbg, uint64_t OpCode, uint64_t cycles, uint64_t functional_unit); //
        ~Operation(); //
        bool operator == (const std::shared_ptr<MULA::Operation> op) const { return this->getUID() == op->getUID(); }
        bool operator != (const std::shared_ptr<MULA::Operation> op) const { return !operator==(op); }
        virtual void initialize(mlir::Operation * op, IRMap * irmap); //

        virtual std::shared_ptr<MULA::Region> getTarget()  { return nullptr; }
        uint64_t getDependencyCount() { return dynamicDependencies.size(); }
        virtual uint64_t getCycleCount() { return cycleCount; }
        uint64_t getUID() const { return uid; }
        virtual uint64_t getOpcode() { return mlirOpCode; }
        uint64_t getCurrentCycle() { return currentCycle; }
        virtual ValueListType getStaticDependencies() const { return staticDependencies; }
        std::map<uint64_t, std::shared_ptr<MULA::Operation>> getDynamicDependencies() const { return dynamicDependencies; }
        std::shared_ptr<MULA::Value> getStaticDependencies(int i) const { return staticDependencies.at(i); }
        std::shared_ptr<MULA::Operation> getDynamicDependencies(int i) const { return dynamicDependencies.at(i); }
        std::string getOpName() {return opName;}
        std::string getDialectName() {return dialectName;}

        virtual std::vector<uint64_t> runtimeInitialize();
        void removeDynamicDependency(uint64_t opuid);
        void addRuntimeDependency(std::shared_ptr<MULA::Operation> dep) {
            dynamicDependencies.insert({dep->getUID(),dep});
        }
        void addRuntimeUser(std::shared_ptr<MULA::Operation> dep) { dynamicUsers.push_back(dep); }
        void signalUsers();
        bool isCommitted() { return committed; }
        //bool hasFunctionalUnit() { return (functional_unit != 0); }
        bool hasFunctionalUnit() { return false; }

        bool debug() { return dbg; }
        void linkOperands(const MULA::Operand &newOp);
        std::vector<MULA::Operand> * getOperands() { return &operands; }
        std::vector<MULA::Value> * getResults() { return &results; }
        uint64_t getFunctionalUnit() { return functional_unit; }
        virtual bool isReturn() { return false; }
        virtual bool isTerminator() { return false; }
        // virtual bool isPhi() { return false; }
        virtual bool isCall() { return false; }
        virtual bool isBr() { return false; }
        virtual bool isLoad() { return false; }
        virtual bool isStore() {return false; }
        // virtual bool isGEP() { return false; }
        virtual bool launch();
        virtual bool commit();
        virtual bool ready();
        virtual void compute() { }
        virtual void reset();
        virtual void setOperandValue(uint64_t uid);
        virtual void dump() { if (dbg) op_dbg->dumper(this); }
        virtual bool isOperation() { return true; }
        virtual bool isLoadingInternal() { return false; }
        virtual bool isLatchingBrExiting() { return false; }
        // virtual void linkFunctionalUnit(HWInterface * hw_interface);
        std::shared_ptr<MULA::Operation> clone() const { return std::static_pointer_cast<MULA::Operation>(createClone()); }
        virtual std::shared_ptr<MULA::Operation> createClone() const { return std::shared_ptr<MULA::Operation>(new MULA::Operation(*this)); }
        virtual MemoryRequest * createMemoryRequest() { return nullptr; }

        // Functions for getting data from operands
        uint64_t getPtrOperandValue(uint64_t op_num) { return (operands.at(op_num).getPtrRegValue()); }
};

} // namespace MULA

#endif // __HWACC_MLIR_OPERATION_HH__