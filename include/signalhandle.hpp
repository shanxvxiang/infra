#ifndef __RAYMON_SHAN_SIGNAL_HANDLE_HPP
#define __RAYMON_SHAN_SIGNAL_HANDLE_HPP

#include "infra.hpp"

// following https://blog.csdn.net/djinglan/article/details/8726871
// -no-pie is important https://blog.csdn.net/kuno_y/article/details/125545762
// signal https://www.xiexianbin.cn/linux/basic/linux-signal/index.html?to_index=1
// addr2line https://github.com/cyicz123/addr2line
//           https://github.com/evmar/maddr

const char *SignalName[] = {
  NULL,       "SIGHUP",   "SIGINT",   "SIGQUIT",
  "SIGILL",   "SIGTRAP",  "SIGABRT",  "SIGBUS",
  "SIGFPE",   "SIGKILL",  "SIGUSR1",  "SIGSEGV",
  "SIGUSR2",  "SIGPIPE",  "SIGALRM",  "SIGTERM",
  "SIGSTKFLT","SIGCHLD",  "SIGCONT",  "SIGSTOP",
  "SIGTSTP",  "SIGTTIN",  "SIGTTOU",  "SIGURG",
  "SIGXCPU",  "SIGXFSZ",  "SIGVTALRM","SIGPROF",
  "SIGWINCH", "SIGIO",    "SIGPWR",   "SIGSYS"
};

class SignalHandle {
public:
  static void SignalParser(int signo) {
    void *signbuffer[30] = {0};
    size_t signbuffersize, i;
    char **stackstrings = NULL;

    printf("In process sign");
    signbuffersize = backtrace(signbuffer, 30);
    fprintf(stdout, "Signal %s(%d) handle, Obtained %zd stack frames\n",
	    SignalName[signo], signo, signbuffersize);
    stackstrings = backtrace_symbols(signbuffer, signbuffersize);
    for (i = 0; i < signbuffersize; i++) {
      fprintf(stdout, "%s\n", stackstrings[i]);
    }
    free(stackstrings);
    exit(0);
  }

  SignalHandle() {
    if (signal(SIGFPE, SignalParser) == SIG_ERR) {
      fprintf(stdout, "Error in Handle Signal SIGFPE");
      exit(1);
    }
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
    if (signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
      // avoid closed by remote RST for TCP closed socket
      fprintf(stdout, "Error in Handle Signal SIGPIPE");
      exit(1);
    }
  }
};

extern "C" {
void SignalParser(int signo) {
  SignalHandle::SignalParser(signo);
};
}
#endif  // __RAYMON_SHAN_SIGNAL_HANDLE_HPP
