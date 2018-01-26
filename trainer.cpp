#include "trainer.h"

Trainer::Trainer(int vector_size_, std::vector<VectorEntry> dataset_) :
  dataset(dataset_),
  vector_size(vector_size_),
  minimum(boost::numeric::ublas::zero_vector<double>(vector_size_)),
  maximum(boost::numeric::ublas::zero_vector<double>(vector_size_))
{
  for (int i = vector_size-1; i >= 0; --i) {
    for (auto it : dataset) {
      if (it.vector[i] > maximum[i]) {
        maximum[i] = it.vector[i];
      }
      if (it.vector[i] < minimum[i]) {
        minimum[i] = it.vector[i];
      }
    }
  }
}

VectorEntry Trainer::generate_random() const {
  return VectorEntry(minimum, maximum);
}
