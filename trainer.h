#ifndef TRAINER_H
#define TRAINER_H

#include <boost/serialization/optional.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/deque.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <forward_list>
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
    Trainer();
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
    std::shared_ptr<Trainer> cut_leaf(std::deque<bool> history);
    void fill_leaf(std::deque<bool> history, int count, Shape shape);
    void give_matrix_stock(std::forward_list<std::shared_ptr<MatrixBranch> >* ms);

    void normalise_dataset();

  protected:
    Trainer(int vector_size_, int depth_, MatrixBranch* matrix_branch_,
            std::forward_list<std::shared_ptr<MatrixBranch> >* ms);
    static int trainer_count;

    std::deque<VectorEntry> dataset;

    void calculate_centres();
    void calculate_division(bool delete_data);
    void purify();

    bool get_random_half() const;
    void add_fake(VectorEntry& vec);
    void categorise(VectorEntry& vec) const;

    std::vector<std::deque<bool> > get_leaves_recursive(std::deque<bool>& history) const;
    std::shared_ptr<Trainer> cut_leaf_recursive(std::deque<bool>& history);
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
    std::shared_ptr<Trainer> positive;
    std::shared_ptr<Trainer> negative;

    MatrixBranch* matrix_branch;
    std::forward_list<std::shared_ptr<MatrixBranch> >* matrix_stock;

    std::string spaces() const;
    void conservate();

  private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & dataset;
      ar & ID;
      ar & vector_size;
      ar & depth;
      ar & minimum;
      ar & maximum;
      ar & true_centre;
      ar & fake_centre;
      ar & true_count;
      ar & fake_count;
      ar & division;
      ar & positive;
      ar & negative;
      ar & matrix_branch;
      //ar & matrix_stock;
    }
};

#endif // TRAINER_H
