/***************************************************************************
 * Author: Christopher Moyer
 * Date: November 19th, 2019
 *
 * This class will take in a multiplication problem formatted as a*b
 * from stdin. The answer will be found using a brute force alogorithim and
 * then using the karatsuba algorithim. Both will be written to stdout.
 *
**/

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::pow;
using std::stoi;
using std::string;
using std::vector;

void padLeft(vector<int> &the_vector, size_t number_of_zeroes) {
  while (number_of_zeroes != 0) {
    the_vector.insert(the_vector.begin(), 0);
    --number_of_zeroes;
  }
}

void carryDigits(vector<int> &digits, int num) {
  if (num > 9) {
    carryDigits(digits, num / 10);
  }
  digits.push_back(num % 10);
}

void addPartialProducts(vector<int> a, vector<int> &c) {
  int carry = 0;
  vector<int> carry_vector;
  // Make both vectors the same length for addition
  if (a.size() != c.size()) {
    if (a.size() < c.size()) {
      padLeft(a, c.size() - a.size());
    } else {
      padLeft(c, a.size() - c.size());
    }
  }

  for (int i = c.size() - 1; i >= 0; --i) {
  // Check if need to carry
  if ((a.at(i) + c.at(i) + carry) <= 9) {
    // Just add the numbers
    if (carry == 0) {
      // No need to carry
      c.at(i) += a.at(i);
    } else {
      // Add the carry
      c.at(i) += a.at(i) + carry;
      carry = 0;
      carry_vector.clear();
    }
  } else {
    // Need to carry
    carry_vector.clear();
    carryDigits(carry_vector, a.at(i) + c.at(i) + carry);
    carry = carry_vector.at(0);
    c.at(i) = carry_vector.at(1);
  }
}
  if (carry > 0) {
    c.insert(c.begin(), carry);
  }
}

vector<int> bruteForceMultiply(vector<int> a, vector<int> b) {
  int carry = 0;
  int count = 0;
  vector<int> carry_vector;
  vector<int> c;
  vector<int> partialProduct;

  for (vector<int>::reverse_iterator it_b = b.rbegin(); it_b != b.rend();
                                                                ++it_b) {
    padLeft(partialProduct, count);
    for (vector<int>::reverse_iterator it_a = a.rbegin(); it_a != a.rend();
                                                                ++it_a) {
      int temp = *it_a * *it_b;

      // Check for carry
      if (carry > 0) {
        temp += carry;
        carry = 0;
        carry_vector.clear();
      }
      // Check if numbers need to be carried then add to the partial product
      if (temp > 9) {
        carryDigits(carry_vector, temp);
        carry = carry_vector.at(0);
        partialProduct.insert(partialProduct.begin(), carry_vector.at(1));
      } else {
        partialProduct.insert(partialProduct.begin(), temp);
      }
    }
    // Check for extra carry
    if (carry > 0) {
      partialProduct.insert(partialProduct.begin(), carry);
      carry = 0;
      carry_vector.clear();
    }
    // Add the partial product to the final answer c
    addPartialProducts(partialProduct, c);
    partialProduct.clear();
    ++count;
  }

  // Remove the padding for printing
  if (c.at(0) == 0) {
    while (c.at(0) == 0) {
      if (c.size() != 1) {
        c.erase(c.begin());
      } else {
        break;
      }
    }
  }
  return c;
}

vector<int> addVectors(vector<int> a, vector<int> c) {
  int carry = 0;
  vector<int> carry_vector;
  // Make both vectors the same length for addition
  if (a.size() != c.size()) {
    if (a.size() < c.size()) {
      padLeft(a, c.size() - a.size());
    } else {
      padLeft(c, a.size() - c.size());
    }
  }

  for (int i = c.size() - 1; i >= 0; --i) {
  // Check if need to carry
  if ((a.at(i) + c.at(i) + carry) <= 9) {
    // Just add the numbers
    if (carry == 0) {
      c.at(i) += a.at(i);
    } else {
      // Add the carry
      c.at(i) += a.at(i) + carry;
      carry = 0;
      carry_vector.clear();
    }
  } else {
    // Need to carry
    carry_vector.clear();
    carryDigits(carry_vector, a.at(i) + c.at(i) + carry);
    carry = carry_vector.at(0);
    c.at(i) = carry_vector.at(1);
  }
}
  if (carry > 0) {
    c.insert(c.begin(), carry);
  }

  return c;
}

vector<int> subtractVectors(vector<int> a, vector<int> b) {
  vector<int> c;
  // Make both vectors the same length
  if (a.size() != b.size()) {
    if (a.size() < b.size()) {
      padLeft(a, b.size() - a.size());
    } else {
      padLeft(b, a.size() - b.size());
    }
  }

  // Subtract
  for (int i = a.size() - 1; i >= 0; --i) {
    // Need to borrow

    // Next number isn't 0. Just borrow and regroup
    if (a.at(i) < b.at(i)) {
      if (a.at(i - 1) != 0) {
        a.at(i - 1) = a.at(i - 1) - 1;
        a.at(i) = a.at(i) + 10;
      } else {
        // The next number isn't 0
        // Find one that isn't 0, borrow, and then regroup
        int count = 0;
        for (int j = i - 1; j >= 0; --j) {
          if (a.at(j) != 0) {
            a.at(j) = a.at(j) - 1;
            ++j;
            while (count >= 0) {
              if (count == 0) {
                a.at(j) = a.at(j) + 10;
                --count;
              } else {
                  a.at(j) = a.at(j) + 10 - 1;
                  --count;
                  ++j;
              }
            }
            break;
          }
          ++count;
        }
      }
    }
    // Do the subtraction
    c.insert(c.begin(), a.at(i) - b.at(i));
  }
  return c;
}

vector<int> karatsuba(vector<int> a, vector<int> b) {
  // Remove the padding that was added before brute force
  if (a.at(0) == 0) {
    while (a.at(0) == 0) {
      if (a.size() != 1) {
        a.erase(a.begin());
      } else {
        break;
      }
    }
  }
  if (b.at(0) == 0) {
    while (b.at(0) == 0) {
      if (b.size() != 1) {
        b.erase(b.begin());
      } else {
        break;
      }
    }
  }
  vector<int> final_answer;
  if (a.size() <= 5 || b.size() <= 5) {
    // A and B are small
    // Do brute force
    return bruteForceMultiply(a, b);
  } else {
    // Do Karatsuba
    int m;
    vector<int> a0, a1, b0, b1, c0, c1, c2;
    // Find max and set m
    if (a.size() > b.size()) {
      m = a.size() / 2;
    } else {
      m = b.size() / 2;
    }
    // a's and b's
    // Set a0
    for (size_t i = a.size() - m; i < a.size(); ++i) {
      a0.push_back(a.at(i));
    }
    // Set a1
    for (size_t i = 0; i < (a.size() - m); ++i) {
      a1.push_back(a.at(i));
    }
    // Set b0
    for (size_t i = b.size() - m; i < b.size(); ++i) {
      b0.push_back(b.at(i));
    }
    // Set b1
    for (size_t i = 0; i < (b.size() - m); ++i) {
      b1.push_back(b.at(i));
    }

    c2 = karatsuba(a1, b1);
    c0 = karatsuba(a0, b0);

    vector<int> a_result = addVectors(a1, a0);
    vector<int> b_result = addVectors(b1, b0);

    c1 = karatsuba(a_result, b_result);

    c1 = subtractVectors(c1, c2);
    c1 = subtractVectors(c1, c0);

    // Get the 10^2m and 10^m part of the expression
    vector<int> m2_v = {1, 0};
    vector<int> m1_v = {1, 0};
    vector<int> ten_vector = {1, 0};
    int m2 = 2 * m;
    int m1 = m;

    for (int i = 1; i < m2; ++i) {
      m2_v = bruteForceMultiply(m2_v, ten_vector);
    }

    for (int i = 1; i < m1; ++i) {
      m1_v = bruteForceMultiply(m1_v, ten_vector);
    }

    // Do the multiplication
    vector<int> answer_c2 = bruteForceMultiply(m2_v, c2);
    vector<int> answer_c1 = bruteForceMultiply(m1_v, c1);

    final_answer = addVectors(answer_c2, answer_c1);
    final_answer = addVectors(final_answer, c0);

    return final_answer;
  }
}
int main() {
  vector<int> a;
  vector<int> b;
  vector<int> brute_force_c;
  vector<int> karatsuba_c;

  string input;

  cin >> input;

  size_t delmiter_index = input.find("*");

  // Convert the ASCII char value to the proper int value
  // and store in the vector
  for (size_t i = 0; i < delmiter_index; ++i) {
    a.push_back(input.at(i) - '0');
  }
  for (size_t i = delmiter_index + 1; i < input.size(); ++i) {
    b.push_back(input.at(i) - '0');
  }

  // Check to see if the numbers are the same length
  // If not, pad left with 0's so they are the same length
  if (a.size() != b.size()) {
    if (a.size() < b.size()) {
      size_t number_of_zeroes = b.size() - a.size();
      padLeft(a, number_of_zeroes);
    } else {
      size_t number_of_zeroes = a.size() - b.size();
      padLeft(b, number_of_zeroes);
    }
  }

  brute_force_c = bruteForceMultiply(a, b);

  cout << "B: ";
  for (size_t i = 0; i < brute_force_c.size(); ++i) {
    cout << brute_force_c.at(i);
  }
  cout << endl;

  // KARATSUBA
  karatsuba_c = karatsuba(a, b);

  cout << "K: ";
  for (size_t i = 0; i < karatsuba_c.size(); ++i) {
    cout << karatsuba_c.at(i);
  }
  cout << endl;
}
