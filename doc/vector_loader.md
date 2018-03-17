# VectorLoader

This is a virtual class for resource-friendly vector loading.

## Methods

* ```VectorLoader()``` This is empty.
* ```~VectorLoader()``` This is empty.

* ```virtual void load_vectors(std::deque<VectorEntry>& dataset) = 0``` Loads all vectors to given dataset.
* ```virtual int get_vector_size() const = 0``` Returns the count of dimensions.
