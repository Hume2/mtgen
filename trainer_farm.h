#ifndef TRAINERFARM_H
#define TRAINERFARM_H

#include <boost/numeric/ublas/vector.hpp>
#include <deque>
#include <memory>
#include <vector>

#include "shape.h"

class Trainer;

class TrainerFarm
{
  public:
    TrainerFarm(std::unique_ptr<Trainer> first_seed);

    void grow(int cycles, int coef, Shape shape);
    void populate(int coef, Shape shape);
    void harverst_one(bool normalise, Shape shape);
    void harverst_cycle(int depth_increase, bool normalise, Shape shape);
    void force_normalise();

    boost::numeric::ublas::vector<double> generate_random(Shape shape) const;

    void show_trees();
    double get_max_volume();

  private:
    std::deque<std::unique_ptr<Trainer> > seeds;
    int total_trues;
    int current_depth;
};

#endif // TRAINERFARM_H
