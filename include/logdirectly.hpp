#ifndef __RAYMON_SHAN_LOG_DIRECTLY_HPP
#define __RAYMON_SHAN_LOG_DIRECTLY_HPP

#include "infra.hpp"

class LogDirectly {
public:
  LogDirectly() {
    threadid = 0x12345678;
  };

  static thread_local char timebuffer[100];
  static thread_local unsigned int threadid;
  static int loghandle;
  static int loglevel;

  static char* Initialize() {
    threadid = syscall(SYS_gettid);
    return NULL;
  }
  static unsigned int GetThreadId() {
    return threadid;
  }  
};

char thread_local LogDirectly::timebuffer[100];
unsigned int thread_local LogDirectly::threadid;
int LogDirectly::loghandle;
int LogDirectly::loglevel;

#endif  // __RAYMON_SHAN_LOG_DIRECTLY_HPP

