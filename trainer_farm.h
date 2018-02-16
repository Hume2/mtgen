#ifndef TRAINERFARM_H
#define TRAINERFARM_H

#include <boost/serialization/forward_list.hpp>
#include <boost/serialization/deque.hpp>
#include <boost/serialization/unique_ptr.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <deque>
#include <forward_list>
#include <memory>
#include <vector>

#include "matrix_branch.h"
#include "shape.h"
#include "trainer.h"

class TrainerFarm
{
  public:
    TrainerFarm(std::unique_ptr<Trainer> first_seed);

    void grow(int cycles, int coef, Shape shape);
    void populate(int coef, Shape shape);
    void harverst_one(bool normalise, Shape shape);
    void harverst_cycle(int depth_increase, bool normalise, Shape shape);
    void force_normalise();

    boost::numeric::ublas::vector<double> generate_random(Shape shape) const;

    void show_trees();
    double get_max_volume();

  private:
    std::deque<std::unique_ptr<Trainer> > seeds;
    int total_trues;
    int current_depth;

    std::forward_list<std::unique_ptr<MatrixBranch> > matrix_stock;

  private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
      ar & seeds;
      ar & total_trues;
      ar & current_depth;
      ar & matrix_stock;
    }
};

#endif // TRAINERFARM_H
