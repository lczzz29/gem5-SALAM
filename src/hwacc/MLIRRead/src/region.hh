#ifndef __MULA_REGION_HH__
#define __MULA_REGION_HH__
//------------------------------------------//
#include "debug_flags.hh"
#include "value.hh"
#include "operation.hh"
//------------------------------------------//
#include "mlir/IR/Region.h"

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
  class Block; // Do not remove

  typedef std::pair<mlir::Region *, std::shared_ptr<Region>> RegionMapType;
  typedef std::map<mlir::Region *, std::shared_ptr<Region>> RegionMap;
  typedef std::vector<std::shared_ptr<Region>> RegionListType;

  class Region {
    private:
      std::vector<std::shared_ptr<MULA::Block>> blocks;
    protected:
      class Region_Debugger: public Debugger
        {
            public:
                Region_Debugger();
                ~Region_Debugger() = default;
                virtual void dumper(MULA::Region * region);
        }; 

        Region_Debugger *region_dbg;
        bool dbg = false;
        uint64_t uid = 0;
        gem5::SimObject *owner;

    public:
      Region(uint64_t id, gem5::SimObject * _owner, bool _dbg);
      ~Region();
      virtual bool isRegion() { return true; }
      void initialize(mlir::Region *region, RegionMap *regionMap, OpMap *opMap, MULA::ValueListType* valueList);
      std::vector<std::shared_ptr<MULA::Block> > * Blocks() { return &blocks; }
      void dump() { if (dbg) region_dbg->dumper(this); }
  };
}

#endif //__MULA_Region_HH__
