#ifndef TRAINER_H
#define TRAINER_H

#include <boost/numeric/ublas/vector.hpp>
#include <memory>
#include <boost/optional/optional.hpp>
#include <string>
#include <vector>

#include "division_plane.h"
#include "vector_entry.h"

class Trainer
{
  public:
    Trainer(int vector_size_, std::vector<VectorEntry> dataset_, int depth_ = 0);

    VectorEntry generate_random() const;

    void populate(int fakes);
    void subdivide(int max_depth, bool delete_data);

    void show_tree(std::string prefix = "");

  protected:
    static int trainer_count;

    void calculate_centres();
    void calculate_division(bool delete_data);

    int get_true_count() const;
    int get_fake_count() const;
    bool is_pure() const;
    bool is_counted() const;

    bool get_random_half() const;
    void add_fake(VectorEntry& vec);
    void categorise(VectorEntry& vec) const;

  private:
    int ID;
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

    std::string spaces() const;
};

#endif // TRAINER_H
