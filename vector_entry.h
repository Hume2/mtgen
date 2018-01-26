#ifndef VECTORENTRY_H
#define VECTORENTRY_H

#include <boost/numeric/ublas/vector.hpp>

class VectorEntry
{
  public:
    VectorEntry(boost::numeric::ublas::vector<double> vector_, bool is_true_ = true);
    VectorEntry(const boost::numeric::ublas::vector<double>& min,
                const boost::numeric::ublas::vector<double>& max, bool is_true_ = false);

    boost::numeric::ublas::vector<double> vector;
    bool is_true;
};

#endif // VECTORENTRY_H