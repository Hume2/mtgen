# SkinManipulator

SkinManipulator is a VectorLoader and a class that operates with skins.

## Methods

* ```SkinManipulator(bool integral_, std::string dirname_, std::string savedir_)``` A constructor. If ```integral_``` is true, the images are not derivated.

* ```VectorEntry load(std::string filename)``` Loads a skin from a file.
* ```void save(VectorEntry img, std::string filename)``` Saves the skin to a file.

* ```std::deque<VectorEntry> load_all_skins()``` Loads all skins from the directory.

* ```virtual void load_vectors(std::deque<VectorEntry>& dataset)``` Loads all skins from a directory in a resource-friendly way.
* ```virtual int get_vector_size() const``` Returns the count of dimensions.
