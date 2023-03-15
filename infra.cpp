#include "include/infra.hpp"

typedef class LinkedNode <String, String, SM3Hash, Hash256> StringNode;
typedef class NodeList<String, String, SM3Hash, Hash256> StringList;

String K("abc");
String V("aasdfsdfds242dfadfasdfdsfdsaf");

StringList list(K, V);
volatile int wwait = 1;

void* TestList(void*) {
  do {} while (wwait);

  for (int i = 0; i < 10; i++) {
    printf("%d, %d\n", ThreadStartInfo.threadID, i);
    list.Insert(new StringNode(K, V));
  }

  return NULL;
};

int main(int, char **) {

  printf("%s  %s Compiled %s %s\n", __MY_PROGRAM, __MY_VERSION,  __DATE__, __TIME__);
  
  LogDirectly *gLogDirectly = new LogDirectly();
  ThreadInfo *gThreadInfo = new ThreadInfo();
  SignalHandle *gSignalHandle = new SignalHandle();
  
  list.PrintList();
  
  pthread_t t1 = ThreadInfo::CreateThread("test", TestList, (void*)0xaaa);
  pthread_t t2 = ThreadInfo::CreateThread("errrr", TestList, (void*)0xbbb);
  pthread_t t3 = ThreadInfo::CreateThread("test", TestList, (void*)0xccc);
  //  ThreadInfo::CreateThread("test", TestList, NULL);
  //  ThreadInfo::CreateThread("test", TestList, NULL);
  //  ThreadInfo::CreateThread("test", TestList, NULL);
  wwait = 0;
  void* retv;
  pthread_join(t1, &retv);
  pthread_join(t2, &retv);
  pthread_join(t3, &retv);
  wwait = 0;
  printf("%d\n", list.Size() );
  list.PrintList();
  
  /*
  ConfigureFile *gConfigureFile = new ConfigureFile(__MY_PROGRAM ".conf");
  gLogDirectly->SetLogFileParameter();

  ClassDefine *gClassDefine = new ClassDefine();

  
  delete gClassDefine;
  delete gConfigureFile;
  */
  delete gSignalHandle;
  delete gThreadInfo;
  delete gLogDirectly;
  


  return 0;
}


