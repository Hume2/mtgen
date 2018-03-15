# MatrixBranch

The transform matrices form a tree. MatrixBranch is a node of the tree. The whole tree is usually contained in a kind of matrix stock.

The MatrixBranch allows to shift the vector in addition to matrix transformation.

## Methods

* ```MatrixBranch()``` A constructor for use only in loading from file.
* ```MatrixBranch(const boost::numeric::ublas::matrix<double>& matrix_, const boost::numeric::ublas::vector<double>& shift_, MatrixBranch* parent_)``` A constructor that requires a matrix, a shift and a parent matrix. If the MatrixBranch represents the root of the matrix tree, the parent is NULL.

* ```void transform(boost::numeric::ublas::vector<double>& vec) const``` Transforms the given vector.
* ```double get_volume() const``` Returns the product of all matrix rows plus the volume of the parent MatrixBranch.
