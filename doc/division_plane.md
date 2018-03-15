# DivisionPlane

DivisionPlane is a multidimensional plane defined by one point and one normal vector. If another point is given, it decides which half it is in. It can also mirror one half into the other.

One half is called positive and the other is called negative. The normal vector points to the positive half.

## Methods

* ```DivisionPlane();``` An empty constructor for use only for loading from file.
* ```DivisionPlane(boost::numeric::ublas::vector<double> point_, boost::numeric::ublas::vector<double> vector_)``` A common constructor.

* ```double rate(const boost::numeric::ublas::vector<double>& vec) const``` Returns positive or negative number depending on which half the given point is in.
* ```bool mirror(boost::numeric::ublas::vector<double>& vec, bool positive) const``` Mirrors the point to the other half if neccessary. The second argument says which half is the target one. This function returns true if the position has been changed.
