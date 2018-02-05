#include <math.h>
#include <random>

#include "vector_entry.h"

VectorEntry::VectorEntry(boost::numeric::ublas::vector<double> vector_, bool is_true_) :
  vector(vector_),
  is_true(is_true_)
{

}

VectorEntry::VectorEntry(const boost::numeric::ublas::vector<double>& min,
                         const boost::numeric::ublas::vector<double>& max,
                         Shape shape, bool is_true_) :
  vector(min.size()),
  is_true(is_true_)
{
  using namespace boost::numeric::ublas;
  switch (shape) {
    case CUBE: {
      for (int i = vector.size()-1; i >= 0; --i) {
        vector[i] = (double)rand() / RAND_MAX * (max[i] - min[i]) + min[i];
      }
    } break;
    case ORTOPLEX: {
      double sum = 1;
      for (int i = vector.size()-1; i >= 0; --i) {
        vector[i] = (1 - pow((double)rand() / RAND_MAX, 1/(i+1)))*sum;
        sum -= vector[i];
        vector[i] = (max[i] - min[i])*vector[i] + (max[i] + min[i])/2;
      }
    } break;
  }
}

