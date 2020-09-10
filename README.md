# Static pipeline

Testing of template based pipeline runner. Compared with a version based on dynamic polymorphism.

## Requirements
* C++11
* CMake 3.12+

## Better tests with CPU scaling disabled
https://github.com/google/benchmark#disabling-cpu-frequency-scaling
```shell script
sudo cpupower frequency-set --governor performance
sudo cpupower frequency-set --governor powersave
```

## Results
See [benchmark results](./tests/results.csv).
