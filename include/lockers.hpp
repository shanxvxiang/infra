#ifndef __RAYMON_SHAN_LOCKS_HPP
#define __RAYMON_SHAN_LOCKS_HPP

#include "systeminclude.hpp"

#define CACHE_LINE_SIZE         64

class MutexLocker {
  pthread_mutex_t mutex;
public:
  MutexLocker() {
    pthread_mutex_init(&mutex, NULL);
  }
  ~MutexLocker() {
    pthread_mutex_destroy(&mutex);
  }
  void operator ++(int) {
    pthread_mutex_lock(&mutex);
  }
  void operator --(int) {
    pthread_mutex_unlock(&mutex);
  }
};

/*
class SpinLock {
  struct spinlock spin;
public:
  SpinLock() {
    spin_lock_init(spin);
  }
  ~SpinLock() {
  }
  void operator ++(int) {
    spin_lock(&spin);
  }
  void operator --(int) {
    spin_unlock(&spin);    
  }
};
*/

// every locker should in different cache line.
class SpinLocker {
private:
  const static unsigned long _M_FREE = 0;
  const static unsigned long _M_BUSY = 1;
  
  volatile unsigned long locker;

public:
  SpinLocker(unsigned long l = _M_FREE) {
    locker = l;
  }
  void operator ++(int) {
    while (!__sync_bool_compare_and_swap(&locker, _M_FREE, _M_BUSY));    
  }
  void operator --(int) {
    locker = _M_FREE;
  }
} __attribute__ ((aligned(CACHE_LINE_SIZE)));


class SpinInt {
private:
  volatile int value;
  
public:
  SpinInt(int l = 0) {
    value = l;
  }

  operator int() {
    return value;
  }
  void operator = (int v) {
    value = v;
  }
  int operator ++(int) {
    return __sync_fetch_and_add(&value, 1);
  }
  int operator --(int) {
    return __sync_fetch_and_sub(&value, 1);
  }  
    
  int operator +=(int v) {
    return __sync_fetch_and_add(&value, v);
  }
  int operator -=(int v) {
    return __sync_fetch_and_sub(&value, v);
  }
  int operator &=(int v) {
    return __sync_fetch_and_and(&value, v);
  }
  int operator |=(int v) {
    return __sync_fetch_and_or(&value, v);
  }
  int operator ^=(int v) {
    return __sync_fetch_and_xor(&value, v);
  }
  void cas(int oldvalue, int newvalue) {
    while (!__sync_bool_compare_and_swap(&value, oldvalue, newvalue));
    return;
  }
} __attribute__ ((aligned(CACHE_LINE_SIZE)));

#endif  // __RAYMON_SHAN_LOCKS_HPP

