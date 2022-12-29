#ifndef __RAYMON_SHAN_SIGNAL_HANDLE_HPP
#define __RAYMON_SHAN_SIGNAL_HANDLE_HPP

#include "infra.hpp"

// following https://blog.csdn.net/djinglan/article/details/8726871
class SignalHandle {
public:
  static void SignalParser(int signo) {
    void *signbuffer[30] = {0};
    size_t signbuffersize, i;
    char **stackstrings = NULL;

    printf("In process sign");
    signbuffersize = backtrace(signbuffer, 30);
    fprintf(stdout, "Signal %d handle, Obtained %zd stack frames\n",
	    signo, signbuffersize);
    stackstrings = backtrace_symbols(signbuffer, signbuffersize);
    for (i = 0; i < signbuffersize; i++) {
      fprintf(stdout, "%s\n", stackstrings[i]);
    }
    free(stackstrings);
    exit(0);
  }

  SignalHandle() {
    if (signal(SIGSEGV, SignalParser) == SIG_ERR) {
      fprintf(stdout, "Error in Handle Signal SIGSEGV");
      exit(1);
    }
    if (signal(SIGILL, SignalParser) == SIG_ERR) {
      fprintf(stdout, "Error in Handle Signal SIGILL");
      exit(1);
    }
    if (signal(SIGTERM, SignalParser) == SIG_ERR) {
      fprintf(stdout, "Error in Handle Signal SIGTERM");
      exit(1);
    }
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {  // avoid closed by remote RST
      fprintf(stdout, "Error in Handle Signal SIGPIPE");
      exit(1);
    }
  }
};

#endif  // __RAYMON_SHAN_SIGNAL_HANDLE_HPP
