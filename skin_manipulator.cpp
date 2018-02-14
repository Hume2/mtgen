#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <png++/png.hpp>
#include <stdio.h>

#include "skin_manipulator.h"

#include "pixel_tools.h"
#include "vector_entry.h"

SkinManipulator::SkinManipulator(bool integral_, bool decompose_, std::string dirname_,
                                 std::string rectlist_filename):
  rectlist(load_rects(rectlist_filename)),
  vector_size(0),
  integral(integral_),
  decompose(decompose_),
  dirname(dirname_)
{
  for (auto it : rectlist) {
    vector_size += it.surface();
  }
  if (!decompose) {
    vector_size *= 4;
  }
  std::cout << "Skin vector dimension is " << vector_size << ".\n";
}

VectorEntry SkinManipulator::load(std::string filename) {
  using namespace boost::numeric::ublas;
  png::image<png::rgba_pixel> image(filename.c_str());
  if (image.get_width() < WIDTH || image.get_height() < HEIGHT) {
    std::cout << "Image \"" << filename << "\" is too small!\n";
    return VectorEntry(zero_vector<double>(vector_size));
  }

  vector<double> result(vector_size);
  int i = 0;
  double d;
  double previous = 0;
  png::rgba_pixel previou(0, 0, 0, 0);
  //std::cout << clr_to_int(image[32][16]) << std::endl;
  for (auto it : rectlist) {
    for (int y = it.y1; y < it.y2; ++y) {
      for (int x = it.x1; x < it.x2; ++x) {
        if (decompose) {
          if (i < 1184) {
            image[y][x].alpha = 255;
          }
          d = clr_to_int(image[y][x]);
          if (integral) {
            result[i] = d;
          } else {
            result[i] = d - previous;
            previous = d;
          }
          ++i;
        } else {
          if (i < 4736) {
            image[y][x].alpha = 255;
          }
          if (integral) {
            result[i] = image[y][x].red;
            result[i+1] = image[y][x].green;
            result[i+2] = image[y][x].blue;
            result[i+3] = image[y][x].alpha;
          } else {
            result[i] = image[y][x].red - previou.red;
            result[i+1] = image[y][x].green - previou.green;
            result[i+2] = image[y][x].blue - previou.blue;
            result[i+3] = image[y][x].alpha - previou.alpha;
            previou = image[y][x];
          }
          i += 4;
        }
      }
    }
  }

  return VectorEntry(result);
}

void SkinManipulator::save(VectorEntry img, std::string filename) {
  png::image<png::rgba_pixel> image(WIDTH, HEIGHT);

  int i = 0;
  double d;
  unsigned int u;
  double previous = 0;
  png::rgba_pixel previou(0, 0, 0, 0);
  for (auto it : rectlist) {
    for (int y = it.y1; y < it.y2; ++y) {
      for (int x = it.x1; x < it.x2; ++x) {
        if (decompose) {
          if (integral) {
            d = img.vec[i];// + 0x80E00000;
          } else {
            d = img.vec[i] + previous;
          }
          if (d < 0) {
            u = 0;
          } else if (d > 0xFFFFFFFF) {
            u = 0xFFFFFFFF;
          } else {
            u = d;
          }
          image[y][x] = int_to_clr(u);
          if (i < 1184) {
            image[y][x].alpha = 255;
          }
          previous = d;
          ++i;
        } else {
          if (integral) {
            image[y][x].red = img.vec[i];
            image[y][x].green = img.vec[i+1];
            image[y][x].blue = img.vec[i+2];
            image[y][x].alpha = img.vec[i+3];
          } else {
            image[y][x].red = previou.red + img.vec[i];
            image[y][x].green = previou.green + img.vec[i+1];
            image[y][x].blue = previou.blue + img.vec[i+2];
            image[y][x].alpha = previou.alpha + img.vec[i+3];
            previou = image[y][x];
          }
          if (i < 4736) {
            image[y][x].alpha = 255;
          }
          i += 4;
        }
      }
    }
  }

  image.write(filename.c_str());
}

std::vector<VectorEntry> SkinManipulator::load_all_skins() {
  using namespace boost::numeric::ublas;
  using namespace boost::filesystem;
  std::vector<VectorEntry> result;

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

void SkinManipulator::load_vectors(std::vector<VectorEntry> &dataset) {
  using namespace boost::numeric::ublas;
  using namespace boost::filesystem;

  std::vector<directory_entry> v;
  if(is_directory(dirname.c_str())) {
    copy(directory_iterator(dirname.c_str()), directory_iterator(), back_inserter(v));

    for ( std::vector<directory_entry>::const_iterator it = v.begin(); it != v.end();  ++ it )
    {
      if (std::string((*it).path().extension().string()) == ".png") {
        dataset.push_back(load((*it).path().string()));
        //std::cout << result.size() << std::endl;
      }
    }
  }
}

int SkinManipulator::get_vector_size() const {
  return vector_size;
}
