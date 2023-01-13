#ifndef __RAYMON_SHAN_TREE_DEFINE_HPP
#define __RAYMON_SHAN_TREE_DEFINE_HPP

#include "infra.hpp"

class TreeNode {
  TreeNode *parent;
  TreeNode *child;
  TreeNode *brother;

  _Hash hashid;
  std::vector<std::any> field;
};





#endif  // __RAYMON_SHAN_TREE_DEFINE_HPP

