/*
 * Newton's method for finding roots of a function
 * Input: a function f, its derivative f', an initial guess x0, and a tolerance and maximum number of iterations
 * Output: an approximation to a root of f
 *
 * Note: Keep in mind numbers like e and pi are not supported.
 *
 * TODO: Add support for numbers like e and pi.
 * TODO: Add support for functions like sin, cos, and tan.
 * TODO: Add support for functions like log and ln.
 * TODO: Add support for functions like sqrt.
 *
 * TODO: Convert all the variables to long long numbers to avoid overflow.
 *
 * Algorithm:
 *  x = x0
 * for i = 1 to maxIterations
 *  x = x - f(x)/f'(x)
 * if |f(x)| < tolerance
 * return x
 * else
 * return "no root found"
 * end if
 * end for
 * return "no root found"
 * end
 */

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

#define __int64 long long
#define __double long double

typedef __int64 int64;
typedef __double double64;

using namespace std;

/*
 * This class represents an equation term.
 * For example, 3x^2 is represented by the object Equation(3, 2).
 * 2x is represented by the object Equation(2, 1).
 * x is represented by the object Equation(1, 1).
 * 5 is represented by the object Equation(5, 0).
 */

class Equation
{
public:
  int coefficient;
  int power;
  Equation(int coefficient, int power)
  {
    this->coefficient = coefficient;
    this->power = power;
  }
};

/*
 * This function parses an equation string into a vector of Equation objects.
 * For example, "3x^2+2x+5" is parsed into the vector [Equation(3, 2), Equation(2, 1), Equation(5, 0)].
 * "x^2+2x+5" is parsed into the vector [Equation(1, 2), Equation(2, 1), Equation(5, 0)].
 * "x^2+2x" is parsed into the vector [Equation(1, 2), Equation(2, 1)].
 * "x^2+2" is parsed into the vector [Equation(1, 2), Equation(2, 0)].
 * "x^2" is parsed into the vector [Equation(1, 2)].
 * "x" is parsed into the vector [Equation(1, 1)].
 * "5" is parsed into the vector [Equation(5, 0)].
 * "-x^2+2x-5" is parsed into the vector [Equation(-1, 2), Equation(2, 1), Equation(-5, 0)].
 */

vector<Equation> parseEquation(string equation)
{
  vector<Equation> result;
  int length = equation.length();
  int i = 0;
  while (i < length)
  {
    int coefficient = 0;
    int power = 0;
    // Parse the coefficient
    if (equation[i] == 'x')
    {
      coefficient = 1;
    }
    else if (equation[i] == '-')
    {
      coefficient = -1;
      i++;
    }
    else if (equation[i] >= '0' && equation[i] <= '9')
    {
      coefficient = equation[i] - '0';
      i++;
      while (i < length && equation[i] >= '0' && equation[i] <= '9')
      {
        coefficient = coefficient * 10 + equation[i] - '0';
        i++;
      }
    }

    // Parse the power
    if (i < length && equation[i] == 'x')
    {
      i++;
      if (i < length && equation[i] == '^')
      {
        i++;
        power = equation[i] - '0';
        i++;
        while (i < length && equation[i] >= '0' && equation[i] <= '9')
        {
          power = power * 10 + equation[i] - '0';
          i++;
        }
      }
      else
      {
        power = 1;
      }
    }
    result.push_back(Equation(coefficient, power));
    if (i < length && equation[i] == '+')
    {
      i++;
    }
  }
  return result;
}

/*
 * This function formats an equation vector into a string.
 * For example, the vector [Equation(3, 2), Equation(2, 1), Equation(5, 0)] is formatted into "3x^2+2x+5".
 * The vector [Equation(1, 2), Equation(2, 1), Equation(5, 0)] is formatted into "x^2+2x+5".
 * The vector [Equation(1, 2), Equation(2, 1)] is formatted into "x^2+2x".
 * The vector [Equation(1, 2), Equation(2, 0)] is formatted into "x^2+2".
 * The vector [Equation(1, 2)] is formatted into "x^2".
 * The vector [Equation(1, 1)] is formatted into "x".
 * The vector [Equation(5, 0)] is formatted into "5".
 * The vector [Equation(-1, 2), Equation(2, 1), Equation(-5, 0)] is formatted into "-x^2+2x-5".
 */

string formatEquation(vector<Equation> equation)
{
  string result = "";
  for (int i = 0; i < equation.size(); i++)
  {
    if (equation[i].coefficient == 0)
    {
      continue;
    }
    if (equation[i].coefficient > 0 && i > 0)
    {
      result += "+";
    }
    if (equation[i].coefficient != 1 || equation[i].power == 0)
    {
      result += to_string(equation[i].coefficient);
    }
    if (equation[i].power == 1)
    {
      result += "x";
    }
    else if (equation[i].power > 1)
    {
      result += "x^" + to_string(equation[i].power);
    }
  }
  if (result.length() == 0)
  {
    result = "0";
  }
  return result;
}

/*
 * This function differentiates a vector of Equation objects.
 * For example, the vector [Equation(3, 2), Equation(2, 1), Equation(5, 0)] is differentiated into [Equation(6, 1), Equation(2, 0)].
 * The vector [Equation(1, 2), Equation(2, 1), Equation(5, 0)] is differentiated into [Equation(2, 1), Equation(2, 0)].
 * The vector [Equation(1, 2), Equation(2, 1)] is differentiated into [Equation(2, 1)].
 * The vector [Equation(1, 2), Equation(2, 0)] is differentiated into [Equation(2, 1)].
 * The vector [Equation(1, 2)] is differentiated into [Equation(2, 1)].
 * The vector [Equation(1, 1)] is differentiated into [Equation(1, 0)].
 * The vector [Equation(5, 0)] is differentiated into [].
 * The vector [Equation(1, 2), Equation(-2, 1), Equation(5, 0)] is differentiated into [Equation(2, 1), Equation(-2, 0)].
 * The vector [Equation(-1, 2), Equation(2, 1), Equation(-5, 0)] is differentiated into [Equation(-2, 1), Equation(2, 0)].
 */
vector<Equation> differentiate(vector<Equation> equation)
{
  vector<Equation> result;
  for (int i = 0; i < equation.size(); i++)
  {
    if (equation[i].power > 0)
    {
      result.push_back(Equation(equation[i].coefficient * equation[i].power, equation[i].power - 1));
    }
  }
  return result;
}

/*
 * This function evaluates an equation at a given value of x.
 * For example, if the equation is "3x^2+2x+5", then the value of the equation at x = 2 is 29.
 */

double64 evaluateEquation(vector<Equation> equation, double x)
{
  double64 result = 0;
  for (int i = 0; i < equation.size(); i++)
  {
    result += equation[i].coefficient * pow(x, equation[i].power);
  }
  return result;
}

/*
 * This function evaluates the derivative of an equation at a given value of x.
 * For example, if the equation is "3x^2+2x+5", then the value of the derivative of the equation at x = 2 is 13.
 */

double64 evaluateDerivative(vector<Equation> equation, double x)
{
  double64 result = 0;
  for (int i = 0; i < equation.size(); i++)
  {
    result += equation[i].coefficient * equation[i].power * pow(x, equation[i].power - 1);
  }
  return result;
}

/*
 * This function finds a root of an equation using Newton's method.
 * Input: an equation, an initial guess x0, a tolerance, and a maximum number of iterations
 * Output: an approximation to a root of the equation
 */

double64 newtonsMethod(vector<Equation> equation, double x0, double tolerance, int maxIterations)
{
  double64 x = x0;
  /*
    Print the iteration number, the current guess, and the value of the equation at the current guess.
    For example, if the equation is "3x^2+2x+5", the initial guess is 2, the tolerance is 0.0001, and the maximum number of iterations is 10,
    then the output should be:
    Iteration 1: x = 2, f(x) = 29
    Iteration 2: x = 1.58621, f(x) = 5.00001
    Iteration 3: x = 1.58114, f(x) = 0.0001024
    Iteration 4: x = 1.58114, f(x) = 0
    The function should return 1.58114.
  */

  for (int i = 1; i <= maxIterations; i++)
  {
    // cout << "Iteration " << i << ": x = " << x << ", f(x) = " << evaluateEquation(equation, x) << endl;
    x = x - evaluateEquation(equation, x) / evaluateDerivative(equation, x);
    if (abs(evaluateEquation(equation, x)) < tolerance)
    {
      return x;
    }

    // Check how many digits are including the decimal point in x and use that to determine how many spaces to print after the x value in the output string (to make the output look nice)
    int numDigitsAfterDecimal = 0;
    double64 xCopy = x;
    while (xCopy - (int)xCopy != 0)
    {
      if (numDigitsAfterDecimal == 0)
        numDigitsAfterDecimal = 1;

      xCopy *= 10;
      numDigitsAfterDecimal++;
    }

    std::cout << "Iteration [" << i << "]:" << right << setw(10 - (i > 9 ? 1 : 0)) << setfill(' ') << "x = " << x << setw(20 - numDigitsAfterDecimal) << setfill(' ') << "f(x) = " << evaluateEquation(equation, x) << endl;
  }

  return -1;
}

int main()
{
  string equationString;
  cout << "Enter an equation: ";
  cin >> equationString;
  vector<Equation> equation = parseEquation(equationString);
  vector<Equation> derivative = differentiate(equation);
  double x0;
  cout << "Enter an initial guess: ";
  cin >> x0;
  double tolerance;
  cout << "Enter a tolerance: ";
  cin >> tolerance;
  int maxIterations;
  cout << "Enter a maximum number of iterations: ";
  cin >> maxIterations;

  std::cout << left << setfill('-') << setw(15 + equationString.length()) << "" << endl; // Print a line of 15 dashes (-----) and the length of the equation string
  std::cout << left << setfill(' ') << setw(15) << "Equation: " << formatEquation(equation) << endl;
  std::cout << left << setfill(' ') << setw(15) << "Derivative: " << formatEquation(derivative) << endl;
  std::cout << left << setfill('-') << setw(15 + equationString.length()) << "" << endl; // Print a line of 15 dashes (-----) and the length of the equation string

  double64 root = newtonsMethod(equation, x0, tolerance, maxIterations);
  if (root == -1)
  {
    cout << "No root found." << endl;
  }
  else
  {
    cout << "Root: " << root << endl;
  }
  return 0;
}
