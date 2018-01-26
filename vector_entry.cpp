#include <random>

#include "vector_entry.h"

VectorEntry::VectorEntry(boost::numeric::ublas::vector<double> vector_, bool is_true_) :
  vector(vector_),
  is_true(is_true_)
{

}

VectorEntry::VectorEntry(const boost::numeric::ublas::vector<double>& min,
                         const boost::numeric::ublas::vector<double>& max, bool is_true_) :
  vector(min.size()),
  is_true(is_true_)
{
  for (int i = vector.size()-1; i >= 0; --i) {
    vector[i] = (double)rand() / RAND_MAX * (max[i] - min[i]) + min[i];
  }
}

