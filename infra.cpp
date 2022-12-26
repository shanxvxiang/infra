
#include "include/infra.hpp"

int main(int argc, char **argv) {
  std::filebuf cfgbuf;
  
  if (cfgbuf.open("infra.conf", std::ios::in)) {
    std::istream cfgfile(&cfgbuf);
    antlr4::ANTLRInputStream cfginput(cfgfile);
    ConfigureFileLexer cfglexer(&cfginput);
    antlr4::CommonTokenStream cfgtokens(&cfglexer);
    ConfigureFileParser cfgparser(&cfgtokens);
    antlr4::tree::ParseTree* cfgtree = cfgparser.allConfigFile();

    infra::ConfigureFileParseImplement cfgimpl;
    cfgimpl.visit(cfgtree);
    cfgimpl.IteratorParameter();
    cfgbuf.close();
  }


  return 0;
}

