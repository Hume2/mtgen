# Progress

Progress is a simple class for displaying the current progress in terminal. It has its title and a number of steps. It might be set to hidden, which allows to show it only when it's neccessary.

## Methods

* ```Progress(std::string title, int max_, bool shown_)``` A costructor.
* ```~Progress()``` A destructor. The destructor calls the function ```done()``` if neccessary.

* ```void step_one()``` Makes one step.
* ```void step(int n)``` Makes n steps.

* ```void done()``` Marks the progress bar as finished.
