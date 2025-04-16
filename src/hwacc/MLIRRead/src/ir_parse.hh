#ifndef __HWACC_MLIR_IR_PARSER_HH__
#define __HWACC_MLIR_IR_PARSER_HH__

#include "mlir/IR/Operation.h"
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/ErrorOr.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Support/raw_ostream.h>
#include "instruction.hh"
#include <string>
#include <iostream>
#include <vector>
#include <memory>

namespace MULA {
    int ir_parser(std::string file);  
    void register_operation(mlir::Operation * op, std::vector<std::shared_ptr<MULA::Operation>> &op_List);

}

#endif //__HWACC_MLIR_IR_PARSER_HH__