#include "pixel_tools.h"

unsigned int clr_to_int(png::rgba_pixel clr) {
  unsigned int result = 0;

  for (int i = 0; i < 8; ++i) {
    result += (clr.blue & 1) << (3*i);
    clr.blue = clr.blue >> 1;

    result += (clr.green & 1) << (3*i + 1);
    clr.green = clr.green >> 1;

    result += (clr.red & 1) << (3*i + 2);
    clr.red = clr.red >> 1;
  }

  result += clr.alpha << 24;
  return result;
}

png::rgba_pixel int_to_clr(unsigned int iii) {
  png::rgba_pixel result(0, 0, 0, 0);
  result.alpha = iii >> 24;
  iii &= 0x00FFFFFF;

  for (int j = 23; j >= 0; --j) {
    switch (j % 3) {
      case 0:
        result.blue = result.blue << 1;
        result.blue |= (iii & (1 << j)) >> j;
        break;
      case 1:
        result.green = result.green << 1;
        result.green |= (iii & (1 << j)) >> j;
        break;
      case 2:
        result.red = result.red << 1;
        result.red |= (iii & (1 << j)) >> j;
        break;
      default:
        break;
    }
  }

  return result;
}

