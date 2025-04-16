#ifndef __MULA_MAP_HH__
#define __MULA_MAP_HH__

#include "mlir/IR/Value.h"
#include "mlir/IR/Block.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/Region.h"

#include <map>
#include <vector>

namespace MULA {

class Value;
typedef std::pair<mlir::Value *, std::shared_ptr<Value>> ValueMapType;
typedef std::map<mlir::Value *, std::shared_ptr<Value>> ValueMap;
typedef std::vector<std::shared_ptr<Value>> ValueListType;

class Operation;
typedef std::pair<mlir::Operation *, std::shared_ptr<Operation>> OpMapType;
typedef std::map<mlir::Operation *, std::shared_ptr<Operation>> OpMap;
typedef std::vector<std::shared_ptr<Operation>> OpListType;

class Block;
typedef std::pair<mlir::Block *, std::shared_ptr<Block>> BlockMapType;
typedef std::map<mlir::Block *, std::shared_ptr<Block>> BlockMap;
typedef std::vector<std::shared_ptr<Block>> BlockListType;

class Region;
typedef std::pair<mlir::Region *, std::shared_ptr<Region>> RegionMapType;
typedef std::map<mlir::Region *, std::shared_ptr<Region>> RegionMap;
typedef std::vector<std::shared_ptr<Region>> RegionListType;

class IRMap
{
private:
    ValueMap valueMap;
    ValueListType valueList;
    
    OpMap opMap;
    OpListType opList;
    
    BlockMap blockMap;
    BlockListType blockList;
    
    RegionMap regionMap;
    RegionListType regionList;

public:
    IRMap();
    ~IRMap();

    // Value methods
    void pushValue(mlir::Value *key, std::shared_ptr<Value> value);
    std::shared_ptr<Value> findValue(mlir::Value *key) const;
    const ValueListType& getValueList() const;

    // Operation methods
    void pushOperation(mlir::Operation *key, std::shared_ptr<Operation> op);
    std::shared_ptr<Operation> findOperation(mlir::Operation *key) const;
    const OpListType& getOperationList() const;

    // Block methods
    void pushBlock(mlir::Block *key, std::shared_ptr<Block> block);
    std::shared_ptr<Block> findBlock(mlir::Block *key) const;
    const BlockListType& getBlockList() const;

    // Region methods
    void pushRegion(mlir::Region *key, std::shared_ptr<Region> region);
    std::shared_ptr<Region> findRegion(mlir::Region *key) const;
    const RegionListType& getRegionList() const;
};

} // namespace MULA


#endif // __MULA_MAP_HH__