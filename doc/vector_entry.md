# VectorEntry

This is a wrapper class for ```std::numeric::ublas::vector<double>``` which adds an attribute of being true or fake.

## Methods

* ```VectorEntry()``` An empty constructor.
* ```VectorEntry(boost::numeric::ublas::vector<double> vector_, bool is_true_ = true)``` A constructor that uses a vector.
* ```VectorEntry(const boost::numeric::ublas::vector<double>& min, const boost::numeric::ublas::vector<double>& max, Shape shape, bool is_true_ = false)``` This constructor generates a random vector within given bounds and [shape](shape.md). If ```SHAPE_SIMPLEX``` is chosen, the result must be transformed and shifted after generation.
