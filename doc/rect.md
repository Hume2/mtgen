# Rectangles

All classes and functions around rectangles are currently implemented in ```rect.cpp``` and ```rect.h```. They are used in image operations.

## Class Rect

This is a base rectangle. It has a top-left and bottom-right corner.

### Methods

* ```Rect()```
* ```Rect(int x1_, int y1_, int x2_, int y2_)```

* ```int surface() const``` Calculates the surface in pixels.

## Class RectMovement

This class consists of two rectangles, one is source and the other is destination.

### Methods

* ```RectMovement()```
* ```RectMovement(Rect source_, Rect dest_)```

## Function load_rects

* ```std::vector<Rect> load_rects(std::string filename)```

This is a separate function that loads a vector of rectangles from a file. There is one rectangle per line and each rectangle is described by four integers. One file might look like this:

```
0 0 32 32
0 32 32 64
```

This file contains two rectangles: Rect(0, 0, 32, 32) and Rect(0 32, 32, 64).
