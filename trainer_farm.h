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

    void grow(int cycles);
    void populate(int coef);
    void harverst_one();
    void harverst_cycle(int depth_increase);

    boost::numeric::ublas::vector<double> generate_random() const;

    void show_trees();

  private:
    std::vector<std::unique_ptr<Trainer> > seeds;
    int total_trues;
    int current_depth;
};

#endif // TRAINERFARM_H
