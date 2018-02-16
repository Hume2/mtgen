#include <boost/numeric/ublas/matrix_vector.hpp>
#include <stdio.h>

#include "matrix_branch.h"

//std::forward_list<std::unique_ptr<MatrixBranch> > MatrixBranch::stock;

MatrixBranch::MatrixBranch(const boost::numeric::ublas::matrix<double>& matrix_,
                           const boost::numeric::ublas::vector<double>& shift_,
                           MatrixBranch* parent_) :
  my_matrix(matrix_),
  shift(shift_),
  parent(),
  volume(0)
{
  using namespace boost::numeric::ublas;
  parent = parent_;
  for (int i = my_matrix.size1() - 1; i >= 0; --i) {
    vector<double> v1(matrix_row<matrix<double> >(my_matrix, 1));
    volume += log2(norm_2(v1));
  }
}

void MatrixBranch::transform(boost::numeric::ublas::vector<double>& vec) const {
  using namespace boost::numeric::ublas;
  vec = prod(vec, my_matrix) + shift;
  if (parent) {
    parent->transform(vec);
  }
  //std::cout << "Transformed vector size is: " << vec.size() << std::endl;
}

double MatrixBranch::get_volume() const {
  if (parent) {
    return volume + parent->get_volume();
  } else {
    return volume;
  }
}

