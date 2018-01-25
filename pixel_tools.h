#ifndef PIXEL_TOOLS_H
#define PIXEL_TOOLS_H

#include <png++/png.hpp>

unsigned int clr_to_int(png::rgba_pixel clr);
png::rgba_pixel int_to_clr(unsigned int iii);

#endif // PIXEL_TOOLS_H
