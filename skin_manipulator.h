#ifndef SKINMANIPULATOR_H
#define SKINMANIPULATOR_H

#include <string>

#include "rect.h"

class SkinManipulator
{
  public:
    SkinManipulator(std::string rectlist_filename);

    const int WIDTH = 64;
    const int HEIGHT = 32;

  private:
    std::vector<Rect> rectlist;
};

#endif // SKINMANIPULATOR_H
