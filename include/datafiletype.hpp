#ifndef __RAYMON_SHAN_DATAFILE_TYPE_HPP
#define __RAYMON_SHAN_DATAFILE_TYPE_HPP

#include "infra.hpp"

class DataField {
  int fieldCategory;            // unique, essential, attribute
  int fieldType;                // string, int, percent, money, hash, time
  std::string fileName;
public:
  DataField(int category, int type, char *name) {};
};

class DataClass {
  DataClass *inheritClass;
  DataClass *aggregationClass;
  DataField *fieldList;
  TreeNode  *dataList;
};


/*
聚合关系（Aggregation） 树木 --o 森林
泛化关系（Generalization） 继承类 --|> 基类
实现关系（Realization）   实现 ..|> 接口
组合关系 Composition      部件 --* 整体 
 */
//struct 

#endif  // __RAYMON_SHAN_DATAFILE_TYPE_HPP


