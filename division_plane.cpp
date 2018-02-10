#include "division_plane.h"

DivisionPlane::DivisionPlane(boost::numeric::ublas::vector<double> point_,
                             boost::numeric::ublas::vector<double> vector_) :
  point(point_),
  normal(vector_),
  mirror_precalc()
{
  using namespace boost::numeric::ublas;
  mirror_precalc = (-2 / inner_prod(normal, normal)) * normal;
}

double DivisionPlane::rate(const boost::numeric::ublas::vector<double>& vec) const {
  using namespace boost::numeric::ublas;
  return inner_prod(vec - point, normal);
}

bool DivisionPlane::mirror(boost::numeric::ublas::vector<double> &vec, bool positive) const {
  using namespace boost::numeric::ublas;
  double rating = rate(vec);
  if (positive == (rating < 0)) {
    vec += rating * mirror_precalc;
    return true;
  }
  return false;
}
