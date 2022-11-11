/****************************************************************************
 * hostif/host_i2c_main.c
 *
 *   Copyright 2021 Sony Semiconductor Solutions Corporation
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of Sony Semiconductor Solutions Corporation nor
 *    the names of its contributors may be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <debug.h>
#include <nuttx/i2c/i2c_master.h>
#include "rgbMatrix.h"
/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/* I2C settings */

#define I2C_SLAVE_ADDR 0x24
#define I2C_SPEED I2C_SPEED_FAST

/* ICMD defnitions */

#define ICMD_AVAILABLE_SIZE(n) (0x10 + (n))
#define ICMD_FIXLEN_TRANS(n) (0x80 + (n))
#define ICMD_VARLEN_TRANS(n) (0xa0 + (n))

/* User defined buffer id */

#define WRITE_BUFFER 0
#define READ_BUFFER 1
#define VERSION_BUFFER 2
#define TIMESTAMP_BUFFER 3

uint8_t rectangle_coor[] = {0, 0, 7, 7};

uint8_t green[][2] = {{2, 1}, {3, 1}, {5, 1}, {1, 2}, {2, 2}, {4, 2}, {5, 2}, {6, 2}, {1, 3}, {2, 3}, {3, 3}, {4, 3}, {6, 3}, {2, 4}, {4, 4}, {5, 4}, {1, 5}, {3, 5}, {5, 5}, {6, 5}, {1, 6}, {2, 6}, {5, 6}, {6, 6}};

uint8_t flash[][2] = {{4, 1}, {3, 2}, {5, 3}, {3, 4}, {2, 5}, {4, 5}};
uint8_t red[][2] = {{0, 3}, {7, 3}, {0, 6}, {7, 6}};
uint8_t yellow[][2] = {{3, 0}, {4, 0}, {3, 6}, {4, 6}, {3, 7}, {4, 7}};
uint8_t color[7][3] = {{255, 0, 0},
                       {255, 102, 0},
                       {255, 255, 0},
                       {0, 255, 0},
                       {0, 128, 128},
                       {0, 0, 255},
                       {128, 0, 128}};

void tree()
{
  int lenTotal_green = sizeof(green) / sizeof(uint8_t);
  int lenLow_green = sizeof(green[0]) / sizeof(uint8_t);
  int lenHigh_green = lenTotal_green / lenLow_green;
  for (int i = 0; i < lenHigh_green; i++)
  {
    draw_point_color(green[i], 0, 255, 0);
  }
  image_test();
  int lenTotal_yellow = sizeof(yellow) / sizeof(uint8_t);
  int lenLow_yellow = sizeof(yellow[0]) / sizeof(uint8_t);
  int lenHigh_yellow = lenTotal_yellow / lenLow_yellow;
  for (int i = 0; i < lenHigh_yellow; i++)
  {
    draw_point_color(yellow[i], 255, 255, 0);
  }
  image_test();
  int lenTotal_red = sizeof(red) / sizeof(uint8_t);
  int lenLow_red = sizeof(red[0]) / sizeof(uint8_t);
  int lenHigh_red = lenTotal_red / lenLow_red;
  for (int i = 0; i < lenHigh_red; i++)
  {
    draw_point_color(red[i], 255, 0, 0);
  }
  image_test();
}

int i = 0;
void dot()
{
  int lenTotal_flash = sizeof(flash) / sizeof(uint8_t);
  int lenLow_flash = sizeof(flash[0]) / sizeof(uint8_t);
  int lenHigh_flash = lenTotal_flash / lenLow_flash;
  // for (int i=0; i<lenHigh_flash; i++){
  //   draw_point_color(flash[i],100,100,100);
  // }
  // image_test();
  for (int j = 0; j < lenHigh_flash; j++)
  {
    draw_point_color(flash[j], color[i][0], color[i][1], color[i][2]);
    i++;
    if (i == 7)
    {
      i = 0;
    }
  }
  image_test();
  usleep(200000);
}

int main(int argc, FAR char *argv[])
{
  RGBMatrixInit();
  draw_rectangle_color(rectangle_coor, 0, 0, 0);
  tree();
  for (;;)
  {
    dot();
  }
  return 0;
}
