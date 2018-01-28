#include <stdio.h>
#include <random>

#include "trainer.h"

int Trainer::trainer_count = 0;

Trainer::Trainer(int vector_size_, std::vector<VectorEntry> dataset_, int depth_) :
  ID(trainer_count),
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
  std::cout << spaces() << "Trainer (depth " << depth << ") has dataset with "
            << dataset.size() << " vectors." << std::endl;
  trainer_count++;
}

VectorEntry Trainer::generate_random() const {
  VectorEntry result(minimum, maximum);
  categorise(result);
  return result;
}

bool Trainer::get_random_half() const {
  bool part;
  if (!positive->get_true_count()) {
    part = false;
  } else if (!negative->get_true_count()) {
    part = true;
  } else {
    int sel = ((int)rand()) % true_count;
    part = sel >= negative->get_true_count();
  }

  return part;
}

void Trainer::categorise(VectorEntry& vec) const {
  if (!positive || !division) {
    return;
  }
  bool part = get_random_half();

  division->mirror(vec.vector, part);
  if (part) {
    positive->categorise(vec);
  } else {
    negative->categorise(vec);
  }
}

void Trainer::add_fake(VectorEntry& vec) {
  if (!positive || !division) {
    dataset.push_back(vec);
    return;
  }

  bool part = get_random_half();
  division->mirror(vec.vector, part);
  if (part) {
    positive->add_fake(vec);
  } else {
    negative->add_fake(vec);
  }
}

void Trainer::populate(int fakes) {
  for (int i = fakes; i; --i) {
    VectorEntry fake(minimum, maximum);
    add_fake(fake);
  }
  /*if (division && positive->true_count) {
    int f1 = fakes * positive->true_count / true_count;
    int f2 = fakes - f1;
    positive->populate(f1);
    negative->populate(f2);
  } else {
    for (int i = fakes; i; --i) {
      //dataset.push_back(VectorEntry(minimum, maximum));
      VectorEntry fake(minimum, maximum);
      add_fake(fake);
    }
  }*/
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

bool Trainer::is_pure() const {
  return (true_count == 0) || (fake_count == 0);
}

bool Trainer::is_counted() const {
  return true_count || fake_count || division;
}

void Trainer::calculate_division(bool delete_data) {
  using namespace boost::numeric::ublas;
  calculate_centres();

  if (is_pure()) {
    if (!true_count && delete_data) {
      dataset.clear();
    }
    return;
  }

  division.emplace(DivisionPlane((true_centre*true_count + fake_centre*fake_count)/(true_count + fake_count),
                                 true_centre - fake_centre));

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

void Trainer::subdivide(int max_depth, bool delete_data) {
  if (depth >= max_depth) {
    std::cout << spaces() << "Maximum depth exceeded." << std::endl;
    return;
  }

  if (dataset.size()) {
    std::cout << spaces() << "Dividing trainer (depth " << depth << ") with " << dataset.size()
              << " vectors." << std::endl;

    if (!positive) {
      calculate_division(delete_data);
    }
    if (!positive) {
      return;
    }

    positive->calculate_division(delete_data);
    negative->calculate_division(delete_data);

    if (!positive->is_pure()) {
      positive->subdivide(max_depth, delete_data);
    }
    if (!negative->is_pure()) {
      negative->subdivide(max_depth, delete_data);
    }

  } else {

    if (positive /*&& !positive->is_pure()*/) {
      positive->subdivide(max_depth, delete_data);
    }
    if (negative /*&& !negative->is_pure()*/) {
      negative->subdivide(max_depth, delete_data);
    }

  }
}

std::string Trainer::spaces() const {
  std::string result = "";
  for (int i = depth; i; --i) {
    result += " ";
  }
  return result + "[" + std::to_string(ID) + "]";
}

void Trainer::show_tree(std::string prefix) {
  std::cout << prefix << "\\_[" << ID << "] " << "T" << true_count << " F" << fake_count << std::endl;
  if (positive) {
    positive->show_tree(prefix + " |");
  }
  if (negative) {
    negative->show_tree(prefix + "  ");
  }
}

int Trainer::count_trues() const {
  int result = 0;
  for (auto it : dataset) {
    if (it.is_true) {
      result++;
    }
  }
  return result;
}

std::vector<std::vector<bool> > Trainer::get_leaves_recursive(std::vector<bool>& history) const {
  if (division) {
    std::vector<std::vector<bool> > result;
    if (positive && positive->get_true_count()) {
      std::vector<bool> history2 = history;
      history2.push_back(true);
      std::vector<std::vector<bool> > r2 = positive->get_leaves_recursive(history2);
      result.insert(result.end(), r2.begin(), r2.end());
    }
    if (negative && negative->get_true_count()) {
      std::vector<bool> history2 = history;
      history2.push_back(false);
      std::vector<std::vector<bool> > r2 = negative->get_leaves_recursive(history2);
      result.insert(result.end(), r2.begin(), r2.end());
    }
    return result;
  } else {
    std::vector<std::vector<bool> > result;
    if (true_count) {
      result.push_back(history);
    }
    return result;
  }
}

std::unique_ptr<Trainer> Trainer::cut_leaf_recursive(std::vector<bool>& history) {
  bool current = history[0];
  history.erase(history.begin());
  if (history.size() > 1) {
    if (current) {
      return std::move(positive->cut_leaf_recursive(history));
    } else {
      return std::move(negative->cut_leaf_recursive(history));
    }
  } else {
    if (current) {
      return std::move(positive);
    } else {
      return std::move(negative);
    }
  }
}

std::vector<std::vector<bool> > Trainer::get_leaves() const {
  std::vector<bool> temp;
  return get_leaves_recursive(temp);
}

std::unique_ptr<Trainer> Trainer::cut_leaf(std::vector<bool> history) {
  return std::move(cut_leaf_recursive(history));
}
