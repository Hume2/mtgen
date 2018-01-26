#ifndef TRAINER_H
#define TRAINER_H

#include <boost/numeric/ublas/vector.hpp>
#include <memory>
#include <boost/optional/optional.hpp>
#include <vector>

#include "division_plane.h"
#include "vector_entry.h"

class Trainer
{
  public:
    Trainer(int vector_size_, std::vector<VectorEntry> dataset_, int depth_ = 0);

    VectorEntry generate_random() const;
    void categorise(VectorEntry& vec) const;

    void populate(int fakes);

    void calculate_centres();
    void calculate_division(bool delete_data);
    void subdivide(int max_depth, bool delete_data);

    int get_true_count() const;
    int get_fake_count() const;
    bool is_pure() const;

  private:
    std::vector<VectorEntry> dataset;
    int vector_size;
    int depth;

    boost::numeric::ublas::vector<double> minimum;
    boost::numeric::ublas::vector<double> maximum;

    boost::numeric::ublas::vector<double> true_centre;
    boost::numeric::ublas::vector<double> fake_centre;

    int true_count;
    int fake_count;

    boost::optional<DivisionPlane> division;
    std::unique_ptr<Trainer> positive;
    std::unique_ptr<Trainer> negative;
};

#endif // TRAINER_H
