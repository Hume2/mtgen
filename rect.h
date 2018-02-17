#ifndef RECT_H
#define RECT_H

#include <string>
#include <vector>

class Rect
{
  public:
    Rect();
    Rect(int x1_, int y1_, int x2_, int y2_);

    int x1, y1, x2, y2;

    int surface() const;
};

class RectMovement
{
  public:
    RectMovement();
    RectMovement(Rect source_, Rect dest_);

    Rect source, dest;
};

std::vector<Rect> load_rects(std::string filename);

#endif // RECT_H
