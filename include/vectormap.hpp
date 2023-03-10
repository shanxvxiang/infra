#ifndef __RAYMON_SHAN_VECTOR_MAP_HPP
#define __RAYMON_SHAN_VECTOR_MAP_HPP

#include "infra.hpp"

template <typename KEY, typename VALUE, typename HASHCLASS, typename HASH>
class LinkedNode {
private:
  HASH hash;
//  KEY key;
  VALUE value;
public:
  volatile LinkedNode *next;
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
public:
  NodeList(KEY& k, VALUE& v) {
    nodeHead = new TNode(k, v);
  };
  bool Insert_once(TNode *node) {
    volatile TNode *old;
    old = nodeHead->next;
    node->next = old;
    return __sync_bool_compare_and_swap(&(nodeHead->next), old, node);
  };
  bool Insert(TNode *node) {  
    volatile TNode *old;
    do {
      old = nodeHead->next;
      node->next = old;
    } while (!__sync_bool_compare_and_swap(&(nodeHead->next), old, node));
    return true;
  };

  int Size() {
    int size = 0;
    volatile TNode *now = nodeHead;
    while (now) {
      now = now->next;
      size ++;
    }
    return size;
  };
  void PrintList() {
    volatile TNode *now = nodeHead;    
    while (now) {
      printf("%p->", now);
      now = now->next;
    }
    printf("\n");
  };
};








#endif  // __RAYMON_SHAN_VECTOR_MAP_HPP
