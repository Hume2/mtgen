#include <stdio.h>
#include <sstream>
#include <iostream>

#include "progress.h"

Progress::Progress(std::__cxx11::string title, int max_, bool shown_) :
  current(0),
  max(max_),
  is_done(false),
  shown(shown_)
{
  if (shown) {
    std::cout << title << " (0/" << max << ")" << std::endl;
  }
}

Progress::~Progress() {
  if (shown && !is_done) {
    done();
  }
}

void Progress::step_one() {
  if (shown) {
    std::cout << "." << std::flush;
    current++;
    if (current % 50 == 0) {
      std::cout << " " << current << "/" << max << std::endl;
    }
  }
}

void Progress::step(int n) {
  if (shown) {
    for (int i = n; i; --i) {
      step_one();
    }
  }
}

void Progress::done() {
  if (shown) {
    std::cout << " Done." << std::endl;
    is_done = true;
  }
}
