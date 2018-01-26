#include "trainer.h"

Trainer::Trainer(int vector_size_, std::vector<VectorEntry> dataset_, int depth_) :
  dataset(dataset_),
  vector_size(vector_size_),
  depth(depth_),
  minimum(boost::numeric::ublas::zero_vector<double>(vector_size_)),
  maximum(boost::numeric::ublas::zero_vector<double>(vector_size_)),
  true_centre(vector_size_),
  fake_centre(vector_size_),
  true_count(0),
  fake_count(0),
  division(),
  positive(),
  negative()
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
  /*VectorEntry result(minimum, maximum);
  int cycles = 5;*/
}

void Trainer::categorise(VectorEntry& vec) const {

}

void Trainer::populate(int fakes) {
  for (int i = fakes; i; --i) {
    dataset.push_back(generate_random());
  }
}

void Trainer::calculate_centres() {
  using namespace boost::numeric::ublas;
  true_centre = zero_vector<double>(vector_size);
  fake_centre = zero_vector<double>(vector_size);
  true_count = 0;
  fake_count = 0;

  for (auto it : dataset) {
    if (it.is_true) {
      true_count++;
      true_centre += it.vector;
    } else {
      fake_count++;
      fake_centre += it.vector;
    }
  }

  if (true_count) {
    true_centre /= true_count;
  }

  if (fake_count) {
    fake_centre /= fake_count;
  }
}

int Trainer::get_true_count() const {
  return true_count;
}

int Trainer::get_fake_count() const {
  return fake_count;
}

void Trainer::calculate_division(bool delete_data) {
  using namespace boost::numeric::ublas;
  calculate_centres();

  division.emplace(DivisionPlane((true_centre + fake_centre)/2, true_centre - fake_centre));

  std::vector<VectorEntry> positive_data;
  std::vector<VectorEntry> negative_data;

  for (auto it: dataset) {
    if (division->rate(it.vector) > 0) {
      positive_data.push_back(it);
    } else {
      negative_data.push_back(it);
    }
  }

  positive.reset(new Trainer(vector_size, positive_data, depth + 1));
  negative.reset(new Trainer(vector_size, negative_data, depth + 1));

  if (delete_data) {
    dataset.clear();
  }
}
