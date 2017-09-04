
#ifndef RTC_H_
#define RTC_H_

#include "myi2c.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <cstdint>
#include <unistd.h>
#include <errno.h>
#include <cstdio>
#include <cstdlib>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <ctime>


#include "pitime.h"
#include "lcd_class.h"
//#include <unistd.h> /// for sleep

#include <termios.h>

#define BAUDRATE B19200
int set_term();

#define I2C_SLAVE_ADDRESS     0x6f    // device slave address, hard coded
#define SRAM_SIZE       0x20    // 64 bytes 0-3f
#define SRAM_START      0x20
#define TIMEKEEPSTART   0x00
#define RTCSEC          0x00
#define RTCMIN          0x01
#define RTCHR           0x02
#define RTCWKDAY        0x03
#define RTCDATE         0x04
#define RTCMTH          0x05
#define RTCYR           0x06
#define RTC_CONTROL     0x07
#define RTC_OSCTRIM     0x08
#define PWRDNMIN        0x18



#endif // RTC_H_





/**
 *
 * per command linei2cdetect -F 1
 * SMBusBlock write yes
 * SMBusBlock read no
 *
 * I2C block Write & read yes, yes
 *
 */







