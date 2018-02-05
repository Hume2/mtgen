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
  sm.save(sm.load("training/character_555.png", true, false), "test.png", true, false);
  std::vector<VectorEntry> arriva = sm.load_all_skins("training", false, false);
  std::cout << arriva.size() << std::endl;

  TrainerFarm tf(std::unique_ptr<Trainer>(new Trainer(sm.get_vector_size()*4, arriva)));
  tf.grow(20);
  tf.harverst_cycle(14, true);
  for (int i = 0; i < 100; ++i) {
    std::cout << "Cycle " << i << "..." << std::endl;
    tf.grow(10, 40);
    tf.harverst_cycle(14, i == 50);
  }
  sm.save(tf.generate_random(), "random.png", false, false);
  //tf.show_trees();
  return 0;
}
