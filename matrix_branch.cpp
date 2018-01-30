#include <boost/numeric/ublas/matrix_vector.hpp>

#include "matrix_branch.h"

std::vector<MatrixBranch> MatrixBranch::stock;

MatrixBranch::MatrixBranch(const boost::numeric::ublas::matrix<double>& matrix_,
                           MatrixBranch* parent_) :
  my_matrix(matrix_),
  parent(parent_),
  volume(0)
{
  using namespace boost::numeric::ublas;
  for (int i = my_matrix.size1() - 1; i >= 0; --i) {
    vector<double> v1(matrix_row<matrix<double> >(my_matrix, 1));
    volume += log2(norm_2(v1));
  }
}

void MatrixBranch::transform(boost::numeric::ublas::vector<double>& vec) const {
  using namespace boost::numeric::ublas;
  vec = prod(vec, my_matrix);
  if (parent) {
    parent->transform(vec);
  }
}

double MatrixBranch::get_volume() const {
  if (parent) {
    return volume + parent->get_volume();
  } else {
    return volume;
  }
}

