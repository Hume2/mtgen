#ifndef TRAINER_H
#define TRAINER_H

#include <boost/numeric/ublas/vector.hpp>
#include <memory>
#include <boost/optional/optional.hpp>
#include <deque>
#include <string>
#include <vector>

#include "division_plane.h"
#include "shape.h"
#include "vector_entry.h"

class MatrixBranch;
class VectorLoader;

class Trainer
{
  public:
    Trainer(int vector_size_, std::deque<VectorEntry> dataset_, int depth_ = 0,
            MatrixBranch* matrix_branch_ = NULL);
    Trainer(VectorLoader* loader);

    VectorEntry generate_random(Shape shape) const;

    void populate(int fakes, Shape shape);
    void subdivide(int max_depth, bool delete_data);

    int count_trues() const;

    void show_tree(std::string prefix = "");

    bool is_pure() const;
    bool is_counted() const;
    int get_true_count() const;
    int get_fake_count() const;

    void recalculate_minmax();
    double get_volume() const;
    int get_vector_size() const;

    std::vector<std::deque<bool> > get_leaves() const;
    std::unique_ptr<Trainer> cut_leaf(std::deque<bool> history);
    void fill_leaf(std::deque<bool> history, int count, Shape shape);

    void normalise_dataset();

  protected:
    Trainer(int vector_size_, int depth_, MatrixBranch* matrix_branch_);
    static int trainer_count;

    std::deque<VectorEntry> dataset;

    void calculate_centres();
    void calculate_division(bool delete_data);
    void purify();

    bool get_random_half() const;
    void add_fake(VectorEntry& vec);
    void categorise(VectorEntry& vec) const;

    std::vector<std::deque<bool> > get_leaves_recursive(std::deque<bool>& history) const;
    std::unique_ptr<Trainer> cut_leaf_recursive(std::deque<bool>& history);
    void fill_leaf_recursive(std::deque<bool>& history, VectorEntry& fake);

  private:
    int ID;
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

    MatrixBranch* matrix_branch;

    std::string spaces() const;
    void conservate();
};

#endif // TRAINER_H
