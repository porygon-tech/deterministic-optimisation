# deterministic-optimisation
The Rosenbrock valley is a well known function used to test performance in optimisation algorithms. 

The conjugate gradient method is not compatible with this function, so its nonlinear version must be used https://math.stackexchange.com/questions/466462/minimize-rosenbrock-function-with-conjugate-gradient-method
Taking into account the steepness of this surface, the starting point (-1.5, -1) seems to be a good seed since it starts near the optimal minimum.

conjugate gradient: 40 iters
Levenbert-Marquardt: 16 iters
