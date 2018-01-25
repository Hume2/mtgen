#include "skin_manipulator.h"

SkinManipulator::SkinManipulator(std::string rectlist_filename = "rectlist.txt"):
  rectlist(load_rects(rectlist_filename))
{

}

