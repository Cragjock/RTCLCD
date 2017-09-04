#ifndef MYCRON_H_INCLUDED
#define MYCRON_H_INCLUDED


#include <iostream>
#include <vector>
#include "pitime.h"
#include "lcd_class.h"
#include <unistd.h> /// for sleep
#include <fcntl.h>
#include <termios.h>

#define BAUDRATE B19200
int set_term();




#endif // MYCRON_H_INCLUDED
