#include <ctime>
#include <memory>
#include <random>
#include <stdio.h>

#include <png++/png.hpp>

#include "pixel_tools.h"
#include "rect.h"
#include "skin_manipulator.h"
#include "trainer.h"
#include "trainer_farm.h"
#include "vector_entry.h"

int main(int argc, char** argv) {
  srandom(time(0));
  SkinManipulator sm;
  sm.save(sm.load("training/character_555.png", false), "test.png", true);
  std::vector<VectorEntry> arriva = sm.load_all_skins("training", false);
  std::cout << arriva.size() << std::endl;

  TrainerFarm tf(std::unique_ptr<Trainer>(new Trainer(sm.get_vector_size(), arriva)));
  tf.grow(3);
  tf.harverst_cycle(14);
  for (int i = 10; i; --i) {
    tf.grow(20);
    tf.harverst_cycle(14);
  }
  sm.save(tf.generate_random(), "random.png", true);
  tf.show_trees();
  return 0;
}
