#include "operand.hh"
#include "sim/sim_object.hh"


MULA::Constant::Constant(uint64_t id, gem5::SimObject * owner, bool dbg) :
                          Value(id, owner, dbg)
{
}

bool
MULA::Constant::checkConstantExpr(mlir::Value * irval) {
    if (auto op = mlir::dyn_cast<mlir::arith::ExtSIOp>(irval)) {
        if (op->getIn().getDefiningOp<mlir::arith::ConstantOp>()) {
            return true;
        }
    } else if (auto op = mlir::dyn_cast<mlir::arith::IndexCastOp>(irval)) {
        if (op->getIn().getDefiningOp<mlir::arith::ConstantOp>()) {
            return true;
        }
    } else if (auto op = mlir::dyn_cast<mlir::arith::TruncIOp>(irval)) {
        if (op->getIn().getDefiningOp<mlir::arith::ConstantOp>()) {
            return true;
        }
    }
    return false;
}

void
MULA::Constant::initialize( mlir::Value * irval,
                            MULA::IRMap * irmap)
{
    //Initialize MULA::Value
    MULA::Value::initialize(irval, irmap);
    // Parse the constant value
    mlir::Operation * op = irval->getDefiningOp();
    assert(op);
    // Check if the value is a constant
    mlir::arith::ConstantOp co = irval->getDefiningOp<mlir::arith::ConstantOp>();
    // mlir::Type irtype = co->getResult().getType();
    mlir::Attribute attr = co.getValue();
    if (co) {
        // The value is defined by a constant operation
        // Get its value and store it in constValue
        if (auto intAttr = attr.dyn_cast<mlir::IntegerAttr>()) {
            auto intValue = intAttr.getValue();
            int64_t intVal = intValue.getSExtValue();
            addAPIntRegister((uint64_t)intVal);
        } else if (auto floatAttr = attr.dyn_cast<mlir::FloatAttr>()) {
            llvm::APFloat floatValue = floatAttr.getValue();
            double floatVal = floatValue.convertToDouble();
            addAPFloatRegister(floatVal);
        }
    }
    // } else if (checkConstantExpr(irval)) {
    //     // The constant is an expression. We need to parse the expression
    //     for (auto oprnd : op->getOperands()) {
    //         // Iterate over operands and add
    //         // new values to our map and value list
    //         auto mapit = irmap->findValue(&oprnd);
    //         // if (mapit == nullptr) {
    //         //     uint64_t id = irmap->getValueList().back()->getUID() + 1;
    //         //     std::shared_ptr<MULA::Constant> con =
    //         //         std::make_shared<MULA::Constant>(id, owner, dbg);
    //         //         irmap->pushValue();
    //         //     irmap->insert(MULA::irvmaptype(&oprnd, con));
    //         //     operands.push_back(con);
    //         //     con->initialize(&oprnd, irmap, values);
    //         // } else {
    //         std::shared_ptr<MULA::Value> opval = mapit;
    //         operands.push_back(opval);
    //         // }
    //     }

    // #if USE_LLVM_AP_VALUES
    //     #if (LLVM_VERSION_MAJOR <= 9)
    //         auto rounding = llvm::APFloat::roundingMode::rmNearestTiesToEven;
    //     #else
    //         auto rounding = llvm::APFloat::roundingMode::NearestTiesToEven;
    //     #endif
    // #endif

    //     if (auto ce = irval->dyn_cast<mlir::arith::ExtSIOp>()) {
    //         #if USE_LLVM_AP_VALUES
    //             auto opdata = operands.front()->getIntRegValue();
    //             opdata.setIsSigned(true);
    //             addAPIntRegister(opdata.extend(size));
    //         #else
    //             int64_t tmp = operands.front()->getSIntRegValue();
    //             addAPIntRegister((uint64_t)tmp);
    //         #endif
    //     } else if (auto ce = irval->dyn_cast<mlir::arith::IndexCastOp>()) {
    //         // TODO: Handle index cast of other constant expressions like ptrtoint
    //         auto opdata = operands.front()->getIntRegValue();
    //         #if USE_LLVM_AP_VALUES
    //             assert(opdata.isUnsigned());
    //             int64_t tmp = opdata.getExtValue();
    //             addAPIntRegister(opdata);
    //         #else
    //             addAPIntRegister(opdata);
    //         #endif
    //     } else if (auto ce = irval->dyn_cast<mlir::arith::TruncIOp>()) {
    //         auto opdata = operands.front()->getIntRegValue();
    //         #if USE_LLVM_AP_VALUES
    //             addAPIntRegister(opdata.trunc(size));
    //         #else
    //             addAPIntRegister(opdata);
    //         #endif
    //     } else {
    //     assert(0); // The value is not a supported type of llvm::Constant
    //     }
    // }
}

MULA::GlobalConstant::GlobalConstant(uint64_t id, gem5::SimObject * owner, bool dbg) :
                                      Constant(id, owner, dbg)
{
}

// TODO: Handle global constant initialization in MLIR based on memref.global
// in Constant::initailze(..)
// Currently no benchmarks contains global constants when modeling accs
void
MULA::GlobalConstant::initialize(mlir::Value * irval,
                                  MULA::IRMap * irmap)
{
    // Parse the initializer of the value
    mlir::memref::GlobalOp glb = irval->getDefiningOp<mlir::memref::GlobalOp>();
    assert(glb);
    assert(!glb.isUninitialized());
    // glb->getInitializer()->print(llvm::outs());

    //Initialize MULA::ConstantData
    MULA::Constant::initialize(irval, irmap);
}

MULA::Argument::Argument(uint64_t id, gem5::SimObject * owner, bool dbg) :
                          Value(id, owner, dbg)
{
}

void
MULA::Argument::initialize(mlir::Value * irval, MULA::IRMap * irmap)
{
    //Initialize MULA::Value
    MULA::Value::initialize(irval, irmap);
    addRegister(irval->getType());
}

MULA::Operand::Operand_Debugger::Operand_Debugger()
{

}

void
MULA::Operand::Operand_Debugger::dumper(Operand * op)
{

}

// copy constructor
MULA::Operand::Operand(const MULA::Operand &copy_val):
           MULA::Value(copy_val)
{
    lockedValue = copy_val.lockedValue;
    set = copy_val.set;
}

// copy constructor from base
MULA::Operand::Operand(const MULA::Value &copy_val):
           MULA::Value(copy_val)
{ // Update here for values in the copied value base class
    initOperandReg();
}

MULA::Operand::Operand(std::shared_ptr<MULA::Value> copy_val):
            MULA::Value(copy_val)
{
    initOperandReg();
}

// operator equals
MULA::Operand&
MULA::Operand::operator = (MULA::Operand &copy_val)
{
    uid = copy_val.uid;
      returnReg = copy_val.returnReg;
    valueTy = copy_val.valueTy;
    size = copy_val.size;
    lockedValue = copy_val.lockedValue;
    set = copy_val.set;
    return *this;
}

void
MULA::Operand::initOperandReg()
{
    bool istracked = false;
    if (returnReg->isIndex()) {
        if (dbg) DPRINTFS(Runtime, owner, "Operand Idx Register Initialized\n");
        lockedValue = std::make_shared<IndexRegister>(istracked);
    } else if (returnReg->isInt()) {
        if (dbg) DPRINTFS(Runtime, owner, "Operand Int Register Initialized\n");
        lockedValue = std::make_shared<APIntRegister>(size, istracked);
    } else if (returnReg->isFP()) {
        if (dbg) DPRINTFS(Runtime, owner, "Operand FP Register Initialized\n");
        lockedValue =
            std::make_shared<APFloatRegister>(valueTy, istracked);
    } else {
        if (dbg) DPRINTFS(Runtime, owner, "Invalid register type. Dumping Operand details\n");
        dump();
        assert(0); // Type is invalid for a register
    }
}

void
MULA::Operand::initialize(mlir::Value * irval, MULA::IRMap * irmap)
{
    MULA::Value::initialize(irval, irmap);
}

void
MULA::Operand::updateOperandRegister() {
    assert(lockedValue);
    if (lockedValue->isIndex()) {
        lockedValue->writeIndexData(returnReg->getIndexData(true),
                                  getSizeInBytes());
    } else if (lockedValue->isInt()) {
        lockedValue->writeIntData(returnReg->getIntData(true));
    } else if (lockedValue->isFP()) {
        lockedValue->writeFloatData(returnReg->getFloatData(true));
    }
}
