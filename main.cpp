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
  //cout << "a is " << a.at(i) << endl;
  //cout << "c is " << c.at(i) << endl;
  if ((a.at(i) + c.at(i) + carry) <= 9) {
    // Just add the numbers
    if (carry == 0) {
      //cout << "No Need to carry" << endl;
      //cout << c.at(i) << " + " << a.at(i) << " = ";
      c.at(i) += a.at(i);
      //cout << c.at(i) << endl;
    } else {
      // Add the carry
      //cout << "Add the carry: " << carry << " to " << c.at(i) << " + " << a.at(i) << endl;
      c.at(i) += a.at(i) + carry;
      //cout << "Answer: " << c.at(i) << endl;
      carry = 0;
      carry_vector.clear();
    }
  } else {
    // Need to carry
    carry_vector.clear();
    carryDigits(carry_vector, a.at(i) + c.at(i) + carry);
    //cout << "Carry Vector Size: " << carry_vector.size() << endl;
	  //cout << "Adding a:" << a.at(i) << " + c:" << c.at(i) << " + carry:" << carry << endl;
	  carry = carry_vector.at(0);
	  c.at(i) = carry_vector.at(1);
	  //cout << "carry digit:" << carry << " result digit(c):" << c.at(i) << endl;
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

  for (vector<int>::reverse_iterator it_b = b.rbegin(); it_b != b.rend(); ++it_b) {
    //cout << "***********OUTER LOOP **************" << endl;
    //cout << "Padding the partial product with " << count << " 0's" << endl;
    padLeft(partialProduct, count);
    for (vector<int>::reverse_iterator it_a = a.rbegin(); it_a != a.rend(); ++it_a) {
      //cout << "Multiply " << *it_a << " * " << *it_b << endl;
      int temp = *it_a * *it_b;
      //cout << "Answer: " << temp << endl;

      // Check for carry
      if (carry > 0) {
        temp += carry;
        //cout << "Adding the carry: " << carry << endl;
        carry = 0;
        carry_vector.clear();
      }
      // Check if numbers need to be carried then add to the partial product
      if (temp > 9) {
        carryDigits(carry_vector, temp);
        carry = carry_vector.at(0);
        //cout << "Carrying a " << carry << endl;
        //cout << "Adding " << carry_vector.at(1) << " to partial product" << endl;
        partialProduct.insert(partialProduct.begin(), carry_vector.at(1));
      } else {
        //cout << "Adding " << temp << " to partial product" << endl;
        partialProduct.insert(partialProduct.begin(), temp);
      }
    }
    // Check for extra carry
    if (carry > 0) {
      //cout << "Extra Cary: " << carry << " adding it to partial product" << endl;
      partialProduct.insert(partialProduct.begin(), carry);
      carry = 0;
      carry_vector.clear();
    }
    // Add the partial product to the final answer c
    //cout << "**********ADDING THE PARTIAL PRODUCT***********" << endl;
    addPartialProducts(partialProduct, c);
    partialProduct.clear();
    ++count;
  }
  if (c.at(0) == 0) {
    while (c.at(0) == 0) {
      if(c.size() != 1) {
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
  //cout << "a is " << a.at(i) << endl;
  //cout << "c is " << c.at(i) << endl;
  if ((a.at(i) + c.at(i) + carry) <= 9) {
    // Just add the numbers
    if (carry == 0) {
      //cout << "No Need to carry" << endl;
      //cout << c.at(i) << " + " << a.at(i) << " = ";
      c.at(i) += a.at(i);
      //cout << c.at(i) << endl;
    } else {
      // Add the carry
      //cout << "Add the carry: " << carry << " to " << c.at(i) << " + " << a.at(i) << endl;
      c.at(i) += a.at(i) + carry;
      //cout << "Answer: " << c.at(i) << endl;
      carry = 0;
      carry_vector.clear();
    }
  } else {
    // Need to carry
    carry_vector.clear();
    carryDigits(carry_vector, a.at(i) + c.at(i) + carry);
    //cout << "Carry Vector Size: " << carry_vector.size() << endl;
	  //cout << "Adding a:" << a.at(i) << " + c:" << c.at(i) << " + carry:" << carry << endl;
	  carry = carry_vector.at(0);
	  c.at(i) = carry_vector.at(1);
	  //cout << "carry digit:" << carry << " result digit(c):" << c.at(i) << endl;
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
    cout << "if " << a.at(i) << " < " << b.at(i) << endl;
    if (a.at(i) < b.at(i)) {
      if (a.at(i - 1) != 0) {
        a.at(i - 1) = a.at(i - 1) - 1;
        a.at(i) = a.at(i) + 10;
      } else {
        cout << "Do the weird stuff" << endl;
        int count = 0;
        for (int j = i - 1; j >= 0; --j) {
          if (a.at(j) != 0) {
            a.at(j) = a.at(j) - 1;
            ++j;
            while (count >= 0) {
              cout << "count is " << count << endl;
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
  if (a.at(0) == 0) {
    while (a.at(0) == 0) {
      if(a.size() != 1) {
        a.erase(a.begin());
      } else {
        break;
      }
    }
  }
  if (b.at(0) == 0) {
    while (b.at(0) == 0) {
      if(b.size() != 1) {
        b.erase(b.begin());
      } else {
        break;
      }
    }
  }
  vector<int> final_answer;
  if (a.size() <= 5 || b.size() <= 5) {
    // Do brute force
    cout << "A is " << a.size() << " B is " << b.size() << endl;
    cout << "A and B are small" << endl;
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
    cout << "M is: " << m << endl;
    // a's and b's
    // Set a0
	cout << "a0 is: ";
	for (size_t i = a.size() - m; i < a.size(); ++i)
	{
		a0.push_back(a.at(i));
		cout << a.at(i);
    }
    cout << endl;
    // Set a1
    cout << "a1 is: ";
    for (size_t i = 0; i < (a.size() - m); ++i) {
      a1.push_back(a.at(i));
      cout << a.at(i);
    }
    cout << endl;
    // Set b0
    cout << "b0 is: ";
    for (size_t i = b.size() - m; i < b.size(); ++i) {
      b0.push_back(b.at(i));
      cout << b.at(i);
    }
    cout << endl;
    // Set b1
    cout << "b1 is: ";
    for (size_t i = 0; i < (b.size() - m); ++i) {
      b1.push_back(b.at(i));
      cout << b.at(i);
    }
    cout << endl;

	cout << "Taking the Karatsuba of ";
	for (size_t i = 0; i < a1.size(); ++i)
	{
	  cout << a1.at(i);
	}
	cout << " and ";
	for (size_t i = 0; i < b1.size(); ++i)
	{
	  cout << b1.at(i);
	}
	cout << endl;
	c2 = karatsuba(a1, b1);

	cout << "Taking the Karatsuba of ";
	for (size_t i = 0; i < a0.size(); ++i)
	{
	  cout << a0.at(i);
	}
	cout << " and ";
	for (size_t i = 0; i < b0.size(); ++i)
	{
	  cout << b0.at(i);
	}
	cout << endl;
	c0 = karatsuba(a0, b0);

	vector<int> a_result = addVectors(a1, a0);
	vector<int> b_result = addVectors(b1, b0);
	cout << "Taking the Karatsuba of ";
	for (size_t i = 0; i < a_result.size(); ++i)
	{
	  cout << a_result.at(i);
	}
	cout << " and ";
	for (size_t i = 0; i < b_result.size(); ++i)
	{
	  cout << b_result.at(i);
	}
	cout << endl;
	c1 = karatsuba(a_result, b_result);

	cout << "Subtacting (c2)";
    for (size_t i = 0; i < c2.size(); ++i) {
      cout << c2.at(i);
    }
    cout << " from (c1)";
    for (size_t i = 0; i < c1.size(); ++i) {
      cout << c1.at(i);
    }
    cout << endl;
    c1 = subtractVectors(c1, c2);

    cout << "Subtacting (c0)";
    for (size_t i = 0; i < c0.size(); ++i) {
      cout << c0.at(i);
    }
    cout << " from (c1)";
    for (size_t i = 0; i < c1.size(); ++i) {
      cout << c1.at(i);
    }
    cout << endl;
    c1 = subtractVectors(c1, c0);
    
    // Get the 10^2m and 10^m part of the expression
    vector<int> m2_v = {1,0};
    vector<int> m1_v = {1,0};
    vector<int> ten_vector = {1,0};
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

	cout << "answer_c2 when were doing the final thing: ";
	for (size_t i = 0; i < answer_c2.size(); ++i) {
		cout << answer_c2.at(i);
	}
	cout << endl;

	cout << "answer_c1 when were doing the final thing: ";
	for (size_t i = 0; i < answer_c1.size(); ++i) {
		cout << answer_c1.at(i) << " ";
	}
	cout << endl;

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