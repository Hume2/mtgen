#ifndef SKINMANIPULATOR_H
#define SKINMANIPULATOR_H

#include <boost/numeric/ublas/vector.hpp>
#include <string>
#include <list>

#include "rect.h"
#include "vector_loader.h"

class VectorEntry;

class SkinManipulator : public VectorLoader
{
  public:
    SkinManipulator(bool integral_, std::string dirname_);

    const unsigned int WIDTH = 64;
    const unsigned int HEIGHT = 32;

    VectorEntry load(std::string filename);
    void save(VectorEntry img, std::string filename);

    std::deque<VectorEntry> load_all_skins();

    virtual void load_vectors(std::deque<VectorEntry>& dataset);
    virtual int get_vector_size() const;

  private:
    int vector_size;

    bool integral;
    std::string dirname;
};

#endif // SKINMANIPULATOR_H
