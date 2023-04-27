#ifndef __RAYMON_SHAN_TREE_DEFINE_HPP
#define __RAYMON_SHAN_TREE_DEFINE_HPP

#include "infra.hpp"

#define LAST_NODE       ((TreeNode*)(-1))                 // insert into last

int count = 0, childcount = 0, brothercount = 0;
static MutexLocker locker;

template <typename HASHCLASS, typename HASH>
class TreeNode {
  
protected:
  TreeNode *parent;
  TreeNode *child;
  TreeNode *brother;
  
public:
  HASH hashid;
  char* fieldBuffer;
  
  //  static MutexLocker locker;
private:
  bool inline chainNode(TreeNode **chain) {


    brother = *chain;
    return __sync_bool_compare_and_swap(chain, brother, this);
  };

public:

  int TraversalNode(int level = 0) {
    for (int i = 0; i < level; i++) printf(" ");
    hashid.Display();
    count ++;
    if (child) {
      childcount++;
      child->TraversalNode(level + 1);
    }
    if (brother) {
      brothercount++;
      return brother->TraversalNode(level);
    }
    return count;
  };
  
  TreeNode() {
  };

  bool InsertNode(TreeNode **par, TreeNode *bro = LAST_NODE) {
    locker++;
    if (*par) {
      parent = *par;
      child = NULL;
      TreeNode *first = (*par)->child;
      if (first) {                                        // with brother
	(*par)->child = this;
	brother = first;	
      } else {                                            // is first node of parent
	(*par)->child = this;
	brother = NULL;
      }
    } else {                                              // is root
      parent = NULL;
      child = NULL;
      brother = NULL;
      *par = this;
    };
    locker--;
    return true;
  };
  
  // par = NULL, is the root node 
  // bro = NULL, is first child. or after the given node, default is last node
  // if hash = NULL, do NOT display the only root node
  /*
  bool InsertNode(TreeNode *par, TreeNode *bro = LAST_NODE) {
    TreeNode *prev, *next;
    
    if (par) {
      if (!bro || !par->child) {          // is the first brother of parent
	chainNode(&(par->child));
      } else {
	next = par->child;
	while (next) {
	  if (bro == next) {
	    chainNode(&(next->brother));
	    return true;
	  }
	  prev = next;
	  next = next->brother;
	}
	chainNode(&(prev->brother));
      }
    }
    return true;
  };
  */
};



#ifdef  _WITH_TEST_NODE

volatile unsigned long start;
int number;
TreeNode firstNode;

void* TestInsertNodeThread(void *arg) {
  char id = (char)(long)arg;
  _Hash hash(id);
  TreeNode *node[number];

  for (int i = 0; i < number; i++) {
    node[i] = new TreeNode{hash};
  }
 
  while (!start);
  for (int i = 0; i < number; i++) {
//    node[i]->InsertNode(&firstNode);
    node[i]->InsertNode(&firstNode, LAST_NODE);
  }
  //  delete node;
  return NULL;
}

void TestInsertNode (int thnum, int nodenum) {
  start = 0;
  number = nodenum;
  char id;
  pthread_t tid[thnum];
  
  for (int i = 0; i < thnum; i++) {
    id ='A' + i;
    tid[i] = ThreadInfo::CreateThread("test", TestInsertNodeThread, (void*)(long)id);
  }
  usleep(100000);
  start = 1;

  void *tret;
  for (int i = 0; i < thnum; i++) pthread_join(tid[i], &tret);

  int count = firstNode.TraversalNode();
  printf("\ncount = %d, child = %d, brother = %d\n", count,
	 (int)TreeNode::childcount, (int)TreeNode::brothercount);  
}



#endif  // _WITH_TEST_NODE

#endif  // __RAYMON_SHAN_TREE_DEFINE_HPP

