# pixel_tools

This is a namespace that contains a few functions for manipulating with images.

## Pixel serialisation

The RGBA pixel consists of four bytes as shown bellow:
* RRRRrrrr
* GGGGgggg
* BBBBbbbb
* AAAAaaaa

One letter stands for one bite and the lowercase letters are the least significant bites.

And the pixel in its deserialised form looks like this:
* AAAAaaaaRGBRGBRGBRGBrgbrgbrgbrgb

## Image derivation / integration

Consider a 2×2 square of pixels:

 A1 | B1
--- | ---
 A2 | B2

The derivation is calculated by formula: B2' = B2 - A2 - B1 + A1

And the integration is calculated by formula: B2' = B2 + A2 + B1 - A1

All pixels outside the image are considered as zero (black).

## Functions

* ```unsigned int clr_to_int(png::rgba_pixel clr)``` Serialises a RGBA pixel to one integer value.
* ```png::rgba_pixel int_to_clr(unsigned int iii)``` Deserialises an integer value to one RGBA pixel.

* ```void derivate_image(png::image<png::rgba_pixel>& img)``` Uses a reversible function for edge detection.
* ```void integrate_image(png::image<png::rgba_pixel>& img)``` Reverts edge detection.

* ```void copy_rect(png::image<png::rgba_pixel>& source, png::image<png::rgba_pixel>& dest, RectMovement rm)``` Copies a rectangle from one image to another. It requires a RectMovement as an argument.

