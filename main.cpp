#include <ctime>
#include <memory>
#include <random>
#include <stdio.h>

#include <png++/png.hpp>

#include "pixel_tools.h"
#include "rect.h"
#include "shape.h"
#include "skin_manipulator.h"
#include "trainer.h"
#include "trainer_farm.h"
#include "vector_entry.h"

int main(int argc, char** argv) {
  srandom(time(0));
  SkinManipulator sm(true, false, "training");
  //sm.save(sm.load("training/character_555.png", true, false), "test.png", true, false);
  std::vector<VectorEntry> arriva = sm.load_all_skins();
  std::cout << arriva.size() << std::endl;

  TrainerFarm tf(std::unique_ptr<Trainer>(new Trainer(sm.get_vector_size(), arriva)));
  tf.force_normalise();
  tf.grow(10, 2, SHAPE_CUBE);
  tf.harverst_cycle(14, true, SHAPE_CUBE);
  for (int i = 1; i < 30; ++i) {
    std::cout << "Cycle " << i << "..." << std::endl;
    tf.grow(2, 40, SHAPE_ORTHOPLEX);
    tf.harverst_cycle(14, i == 50, SHAPE_ORTHOPLEX);
  }
  sm.save(tf.generate_random(SHAPE_ORTHOPLEX), "random.png");
  //tf.show_trees();
  return 0;
}
