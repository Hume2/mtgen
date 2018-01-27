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
    boost::numeric::ublas::vector<double> generate_random() const;

  private:
    std::vector<std::unique_ptr<Trainer> > seeds;
    int total_trues;
};

#endif // TRAINERFARM_H
