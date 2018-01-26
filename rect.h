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

std::vector<Rect> load_rects(std::string filename);

#endif // RECT_H