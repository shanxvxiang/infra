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

#define COLOR_CRIT "\033[5;31m"
#define COLOR_EROR "\033[0;31m"
#define COLOR_WARN "\033[0;33m"
#define COLOR_INFO "\033[0;32m"
#define COLOR_DBUG "\033[0;37m"
#define COLOR_TRAC "\033[1;37m"
#define COLOR_END  "\033[0m"

class LogDirectly {
public:
  LogDirectly() {
    SetLogFileParameter();
  };
  static thread_local char timeBuffer[SMALL_CHAR_LENGTH];
  static int LogFileHandle;
  static std::string LogPath;
  static int LogFileLines;                      // open new log file for overload
  static int LogFileLevel;
  static int LogTermLevel;

  static void SetLogFileLevel(int level) {
    LogFileLevel = level;
  };
  static void SetLogTermLevel(int level) {
    LogTermLevel = level;
  };
  static bool IsFileLog(int level) {
    return (level <= LogFileLevel);
  }
  static bool IsTermLog(int level) {
    return (level <= LogTermLevel);
  }
  static int GetLogHandle() {
    return LogFileHandle;
  }
  static char* GetTimeBuffer() {
    return timeBuffer;
  }
  static unsigned int GetThreadID() {
    return ThreadInfo::threadID;
  }
  static char* GetThreadName() {
    return ThreadInfo::threadInfo.threadName;
  }  
  static void GetFormat() {
    time_t time_struct;
    time(&time_struct);
    struct tm *gmt = localtime(&time_struct);
    strftime(timeBuffer, 32, "%Y-%m-%d:%T", gmt);
  }
  static void ShouldOpenLogFile();
  static void SetLogFileParameter();
};

#define FORMAT "[%s][%8s:%-6d][%s][%18s:%-4d]"
#define CREND "\n"
#define CNAME LogDirectly
#define ARGVS(LEVEL) \
  CNAME::GetTimeBuffer(), CNAME::GetThreadName(), CNAME::GetThreadID(),        \
    LEVEL, RightOfSlash((char*)__FILE__), __LINE__

#define _LOG_FILE_OUT(LEVEL, format, args...)                                  \
  if (CNAME::GetLogHandle() > 0) {					       \
      CNAME::ShouldOpenLogFile();                                              \
      dprintf(CNAME::GetLogHandle(), FORMAT " " format CREND, ARGVS(LEVEL), ##args);\
  }
#define _LOG_TERM_OUT(LEVEL, COLOR, format, args...)	\
  printf(COLOR FORMAT COLOR_END " " format CREND, ARGVS(LEVEL), ##args);

#define _LOG_COMMAND(LEVEL, format, args...)		                       \
  if ( CNAME::IsFileLog( JOIN(LEVEL_LOG_, LEVEL))  ||                          \
       CNAME::IsTermLog( JOIN(LEVEL_LOG_, LEVEL))  ) {	                       \
    CNAME::GetFormat();                                                        \
    if (CNAME::IsFileLog( JOIN(LEVEL_LOG_, LEVEL)))                            \
      _LOG_FILE_OUT(TOSTRING(LEVEL), format, ##args)                           \
    if (CNAME::IsTermLog( JOIN(LEVEL_LOG_, LEVEL)))	                       \
      _LOG_TERM_OUT(TOSTRING(LEVEL), JOIN(COLOR_, LEVEL), format, ##args) }

#define _LOG_CRIT(format, args...)     _LOG_COMMAND(CRIT, format, ##args)
#define _LOG_EROR(format, args...)     _LOG_COMMAND(EROR, format, ##args)
#define _LOG_WARN(format, args...)     _LOG_COMMAND(WARN, format, ##args)
#define _LOG_INFO(format, args...)     _LOG_COMMAND(INFO, format, ##args)
#define _LOG_DBUG(format, args...)     _LOG_COMMAND(DBUG, format, ##args)
#define _LOG_TRAC(format, args...)     _LOG_COMMAND(TRAC, format, ##args)

int LogDirectly::LogFileHandle = 0;
std::string LogDirectly::LogPath;
int LogDirectly::LogFileLines;
int LogDirectly::LogFileLevel = 0;
int LogDirectly::LogTermLevel = 6;              // start value
char thread_local LogDirectly::timeBuffer[SMALL_CHAR_LENGTH];

#define GetSingleConfigSegment(ret, keyword, type)	                       \
  ret = GetSingleConfig(keyword);                                              \
  if (ret) {                                                                   \
    _LOG_CRIT("%s <%s:%s>", ret, TOSTRING(keyword), type);                     \
    exit(1);                                                                   \
  }

void LogDirectly::ShouldOpenLogFile() {
  static int linenow = 0;
  struct stat logstat;
  char logfilename[NORMAL_CHAR_LENGTH];

  if (linenow == 0 || LogFileHandle <= 0) {
    if (LogPath[LogPath.size()-1] == '/' &&
	stat(LogPath.c_str(), &logstat) == 0 &&
	(logstat.st_mode & S_IFDIR)) {
      if (LogFileHandle) close(LogFileHandle);
      GetFormat();
      snprintf(logfilename, NORMAL_CHAR_LENGTH, "%s%s%s",
	       LogPath.c_str(), __MY_PROGRAM, timeBuffer);
      LogFileHandle = open(logfilename,
			   O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    } else {
      _LOG_EROR(ERROR_INVALID_LOGPATH " <%s>", LogPath.c_str());
      exit(1);
    }
    if (LogFileHandle == -1) {
      _LOG_EROR(ERROR_INVALID_LOGFILE " <%s>", logfilename);
      exit(1);
    }
    dprintf(LogFileHandle, "[   DATE   :  TIME  ][THREAD NAME:ID ][LEVL]"
	    "[       SOURCE FILE:LINE] DESCRIBE\n");
  }
  if (linenow++ >= LogFileLines - 1) linenow = 0;
}

void LogDirectly::SetLogFileParameter() {
  char *ret;

  GetSingleConfigSegment(ret, LogPath, "string");
  GetSingleConfigSegment(ret, LogFileLines, "int");
  if (LogFileLines < 1) {
    _LOG_CRIT(ERROR_INVALID_LOGLINES " <%d>", LogFileLines);
    exit(1);
  }
  GetSingleConfigSegment(ret, LogFileLevel, "int");
  if (LogFileLevel > LEVEL_LOG_TRAC) {
    _LOG_CRIT(ERROR_INVALID_LOGFILELEVEL " <%d> should be 0~6", LogFileLevel);
    exit(1);
  }
  LogTermLevel = LogFileLevel;
  ShouldOpenLogFile();
  
};
#endif  // __RAYMON_SHAN_LOG_DIRECTLY_HPP

