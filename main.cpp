#include <ctime>
#include <random>
#include <stdio.h>

#include <png++/png.hpp>

#include "pixel_tools.h"
#include "rect.h"
#include "skin_manipulator.h"
#include "vector_entry.h"

int main(int argc, char** argv) {
  srandom(time(0));
  SkinManipulator sm;
  sm.save_derivation(sm.load("training/character_555.png"), "test.png");
  std::vector<VectorEntry> arriva = sm.load_all_skins("training");
  std::cout << arriva.size() << std::endl;
  return 0;
}
