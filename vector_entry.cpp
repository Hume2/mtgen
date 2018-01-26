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
    if (max[i] > min[i]) {
      vector[i] = fmod(double(random()), max[i] - min[i]) + min[i];
    } else if (max[i] < min[i]) {
      vector[i] = fmod(double(random()), min[i] - max[i]) + max[i];
    } else {
      vector[i] = min[i];
    }
  }
}

