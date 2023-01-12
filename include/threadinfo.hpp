#ifndef __RAYMON_SHAN_THREAD_INFO_HPP
#define __RAYMON_SHAN_THREAD_INFO_HPP

#include "systeminclude.hpp"
#include "raymoncommon.hpp"
#include "lockers.hpp"

struct threadStartInfo {
  char threadName[SMALL_CHAR_LENGTH];
  void *(*threadFunc)(void *);
  void *threadArg;
};

void *InitializeThread(void *arg);


class ThreadInfo {
public:
  ThreadInfo() {
    strncpy(threadInfo.threadName, "MAIN", SMALL_CHAR_LENGTH - 1);
    threadID = syscall(SYS_gettid);
  };
  static MutexLock serializeMutex;
  
  static thread_local threadStartInfo threadInfo;
  static thread_local unsigned int threadID;

  static int CreateThread(char *tname, void *(*func)(void *), void *arg) {
    pthread_t tid;
    threadStartInfo startInfo;

    serializeMutex++;
    strncpy(startInfo.threadName, tname, SMALL_CHAR_LENGTH - 1);
    startInfo.threadFunc = func;
    startInfo.threadArg = arg;
    pthread_create(&tid, NULL, InitializeThread, &startInfo);
    // should add control for return
    pthread_join(tid, NULL);
    return 0;
  };
};

#ifndef __RAYMON_SHAN_FOR_L_Y

void *InitializeThread(void *arg)
{
  memcpy(&ThreadInfo::threadInfo, arg, sizeof(threadStartInfo));
  ThreadInfo::serializeMutex--;
  
  ThreadInfo::threadID = syscall(SYS_gettid);
  
  return ThreadInfo::threadInfo.threadFunc(ThreadInfo::threadInfo.threadArg);
}

MutexLock ThreadInfo::serializeMutex;
threadStartInfo thread_local ThreadInfo::threadInfo;
unsigned int thread_local ThreadInfo::threadID;

#endif // __RAYMON_SHAN_FOR_L_Y



#endif  // __RAYMON_SHAN_THREAD_INFO_HPP

