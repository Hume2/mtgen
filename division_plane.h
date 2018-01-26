#ifndef DIVISIONPLANE_H
#define DIVISIONPLANE_H

#include <boost/numeric/ublas/vector.hpp>

class DivisionPlane
{
  public:
    DivisionPlane(boost::numeric::ublas::vector<double> point_,
                  boost::numeric::ublas::vector<double> vector_);

    double rate(const boost::numeric::ublas::vector<double>& vec) const;
    bool mirror(boost::numeric::ublas::vector<double>& vec) const;

  private:
    boost::numeric::ublas::vector<double> point;
    boost::numeric::ublas::vector<double> vector;

    boost::numeric::ublas::vector<double> mirror_precalc;
};

#endif // DIVISIONPLANE_H
