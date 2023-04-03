#ifndef __RAYMON_SHAN_VECTOR_MAP_HPP
#define __RAYMON_SHAN_VECTOR_MAP_HPP

#include "infra.hpp"

template <typename KEY, typename VALUE, typename HASHCLASS, typename HASH>
class LinkedNode {
public:
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
    hash.PrintHash(3);
  }
};

template <typename KEY, typename VALUE, typename HASHCLASS, typename HASH>
class NodeList {
  typedef LinkedNode<KEY, VALUE, HASHCLASS, HASH> TNode;
private:
  volatile TNode *nodeHead;
public:
  NodeList() {
    nodeHead = NULL;
  };

  bool InsertAhead(TNode *node) {  
    volatile TNode *old;
    do {
      old = nodeHead;
      node->next = old;
    } while (!__sync_bool_compare_and_swap(&nodeHead, old, node));
    return true;
  };
  TNode* FindOrInsert(TNode *node) {
    volatile TNode *oldvalue;
    volatile TNode **oldplace;
    int retcmp;
    bool retcas;

    do {
      oldplace = &nodeHead;
      oldvalue = nodeHead;
      if (nodeHead == NULL) {
	node->next = oldvalue;
	retcas = __sync_bool_compare_and_swap(oldplace, oldvalue, node);       // NULL pointer
      } else {
	do {
	  retcmp = node->hash.Compare(((TNode*)oldvalue)->hash);
	  if (retcmp == 0) {
	    printf("find same\n");
	    return (TNode*)oldvalue;
	  } else if (retcmp > 0) {
	    oldplace = &(((TNode*)oldvalue)->next);
	    oldvalue = oldvalue->next;                                         // get next
	    if (oldvalue == NULL) {
	      node->next = oldvalue;
	      retcas = __sync_bool_compare_and_swap(oldplace, oldvalue, node); // add to last
	      break;
	    }
	  } else {
	    node->next = oldvalue;
	    retcas = __sync_bool_compare_and_swap(oldplace, oldvalue, node);   // insert between
	    break;
	  }
	} while (true);
      }
    } while (!retcas);
    return node;
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
      printf("\n%p->", now);
      ((TNode*)now)->PrintHash();      
      now = now->next;
    }
    printf("\n");
  };
};

template <typename KEY, typename VALUE, typename HASHCLASS, typename HASH>
class HashListMap {
  typedef LinkedNode<KEY, VALUE, HASHCLASS, HASH> TNode;
  typedef NodeList<KEY, VALUE, HASHCLASS, HASH> TList;
private:
  int bucketNumber;
  void *listArray;
  TList **bucketList;
public:
  HashListMap(int bucketNumber) {
    this->bucketNumber = bucketNumber;
    listArray = malloc(bucketNumber * sizeof(TList*));
    bucketList = (TList**)listArray;
    for (int i = 0; i < bucketNumber; i++) bucketList[i] = new TList();
  };
  ~HashListMap() {
    for (int i = 0; i < bucketNumber; i++) delete bucketList[i];
    free(listArray);
  };
  int GetBucket(HASH hash) {
    unsigned int *index = (unsigned int*) &hash;
    return *index % bucketNumber;
  };
  TNode* FindOrInsert(TNode *node) {
    int num = GetBucket(node->hash);
    printf("hash insert %d\n", num);
    return bucketList[GetBucket(node->hash)]->FindOrInsert(node);
  };
};





#endif  // __RAYMON_SHAN_VECTOR_MAP_HPP
