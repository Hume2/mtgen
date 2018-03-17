# TrainerFarm

The class Trainer might look like it has enough functionality to perform all stuff. Howwever, the tree structure grows and becomes ineffective. The long branches are no longer useful and only waste the resources. The TrainerFarm cuts the leaves and discards the rest of the tree when it's no longer useful.

## Methods

* ```TrainerFarm()``` A constructor for use only for loading from file.
* ```TrainerFarm(std::shared_ptr<Trainer> first_seed)``` Creates a TrainerFarm from one seed.

* ```void grow(int cycles, int coef, Shape shape)``` Performs Trainer subdivision.
* ```void populate(int coef, Shape shape)``` Populates the Trainers by fake data. The ```coef``` says how many times the fake data shoud be bigger than the true data.
* ```void harverst_one(bool normalise, Shape shape)``` Cuts the leaves from the first Trainer tree and pushes them on the end. The rest of the Trainer tree is discarded. The leaves might be normalised after this procedure.
* ```void harverst_cycle(int depth_increase, bool normalise, Shape shape)``` Cuts the leaves form all current Trainer tree and discards the rest. The leaves might be normalised after this procedure.
* ```void force_normalise()``` Normalises all Trainers.

* ```boost::numeric::ublas::vector<double> generate_random(Shape shape) const``` Generates a random vector from a random Trainer.

* ```void show_trees()``` Prints all Trainer tree on the standart output.
* ```double get_max_volume()``` Returns the volume of the biggest Trainer.
