//------------------------------------------//
#include "region.hh"

#include "sim/sim_object.hh"
//------------------------------------------//

using namespace MULA;

MULA::Region::Region(uint64_t id, gem5::SimObject * _owner, bool _dbg)
    // MULA::Value(id, owner, dbg) 
{
    uid = id;
    owner = _owner;
    dbg = _dbg;
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    // if (DTRACE(MULA_Debug)) {
    //     this->dbg = true;
    //     this->bb_dbg = new Region_Debugger();
    // }
}

MULA::Region::~Region() 
{
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace Deleted: %s \n", __PRETTY_FUNCTION__);
    //// if (DTRACE(MULA_Debug)) delete bb_dbg;
}

MULA::Region::Region_Debugger::Region_Debugger()
{
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
}

void
MULA::Region::Region_Debugger::dumper(MULA::Region *region)
{
    // if (DTRACE(MULA_Debug)) {
        // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    //     DPRINTF(MULA_Debug, "%s \n\t\t\t %s %d  \n", 
    //         "************** Basic Region Dump **************",
    //         "UID: ", region->getUID()
    //     );
    // }
}

void
MULA::Region::initialize(mlir::Region * region, RegionMap *regionMap, OpMap *opMap, MULA::ValueListType *valueList) {
    // if (DTRACE(Trace)) DPRINTF(Runtime, "Trace: %s \n", __PRETTY_FUNCTION__);
    if (dbg) DPRINTFS(mlirParse, owner, "Initialize - Region::initialize\n");
	//Parse irval for Region params

    if (dbg) DPRINTFS(mlirParse, owner, "Initialize Regions\n");
	for (auto block_iter = region->begin(); block_iter != region->end(); block_iter++) {
        mlir::Block &block = *block_iter;
        std::shared_ptr<MULA::Operation> op = opMap->find(&op)->second;
        assert(op);
        operations.push_back(op);
        op->initialize(&op, vmap, valueList);
        if (dbg) DPRINTFS(mlirParse, owner, "Operation (UID: %d) Initialization Complete\n", opruct->getUID());
    }
}
