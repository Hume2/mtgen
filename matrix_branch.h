#ifndef MATRIXBRANCH_H
#define MATRIXBRANCH_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <vector>

class MatrixBranch
{
  public:
    MatrixBranch(const boost::numeric::ublas::matrix<double>& matrix_,
                 MatrixBranch* parent_);

    static std::vector<MatrixBranch> stock;

    void transform(boost::numeric::ublas::vector<double>& vec) const;
    double get_volume() const;

  private:
    boost::numeric::ublas::matrix<double> my_matrix;
    MatrixBranch* parent;
    double volume;
};

#endif // MATRIXBRANCH_H
