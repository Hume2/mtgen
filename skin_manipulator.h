#ifndef SKINMANIPULATOR_H
#define SKINMANIPULATOR_H

#include <boost/numeric/ublas/vector.hpp>
#include <string>
#include <list>

#include "rect.h"

class VectorEntry;

class SkinManipulator
{
  public:
    SkinManipulator(std::string rectlist_filename = "skin_rectlist.txt");

    const unsigned int WIDTH = 64;
    const unsigned int HEIGHT = 32;

    VectorEntry load(std::string filename, bool integral, bool decompose);
    void save(VectorEntry img, std::string filename, bool derivation, bool compose);

    std::vector<VectorEntry> load_all_skins(std::string dirname, bool integral = false, bool decompose = true);

    int get_vector_size() const;

  private:
    std::vector<Rect> rectlist;
    int vector_size;
};

#endif // SKINMANIPULATOR_H
