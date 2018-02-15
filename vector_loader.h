#ifndef VECTORLOADER_H
#define VECTORLOADER_H

#include <deque>
#include <string>

#include "vector_entry.h"

class VectorLoader
{
  public:
    VectorLoader();
    ~VectorLoader();

    virtual void load_vectors(std::deque<VectorEntry>& dataset) = 0;
    virtual int get_vector_size() const = 0;
};

#endif // VECTORLOADER_H
