#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

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
 * "x^2-2x+5" is parsed into the vector [Equation(1, 2), Equation(-2, 1), Equation(5, 0)].
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
    else
    {
      // Constant term, skip it
      while (i < length && equation[i] != '+' && equation[i] != '-')
      {
        i++;
      }
      continue;
    }
    result.push_back(Equation(coefficient, power));
    if (i < length)
    {
      // Skip the sign
      i++;
    }
  }
  return result;
}

/*
 * This function formats a vector of Equation objects into a string.
 * For example, the vector [Equation(3, 2), Equation(2, 1), Equation(5, 0)] is formatted into "3x^2+2x+5".
 * The vector [Equation(1, 2), Equation(2, 1), Equation(5, 0)] is formatted into "x^2+2x+5".
 * The vector [Equation(1, 2), Equation(2, 1)] is formatted into "x^2+2x".
 * The vector [Equation(1, 2), Equation(2, 0)] is formatted into "x^2+2".
 * The vector [Equation(1, 2)] is formatted into "x^2".
 * The vector [Equation(1, 1)] is formatted into "x".
 * The vector [Equation(5, 0)] is formatted into "5".
 * The vector [Equation(1, 2), Equation(-2, 1), Equation(5, 0)] is formatted into "x^2-2x+5".
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
 * This function is the main function of the program.
 * It prompts the user to enter an equation, parses the equation, differentiates the equation, and prints the result.
 */
int main()
{
  string equation;
  std::cout << "Enter an equation: ";
  getline(cin, equation);
  vector<Equation> parsedEquation = parseEquation(equation);
  vector<Equation> differentiatedEquation = differentiate(parsedEquation);
  std::cout << "The derivative of the equation is: " << formatEquation(differentiatedEquation) << std::endl;

  return 0;
}