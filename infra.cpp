
#include <iostream>
#include "include/parse/ConfigureFileLexer.h"
#include "include/parse/ExprParser.h"
#include "include/infra.hpp"

int main(int argc, char **argv) {
  std::filebuf cfgbuf;
  if (cfgbuf.open("infra.conf", std::ios::in)) {
    std::istream cfgfile(&cfgbuf);
    antlr4::ANTLRInputStream cfginput(cfgfile);
    ConfigureFileLexer cfglexer(&cfginput);
    antlr4::CommonTokenStream cfgtokens(&cfglexer);
    ConfigureFileParser cfgparser(&cfgtokens);
    antlr4::tree::ParseTree* cfgtree = cfgparser.allConfig();

    ConfigureFileImplement cfg;
    cfg.visit(cfgtree);
    cfgbuf.close();
  }
  return 0;
}

