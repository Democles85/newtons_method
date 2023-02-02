## Overview

This code is an implementation of Newton's method for finding the roots of a mathematical function. The input to the algorithm is a function `f`, its derivative `f'`, an initial guess `x0`, and a tolerance and maximum number of iterations. The output is an approximation of a root of `f`.

## Algorithm

This code implements Newton's method for finding roots of a mathematical function. Given a function `f`, its derivative `f'`, an initial guess `x0`, and a tolerance and maximum number of iterations, it returns an approximation to a root of the function.

The algorithm works as follows:

1. Set `x = x0`
2. Repeat the following steps for `i` from 1 to `maxIterations`:
  - Calculate `x = x - f(x)/f'(x)`
    
  - If `|f(x)| < tolerance`, return `x`
    
3. If the loop has not returned, return "no root found"

Please note that the current implementation of the code does not support mathematical constants such as `e` or `pi`, or functions such as `sin`, `cos`, `tan`, `log`, `ln`, or `sqrt`.

To avoid potential overflow issues, it is recommended to convert all the variables to `long long` numbers. The code also includes a `vector` of `Equation` objects, which can be used to parse an equation string and format an equation vector into a string.

## Classes and Functions

The code contains the following classes and functions:

- `Equation` class: Represents an equation term, for example, 3x^2 is represented by `Equation(3, 2)`.
- `parseEquation` function: Parses an equation string into a vector of `Equation` objects.
- `formatEquation` function: Formats an equation vector into a string.

## Limitations

The current implementation has the following limitations:

- Does not support numbers like `e` and `pi`.
- Does not support functions like `sin`, `cos`, `tan`, `log`, `ln`, and `sqrt`.

## TODOs

The following improvements are planned to be added in the future:

- Add support for numbers like `e` and `pi`.
- Add support for functions like `sin`, `cos`, `tan`, `log`, `ln`, and `sqrt`.
- Convert all variables to long long numbers to avoid overflow.

## Conclusion

This code provides an implementation of Newton's method for finding the roots of a function. However, it has some limitations and improvements are planned for the future.
