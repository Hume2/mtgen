#include <ctime>
#include <random>
#include <stdio.h>

#include <png++/png.hpp>

#include "pixel_tools.h"
#include "rect.h"
#include "skin_manipulator.h"
#include "trainer.h"
#include "vector_entry.h"

int main(int argc, char** argv) {
  srandom(time(0));
  SkinManipulator sm;
  sm.save_derivation(sm.load("training/character_555.png"), "test.png");
  std::vector<VectorEntry> arriva = sm.load_all_skins("training");
  std::cout << arriva.size() << std::endl;

  Trainer tr(sm.get_vector_size(), arriva);
  int max_depth = 6;
  for (int i = 2; i; --i) {
    tr.populate(2000);
    tr.subdivide(max_depth, true);
    max_depth += 3;
  }
  sm.save(tr.generate_random(), "random.png");
  tr.show_tree();
  return 0;
}
