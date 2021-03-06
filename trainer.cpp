#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_vector.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <limits>
#include <stdio.h>
#include <random>
#include <math.h>

#include "trainer.h"

#include "matrix_branch.h"
#include "progress.h"
#include "vector_loader.h"

int Trainer::trainer_count = 0;

Trainer::Trainer() :
  dataset(),
  ID(),
  vector_size(),
  depth(),
  minimum(),
  maximum(),
  true_centre(),
  fake_centre(),
  true_count(),
  fake_count(),
  division(),
  positive(),
  negative(),
  matrix_branch(),
  matrix_stock()
{

}

Trainer::Trainer(int vector_size_, std::deque<VectorEntry> dataset_, int depth_,
                 MatrixBranch* matrix_branch_) :
  dataset(dataset_),
  ID(trainer_count),
  vector_size(vector_size_),
  depth(depth_),
  minimum(vector_size),
  maximum(vector_size),
  true_centre(vector_size_),
  fake_centre(vector_size_),
  true_count(0),
  fake_count(0),
  division(),
  positive(),
  negative(),
  matrix_branch(),
  matrix_stock()
{
  matrix_branch = matrix_branch_;
  recalculate_minmax();
  //std::cout << spaces() << "Trainer (depth " << depth << ") has dataset with "
  //          << dataset.size() << " vectors. V_log = " << get_volume() << std::endl;
  trainer_count++;
}

Trainer::Trainer(VectorLoader* loader) :
  dataset(),
  ID(trainer_count),
  vector_size(loader->get_vector_size()),
  depth(0),
  minimum(vector_size),
  maximum(vector_size),
  true_centre(vector_size),
  fake_centre(vector_size),
  true_count(0),
  fake_count(0),
  division(),
  positive(),
  negative(),
  matrix_branch(),
  matrix_stock()
{
  loader->load_vectors(dataset);
  matrix_branch = NULL;
  recalculate_minmax();
  trainer_count++;
}

Trainer::Trainer(int vector_size_, int depth_, MatrixBranch* matrix_branch_,
                 std::forward_list<std::shared_ptr<MatrixBranch> >* ms) :
  dataset(),
  ID(trainer_count),
  vector_size(vector_size_),
  depth(depth_),
  minimum(vector_size),
  maximum(vector_size),
  true_centre(vector_size),
  fake_centre(vector_size),
  true_count(0),
  fake_count(0),
  division(),
  positive(),
  negative(),
  matrix_branch(),
  matrix_stock()
{
  matrix_branch = matrix_branch_;
  matrix_stock = ms;
  trainer_count++;
}

void Trainer::give_matrix_stock(std::forward_list<std::shared_ptr<MatrixBranch> > *ms) {
  matrix_stock = ms;
  if (positive) {
    positive->give_matrix_stock(ms);
  }
  if (negative) {
    negative->give_matrix_stock(ms);
  }
}

void Trainer::recalculate_minmax() {
  using namespace boost::numeric::ublas;
  maximum = scalar_vector<double>(vector_size, -std::numeric_limits<double>::max());
  minimum = scalar_vector<double>(vector_size, std::numeric_limits<double>::max());
  for (int i = vector_size-1; i >= 0; --i) {
    for (auto it : dataset) {
      if (it.vec[i] > maximum[i]) {
        maximum[i] = it.vec[i];
      }
      if (it.vec[i] < minimum[i]) {
        minimum[i] = it.vec[i];
      }
    }
  }
}

double Trainer::get_volume() const {
  double volume = 0;
  for (int i = vector_size-1; i >= 0; --i) {
    volume += log2(maximum[i] - minimum[i]);
  }
  /*if (matrix_branch) {
    volume += matrix_branch->get_volume();
  }*/
  return volume;
}

VectorEntry Trainer::generate_random(Shape shape) const {
  VectorEntry result(minimum, maximum, shape);
  categorise(result);
  matrix_branch->transform(result.vec);
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

  division->mirror(vec.vec, part);
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
  division->mirror(vec.vec, part);
  if (part) {
    positive->add_fake(vec);
  } else {
    negative->add_fake(vec);
  }
}

void Trainer::populate(int fakes, Shape shape) {
  for (int i = fakes; i; --i) {
    VectorEntry fake(minimum, maximum, shape);
    add_fake(fake);
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
      true_centre += it.vec;
    } else {
      fake_count++;
      fake_centre += it.vec;
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

void Trainer::conservate() {
  true_count = 0;
  fake_count = 0;
  for (auto it : dataset) {
    if (it.is_true) {
      true_count++;
    } else {
      fake_count++;
    }
  }
}

void Trainer::purify() {
  for (int i = dataset.size()-1; i >= 0; --i) {
    if (dataset[i].is_true) {
      break;
    } else {
      dataset.pop_back();
    }
  }
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

  positive.reset(new Trainer(vector_size, depth + 1, matrix_branch, matrix_stock));
  negative.reset(new Trainer(vector_size, depth + 1, matrix_branch, matrix_stock));

  while (dataset.size()) {
    if (division->rate(dataset.rbegin()->vec) > 0) {
      positive->dataset.push_back(*(dataset.rbegin()));
    } else {
      negative->dataset.push_back(*(dataset.rbegin()));
    }

    if (delete_data) {
      dataset.pop_back();
    }
  }

  positive->recalculate_minmax();
  negative->recalculate_minmax();

  if (!positive->dataset.size()) {
    negative->purify();
  }
  if (!negative->dataset.size()) {
    positive->purify();
  }
}

void Trainer::subdivide(int max_depth, bool delete_data) {
  if (depth >= max_depth) {
    //std::cout << spaces() << "Maximum depth exceeded." << std::endl;
    conservate();
    return;
  }

  if (dataset.size()) {
    //std::cout << spaces() << "Dividing trainer (depth " << depth << ") with " << dataset.size()
    //          << " vectors." << std::endl;

    if (!positive) {
      calculate_division(delete_data);
    }
    if (!positive) {
      return;
    }

    positive->subdivide(max_depth, delete_data);
    negative->subdivide(max_depth, delete_data);

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

std::vector<std::deque<bool> > Trainer::get_leaves_recursive(std::deque<bool>& history) const {
  if (division) {
    std::vector<std::deque<bool> > result;
    if (positive && positive->get_true_count()) {
      std::deque<bool> history2 = history;
      history2.push_back(true);
      std::vector<std::deque<bool> > r2 = positive->get_leaves_recursive(history2);
      result.insert(result.end(), r2.begin(), r2.end());
    }
    if (negative && negative->get_true_count()) {
      std::deque<bool> history2 = history;
      history2.push_back(false);
      std::vector<std::deque<bool> > r2 = negative->get_leaves_recursive(history2);
      result.insert(result.end(), r2.begin(), r2.end());
    }
    return result;
  } else {
    std::vector<std::deque<bool> > result;
    if (true_count) {
      result.push_back(history);
    }
    return result;
  }
}

std::shared_ptr<Trainer> Trainer::cut_leaf_recursive(std::deque<bool>& history) {
  bool current = history[0];
  history.pop_front();
  if (history.size()) {
    if (current) {
      return positive->cut_leaf_recursive(history);
    } else {
      return negative->cut_leaf_recursive(history);
    }
  } else {
    if (current) {
      return positive;
    } else {
      return negative;
    }
  }
}

void Trainer::fill_leaf_recursive(std::deque<bool>& history, VectorEntry& fake) {
  if (history.size() && division) {
    bool current = history[0];
    history.pop_front();
    division->mirror(fake.vec, current);
    if (current) {
      positive->fill_leaf_recursive(history, fake);
    } else {
      negative->fill_leaf_recursive(history, fake);
    }
  } else {
    add_fake(fake);
  }
}

std::vector<std::deque<bool> > Trainer::get_leaves() const {
  std::deque<bool> temp;
  return get_leaves_recursive(temp);
}

std::shared_ptr<Trainer> Trainer::cut_leaf(std::deque<bool> history) {
  return cut_leaf_recursive(history);
}

void Trainer::fill_leaf(std::deque<bool> history, int count, Shape shape) {
  std::deque<bool> h_;
  for (int i = count; i; --i) {
    h_ = history;
    VectorEntry fake(minimum, maximum, shape);
    fill_leaf_recursive(h_, fake);
  }
}

int Trainer::get_vector_size() const {
  return vector_size;
}

void Trainer::normalise_dataset() {
  using namespace boost::numeric::ublas;
  vector<double> shift = dataset.begin()->vec;//(maximum + minimum) / 2;
  std::vector<vector<double> > basis;
  std::vector<VectorEntry> data_copy;
  std::vector<double> inverse_dot_products;

  for (auto it : dataset) {
    data_copy.push_back(VectorEntry(it.vec - shift, it.is_true));
  }

  int i_max = std::min(vector_size, int(dataset.size()) - 1);
  Progress pr("Calculating transform matrix.", i_max, i_max > 50);

  for (int i = i_max; i; --i) {

    double max_size = norm_2(data_copy.begin()->vec);
    auto max_it = data_copy.begin();
    for (auto it = data_copy.begin(); it != data_copy.end(); ++it) {
      double size = norm_2(it->vec);
      if (size > max_size) {
        max_size = size;
        max_it = it;
      }
    }

    if (max_size <= 0) {
      break;
    }

    basis.push_back(max_it->vec);
    vector<double> vec = max_it->vec;
    double idp = 1/inner_prod(vec, vec);
    inverse_dot_products.push_back(idp);

    for (auto it = data_copy.begin(); it != data_copy.end(); ++it) {
      it->vec = it->vec - (inner_prod(it->vec, vec)*idp) * vec;
    }
    pr.step_one();
  }
  pr.done();

  matrix<double> M(basis.size(), vector_size);
  for (unsigned int i = 0; i < basis.size(); ++i) {
    for (int j = 0; j < vector_size; ++j) {
      M(i, j) = basis[i][j];
    }
  }

  vector<double> inverse(inverse_dot_products.size());
  int i = 0;
  for (auto it = inverse_dot_products.begin(); it != inverse_dot_products.end(); ++it) {
    inverse[i] = *it;
    ++i;
  }

  Progress pr2("Transforming data.", dataset.size(), dataset.size() > 50);
  for (auto it = dataset.begin(); it != dataset.end(); ++it) {
    it->vec = element_prod(prod(M, it->vec - shift), inverse);
    pr2.step_one();
  }
  pr2.done();

  //std::cout << "Found Matrix: " << M << std::endl;
  //std::cout << inverse << std::endl;

  std::shared_ptr<MatrixBranch> new_branch(new MatrixBranch(M, shift, matrix_branch));
  matrix_stock->push_front(new_branch);
  matrix_branch = matrix_stock->begin()->get();
  vector_size = inverse_dot_products.size();
  recalculate_minmax();
}

