
#include "include/infra.hpp"

int main(int, char **) {

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);
  
  ThreadInfo *gThreadInfo = new ThreadInfo;
  ConfigureFile *gConfigureFile = new ConfigureFile(__MY_PROGRAM ".conf");
  LogDirectly *gLogDirectly = new LogDirectly();
  SignalHandle *gSignalHandle = new SignalHandle();

  usleep(10);
  int a = 0;
  int b = 100 /a;

  std::cout << b << std::endl;
 
  delete gSignalHandle;
  delete gConfigureFile;
  delete gLogDirectly;
  delete gThreadInfo;

  return 0;

}


