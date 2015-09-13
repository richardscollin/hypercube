#include <errno.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

int const DEVICE_ADDRESS = 105;

#define GYRO_XOUT_H 29
#define GYRO_XOUT_L 30
#define GYRO_YOUT_H 31
#define GYRO_YOUT_L 32
#define GYRO_ZOUT_H 33
#define GYRO_ZOUT_L 34


static int fd;

void create_i2c() {
     fd = open("/dev/i2c-1", O_RDWR);
}

void clean_i2c() {
    close(fd);
}

int gyro_x() {
    int low, high;
    char buf[1];

    ioctl(fd, I2C_SLAVE, DEVICE_ADDRESS);

    buf[1] = GYRO_XOUT_H;
    write(fd, buf, 1);
    read(fd, buf, 1);
    high = buf[0];

    buf[1] = GYRO_XOUT_L;
    write(fd, buf, 1);
    read(fd, buf, 1);
    low = buf[0];

    return high | (low << 8);
}

int main()
{
    create_i2c();
    printf("%d\n", gyro_x());
}

