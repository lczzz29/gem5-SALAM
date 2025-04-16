#ifndef __HWACC_MLIR_MEM_HH__
#define __HWACC_MLIR_MEM_HH__

#include <math.h>
#include "debug_flags.hh"
#include "llvm/IR/Value.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Constants.h"
#include "llvm/ADT/APSInt.h"
#include "llvm/ADT/APFloat.h"
#include <llvm-c/Core.h>
#include "mlir/IR/Types.h"
#include "mlir/IR/Value.h"
#include "mlir/IR/BuiltinTypes.h"

#define USE_LLVM_AP_VALUES 0

namespace MULA
{
/*****************************************************************************
* Register is the data storage container for MULA::Values.
* Every operation and function argument has a corresponding register that
* is tracked for power/area/timing. Additionally Constants have corresponding
* registers, which are not tracked, since they do not have a timing component.
*****************************************************************************/
class Register
{
    protected:
        bool tracked;
        bool isNULL = false;
        bool dbg = false;
        uint64_t reads = 0;
        uint64_t writes = 0;
        uint64_t regdata;

        class Register_Debugger: public Debugger
        {
            public:
                Register_Debugger();
                ~Register_Debugger() = default;
                virtual void dumper(MULA::Register *reg);
        };

        Register_Debugger reg_dbg;

    public:
        Register(bool trk=true,
                 bool nul=false);
        ~Register();
        virtual uint64_t getFloatData(bool incReads=true) {
            assert(0 && "Attempted to read float data from non-float register");
            return 0;
        }
        virtual float getFloat(bool incReads=true) {
            assert(0 && "Attempted to read float data from non-float register");
            return NAN;
        }
        virtual double getDouble(bool incReads=true) {
            assert(0 && "Attempted to read float data from non-float register");
            return NAN;
        }
        virtual uint64_t getIntData(bool incReads=true) {
            assert(0 && "Attempted to read integer data from non-integer register");
            return 0;
        }
        virtual uint64_t getUnsignedInt(bool incReads=true) {
            assert(0 && "Attempted to read integer data from non-integer register");
            return 0;
        }
        virtual int64_t getSignedInt(size_t sizeInBits, bool incReads=true) {
            assert(0 && "Attempted to read integer data from non-integer register");
            return 0;
        }
        virtual uint64_t getIndexData(bool incReads=true) {
            assert(0 && "Attempted to read index data from non-index register");
            return 0;
        }
        virtual uint64_t getPtrData(bool incReads=true) {
            assert(0 && "Attempted to read pointer data from non-pointer register");
            return 0;
        }
        virtual void writeFloatData(uint64_t apf, size_t len=8, bool incWrites=true) {
            assert(0 && "Attempted to write float data on non-float register");
        }
        virtual void writeIntData(uint64_t api, size_t len=8, bool incWrites=true) {
            assert(0 && "Attempted to write interger data on non-integer register");
        }
        virtual void writeIndexData(uint64_t ptr, size_t len=8, bool incWrites=true) {
            assert(0 && "Attempted to write index data on non-index register");
        }
        virtual void writePtrData(uint64_t ptr, size_t len=8, bool incWrites=true) {
            assert(0 && "Attempted to write pointer data on non-pointer register");
        }
        virtual bool isInt() { return false; }
        virtual bool isFP() { return false; }
        virtual bool isIndex() { return false; }
        virtual bool isPtr() { return false; }
        bool isTracked() { return tracked; }
        bool isNull() { return isNULL; }
        void setNull(bool flag) { isNULL = flag; }
        void setTracked(bool flag) { tracked = flag; }
        void dump() { if (dbg) reg_dbg.dumper(this); }
        uint64_t getReads() { return reads; }
        uint64_t getWrites() { return writes; }
        virtual std::string dataString() = 0;
};

class APFloatRegister : public Register
{
    private:
        // We use uint64_t to store the bitcast of the FP value.
        // Compute should be performed after bitcasting back to appropriate type
        uint64_t data = 0;
    public:
        APFloatRegister(mlir::Type T,
                        bool isTracked=true);
        // This constructor is only used for constants.
        APFloatRegister(const mlir::FloatType &RHS);
        // ~APFloatRegister() { if (data) delete data; }
        // This constructor is only used for constants.
        APFloatRegister(const uint64_t RHS) : Register(false) {
            data = RHS;
            regdata = data;    
        }
        virtual uint64_t getFloatData(bool incReads=true) override;
        virtual float getFloat(bool incReads=true) override;
        virtual double getDouble(bool incReads=true) override;
        virtual void writeFloatData(uint64_t apf, size_t len=8, bool incWrites=true) override;
        virtual bool isFP() override { return true; }
        virtual std::string dataString() override;
};

class APIntRegister : public Register
{
    private:
        uint64_t data = 0;
    public:
        APIntRegister(uint64_t bitwidth,
                      bool isTracked);
        APIntRegister(mlir::Type * T,
                      bool isTracked=true);
        // This constructor is only used for constants.
        APIntRegister(const mlir::IntegerType &RHS);
        // ~APIntRegister() { if (data) delete data; }
        // This constructor is only used for constants.
        APIntRegister(const uint64_t RHS) : Register(false) {
            data = RHS;
            regdata = data;
        }
        virtual uint64_t getIntData(bool incReads=true) override;
        virtual uint64_t getUnsignedInt(bool incReads=true) override;
        virtual int64_t getSignedInt(size_t sizeInBits, bool incReads=true) override;
        virtual void writeIntData(uint64_t api, size_t len=8, bool incWrites=true) override;
        virtual bool isInt() override { return true; }
        virtual std::string dataString() override;
};

class IndexRegister : public Register
{
    private:
        uint64_t pointer = 0;
    public:
        IndexRegister(bool isTracked=true,
                        bool isNull=false);
        IndexRegister(uint64_t val,
                        bool isTracked=true,
                        bool isNull=false);
        virtual bool isIndex() override { return true; }
        virtual uint64_t getIndexData(bool incReads=true) override;
        virtual void writeIndexData(uint64_t ptr, size_t len=8, bool incWrites=true) override;
        virtual std::string dataString() override;
};

class MemrefRegister : public Register {
    private:
        uint64_t baseAddress;  // Base pointer of the memref data
        unsigned rank;         // Number of dimensions
        llvm::SmallVector<int64_t, 4> strides; // Stride for each dimension
        int64_t offset;        // Offset in bytes from base
        mlir::Type elementType; // Element type (e.g., f32, i64, vector<4xf32>)
    
    public:
        // Constructor with full memref metadata
        MemrefRegister(uint64_t baseAddr, 
                       unsigned rank,
                       llvm::SmallVector<int64_t, 4> strides,
                       int64_t offset,
                       mlir::Type elementType,
                       bool isTracked = true,
                       bool isNull = false)
            : Register(isTracked, isNull),
              baseAddress(baseAddr),
              rank(rank),
              strides(std::move(strides)),
              offset(offset),
              elementType(elementType) {}
    
        // Accessors
        uint64_t getBaseAddress() const { return baseAddress; }
        unsigned getRank() const { return rank; }
        const llvm::SmallVector<int64_t, 4>& getStrides() const { return strides; }
        int64_t getOffset() const { return offset; }
        mlir::Type getElementType() const { return elementType; }
    
        // Element size information
        unsigned getElementSize() const {
            // Returns size in bits (standard for MLIR types)
            return elementType.getIntOrFloatBitWidth();
        }
    
        unsigned getElementSizeInBytes() const {
            // Returns size in bytes (rounded up)
            return (getElementSize() + 7) / 8;
        }
    
        // For vector types
        unsigned getNumElements() const {
            if (auto vectorType = elementType.dyn_cast<mlir::VectorType>())
                return vectorType.getNumElements();
            return 1; // Scalar type
        }
    
        // Update metadata
        void setMemrefMetadata(uint64_t newBase, unsigned newRank,
                             llvm::SmallVector<int64_t, 4> newStrides,
                             int64_t newOffset,
                             mlir::Type newElementType) {
            baseAddress = newBase;
            rank = newRank;
            strides = std::move(newStrides);
            offset = newOffset;
            elementType = newElementType;
        }
    
        // Overridden methods
        bool isPtr() override { return true; }
        
        uint64_t getPtrData(bool incReads) override;
    
        void writePtrData(uint64_t ptr, size_t len, bool incWrites) override;
    
        std::string dataString() override {
            std::string typeStr;
            llvm::raw_string_ostream os(typeStr);
            elementType.print(os);
            
            std::string str = "Memref[base=" + std::to_string(baseAddress) + 
                             ", rank=" + std::to_string(rank) +
                             ", offset=" + std::to_string(offset) + 
                             ", type=" + os.str() +
                             ", strides=[";
            for (size_t i = 0; i < strides.size(); ++i) {
                if (i != 0) str += ", ";
                str += std::to_string(strides[i]);
            }
            return str + "]]";
        }

};

class LocalMemrefRegister : public Register {
    private:
        llvm::SmallVector<int64_t, 4> shape;      // Shape of the memref
        llvm::SmallVector<int64_t, 4> strides;    // Stride for each dimension
        mlir::Type elementType;                   // Element type
        std::unique_ptr<uint8_t[]> storage;       // Local storage for data
        size_t totalElements;                    // Total number of elements
        size_t elementSize;                      // Size of each element in bytes
    
    public:
        // Constructor with shape and element type
        LocalMemrefRegister(llvm::ArrayRef<int64_t> shape,
                           mlir::Type elementType,
                           bool isTracked = true,
                           bool isNull = false)
            : Register(isTracked, isNull),
              shape(shape.begin(), shape.end()),
              elementType(elementType) {
            
            // Calculate strides (assuming row-major layout)
            strides.resize(shape.size());
            int64_t stride = 1;
            for (int i = shape.size() - 1; i >= 0; --i) {
                strides[i] = stride;
                stride *= shape[i];
            }
    
            // Calculate total elements and allocate storage
            totalElements = 1;
            for (auto dim : shape) {
                totalElements *= dim;
            }
    
            elementSize = (elementType.getIntOrFloatBitWidth() + 7) / 8;
            storage = std::make_unique<uint8_t[]>(totalElements * elementSize);
        }
    
        // Accessors
        unsigned getRank() const { return shape.size(); }
        const llvm::SmallVector<int64_t, 4>& getShape() const { return shape; }
        const llvm::SmallVector<int64_t, 4>& getStrides() const { return strides; }
        mlir::Type getElementType() const { return elementType; }
        size_t getElementSize() const { return elementSize; }
        size_t getTotalElements() const { return totalElements; }
    
        // Calculate linear offset from indices
        size_t calculateOffset(llvm::ArrayRef<uint64_t> indices) const {
            size_t offset = 0;
            for (unsigned i = 0; i < indices.size(); ++i) {
                offset += indices[i] * strides[i];
            }
            return offset;
        }
    
        // Write element value at given indices
        void writeElementValue(llvm::ArrayRef<uint64_t> indices, uint64_t value) {
            size_t offset = calculateOffset(indices);
            uint8_t* elementPtr = storage.get() + offset * elementSize;
            std::memcpy(elementPtr, &value, elementSize);
        }
    
        // Get element value at given indices
        uint64_t getElementValue(llvm::ArrayRef<uint64_t> indices) const {
            size_t offset = calculateOffset(indices);
            const uint8_t* elementPtr = storage.get() + offset * elementSize;
            uint64_t value = 0;
            std::memcpy(&value, elementPtr, elementSize);
            return value;
        }
    
        // Overridden methods
        bool isPtr() override { return true; }
        
        uint64_t getPtrData(bool incReads) override {
            return reinterpret_cast<uint64_t>(storage.get());
        }
    
        void writePtrData(uint64_t ptr, size_t len, bool incWrites) override {
            // Not implemented for local storage
            llvm_unreachable("Cannot write pointer data to local memref storage");
        }
    
        std::string dataString() override {
            std::string typeStr;
            llvm::raw_string_ostream os(typeStr);
            elementType.print(os);
            
            std::string str = "LocalMemref[shape=[";
            for (size_t i = 0; i < shape.size(); ++i) {
                if (i != 0) str += ", ";
                str += std::to_string(shape[i]);
            }
            str += "], type=" + os.str() + ", strides=[";
            for (size_t i = 0; i < strides.size(); ++i) {
                if (i != 0) str += ", ";
                str += std::to_string(strides[i]);
            }
            return str + "]]";
        }
};

} // End MULA Namespace
#endif