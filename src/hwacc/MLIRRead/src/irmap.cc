#include "irmap.hh"

namespace MULA{

IRMap::IRMap() = default;

IRMap::~IRMap() = default;

// Value methods
void IRMap::pushValue(mlir::Value *key, std::shared_ptr<Value> value) {
    valueMap[key] = value;
    valueList.push_back(value);
}

std::shared_ptr<Value> IRMap::findValue(mlir::Value *key) const {
    auto it = valueMap.find(key);
    return it != valueMap.end() ? it->second : nullptr;
}

const ValueListType& IRMap::getValueList() const {
    return valueList;
}

// Operation methods
void IRMap::pushOperation(mlir::Operation *key, std::shared_ptr<Operation> op) {
    opMap[key] = op;
    opList.push_back(op);
}

std::shared_ptr<Operation> IRMap::findOperation(mlir::Operation *key) const {
    auto it = opMap.find(key);
    return it != opMap.end() ? it->second : nullptr;
}

const OpListType& IRMap::getOperationList() const {
    return opList;
}

// Block methods
void IRMap::pushBlock(mlir::Block *key, std::shared_ptr<Block> block) {
    blockMap[key] = block;
    blockList.push_back(block);
}

std::shared_ptr<Block> IRMap::findBlock(mlir::Block *key) const {
    auto it = blockMap.find(key);
    return it != blockMap.end() ? it->second : nullptr;
}

const BlockListType& IRMap::getBlockList() const {
    return blockList;
}

// Region methods
void IRMap::pushRegion(mlir::Region *key, std::shared_ptr<Region> region) {
    regionMap[key] = region;
    regionList.push_back(region);
}

std::shared_ptr<Region> IRMap::findRegion(mlir::Region *key) const {
    auto it = regionMap.find(key);
    return it != regionMap.end() ? it->second : nullptr;
}

const RegionListType& IRMap::getRegionList() const {
    return regionList;
}

} // namespace MULA