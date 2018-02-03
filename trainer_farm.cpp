#include <stdio.h>
#include <random>

#include "trainer_farm.h"

#include "trainer.h"
#include "progress.h"

TrainerFarm::TrainerFarm(std::unique_ptr<Trainer> first_seed) :
  seeds(),
  total_trues(first_seed->count_trues()),
  current_depth(10)
{
  std::cout << "TrainerFarm created" << std::endl;
  first_seed->normalise_dataset();
  seeds.push_back(std::move(first_seed));
}

void TrainerFarm::grow(int cycles) {
  Progress pr("Applying growoth.", cycles, true);
  for (int i = cycles; i; --i) {
    populate(2);
    for (auto& it : seeds) {
      it->subdivide(current_depth, true);
    }
    current_depth += 3;
    pr.step_one();
  }
  pr.done();
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

void TrainerFarm::show_trees() {
  for (auto& it : seeds) {
    it->show_tree();
  }
}

void TrainerFarm::harverst_one(bool normalise) {
  std::vector<std::vector<bool> > leaves = seeds[0]->get_leaves();
  for (auto it : leaves) {
    seeds[0]->fill_leaf(it, /*seeds[0]->get_vector_size()*/ 30);
    seeds.push_back(std::move(seeds[0]->cut_leaf(it)));
    Trainer* tr = (*(seeds.end()-1)).get();

    if (normalise) {
      tr->normalise_dataset();
    } else {
      tr->recalculate_minmax();
    }
    tr->subdivide(current_depth, true);
  }
  seeds.erase(seeds.begin());
}

void TrainerFarm::harverst_cycle(int depth_increase, bool normalise) {
  //show_trees();
  int size1 = seeds.size();
  current_depth += depth_increase;
  for (int i = size1; i; --i) {
    harverst_one(normalise);
  }
  std::cout << "Harversted trainer farm. " << size1 << "seeds -> " <<
               seeds.size() << "seeds (max. volume = " << get_max_volume() <<
               ")" << std::endl;
}

double TrainerFarm::get_max_volume() {
  double result = 0;
  for (auto& it : seeds) {
    result = std::max(result, it->get_volume());
  }
  return result;
}
