# Trainer

Trainer is the class that performs training and subdivision. Each trainer may contain two references to other trainers which create a tree structure.

## Methods

* ```Trainer()``` An empty constructor for use only for loading from file.
* ```Trainer(int vector_size_, std::deque<VectorEntry> dataset_, int depth_ = 0, MatrixBranch* matrix_branch_ = NULL);``` An obsolette constructor.
* ```Trainer(VectorLoader* loader);``` An efficient constructor that requires a [VectorLoader](vector_loader.md).

* ```VectorEntry generate_random(Shape shape) const``` Returns a random vector according to current subdivision.

* ```void populate(int fakes, Shape shape)``` Adds some fake vectors into the datasets of leaf trainers.
* ```void subdivide(int max_depth, bool delete_data);``` Performs subdivision and removes all fake data. The data is moved into the leaves after the subdivision has been performed.

* ```int count_trues() const``` Counts all true vectors in the current dataset.

* ```void show_tree(std::string prefix = "")``` Prints the trainer tree into the standart output.

* ```bool is_pure() const``` Returns true when the dataset contained only true vectors or only fake vectors before the subdivision has been performed.
* ```bool is_counted() const``` Returns true if the current dataset has definitive counts of trues and fakes.
* ```int get_true_count() const``` Returns the count of true vectors before the subdivision has been performed.
* ```int get_fake_count() const``` Returns the count of fake vectors before the subdivision has been performed.

* ```void recalculate_minmax()``` Recalculates the bounding box of the dataset.
* ```double get_volume() const``` Returns the volume of the bounding box dataset plus the volume of current matrix transformation.
* ```int get_vector_size() const``` Returns the number of dimensions of one vector.

* ```std::vector<std::deque<bool> > get_leaves() const``` Returns the references of all leaf trainers in a deque.
* ```std::shared_ptr<Trainer> cut_leaf(std::deque<bool> history)``` Removes one leaf trainer from the trainer tree.
* ```void fill_leaf(std::deque<bool> history, int count, Shape shape)``` Fills the given leaf by a certain amount of fake vectors.
* ```void give_matrix_stock(std::forward_list<std::shared_ptr<MatrixBranch> >* ms)``` Gives the trainer a reference to the [matrix stock](matrix_branch.md).

* ```void normalise_dataset()``` Orthogonalises the dataset and reduces the dimension if possible.
