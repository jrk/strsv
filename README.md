# Optimized STRSV

`STRSV` is a [BLAS level 2](http://www.netlib.org/lapack/explore-html/d6/d30/group__single__blas__level2_ga59aeaec580e854d68c43c47e951637fe.html)
operator for solving systems of the form `Ly=b` or `Ux=y` for a factored square matrix `A=LU`.
This repository (currently) tries to produce an optimized solver for the lower-triangular case,
under several ideal conditions:

1. The dimension of `L` is divisible by 4.
2. `L` is a large, square block of memory
3. `L` is a unit matrix (1s along diagonal)

The file `src/blocked-solver.cpp` contains this solver.

## Approach

The basic optimization strategy is to carve the matrix `L` into nx4 blocks with a 4x4 triangle on top and 4x4 squares
below it.
The dependency structure allows us to process the triangle first and then the squares beneath can be vectorized and even
parallelized (though the implementation does not yet do this and it's not clear it would be beneficial).
Illustrated in ASCII-art this is:
```
*
**
***
****

....*
....**
....***
....****

....
....
....
....
```
and so on.

This matches the performance of OpenBLAS for me.