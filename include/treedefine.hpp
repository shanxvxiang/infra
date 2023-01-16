#ifndef __RAYMON_SHAN_TREE_DEFINE_HPP
#define __RAYMON_SHAN_TREE_DEFINE_HPP

#include "infra.hpp"

#define LAST_NODE       ((TreeNode*)(-1))

class TreeNode {
protected:
  TreeNode *parent;
  TreeNode *child;
  TreeNode *brother;

  _Hash hashid;

  static SpinLock lock;
public:
  // par = NULL, is the root node 
  // bro = NULL, is first child. or after the given node, default is last node
  // if hash = NULL, do NOT display the only root node
  TreeNode(TreeNode *par, _Hash hash, TreeNode *bro = LAST_NODE) {
    TreeNode *prev, *next;
    
    parent = par;
    child = brother = NULL;
    hashid = hash;
    
    if (par) {
      if (bro = NULL) {          // is the first brother of parent
	lock++;
	brother = par.child;
	par.child = this;
	lock--;
      } else {
	next = par.child;
	while (bro == LAST_NODE || bro != next) {
	}
      }
    }

    
  };
};


class CustomTreeNode : public TreeNode{
private:
  TreeNode realNode;
};


#endif  // __RAYMON_SHAN_TREE_DEFINE_HPP

