#ifndef VECTORLOADER_H
#define VECTORLOADER_H

#include <string>
#include <vector>

#include "vector_entry.h"

class VectorLoader
{
  public:
    VectorLoader();
    ~VectorLoader();

    virtual void load_vectors(std::vector<VectorEntry>& dataset) = 0;
    virtual int get_vector_size() const = 0;
};

#endif // VECTORLOADER_H
