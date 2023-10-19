# An Effective Memetic Algorithm for the Close-Enough Traveling Salesman Problem

This repository is the implementation in C++ for the paper [An Effective Memetic Algorithm for the Close-Enough Traveling Salesman Problem](link) by Zhenyu Lei, Jin-Kao Hao.

We propose an effective memetic algorithm to solve the Close-Enough Traveling Salesman Problem (CETSP) which is a variant of the well-known Traveling Salesman Problem (TSP). Experimental results on the well-known benchmark instances show that the algorithm is highly competitive with the state-of-the-art methods. We also demonstrate the usefulness of the algorithm on a real laser welding robot path planning problem.

## Overview

In this repository, we have:

- `cmake/` folder contains the cmake configuration for gurobi solver.
- `datasets/` folder is for the benchmark instances and real-world instances used in the paper.
- `include/` and `src/` folders contain the source code of the algorithm.
- `CMakelists.txt` is the cmake configuration file.

## Requirements

### Instances

We conducted experiments on the well-known benchmark instances proposed by Dr. Mennell. The instances are available at [link](https://drum.lib.umd.edu/handle/1903/9822). 

And we also tested our algorithm on real-world instances provided by Prof. Béla Vizvári, one of authors of [Nedjatia et al.](https://d1wqtxts1xzle7.cloudfront.net/65000401/CRPASE_Transactions_of_Industrial_Engineering_Vol._06_04_288_293_December_2020-libre.pdf?1606017364=&response-content-disposition=inline%3B+filename%3DRobot_Path_Planning_by_Traveling_Salesma.pdf&Expires=1697549284&Signature=hBOKgxVRfdkVHbMLbBgrqNUSt2Q1roDGMVh2syU0kI1nLx1k2VScQw34ztRuKTWvxAXk3ka7JTHMLw66gb3zIrGk0biWChBfb0sbkE~aYEYWJJuaWaU6jYV14vM5YxUWpWQ~WOzfEoLJYHIcy6frObVjgurZkLc9LAiGRYWlCNa~UubvWY2R6YyCVH2uejTgIIJzRCV19nIRyR1gSBPDvYVGFb3D4PBPQuPYQIx1U4grOfJiDYaq~6Zge51WyLQbcW8r9V8Oqq81Htv-Nw~MAJLwhL5VvZxlJUup8tUmWetYNSKwh2bRFHdoTKIqSv9ZLbPwxbe00kenyr5drG-RXg__&Key-Pair-Id=APKAJLOHF5GGSLRBV4ZA). We provide the instances in the folder `datasets/`.

### Solver

It is necessary to install [LKH-2.0 solver](http://akira.ruc.dk/~keld/research/LKH/) which is used to optimize the visiting sequence of solutions, and [Gurobi 10.0 solver](https://www.gurobi.com/) which is used to obtain the optimal visiting positions for a given visiting sequence.

## Run the code

Please configure Gurobi solver path in the `CMakeLists.txt`, and other necessary directories and parameters in `include/Defs.hpp` file.

And then compile the code by the following commands:

```bash
mkdir build
cd build
cmake ..
make
```

Then you can run directly the executable binary with default parameters set in `include/Defs.hpp` by the following command:

```bash
./MA-CETSP
```

In addition, you can run the code with your own parameters by the following command:

```bash
./MA-CETSP -i <instance> -s <seed> -r <max iteration> -p <population size> -b <fitness beta> -d <distance threshold> -n <neighbor size>
```

## Citation

If it is helpful for your research, please cite our paper:

```bibtex

```
