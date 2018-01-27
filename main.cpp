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
  tr.populate(2000);
  tr.subdivide(6, true);
  std::cout << "Retry" << std::endl;
  tr.populate(2000);
  tr.subdivide(10, true);
  sm.save(tr.generate_random(), "random.png");
  tr.show_tree();
  return 0;
}
