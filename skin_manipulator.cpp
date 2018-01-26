#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <png++/png.hpp>
#include <stdio.h>

#include "skin_manipulator.h"

#include "pixel_tools.h"

SkinManipulator::SkinManipulator(std::string rectlist_filename):
  rectlist(load_rects(rectlist_filename)),
  vector_size(0)
{
  for (auto it : rectlist) {
    vector_size += it.surface();
  }
  std::cout << "Skin vector dimension is " << vector_size << ".\n";
}

boost::numeric::ublas::vector<double> SkinManipulator::load(std::string filename) {
  using namespace boost::numeric::ublas;
  png::image<png::rgba_pixel> image(filename.c_str()/*, png::require_color_space<png::rgba_pixel>()*/);
  if (image.get_width() < WIDTH || image.get_height() < HEIGHT) {
    std::cout << "Image \"" << filename << "\" is too small!\n";
    return zero_vector<double>(vector_size);
  }

  vector<double> result(vector_size);
  int i = 0;
  double d;
  double previous = 0;
  for (auto it : rectlist) {
    for (int y = it.y1; y < it.y2; ++y) {
      for (int x = it.x1; x < it.x2; ++x) {
        d = clr_to_int(image[y][x]);
        result[i] = d - previous;
        previous = d;
        ++i;
      }
    }
  }

  return result;
}

void SkinManipulator::save(boost::numeric::ublas::vector<double> img, std::string filename) {
  using namespace boost::numeric::ublas;
  png::image<png::rgba_pixel> image(WIDTH, HEIGHT);

  int i = 0;
  double d;
  unsigned int u;
  double previous = 0;
  for (auto it : rectlist) {
    for (int y = it.y1; y < it.y2; ++y) {
      for (int x = it.x1; x < it.x2; ++x) {
        d = img[i] + previous;
        if (d < 0) {
          u = 0;
        } else if (d > 0xFFFFFFFF) {
          u = 0xFFFFFFFF;
        } else {
          u = d;
        }
        image[y][x] = int_to_clr(u);
        previous = d;
        ++i;
      }
    }
  }

  image.write(filename.c_str());
}

void SkinManipulator::save_derivation(boost::numeric::ublas::vector<double> img, std::string filename) {
  using namespace boost::numeric::ublas;
  png::image<png::rgba_pixel> image(WIDTH, HEIGHT);

  int i = 0;
  double d;
  unsigned int u;
  for (auto it : rectlist) {
    for (int y = it.y1; y < it.y2; ++y) {
      for (int x = it.x1; x < it.x2; ++x) {
        d = img[i] + 0x80E00000;
        if (d < 0) {
          u = 0;
        } else if (d > 0xFFFFFFFF) {
          u = 0xFFFFFFFF;
        } else {
          u = d;
        }
        image[y][x] = int_to_clr(u);
        ++i;
      }
    }
  }

  image.write(filename.c_str());
}

std::vector<boost::numeric::ublas::vector<double> > SkinManipulator::load_all_skins(std::string dirname) {
  using namespace boost::numeric::ublas;
  using namespace boost::filesystem;
  std::vector<vector<double> > result;

  std::vector<directory_entry> v;
  if(is_directory(dirname.c_str())) {
    copy(directory_iterator(dirname.c_str()), directory_iterator(), back_inserter(v));

    for ( std::vector<directory_entry>::const_iterator it = v.begin(); it != v.end();  ++ it )
    {
      if (std::string((*it).path().extension().string()) == ".png") {
        result.push_back(load((*it).path().string()));
        //std::cout << result.size() << std::endl;
      }
    }
  }

  return result;
}

int SkinManipulator::get_vector_size() const {
  return vector_size;
}
