#ifndef MATRIXBRANCH_H
#define MATRIXBRANCH_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <memory>
#include <vector>

class MatrixBranch
{
  public:
    MatrixBranch(const boost::numeric::ublas::matrix<double>& matrix_,
                 const boost::numeric::ublas::vector<double>& shift_,
                 MatrixBranch* parent_);

    static std::vector<std::unique_ptr<MatrixBranch> > stock;

    void transform(boost::numeric::ublas::vector<double>& vec) const;
    double get_volume() const;

  private:
    boost::numeric::ublas::matrix<double> my_matrix;
    boost::numeric::ublas::vector<double> shift;
    MatrixBranch* parent;
    double volume;
};

#endif // MATRIXBRANCH_H
