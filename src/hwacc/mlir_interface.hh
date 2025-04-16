#ifndef __HWACC_MLIR_INTERFACE_HH__
#define __HWACC_MLIR_INTERFACE_HH__

// C++ Includes
#include <algorithm>
#include <chrono>
#include <ctime>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <ratio>
#include <type_traits>
#include <typeinfo>

// LLVM Includes
#include <llvm-c/Core.h>
#include <llvm/Analysis/LoopInfo.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Dominators.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>
#include <llvm/Transforms/Utils/Cloning.h>

// MLIR Includes
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/Value.h"

// // SALAM Includes
// #include "hwacc/HWModeling/src/hw_interface.hh"
// #include "hwacc/LLVMRead/src/basic_block.hh"
// #include "hwacc/LLVMRead/src/debug_flags.hh"
// #include "hwacc/LLVMRead/src/function.hh"
// #include "hwacc/LLVMRead/src/operand.hh"
// #include "hwacc/compute_unit.hh"
// #include "params/LLVMInterface.hh"

// MULA MLIRRead Includes
#include "hwacc/MLIRRead/src/block.hh"
#include "hwacc/MLIRRead/src/region.hh"
#include "hwacc/MLIRRead/src/debug_flags.hh"
#include "hwacc/MLIRRead/src/function.hh"
#include "hwacc/MLIRRead/src/operand.hh"
#include "hwacc/MLIRRead/src/value.hh"
#include "hwacc/MLIRRead/src/dialect/func.hh"
#include "hwacc/MLIRRead/src/operation.hh"
#include "hwacc/compute_unit.hh"
#include "params/MLIRInterface.hh"


class MLIRInterface : public ComputeUnit
{
  private:
    std::string filename;
    std::string topName;
    uint32_t scheduling_threshold;
    int32_t clock_period;
    int cycle;
    int stalls;

    bool running;
    bool loadOpScheduled;
    bool storeOpScheduled;
    bool compOpScheduled;
    bool lockstep;
    bool dbg;
    std::chrono::duration<float> setupTime;
    std::chrono::duration<float> simTotal;
    std::chrono::duration<float> simTime;
    std::chrono::duration<float> schedulingTime;
    std::chrono::duration<float> queueProcessTime;
    std::chrono::duration<float> computeTime;
    std::chrono::duration<float> hwTime;
    std::chrono::high_resolution_clock::time_point simStop;
    std::chrono::high_resolution_clock::time_point setupStop;
    std::chrono::high_resolution_clock::time_point timeStart;


    class ActiveFunc
    {
      friend class MLIRInterface;
    private:
        MLIRInterface * owner;
        HWInterface* hw;
        // TODO: There may be more ops with FucntionOpInterface
        std::shared_ptr<MULA::func::FuncOp> func;
        // TODO: There may be more ops with CallOpInterface
        std::shared_ptr<MULA::func::CallOp> caller;
        std::list<std::shared_ptr<MULA::Operation>> reservation;
        std::map<uint64_t, std::shared_ptr<MULA::Operation>> readQueue;
        std::map<MemoryRequest *, uint64_t> readQueueMap;
        std::map<uint64_t, std::shared_ptr<MULA::Operation>> writeQueue;
        std::map<MemoryRequest *, uint64_t> writeQueueMap;
        std::map<uint64_t, std::shared_ptr<MULA::Operation>> computeQueue;
        std::shared_ptr<MULA::Block> previousBlock;
        HW_Cycle_Stats hw_cycle_stats;
        uint32_t scheduling_threshold;
        bool returned = false;
        bool lockstep;
        bool dbg;

        inline bool uidActive(uint64_t id) {
          return computeUIDActive(id) || readUIDActive(id) || writeUIDActive(id);
        }

        std::map<Addr, std::shared_ptr<MULA::Operation>> activeWrites;
        inline void trackWrite(Addr writeAddr, std::shared_ptr<MULA::Operation> writeOp) {
          activeWrites.insert({writeAddr, writeOp});
        }
        inline void untrackWrite(uint64_t writeAddr) {
          auto it = activeWrites.find(writeAddr);
          if (it != activeWrites.end()) activeWrites.erase(it);
        }
        inline bool writeActive(uint64_t writeAddr) {
          return (activeWrites.find(writeAddr) != activeWrites.end());
        }

        inline std::shared_ptr<MULA::Operation> getActiveWrite(uint64_t writeAddr) {
          return activeWrites.find(writeAddr)->second;
        }
        // std::map<Addr, std::shared_ptr<MULA::Operation>> activeReads;
        // inline void trackRead(Addr readAddr, std::shared_ptr<MULA::Operation> readOp) {
        //   activeReads.insert({readAddr, readOp});
        // }
        // inline void untrackRead(uint64_t readAddr) {
        //   auto it = activeReads.find(readAddr);
        //   if (it != activeReads.end()) activeReads.erase(it);
        // }
        // inline bool readActive(uint64_t readAddr) {
        //   return (activeReads.find(readAddr) != activeReads.end());
        // }
        // inline std::shared_ptr<MULA::Operation> getActiveRead(uint64_t readAddr) {
        //   return activeReads.find(readAddr)->second;
        // }
        inline bool writeUIDActive(uint64_t uid) {
          return (writeQueue.find(uid) != writeQueue.end());
        }
        inline bool readUIDActive(uint64_t uid) {
          return (readQueue.find(uid) != readQueue.end());
        }
        inline bool computeUIDActive(uint64_t uid) {
          return (computeQueue.find(uid) != computeQueue.end());
        }
    public:
        ActiveFunc(MLIRInterface * _owner, std::shared_ptr<MULA::func::FuncOp> _func,
                       std::shared_ptr<MULA::func::CallOp> _caller):
                       owner(_owner), func(_func), caller(_caller),
                       previousBlock(nullptr) {
                          scheduling_threshold = owner->getSchedulingThreshold();
                          lockstep = (owner->getLockstepStatus());
                          dbg = owner->debug();
                       }
        void readCommit(MemoryRequest *req);
        void writeCommit(MemoryRequest *req);
        void findDynamicDeps(std::shared_ptr<MULA::Operation> op);
        void scheduleBlock(std::shared_ptr<MULA::Block> block);
        void scheduleRegion(std::shared_ptr<MULA::Region> region);
        void processQueues();
        void launch();
        inline bool queuesClear() {
          return readQueue.empty() && writeQueue.empty() && computeQueue.empty();
        }
        inline bool lockstepReady() {
          return !lockstep || queuesClear();
        }
        inline bool canReturn() {
            return queuesClear() && reservation.front()->isReturn();
        }
        void launchRead(std::shared_ptr<MULA::Operation> readOp);
        void launchWrite(std::shared_ptr<MULA::Operation> writeOp);
        bool hasReturned() { return returned; }
    };

    std::list<ActiveFunc> activeFuncs;
    std::map<MemoryRequest *, ActiveFunc *> globalReadQueue;
    std::map<MemoryRequest *, ActiveFunc *> globalWriteQueue;

    std::vector<std::shared_ptr<MULA::func::FuncOp>> functions;
    std::vector<std::shared_ptr<MULA::Value>> values;
  protected:
    // const std::string name() const { return comm->getName() + ".compute"; }
    virtual bool debug() { return comm->debug(); }
    // virtual bool debug() { return true; }
  public:
    PARAMS(MLIRInterface);
    MLIRInterface(const MLIRInterfaceParams &p);
    void tick();
    void constructStaticGraph();
    void startup();
    void initialize();
    void finalize();
    void debug(uint64_t flags);
    bool getLockstepStatus() { return lockstep; }
    void readCommit(MemoryRequest *req);
    void writeCommit(MemoryRequest *req);
    void dumpModule(mlir::ModuleOp *m);
    void printResults();
    void launchFunc(std::shared_ptr<MULA::func::FuncOp> callee,
                    std::shared_ptr<MULA::Operation> caller);
    void launchTopFunc();
    void endFunction(ActiveFunc * afunc);
    void launchRead(MemoryRequest * memReq, ActiveFunc * func);
    void launchWrite(MemoryRequest * memReq, ActiveFunc * func);
    std::shared_ptr<MULA::Operation> createOp(mlir::Operation *op,
                                                          uint64_t id);
    void dumpQueues();
    uint32_t getSchedulingThreshold() { return scheduling_threshold; }
    void addSchedulingTime(std::chrono::duration<float> timeDelta) { schedulingTime = schedulingTime + timeDelta; }
    void addQueueTime(std::chrono::duration<float> timeDelta) { queueProcessTime = queueProcessTime + timeDelta; }
    void addComputeTime(std::chrono::duration<float> timeDelta) { computeTime = computeTime + timeDelta; }
    void addHWTime(std::chrono::duration<float> timeDelta) { hwTime = hwTime + timeDelta; }
};

#endif //__HWACC_MLIR_INTERFACE_HH__
