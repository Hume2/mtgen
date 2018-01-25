#include <stdio.h>

#include "rect.h"

Rect::Rect() :
  x1(0),
  y1(0),
  x2(0),
  y2(0)
{

}

Rect::Rect(int x1_, int y1_, int x2_, int y2_):
  x1(x1_),
  y1(y1_),
  x2(x2_),
  y2(y2_)
{

}

int Rect::surface() const {
  return (x2 - x1) * (y2 - y1);
}

std::vector<Rect> load_rects(std::string filename) {
  FILE *f;
  std::vector<Rect> result;

  f = fopen(filename.c_str(), "r");
  if (!f) {
    return result;
  }

  int x1, y1, x2, y2;
  while (fscanf(f, "%d %d %d %d\n", &x1, &y1, &x2, &y2) == 4) {
    result.push_back(Rect(x1, y1, x2, y2));
  }

  return result;
}
