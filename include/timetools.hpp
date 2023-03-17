#ifndef __RAYMON_SHAN_TIME_TOOLS_HPP
#define __RAYMON_SHAN_TIME_TOOLS_HPP

#include "infra.hpp"

class TimeSpend { 
  struct timeval tpstart, tpend;
public:
  TimeSpend() {};
  void TimeStart() {
    gettimeofday(&tpstart, NULL);
  }
  int TimeClick() {
    gettimeofday(&tpend, NULL);    
    int ret = 1000000 * (tpend.tv_sec - tpstart.tv_sec) + tpend.tv_usec - tpstart.tv_usec;
    tpstart = tpend;
    return ret;
  }
};

#endif  // __RAYMON_SHAN_TIME_TOOLS_HPP
