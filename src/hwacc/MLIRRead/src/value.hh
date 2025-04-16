#ifndef __MULA_MLIR_VALUE_HH__
#define __MULA_MLIR_VALUE_HH__

#include "llvm-c/Core.h"
#include "mlir/IR/Value.h"
#include "mlir/IR/Types.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/Support/TypeID.h"
#include "mlir/IR/AsmState.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/Block.h"
#include "mlir/IR/Region.h"
#include "mlir/IR/Operation.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/MemRef/IR/MemRef.h"

#include <map>
#include <memory>
#include <vector>

#include "debug_flags.hh"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/APSInt.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Value.h"
#include "registers.hh"
#include "irmap.hh"

namespace gem5
{
    class SimObject;
}

namespace MULA
{

class Value
{
    public:

    protected:
        uint64_t uid = 0;
        uint64_t size = 0;
        gem5::SimObject * owner;
        std::string ir_string;
        std::string ir_stub;
        mlir::Type valueTy;
        std::shared_ptr<MULA::Register> returnReg;
        bool dbg = false;
        bool inst = false;

        void addRegister(mlir::Type type, bool isTracked=true);
    #if USE_LLVM_AP_VALUES
        void addAPIntRegister(const llvm::APInt & val);
        void addAPIntRegister(const llvm::APSInt & val);
        void addAPFloatRegister(const llvm::APFloat & val);
    #else
        void addAPIntRegister(const uint64_t & val);
        void addAPFloatRegister(const uint64_t & val);
    #endif
        void addIndexRegister(mlir::IndexType type, uint64_t value);
        
        class Value_Debugger: public Debugger
        {
            public:
                Value_Debugger();
                ~Value_Debugger() = default;
                virtual void dumper(MULA::Value * value);
        };

        Value_Debugger* value_dbg;
        Value(const MULA::Value &copy_val);
        Value(std::shared_ptr<MULA::Value> copy_val);

    public:
        /** Class Constructor.
         * @param id
         */
        Value(uint64_t id, gem5::SimObject * _owner, bool _dbg);
        Value& operator = (Value &copy_val);
        bool operator == (const Value &v) { return uid == v.uid; }
        ~Value();
        virtual void initialize(mlir::Value *irval,
                                MULA::IRMap *irMap);
        uint64_t getSize() { return size; }
        uint64_t getSizeInBytes() {
            if (size==0)
                return 0;
            else
                return ((size - 1) >> 3) + 1;
        }
        uint64_t getUID() const { return uid; }
        std::shared_ptr<MULA::Register> getReg() { return returnReg; }
        mlir::Type getType() { return valueTy; }
        std::string getIRString() { return ir_string; }
        std::string getIRStub() { return ir_stub; }
        gem5::SimObject * getOwner() { return owner; }
        bool debug() { return dbg; }

        // Helper functions for setting the value of the return register directly from the value
        // Using these functions will increment the write counters on tracked registers
        // If you'd like to avoid incrementing write counters, directly pull the register and
        // use its appropriate write function
    #if USE_LLVM_AP_VALUES
        void setRegisterValue(const llvm::APInt &data);
        void setRegisterValue(const llvm::APFloat &data);
    #endif
        void setRegisterValue(const uint64_t data);
        void setRegisterValue(uint8_t * data);
        void setRegisterValue(bool data);
        void setRegisterValue(std::shared_ptr<MULA::Register> reg);

        // Helper functions for getting the value of the return register directly from the value
        // Using these functions will increment the read counters on tracked registers
        // If you'd like to avoid incrementing read counters, directly pull the register and
        // use its appropriate read cfunction
    #if USE_LLVM_AP_VALUES
        virtual llvm::APFloat getFloatRegValue() { return returnReg->getFloatData(); }
        virtual llvm::APSInt getIntRegValue() { return returnReg->getIntData(); }
    #else
        virtual uint64_t getPtrRegValue() { return returnReg->getPtrData(); }
        virtual uint64_t getFloatRegValue() { return returnReg->getFloatData(); }
        virtual float getFloatFromReg() { return returnReg->getFloat(); }
        virtual double getDoubleFromReg() { return returnReg->getDouble(); }
        virtual uint64_t getIntRegValue() { return returnReg->getIntData(); }
        virtual uint64_t getUIntRegValue() { return returnReg->getUnsignedInt(); }
        virtual int64_t getSIntRegValue() { return returnReg->getSignedInt(size); }
        virtual uint64_t getIndexRegValue() { return returnReg->getIndexData(); }
    #endif

        virtual bool isConstant() {return false;}
        virtual bool isGlobalConstant() {return false; }
        virtual bool isArgument() {return false;}
        virtual bool isFunction() {return false;}
        virtual bool isBlock() {return false;}
        virtual bool isRegion() {return false;}
        virtual bool isOperation() {return false;}
        virtual uint64_t getOpcode() {return -1;}

        void value_dump() { if (dbg) value_dbg->dumper(this); }
        std::string registerDataString() { return returnReg->dataString(); }
        std::shared_ptr<MULA::Value> clone() const { return createClone(); }
        virtual std::shared_ptr<MULA::Value> createClone() const { return std::shared_ptr<MULA::Value>(new MULA::Value(*this)); }

};

} // End MULA Namespace


#endif //__MULA_MLIR_VALUE_HH__
