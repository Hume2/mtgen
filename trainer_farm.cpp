#include <random>

#include "trainer_farm.h"

#include "trainer.h"

TrainerFarm::TrainerFarm(std::unique_ptr<Trainer> first_seed) :
  seeds(),
  total_trues(first_seed->count_trues())
{
  seeds.push_back(std::move(first_seed));
}

void TrainerFarm::grow(int cycles) {
  int max_depth = 10;
  for (int i = cycles; i; --i) {
    populate(2);
    for (auto& it : seeds) {
      it->subdivide(max_depth, true);
    }
    max_depth += 3;
  }
}

void TrainerFarm::populate(int coef) {
  int local_true;
  for (auto& it : seeds) {
    if (it->is_counted()) {
      local_true = it->get_true_count();
    } else {
      local_true = it->count_trues();
    }
    it->populate(coef * local_true);
  }
}

boost::numeric::ublas::vector<double> TrainerFarm::generate_random() const {
  int n = ((int)rand()) % total_trues;
  for (auto& it : seeds) {
    n -= it->get_true_count();
    if (n < 0) {
      return it->generate_random().vector;
    }
  }
  return seeds[0]->generate_random().vector;
}
