#ifndef VECTORENTRY_H
#define VECTORENTRY_H

#include <boost/numeric/ublas/vector.hpp>

#include "shape.h"

class VectorEntry
{
  public:
    VectorEntry();
    VectorEntry(boost::numeric::ublas::vector<double> vector_, bool is_true_ = true);
    VectorEntry(const boost::numeric::ublas::vector<double>& min,
                const boost::numeric::ublas::vector<double>& max,
                Shape shape, bool is_true_ = false);

    boost::numeric::ublas::vector<double> vec;
    bool is_true;

  private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & vec;
      ar & is_true;
    }
};

#endif // VECTORENTRY_H
