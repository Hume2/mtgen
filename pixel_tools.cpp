#include "pixel_tools.h"

namespace pixel_tools {

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

void derivate_image(png::image<png::rgba_pixel>& img) {
  unsigned int h = img.get_height(), w = img.get_width();
  for (unsigned int y = h-1; y; --y) {
    for (unsigned int x = w-1; x; --x) {
      img[y][x].red = img[y][x].red - img[y-1][x].red - img[y][x-1].red + img[y-1][x-1].red;
      img[y][x].green = img[y][x].green - img[y-1][x].green - img[y][x-1].green + img[y-1][x-1].green;
      img[y][x].blue = img[y][x].blue - img[y-1][x].blue - img[y][x-1].blue + img[y-1][x-1].blue;
      img[y][x].alpha = img[y][x].alpha - img[y-1][x].alpha - img[y][x-1].alpha + img[y-1][x-1].alpha;
    }
  }
  for (unsigned int x = w-1; x; --x) {
    img[0][x].red -= img[0][x-1].red;
    img[0][x].green -= img[0][x-1].green;
    img[0][x].blue -= img[0][x-1].blue;
    img[0][x].alpha -= img[0][x-1].alpha;
  }
  for (unsigned int y = h-1; y; --y) {
    img[y][0].red -= img[y-1][0].red;
    img[y][0].green -= img[y-1][0].green;
    img[y][0].blue -= img[y-1][0].blue;
    img[y][0].alpha -= img[y-1][0].alpha;
  }
}

void integrate_image(png::image<png::rgba_pixel>& img) {
  unsigned int h = img.get_height(), w = img.get_width();
  for (unsigned int x = 1; x < w; ++x) {
    img[0][x].red += img[0][x-1].red;
    img[0][x].green += img[0][x-1].green;
    img[0][x].blue += img[0][x-1].blue;
    img[0][x].alpha += img[0][x-1].alpha;
  }
  for (unsigned int y = 1; y < h; ++y) {
    img[y][0].red += img[y-1][0].red;
    img[y][0].green += img[y-1][0].green;
    img[y][0].blue += img[y-1][0].blue;
    img[y][0].alpha += img[y-1][0].alpha;
  }
  for (unsigned int y = 1; y < h; ++y) {
    for (unsigned int x = 1; x < w; ++x) {
      img[y][x].red = img[y][x].red + img[y-1][x].red + img[y][x-1].red - img[y-1][x-1].red;
      img[y][x].green = img[y][x].green + img[y-1][x].green + img[y][x-1].green - img[y-1][x-1].green;
      img[y][x].blue = img[y][x].blue + img[y-1][x].blue + img[y][x-1].blue - img[y-1][x-1].blue;
      img[y][x].alpha = img[y][x].alpha + img[y-1][x].alpha + img[y][x-1].alpha - img[y-1][x-1].alpha;
    }
  }
}

}
