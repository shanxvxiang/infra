#ifndef __RAYMON_SHAN_VECTOR_MAP_HPP
#define __RAYMON_SHAN_VECTOR_MAP_HPP

#include "infra.hpp"

template <typename KEY, typename VALUE, typename HASHCLASS, typename HASH>
class LinkedNode {
private:
  HASH hash;
  //  KEY key;
  VALUE value;
  LinkedNode *next;
public:
  LinkedNode(KEY& k, VALUE& v) {
    // key = k;
    value = v;
    HASHCLASS::Digest(k.GetAddress(), k.GetLength(), hash.GetAddress());
    next = NULL;
  }
  void PrintHash() {
    HASHCLASS::PrintHash(hash.GetAddress());
  }
};

template <typename KEY, typename VALUE, typename HASHCLASS, typename HASH>
class NodeList {
  typedef LinkedNode<KEY, VALUE, HASHCLASS, HASH> TNode;
private:
  TNode *nodeHead;
  SpinInt nodeSize;
public:
  NodeList() : nodeSize(0) { nodeHead = NULL; };
  bool Insert(TNode *node) { return Insert(nodeHead, node); };
  bool Insert(TNode *from, TNode *node) {
    return true;
  };
  bool InsertInOrder(TNode *node) { return InsertInOrder(nodeHead, node); };
  bool InsertInOrder(TNode *from, TNode *node) {
    return true;
  }
};








#endif  // __RAYMON_SHAN_VECTOR_MAP_HPP
