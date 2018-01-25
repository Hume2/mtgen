#ifndef SKINMANIPULATOR_H
#define SKINMANIPULATOR_H

#include <boost/numeric/ublas/vector.hpp>
#include <string>
#include <list>

#include "rect.h"

class SkinManipulator
{
  public:
    SkinManipulator(std::string rectlist_filename = "skin_rectlist.txt");

    const int WIDTH = 64;
    const int HEIGHT = 32;

    boost::numeric::ublas::vector<double> load(std::string filename);
    void save(boost::numeric::ublas::vector<double> img, std::string filename);
    void save_derivation(boost::numeric::ublas::vector<double> img, std::string filename);

    std::vector<boost::numeric::ublas::vector<double> > load_all_skins(std::string dirname);

  private:
    std::vector<Rect> rectlist;
    int vector_size;
};

#endif // SKINMANIPULATOR_H
