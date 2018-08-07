#include "config.h"

#if NEED_ANDROID_OPENPTY_COMPAT

#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>

int openpty(int* master, int* slave, char* name, const struct termios* t, const struct winsize* ws) {
  *master = getpt();
  if (*master == -1) {
    return -1;
  }

  if (grantpt(*master) == -1 || unlockpt(*master) == -1) {
    close(*master);
    return -1;
  }

  char buf[32];
  if (name == NULL) {
    name = buf;
  }
  if (ptsname_r(*master, name, sizeof(buf)) != 0) {
    close(*master);
    return -1;
  }

  *slave = open(name, O_RDWR|O_NOCTTY);
  if (*slave == -1) {
    close(*master);
    return -1;
  }

  if (t != NULL) {
    tcsetattr(*slave, TCSAFLUSH, t);
  }
  if (ws != NULL) {
    ioctl(*slave, TIOCSWINSZ, ws);
  }

  return 0;
}

#endif

#if NEED_ANDROID_TTYNAME_COMPAT

char* ttyname(int fd) {
  static char buf[64];
  return ttyname_r(fd, buf, sizeof(buf)) == 0 ? buf : NULL;
}

int ttyname_r(int fd, char* buf, size_t len) {
  if (buf == NULL) {
    errno = EINVAL;
    return errno;
  }

  if (!isatty(fd)) {
    return errno;
  }

  char path[64];
  snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);

  ssize_t count = readlink(path, buf, len);
  if (count == -1) {
    return errno;
  }
  if ((size_t)count == len) {
    errno = ERANGE;
    return errno;
  }
  buf[count] = '\0';
  return 0;
}

#endif
