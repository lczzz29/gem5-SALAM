#ifndef __MULA_BLOCK_HH__
#define __MULA_BLOCK_HH__
//------------------------------------------//
#include "debug_flags.hh"
#include "value.hh"
#include "operation.hh"
#include "irmap.hh"
// #include "llvm/IR/BasicBlock.h"
// #include "llvm/IR/Operation.h"
//------------------------------------------//
#include "mlir/IR/Block.h"
//------------------------------------------//
#include <memory>
#include <iomanip>
#include <string>
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
//------------------------------------------//

namespace MULA {
  class Operation; // Do not remove

  class Block {
    private:
      std::vector<std::shared_ptr<MULA::Block>> predecessors;
      std::vector<std::shared_ptr<MULA::Operation>> operations;
    protected:
      class Block_Debugger: public Debugger
        {
            public:
                Block_Debugger();
                ~Block_Debugger() = default;
                virtual void dumper(MULA::Block * block);
        }; 

        Block_Debugger* block_dbg;
        bool dbg = false;
        uint64_t uid = 0;
        gem5::SimObject * owner;

    public:
      Block(uint64_t id, gem5::SimObject * _owner, bool _dbg);
      ~Block();
      virtual bool isBlock() { return true; }
      uint64_t getUID() const { return uid; }
      void initialize(mlir::Block * block, IRMap *irMap);
      std::vector<std::shared_ptr<MULA::Operation> > * Operations() { return &operations; }
      void dump() { if (dbg) block_dbg->dumper(this); }
      bool validPredecessor(std::shared_ptr<MULA::Block> block) {
        auto it = std::find(predecessors.begin(), predecessors.end(), block);
        if (it == predecessors.end()) return false;
        return true;
      }
  };
}

#endif //__MULA_BLOCK_HH__
