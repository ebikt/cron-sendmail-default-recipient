#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef SBINDIR
#define SBINDIR /usr/sbin
#endif

#define Q(S) #S
#define QA(S) Q(S)

#define RECIPIENTFILE  "/etc/cron-sendmail-default-recipient"
#define CMD_SENDMAIL   QA(SBINDIR) "/cron-sendmail-default-original"

#define ERROR(RET, MSG) { write(2, MSG "\n", sizeof(MSG)); return RET; }

int main (int argc, char **argv) {
  int i, fd, len;
  char buffer[1024], *start;
  if (argv[argc] != NULL) ERROR(67, "Assertion error: argv[argc] must be NULL")

  switch (argc < 3) {
    case 0: // There is program name and at least two arguments

      for (i=0; i < argc; i++) if (strcmp(argv[i],"-FCronDaemon") == 0) break;
      if (i == argc) break; // No -FCronDaemon in arguments
      i = argc - 1;

      if (strchr(argv[i],'@') != NULL) break; // Do not rewrite remote recipient

      // Read new recipient from RECIPIENTFILE
      fd = open(RECIPIENTFILE, O_RDONLY);
      if (fd == -1) break;
      len = read(fd, buffer, 1023);
      close(fd);
      while (len > 1 && buffer[len-1] <= ' ') len--;
      buffer[len] = 0;
      argv[argc-1] = buffer;
      start = buffer;
      while (*start != 0 && *start <= ' ') start++;
      if (*start == 0) break;

      argv[argc-1] = start;
  }
  execv(CMD_SENDMAIL, argv);
  ERROR(66, "Cannot execute " CMD_SENDMAIL);
}
