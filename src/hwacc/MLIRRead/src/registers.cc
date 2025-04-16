//------------------------------------------//
#include "registers.hh"
//------------------------------------------//

MULA::Register::Register(bool trk,
                          bool nul) :
                          tracked(trk),
                          isNULL(nul)
{
}

MULA::Register::~Register()
{
}

MULA::Register::Register_Debugger::Register_Debugger()
{
}

void
MULA::Register::Register_Debugger::dumper(MULA::Register *reg)
{
}


MULA::APFloatRegister::APFloatRegister(mlir::Type T,
                                        bool isTracked=true) :
                                        Register(isTracked)
{
    if (T.isa<mlir::Float32Type>()) {
        data = 0;
    } else if (T.isa<mlir::Float64Type>()) {
        data = 0;
    } else {
        assert(0 && "Specified Floating Point type is not supported");
    }
}

MULA::APFloatRegister::APFloatRegister(const mlir::FloatType &RHS) :
                                        Register(false)
{
    if (RHS.isa<mlir::Float32Type>()) {
        data = 0;
    } else if (RHS.isa<mlir::Float64Type>()) {
        data = 0;
    } else {
        assert(0 && "Specified Floating Point type is not supported");
    }
}

MULA::APIntRegister::APIntRegister(mlir::Type * T,
                                    bool tracked) :
                                    Register(tracked)
{
        data = 0;
}

MULA::APIntRegister::APIntRegister(const mlir::IntegerType &RHS) :
                                    Register(false)
{
    data = 0;
}

MULA::APIntRegister::APIntRegister(uint64_t bitwidth,
                                    bool tracked) :
                                    Register(tracked)
{
    data = 0;
}

MULA::IndexRegister::IndexRegister(bool tracked,
                                        bool isNull) :
                                        Register(tracked,
                                        isNull),
                                        pointer(0)
{
}

MULA::IndexRegister::IndexRegister(uint64_t val,
                                        bool tracked,
                                        bool isNull) :
                                        Register(tracked,
                                        isNull),
                                        pointer(val)
{
}

uint64_t
MULA::APFloatRegister::getFloatData(bool incReads)
{
    if (incReads && tracked) reads++;
    return data;
}

float
MULA::APFloatRegister::getFloat(bool incReads) {
    if (incReads && tracked) reads++;
    return *(float *)&data;
}

double
MULA::APFloatRegister::getDouble(bool incReads) {
    if (incReads && tracked) reads++;
    return *(double *)&data;
}

void
MULA::APFloatRegister::writeFloatData(uint64_t apf, size_t len, bool incWrites)
{
    if (incWrites && tracked) writes++;
    std::memcpy(&data, &apf, len);
    regdata = data;
}

uint64_t
MULA::APIntRegister::getIntData(bool incReads)
{
    if (incReads && tracked) reads++;
    return data;
}

uint64_t
MULA::APIntRegister::getUnsignedInt(bool incReads)
{
    if (incReads && tracked) reads++;
    return data;
}

uint64_t
MULA::APIntRegister::getIntData(bool incReads)
{
    if (incReads && tracked) reads++;
    return data;
}

uint64_t
MULA::APIntRegister::getUnsignedInt(bool incReads) {
    if (incReads && tracked) reads++;
    return data;
}

int64_t
MULA::APIntRegister::getSignedInt(size_t sizeInBits, bool incReads) {
    if (incReads && tracked) reads++;
    int64_t tmp;
    switch (sizeInBits) {
        case 8:
            {
                tmp = (int64_t)((int8_t)(data));
                break;
            }
        case 16:
            {
                tmp = (int64_t)((int16_t)(data));
                break;
            }
        case 32:
            {
                tmp = (int64_t)((int32_t)(data));
                break;
            }
        case 64:
            {
                tmp = (int64_t)(data);
                break;
            }
        default:
            {
                assert(0 && "Must use AP values for nonstandard int sizes.");
                break;
            }
    }
    return tmp;
}

void
MULA::APIntRegister::writeIntData(uint64_t api, size_t len, bool incWrites)
{
    if (incWrites && tracked) writes++;
    std::memcpy(&data, &api, len);
    regdata = data;
}

uint64_t
MULA::IndexRegister::getIndexData(bool incReads)
{
    if (incReads && tracked) reads++;
    return pointer;
}

void
MULA::IndexRegister::writeIndexData(uint64_t ptr, size_t len, bool incWrites)
{
    if (incWrites && tracked) writes++;
    std::memcpy(&pointer, &ptr, len);
    regdata = pointer;
}

std::string
MULA::APFloatRegister::dataString() {
    std::stringstream ss;
    float fdata = *(float*)&data;
    double ddata = *(double*)&data;
    ss << fdata << "f " << ddata << "d";
    return ss.str();
}

std::string
MULA::APIntRegister::dataString() {
    std::stringstream ss;
    ss << "0x" << std::hex << data;
    return ss.str();
}

std::string
MULA::IndexRegister::dataString() {
    std::stringstream ss;
    ss << "0x" << std::hex << pointer;
    return ss.str();
}

uint64_t
MULA::MemrefRegister::getPtrData(bool incReads)
{
    if (incReads && tracked) reads++;
    return baseAddress;
}

void
MULA::MemrefRegister::writePtrData(uint64_t ptr, size_t len, bool incWrites)
{
    if (incWrites && tracked) writes++;
    std::memcpy(&baseAddress, &ptr, len);
    regdata = baseAddress;
}