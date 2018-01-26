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

  boost::numeric::ublas::vector<double> min(1568);
  boost::numeric::ublas::vector<double> max(1568);
  for (int i = 1567; i >= 0; --i) {
    min[i] = -double(0x80FFFFFF);
    max[i] = double(0x80FFFFFF);
  }
  VectorEntry r(min, max);
  sm.save(r, "random.png");
  return 0;
}
