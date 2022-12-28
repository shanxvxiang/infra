
#include "include/infra.hpp"

void *threadfunc1(void *arg)
{
  char buffer[1000];
  sprintf(buffer, "%s %s %s\n",
	  infra::ThreadInfo::threadInfo.threadName, "first", (char*)arg);
  std::cout << buffer;
  return (void *)0;
}

void *threadfunc2(void *arg)
{
  char buffer[1000];
  sprintf(buffer, "%s %s %s\n",
	  infra::ThreadInfo::threadInfo.threadName, "second", (char*)arg);
  std::cout << buffer;
  return (void *)0;
}

char first[] = "FIRST";
char second[] = "SECOND";

int main(int /*argc*/, char **/*argv*/) {

  infra::ThreadInfo *gThreadInfo = new(infra::ThreadInfo);

  delete gThreadInfo;

  infra::LogDirectly::SetLogTermLevel(6);
  _LOG_TERM_OUT("INFO", "%s", "asdfsdf");
  _LOG_INFO("%d %s", 333, "fdsafdsfd");

  return 0;

  
  std::filebuf cfgbuf;
  
  if (cfgbuf.open("infra.conf", std::ios::in)) {
    std::istream cfgfile(&cfgbuf);
    antlr4::ANTLRInputStream cfginput(cfgfile);
    ConfigureFileLexer cfglexer(&cfginput);
    antlr4::CommonTokenStream cfgtokens(&cfglexer);
    ConfigureFileParser cfgparser(&cfgtokens);
    antlr4::tree::ParseTree* cfgtree = cfgparser.allConfigFile();

    infraapp::ConfigureFileParseImplement cfgimpl;
    cfgimpl.visit(cfgtree);
    cfgimpl.IteratorParameter();
    cfgbuf.close();
  }

  return 0;
}

