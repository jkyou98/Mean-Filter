/**
 * @file main.c
 * @author your name (jkyou98@gmail.com)
 * @brief This is Demo Code for MeanFilter and use NUCL raw image as example
 * @version 0.1
 * @date 2022-01-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "BMP.h"
#include "Mean_Filter.h"
#include "MinMax_Mapping.h"
#include "RAW.h"
#include "param.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IMAGE_PATH "res/lena_gray_noise.raw" ///<
#define IMAGE_BIT 8
#define WIDTH 512
#define HEIGHT 512
#define MF_SIZE 3

int
main (void)
{
  char filepath[256];
  uint8_t *In_Out_IMG
      = (uint8_t *)calloc (WIDTH * HEIGHT, sizeof (uint8_t));
  uint16_t IMG_padding_w = WIDTH + (MF_SIZE / 2) * 2,
           IMG_padding_h = HEIGHT + (MF_SIZE / 2) * 2;
  uint8_t *IMG_padding
      = (uint8_t *)calloc (IMG_padding_w * IMG_padding_h, sizeof (uint8_t));

  // initialize parameters
  ImageInfo IMG_Info = { .image = (void *)In_Out_IMG,
                         .width = WIDTH,
                         .height = HEIGHT,
                         .bit = IMAGE_BIT };
  Mean_Filter_param MF_Param
      = { .image_padding = (void *)IMG_padding, .MF_size = MF_SIZE };
  // Reading Image
  sprintf (filepath, "%s", IMAGE_PATH);
  RAW_READ_uint8_t (filepath, In_Out_IMG, WIDTH, HEIGHT);

  // MeanFilter (mask = 3)
  Mean_Filter (&IMG_Info, &MF_Param);

  // Save the Output_IMG

  RAW_WRITE_uint8_t ("lena_gray_noise_MFsize3.raw", In_Out_IMG, WIDTH, HEIGHT);
  BMP_W_GRAY_8BIT ("lena_gray_noise_MFsize3.bmp", In_Out_IMG, WIDTH, HEIGHT);

  free (In_Out_IMG);
  return 0;
}