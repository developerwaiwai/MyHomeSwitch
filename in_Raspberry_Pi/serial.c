#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <time.h>

#define DEV_NAME "/dev/ttyACM0"
#define BAUD_RATE B9600


void serialInitialize(int fd) {

  struct termios t;
  memset(&t, 0, sizeof(t));
  t.c_cflag = CS8 | CLOCAL | CREAD;
  t.c_cc[VTIME] = 100;

  cfsetispeed(&t, BAUD_RATE);
  cfsetospeed(&t, BAUD_RATE);

  tcsetattr(fd, TCSANOW, &t);

}

int main() {

  int fd;
  char oneBuffer = 0x01;

  fd = open(DEV_NAME, O_RDWR | O_NONBLOCK );
  if(fd < 0) {
    printf("ERROR open\n");
    exit(1);
  }

  serialInitialize(fd);

  write(fd, &oneBuffer, 1);

  close(fd);

}
