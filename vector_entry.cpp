#include <math.h>
#include <random>

#include "vector_entry.h"

VectorEntry::VectorEntry(boost::numeric::ublas::vector<double> vector_, bool is_true_) :
  vec(vector_),
  is_true(is_true_)
{

}

VectorEntry::VectorEntry(const boost::numeric::ublas::vector<double>& min,
                         const boost::numeric::ublas::vector<double>& max,
                         Shape shape, bool is_true_) :
  vec(min.size()),
  is_true(is_true_)
{
  using namespace boost::numeric::ublas;
  switch (shape) {
    default:
    case SHAPE_CUBE: {
      for (int i = vec.size()-1; i >= 0; --i) {
        vec[i] = (double)rand() / RAND_MAX * (max[i] - min[i]) + min[i];
      }
    } break;
    case SHAPE_ORTHOPLEX: {
      double sum = 1;
      for (int i = vec.size()-1; i >= 0; --i) {
        vec[i] = (1 - pow((double)rand() / RAND_MAX, 1/(i+1)))*sum;
        sum -= vec[i];
        if (rand() % 2) {
          vec[i] = -vec[i];
        }
        vec[i] = ((max[i] - min[i])*vec[i] + (max[i] + min[i]))/2;
      }
    } break;
    case SHAPE_SIMPLEX: {
      double sum = 1;
      for (int i = vec.size()-1; i >= 0; --i) {
        vec[i] = (1 - pow((double)rand() / RAND_MAX, 1/(i+1)))*sum;
        sum -= vec[i];
        vec[i] = (max[i] - min[i])*vec[i]/2;
      }
    } break;
  }
}

