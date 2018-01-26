#ifndef TRAINER_H
#define TRAINER_H

#include <boost/numeric/ublas/vector.hpp>
#include <vector>

#include "vector_entry.h"

class Trainer
{
  public:
    Trainer(int vector_size_, std::vector<VectorEntry> dataset_);

    std::vector<VectorEntry> dataset;

    VectorEntry generate_random() const;

    void populate(int fakes);

  private:
    int vector_size;

    boost::numeric::ublas::vector<double> minimum;
    boost::numeric::ublas::vector<double> maximum;
};

#endif // TRAINER_H
