#ifndef PROGRESS_H
#define PROGRESS_H

#include <string>

class Progress
{
  public:
    Progress(std::string title, int max_, bool shown_);
    ~Progress();

    void step_one();
    void step(int n);

    void done();

  private:
    int current;
    int max;
    bool is_done;
    bool shown;
};

#endif // PROGRESS_H
