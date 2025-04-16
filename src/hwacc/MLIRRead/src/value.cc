#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "sim/sim_object.hh"
#include "value.hh"

MULA::Value::Value(uint64_t id, gem5::SimObject * _owner, bool _dbg) {
    uid = id;
    size = 0;
    owner = _owner;
    dbg = _dbg;
}

MULA::Value::~Value()
{
}

// copy constructor
MULA::Value::Value(const Value &copy_val)
{
    uid = copy_val.uid;
    returnReg = copy_val.returnReg;
    valueTy = copy_val.valueTy;
    size = copy_val.size;
    ir_string = copy_val.ir_string;
    ir_stub = copy_val.ir_stub;
    owner = copy_val.owner;
    dbg = copy_val.dbg;
}

MULA::Value::Value(std::shared_ptr<MULA::Value> copy_val)
{
    uid = copy_val->getUID();
    returnReg = copy_val->getReg();
    valueTy = copy_val->getType();
    size = copy_val->getSize();
    ir_string = copy_val->getIRString();
    ir_stub = copy_val->getIRStub();
    owner = copy_val->getOwner();
    dbg = copy_val->debug();
}

// operator equals
MULA::Value&
MULA::Value::operator = (Value &copy_val)
{
    uid = copy_val.uid;
    returnReg = copy_val.returnReg;
    valueTy = copy_val.valueTy;
    size = copy_val.size;
    ir_string = copy_val.ir_string;
    ir_stub = copy_val.ir_stub;
    return *this;
}

MULA::Value::Value_Debugger::Value_Debugger()
{
}

void
MULA::Value::Value_Debugger::dumper(MULA::Value *value)
{
}

void
MULA::Value::initialize(mlir::Value * irval, MULA::IRMap * irMap) {
    mlir::Type valueTy = irval->getType();
    if (valueTy.isa<mlir::IndexType>()) {
        size = 64; //We assume a 64-bit memory address space
    } else if(valueTy.isa<mlir::IntegerType>()) {
        size = valueTy.getIntOrFloatBitWidth();
    } else if(valueTy.isa<mlir::MemRefType>()) {
        size = 64; //We assume a 64-bit memory address space
    }
    // Link Return Register
    if (size>0) addRegister(valueTy, true);

    std::string tmpStr1;
    llvm::raw_string_ostream ss(tmpStr1);
    ss << *irval;
    ir_string = ss.str();

    std::string tmpStr2;
    llvm::raw_string_ostream ss2(tmpStr2);
    mlir::AsmState state(irval->getContext());
    irval->printAsOperand(ss2, state);
    ir_stub = ss2.str();
}


#if USE_LLVM_AP_VALUES
    void
    SALAM::Value::setRegisterValue(const llvm::APInt &data) {

        if (dbg) DPRINTFS(Runtime, owner, "| APInt Register\n");
        if (returnReg->isInt()) {
            returnReg->writeIntData(data);
        } else {
            if (dbg) DPRINTFS(Runtime, owner, "Unsupported type for register operation. \
                Tried to place integer data in non-integer register.\n");
        }
    }
    void
    SALAM::Value::setRegisterValue(const llvm::APFloat &data) {

        if (dbg) DPRINTFS(Runtime, owner, "| APFloat Register\n");
        if (returnReg->isFP()) {
            returnReg->writeFloatData(data);
        } else {
            if (dbg) DPRINTFS(Runtime, owner, "Unsupported type for register operation. \
                Tried to place float data in non-float register.\n");
        }
    }
#endif

void
MULA::Value::setRegisterValue(const uint64_t data) {
    if (returnReg->isIndex()) {
        if (dbg) DPRINTFS(Runtime, owner, "| Index Register\n");
        returnReg->writeIndexData(data);
    } else {
        if (returnReg->isInt()) {
            if (dbg) DPRINTFS(Runtime, owner, "| Int Register\n");
            returnReg->writeIntData(data, getSizeInBytes());
        } else {
            if (dbg) DPRINTFS(Runtime, owner, "| FP Register\n");
            returnReg->writeFloatData(data, getSizeInBytes());
        }
    }
}
void
MULA::Value::setRegisterValue(uint8_t * data) {
    if (dbg) DPRINTFS(Runtime, owner, "| Set Register Data - ");
    if (valueTy.isa<mlir::FloatType>()) {
        if (dbg) DPRINTFS(Runtime, owner, "Float\n");
        returnReg->writeFloatData(*(uint64_t *)data, (size_t)4);
    } else if (valueTy.isa<mlir::IntegerType>()) {
        if (dbg) DPRINTFS(Runtime, owner, "Integer Type | Size = %d\n", size);
        returnReg->writeIntData(*(uint64_t *)data, (size_t)getSizeInBytes());
    } else if (valueTy.isa<mlir::IndexType>()) {
        if (dbg) DPRINTFS(Runtime, owner, "Index Type\n");
        returnReg->writeIndexData(*(uint64_t *)data);
    } else {
        assert(0 && "Unsupported type for register operation");
    }
}

void
MULA::Value::setRegisterValue(bool data) {
    if (dbg) DPRINTFS(Runtime, owner, "| Int Register\n");
    if (returnReg->isInt()) {
    #if USE_LLVM_AP_VALUES
        if (data) {
            setRegisterValue(llvm::APInt::getAllOnesValue(1));
        } else {
            setRegisterValue(llvm::APInt::getNullValue(1));
        }
    #else
        if (data) {
            setRegisterValue((uint64_t)1);
        } else {
            setRegisterValue((uint64_t)0);
        }
    #endif
    } else {
        if (dbg) DPRINTFS(Runtime, owner, "Unsupported type for register operation. \
            Tried to place integer data in non-integer register.\n");
    }
}

void
MULA::Value::setRegisterValue(std::shared_ptr<MULA::Register> reg) {
    if (reg->isIndex()) {
        setRegisterValue((reg->getIndexData()));
    } else if (reg->isInt()) {
        setRegisterValue((reg->getIntData()));
    } else if (reg->isFP()) {
        setRegisterValue((reg->getFloatData()));
    } else {
        assert(0 && "Unsupported type for register operation");
    }
    if (dbg) DPRINTFS(Runtime, owner, "||==setRegisterValue====\n");
}

void
MULA::Value::addRegister(mlir::Type type, bool isTracked) {
    if (auto memRefType = type.dyn_cast<mlir::MemRefType>()) {
        returnReg = std::make_shared<IndexRegister>(isTracked);
    } else if (auto intType = type.dyn_cast<mlir::IntegerType>()) {
        returnReg = std::make_shared<APIntRegister>(intType.getWidth(), isTracked);
    } else if (type.isa<mlir::FloatType>()) {
        returnReg = std::make_shared<APFloatRegister>(type, isTracked);
    } else {
        returnReg = nullptr;
    }
}

#if USE_LLVM_AP_VALUES
    void
    MULA::Value::addAPIntRegister(const llvm::APInt & val) {

        assert(irtype->isIntegerTy());
        returnReg = std::make_shared<APIntRegister>(val);
    }
    void
    MULA::Value::addAPIntRegister(const llvm::APSInt & val) {

        assert(irtype->isIntegerTy());
        returnReg = std::make_shared<APIntRegister>(val);
    }
    void
    MULA::Value::addAPFloatRegister(const llvm::APFloat & val) {

        assert(irtype->isFloatingPointTy());
        returnReg = std::make_shared<APFloatRegister>(val);
    }
#else
    void
    MULA::Value::addAPIntRegister(const uint64_t & val) {
        assert(valueTy.isa<mlir::IntegerType>());
        uint64_t bitmask = 0;
        assert((size <= 64) &&
            "Only 64-bit and smaller values are \
             supported when not using AP values.");
        bitmask = (bitmask - 1) >> (64 - size);
        returnReg = std::make_shared<APIntRegister>(val & bitmask);
    }
    void
    MULA::Value::addAPFloatRegister(const uint64_t & val) {

        assert(valueTy.isa<mlir::FloatType>());
        uint64_t bitmask = 0;
        assert((size <= 64) &&
            "Only 64-bit and smaller values are \
            supported when not using AP values.");
        bitmask = (bitmask - 1) >> (64 - size);
        returnReg = std::make_shared<APFloatRegister>(val & bitmask);
    }
#endif