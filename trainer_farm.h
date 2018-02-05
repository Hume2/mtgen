#ifndef TRAINERFARM_H
#define TRAINERFARM_H

#include <boost/numeric/ublas/vector.hpp>
#include <memory>
#include <vector>

class Trainer;

class TrainerFarm
{
  public:
    TrainerFarm(std::unique_ptr<Trainer> first_seed);

    void grow(int cycles, int coef = 2);
    void populate(int coef);
    void harverst_one(bool normalise);
    void harverst_cycle(int depth_increase, bool normalise);

    boost::numeric::ublas::vector<double> generate_random() const;

    void show_trees();
    double get_max_volume();

  private:
    std::vector<std::unique_ptr<Trainer> > seeds;
    int total_trues;
    int current_depth;
};

#endif // TRAINERFARM_H
