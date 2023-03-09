#include "include/infra.hpp"

int main(int, char **) {

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);
  /*
  LogDirectly *gLogDirectly = new LogDirectly();
  ThreadInfo *gThreadInfo = new ThreadInfo();
  SignalHandle *gSignalHandle = new SignalHandle();
  ConfigureFile *gConfigureFile = new ConfigureFile(__MY_PROGRAM ".conf");
  gLogDirectly->SetLogFileParameter();

  ClassDefine *gClassDefine = new ClassDefine();

  
  delete gClassDefine;
  delete gConfigureFile;
  delete gSignalHandle;
  delete gThreadInfo;
  delete gLogDirectly;
  */

  String K("abc");
  String V("aasdfsdfds242dfadfasdfdsfdsaf");
  
  StringNode node(K, V);
  node.PrintHash();
  return 0;

}


