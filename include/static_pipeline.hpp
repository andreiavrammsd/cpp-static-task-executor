#ifndef STATIC_PIPELINE_HPP_
#define STATIC_PIPELINE_HPP_

#include <tuple>

namespace static_pipeline {

template <typename T, std::size_t S = std::tuple_size<T>::value, std::size_t I = S - 1>
struct Pipeline {
    T &tasks;

    void Run()
    {
        std::get<S - I - 1>(tasks).Run();
        Pipeline<T, S, I - 1>{tasks}.Run();
    }
};

template <typename T, std::size_t S>
struct Pipeline<T, S, 0> {
    T &tasks;

    void Run() { std::get<S - 1>(tasks).Run(); }
};

}  // namespace static_pipeline

#endif  // STATIC_PIPELINE_HPP_
