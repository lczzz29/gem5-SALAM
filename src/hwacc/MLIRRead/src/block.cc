//------------------------------------------//
#include "block.hh"
// #include "mlir/IR/CFG.h"

#include "sim/sim_object.hh"
//------------------------------------------//

using namespace MULA;

MULA::Block::Block(uint64_t id, gem5::SimObject * _owner, bool _dbg)
    // MULA::Value(id, owner, dbg) 
{
    uid = id;
    owner = _owner;
    dbg = _dbg;
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    // if (DTRACE(MULA_Debug)) {
    //     this->dbg = true;
    //     this->bb_dbg = new Block_Debugger();
    // }
}

MULA::Block::~Block() 
{
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace Deleted: %s \n", __PRETTY_FUNCTION__);
    //// if (DTRACE(MULA_Debug)) delete bb_dbg;
}

MULA::Block::Block_Debugger::Block_Debugger()
{
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
}

void
MULA::Block::Block_Debugger::dumper(MULA::Block *block)
{
    // if (DTRACE(MULA_Debug)) {
        // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    //     DPRINTF(MULA_Debug, "%s \n\t\t\t %s %d  \n", 
    //         "************** Basic Block Dump **************",
    //         "UID: ", block->getUID()
    //     );
    // }
}

void
MULA::Block::initialize(mlir::Block * block, IRMap *irMap) {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    if (dbg) DPRINTFS(MLIRParse, owner, "Initialize - Block::initialize\n");
	//Parse irval for Block params
    for (auto it : block->getPredecessors()) {
        mlir::Block * predecessor = it;
        std::shared_ptr<MULA::Block> pred =
            std::dynamic_pointer_cast<MULA::Block>(irMap->findBlock(predecessor));
        predecessors.push_back(pred);
    }

    if (dbg) DPRINTFS(MLIRParse, owner, "Initialize Blocks\n");
	for (auto op_iter = block->begin(); op_iter != block->end(); op_iter++) {
        mlir::Operation &op = *op_iter;
        std::shared_ptr<MULA::Operation> operation = irMap->findOperation(&op);
        assert(operation);
        operations.push_back(operation);
        operation->initialize(&op, irMap);
        if (dbg) DPRINTFS(MLIRParse, owner, "Operation (UID: %d) Initialization Complete\n", opruct->getUID());
    }
}
