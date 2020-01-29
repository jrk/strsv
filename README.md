# Optimized STRSV

`STRSV` is a [BLAS level 2](http://www.netlib.org/lapack/explore-html/d6/d30/group__single__blas__level2_ga59aeaec580e854d68c43c47e951637fe.html)
operator for solving systems of the form `Ly=b` or `Ux=y` for a factored square matrix `A=LU`.
This repository (currently) tries to produce an optimized solver for the lower-triangular case,
under several ideal conditions:

1. The dimension of `L` is divisible by 4.
2. `L` is 64-byte aligned
3. `L` is a large, square block of memory
4. `L` is a unit matrix (1s along diagonal)

In BLAS, this corresponds to:

```
strsv('L', 'N', 'U', N, L, N, y, 1)
```

where `L` is the matrix, `N` is its dimension, and `y` is initially `b`, but is overwritten to be the solution. 