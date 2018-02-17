#include <boost/serialization/unique_ptr.hpp>

#include <ctime>
#include <memory>
#include <random>
#include <stdio.h>

#include <png++/png.hpp>

#include "pixel_tools.h"
#include "progress.h"
#include "rect.h"
#include "shape.h"
#include "skin_manipulator.h"
#include "trainer.h"
#include "trainer_farm.h"
#include "vector_entry.h"

#include <fstream>

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

int main(int argc, char** argv) {
  srandom(time(0));
  SkinManipulator sm(false, "training");

  /*TrainerFarm tf(std::shared_ptr<Trainer>(new Trainer(&sm)));
  //tf.force_normalise();
  tf.grow(10, 2, SHAPE_CUBE);
  tf.harverst_cycle(14, true, SHAPE_CUBE);
  for (int i = 1; i < 30; ++i) {
    std::cout << "Cycle " << i << "..." << std::endl;
    tf.grow(2, 40, SHAPE_ORTHOPLEX);
    tf.harverst_cycle(14, i == 50, SHAPE_ORTHOPLEX);
  }

  std::ofstream ofs("training_results/derivative.dat");
  {
    boost::archive::binary_oarchive oa(ofs);
    oa << tf;
  }*/
  TrainerFarm tf;
  {
    std::ifstream ifs("training_results/derivative.dat");
    boost::archive::binary_iarchive ia(ifs);
    ia >> tf;
  }
  Progress pr("Generating stuff", 1000, true);
  for (int i = 0; i < 1000; ++i) {
    sm.save(tf.generate_random(SHAPE_ORTHOPLEX), "results/random_" + std::to_string(i) + ".png");
    pr.step_one();
  }
  pr.done();

  //tf.show_trees();
  return 0;
}
