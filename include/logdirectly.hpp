#ifndef __RAYMON_SHAN_LOG_DIRECTLY_HPP
#define __RAYMON_SHAN_LOG_DIRECTLY_HPP

#include "infra.hpp"

#define LEVEL_LOG_NONE         0
#define LEVEL_LOG_CRIT         1
#define LEVEL_LOG_EROR         2
#define LEVEL_LOG_WARN         3
#define LEVEL_LOG_INFO         4
#define LEVEL_LOG_DBUG         5
#define LEVEL_LOG_TRAC         6

class LogDirectly {
public:
  static thread_local char timeBuffer[NORMAL_CHAR_LENGTH];
  static int logFileHandle;
  static int logFileLevel;
  static int logTermLevel;

  static void SetLogFileLevel(int level) {
    logFileLevel = level;
  };
  static void SetLogTermLevel(int level) {
    logTermLevel = level;
  };
  static bool IsFileLog(int level) {
    return level <= logFileLevel;
  }
  static bool IsTermLog(int level) {
    return level <= logTermLevel;
  }
  static int GetLogHandle() {
    return logFileHandle;
  }
  static char* GetTimeBuffer() {
    return timeBuffer;
  }
  static unsigned int GetThreadID() {
    return infra::ThreadInfo::threadID;
  }
  static char* GetThreadName() {
    return infra::ThreadInfo::threadInfo.threadName;
  }  
  static void GetFormat() {
    time_t time_struct;
    time(&time_struct);
    struct tm *gmt = localtime(&time_struct);
    strftime(timeBuffer, 32, "%Y-%m-%d %T", gmt);
  }
};

#define rname(x) strrchr(x,'/')?strrchr(x,'/')+1:x

#define FORMAT "[%s][%8s:%-6d][%s][%16s:%-3d] "
#define CREND "\n"
#define CNAME infra::LogDirectly
#define ARGVS(LEVEL) \
  CNAME::GetTimeBuffer(), CNAME::GetThreadName(), CNAME::GetThreadID(),        \
    LEVEL, rname(__FILE__), __LINE__

#define _LOG_FILE_OUT(LEVEL, format, args...)                                  \
  if (CNAME::GetLogHandle() > 0)                                               \
    dprintf(CNAME::GetLogHandle(), FORMAT format CREND, ARGVS(LEVEL), ##args);
#define _LOG_TERM_OUT(LEVEL, format, args...)                                  \
  printf(FORMAT format CREND, ARGVS(LEVEL), ##args);

#define _LOG_INFO(format, args...)                                             \
  if (CNAME::IsFileLog(LEVEL_LOG_INFO) || CNAME::IsTermLog(LEVEL_LOG_INFO)) {  \
    CNAME::GetFormat();                                                        \
    if (CNAME::IsFileLog(LEVEL_LOG_INFO)) _LOG_FILE_OUT("INFO", format, ##args)\
    if (CNAME::IsTermLog(LEVEL_LOG_INFO)) _LOG_TERM_OUT("INFO", format, ##args)\
  };


int LogDirectly::logFileHandle;
int LogDirectly::logFileLevel;
int LogDirectly::logTermLevel;
char thread_local LogDirectly::timeBuffer[NORMAL_CHAR_LENGTH];

#endif  // __RAYMON_SHAN_LOG_DIRECTLY_HPP

