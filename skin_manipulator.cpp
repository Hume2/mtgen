#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <stdio.h>

#include "skin_manipulator.h"

#include "pixel_tools.h"
#include "vector_entry.h"

namespace {

const int rectlist_size = 10;
const int rectlist_critical = 8;
const Rect rectlist[rectlist_size] = {
  {8, 0, 24, 8},
  {0, 8, 32, 16},
  {20, 16, 36, 20},
  {16, 20, 40, 32},
  {44, 16, 52, 20},
  {40, 20, 56, 32},
  {4, 16, 12, 20},
  {0, 20, 16, 32},
  {40, 0, 56, 8},
  {32, 8, 64, 16}
};

const int mess_rectlist_size = 8;
const Rect mess_rectlist[mess_rectlist_size] = {
  {0, 0, 8, 8},
  {24, 0, 40, 8},
  {56, 0, 64, 8},
  {0, 16, 4, 20},
  {12, 16, 20, 20},
  {36, 16, 44, 20},
  {52, 16, 56, 20},
  {56, 16, 64, 32}
};

}

SkinManipulator::SkinManipulator(bool integral_, std::string dirname_):
  vector_size(0),
  integral(integral_),
  dirname(dirname_)
{
  if (integral) {
    for (auto it : rectlist) {
      vector_size += it.surface();
    }
    vector_size *= 4;
  } else {
    vector_size = WIDTH * HEIGHT * 4;
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

  if (!integral) {
    clear_mess(image);
    pixel_tools::derivate_image(image);
    //pixel_tools::integrate_image(image);
  }

  vector<double> result(vector_size);
  int i = 0;
  if (integral) {
    for (int r = 0; r < rectlist_size; ++r) {
      for (int y = rectlist[r].y1; y < rectlist[r].y2; ++y) {
        for (int x = rectlist[r].x1; x < rectlist[r].x2; ++x) {
          result[i] = image[y][x].red;
          result[i+1] = image[y][x].green;
          result[i+2] = image[y][x].blue;
          result[i+3] = image[y][x].alpha;
          i += 4;
        }
      }
    }
  } else {
    for (unsigned int y = 0; y < HEIGHT; ++y) {
      for (unsigned int x = 0; x < WIDTH; ++x) {
        result[i] = to_number(image[y][x].red);
        result[i+1] = to_number(image[y][x].green);
        result[i+2] = to_number(image[y][x].blue);
        result[i+3] = to_number(image[y][x].alpha);
        i += 4;
      }
    }
  }
  return VectorEntry(result);
}

void SkinManipulator::save(VectorEntry img, std::string filename) {
  png::image<png::rgba_pixel> image(WIDTH, HEIGHT);

  int i = 0;
  if (integral) {
    for (int r = 0; r < rectlist_size; ++r) {
      for (int y = rectlist[r].y1; y < rectlist[r].y2; ++y) {
        for (int x = rectlist[r].x1; x < rectlist[r].x2; ++x) {
          image[y][x].red = img.vec[i];
          image[y][x].green = img.vec[i+1];
          image[y][x].blue = img.vec[i+2];
          image[y][x].alpha = img.vec[i+3];
          i += 4;
        }
      }
    }
  } else {
    for (unsigned int y = 0; y < HEIGHT; ++y) {
      for (unsigned int x = 0; x < WIDTH; ++x) {
        image[y][x].red = to_pix(img.vec[i]);
        image[y][x].green = to_pix(img.vec[i+1]);
        image[y][x].blue = to_pix(img.vec[i+2]);
        image[y][x].alpha = to_pix(img.vec[i+3]);
        i += 4;
      }
    }
    pixel_tools::integrate_image(image);
    clear_mess(image);
  }

  image.write(filename.c_str());
}

std::deque<VectorEntry> SkinManipulator::load_all_skins() {
  using namespace boost::numeric::ublas;
  using namespace boost::filesystem;
  std::deque<VectorEntry> result;

  std::vector<directory_entry> v;
  if(is_directory(dirname.c_str())) {
    copy(directory_iterator(dirname.c_str()), directory_iterator(), back_inserter(v));

    for ( std::vector<directory_entry>::const_iterator it = v.begin(); it != v.end();  ++ it )
    {
      if (std::string((*it).path().extension().string()) == ".png") {
        result.push_back(load((*it).path().string()));
      }
    }
  }

  return result;
}

void SkinManipulator::load_vectors(std::deque<VectorEntry>& dataset) {
  using namespace boost::numeric::ublas;
  using namespace boost::filesystem;

  std::vector<directory_entry> v;
  if(is_directory(dirname.c_str())) {
    copy(directory_iterator(dirname.c_str()), directory_iterator(), back_inserter(v));

    for ( std::vector<directory_entry>::const_iterator it = v.begin(); it != v.end();  ++ it )
    {
      if (std::string((*it).path().extension().string()) == ".png") {
        dataset.push_back(load((*it).path().string()));
      }
    }
  }
}

int SkinManipulator::get_vector_size() const {
  return vector_size;
}

void SkinManipulator::clear_mess(png::image<png::rgba_pixel>& img) const {
  for (int r = 0; r < mess_rectlist_size; ++r) {
    for (int y = mess_rectlist[r].y1; y < mess_rectlist[r].y2; ++y) {
      for (int x = mess_rectlist[r].x1; x < mess_rectlist[r].x2; ++x) {
        img[y][x].red = 0;
        img[y][x].green = 0;
        img[y][x].blue = 0;
        img[y][x].alpha = 0;
      }
    }
  }
  for (int r = 0; r < rectlist_critical; ++r) {
    for (int y = rectlist[r].y1; y < rectlist[r].y2; ++y) {
      for (int x = rectlist[r].x1; x < rectlist[r].x2; ++x) {
        img[y][x].alpha = 255;
      }
    }
  }
  for (int r = rectlist_critical; r < rectlist_size; ++r) {
    for (int y = rectlist[r].y1; y < rectlist[r].y2; ++y) {
      for (int x = rectlist[r].x1; x < rectlist[r].x2; ++x) {
        if (img[y][x].alpha >= 128) {
          img[y][x].alpha = 255;
        } else {
          img[y][x].alpha = 0;
        }
      }
    }
  }
}

double SkinManipulator::to_number(unsigned char uc) const {
  if (uc >= 128) {
    return double(uc) - 256;
  } else {
    return uc;
  }
}

unsigned char SkinManipulator::to_pix(double num) const {
  if (num < 0) {
    return 256 + num;
  } else {
    return num;
  }
}
