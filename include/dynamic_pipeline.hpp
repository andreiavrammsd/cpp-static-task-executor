#ifndef DYNAMIC_PIPELINE_HPP_
#define DYNAMIC_PIPELINE_HPP_

namespace dynamic_pipeline {

class Task {
   public:
    virtual void Run() = 0;
};

template <typename T>
struct Pipeline {
    T& tasks;

    void Run()
    {
        for (auto& task : tasks) {
            task->Run();
        }
    }
};

}  // namespace dynamic_pipeline

#endif  // DYNAMIC_PIPELINE_HPP_
