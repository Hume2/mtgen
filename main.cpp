#include <ctime>
#include <memory>
#include <random>
#include <stdio.h>

#include <boost/numeric/ublas/vector.hpp>
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
  SkinManipulator sm;
  sm.save(sm.load("training/character_555.png", true, false), "test.png", true, false);
  //std::vector<VectorEntry> arriva = sm.load_all_skins("training", false, false);
  //std::cout << arriva.size() << std::endl;

  using namespace boost::numeric::ublas;
  vector<double> u1(4), u2(4), u3(4), u4(4);
  u1[0] = 1;     u2[0] = 1;     u3[0] = 3;     u4[0] = 1;
  u1[1] = 0;     u2[1] = 2;     u3[1] = 0;     u4[1] = 1;
  u1[2] = 1;     u2[2] = 3;     u3[2] = 1;     u4[2] = 1;
  u1[3] = 0;     u2[3] = 4;     u3[3] = 2;     u4[3] = 2;

  std::vector<VectorEntry> arriva;
  arriva.push_back(VectorEntry(u1));
  arriva.push_back(VectorEntry(u2));
  arriva.push_back(VectorEntry(u3));
  arriva.push_back(VectorEntry(u4));

  TrainerFarm tf(std::unique_ptr<Trainer>(new Trainer(/*sm.get_vector_size()**/4, arriva)));
  /*tf.grow(20, 2, SHAPE_ORTHOPLEX);
  tf.harverst_cycle(14, true, SHAPE_CUBE);
  for (int i = 1; i < 200; ++i) {
    std::cout << "Cycle " << i << "..." << std::endl;
    tf.grow(2, 40, SHAPE_ORTHOPLEX);
    tf.harverst_cycle(14, i == 50, SHAPE_ORTHOPLEX);
  }*/
  //sm.save(tf.generate_random(SHAPE_ORTHOPLEX), "random.png", false, false);
  tf.save_as_skins(&sm);
  //tf.show_trees();
  return 0;
}
