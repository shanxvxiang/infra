#ifndef __RAYMON_SHAN_COMMON_HPP
#define __RAYMON_SHAN_COMMON_HPP

#define __MY_PROGRAM            "infra"
#define __MY_VERSION            "v0.1"

#define _TOSTRING(x)            #x
#define TOSTRING(x)             _TOSTRING(x)
#define _JOIN(x,y)              x ## y
#define JOIN(x,y)               _JOIN(x,y)

typedef union {
  long l_value;
  long *l_addr;
  void *v_addr;
  char *p_addr;
  char **pp_addr;
}ADDR, *PADDR;

#define SMALL_CHAR_LENGTH       32
#define NORMAL_CHAR_LENGTH      128
//#define 
#define CACHE_LINE_SIZE         64



#endif  // __RAYMON_SHAN_COMMON_HPP
