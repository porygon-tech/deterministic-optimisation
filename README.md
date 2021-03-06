# Deterministic optimisation
The Rosenbrock valley or Rosenbrock function is a well known function commonly used for testing performance in optimisation algorithms.

![rosenbrock](/rosenbrock.png)

In this report, the performance of two iterative optimisation algorithms for minimisation is assessed on the Rosenbrock function, which has its global minimum at (1, 1) The first one is the Conjugate Gradient method (CG), which had to be implemented in its nonlinear version to make it compatible with this function; while the second one is the Levenberg-Marquardt method (LM), which combines the best of the Newton method and the steepest descent.
\
Taking into account the steepness of this surface, the starting point (-1.5, -1) seems to be a good seed since it starts near the optimal minimum (a condition usually required by some fast-converging algorithms such LM or the Newton\'s method).

------------

The following results are consistent with the properties of both algorithms, since the LM converges very quickly (at the cost of a high sensitivity to initial conditions (needs to be close to the local/global minimum).

Conjugate Gradient (`rosenbrock2.c`): 40 iters:

![CG](/CG.png)

Levenberg-Marquardt (`rosenbrock_lma.c`): 16 iters:

![LM](/LM.png)


Evaluating the hessian properties, the function is convex in all R2.

