#ifndef __RAYMON_SHAN_SIGNAL_HANDLE_HPP
#define __RAYMON_SHAN_SIGNAL_HANDLE_HPP

#include "infra.hpp"

// following https://blog.csdn.net/djinglan/article/details/8726871
// -no-pie is important https://blog.csdn.net/kuno_y/article/details/125545762
// signal https://www.xiexianbin.cn/linux/basic/linux-signal/index.html?to_index=1
/*
 1) SIGHUP	 2) SIGINT	 3) SIGQUIT	 4) SIGILL	 5) SIGTRAP
 6) SIGABRT	 7) SIGBUS	 8) SIGFPE	 9) SIGKILL	10) SIGUSR1
11) SIGSEGV	12) SIGUSR2	13) SIGPIPE	14) SIGALRM	15) SIGTERM
16) SIGSTKFLT	17) SIGCHLD	18) SIGCONT	19) SIGSTOP	20) SIGTSTP
21) SIGTTIN	22) SIGTTOU	23) SIGURG	24) SIGXCPU	25) SIGXFSZ
26) SIGVTALRM	27) SIGPROF	28) SIGWINCH	29) SIGIO	30) SIGPWR
31) SIGSYS	34) SIGRTMIN	35) SIGRTMIN+1	36) SIGRTMIN+2	37) SIGRTMIN+3
38) SIGRTMIN+4	39) SIGRTMIN+5	40) SIGRTMIN+6	41) SIGRTMIN+7	42) SIGRTMIN+8
43) SIGRTMIN+9	44) SIGRTMIN+10	45) SIGRTMIN+11	46) SIGRTMIN+12	47) SIGRTMIN+13
48) SIGRTMIN+14	49) SIGRTMIN+15	50) SIGRTMAX-14	51) SIGRTMAX-13	52) SIGRTMAX-12
53) SIGRTMAX-11	54) SIGRTMAX-10	55) SIGRTMAX-9	56) SIGRTMAX-8	57) SIGRTMAX-7
58) SIGRTMAX-6	59) SIGRTMAX-5	60) SIGRTMAX-4	61) SIGRTMAX-3	62) SIGRTMAX-2
63) SIGRTMAX-1	64) SIGRTMAX
*/
const char *SignalName[] = {
  NULL,      "SIGHUP",  "SIGINT",  "SIGQUIT", "SIGILL",  "SIGTRAP", "SIGABRT", "SIGBUS",
  "SIGFPE",  "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM"
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

#endif  // __RAYMON_SHAN_SIGNAL_HANDLE_HPP
