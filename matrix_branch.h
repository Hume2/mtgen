#ifndef MATRIXBRANCH_H
#define MATRIXBRANCH_H

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <memory>

class MatrixBranch
{
  public:
    MatrixBranch();
    MatrixBranch(const boost::numeric::ublas::matrix<double>& matrix_,
                 const boost::numeric::ublas::vector<double>& shift_,
                 MatrixBranch* parent_);

    //static std::forward_list<std::unique_ptr<MatrixBranch> > stock;

    void transform(boost::numeric::ublas::vector<double>& vec) const;
    double get_volume() const;

  private:
    boost::numeric::ublas::matrix<double> my_matrix;
    boost::numeric::ublas::vector<double> shift;
    MatrixBranch* parent;
    double volume;

  private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & my_matrix;
      ar & shift;
      ar & parent;
      ar & volume;
    }
};

#endif // MATRIXBRANCH_H
