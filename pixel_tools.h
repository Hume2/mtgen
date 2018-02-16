#ifndef PIXEL_TOOLS_H
#define PIXEL_TOOLS_H

#include <png++/png.hpp>

namespace pixel_tools {

unsigned int clr_to_int(png::rgba_pixel clr);
png::rgba_pixel int_to_clr(unsigned int iii);

void derivate_image(png::image<png::rgba_pixel>& img);
void integrate_image(png::image<png::rgba_pixel>& img);

}

#endif // PIXEL_TOOLS_H
