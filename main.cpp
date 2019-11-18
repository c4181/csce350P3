#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
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
  cout << "a is " << a.at(i) << endl;
  cout << "c is " << c.at(i) << endl;
  if ((a.at(i) + c.at(i) + carry) <= 9) {
    // Just add the numbers
    if (carry == 0) {
      cout << "No Need to carry" << endl;
      cout << c.at(i) << " + " << a.at(i) << " = ";
      c.at(i) += a.at(i);
      cout << c.at(i) << endl;
    } else {
      // Add the carry
      cout << "Add the carry: " << carry << " to " << c.at(i) << " + " << a.at(i) << endl;
      c.at(i) += a.at(i) + carry;
      cout << "Answer: " << c.at(i) << endl;
      carry = 0;
      carry_vector.clear();
    }
  } else {
    // Need to carry
    carry_vector.clear();
    carryDigits(carry_vector, a.at(i) + c.at(i) + carry);
    cout << "Carry Vector Size: " << carry_vector.size() << endl;
	  cout << "Adding a:" << a.at(i) << " + c:" << c.at(i) << " + carry:" << carry << endl;
	  carry = carry_vector.at(0);
	  c.at(i) = carry_vector.at(1);
	  cout << "carry digit:" << carry << " result digit(c):" << c.at(i) << endl;
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
    cout << "***********OUTER LOOP **************" << endl;
    cout << "Padding the partial product with " << count << " 0's" << endl;
    padLeft(partialProduct, count);
    for (vector<int>::reverse_iterator it_a = a.rbegin(); it_a != a.rend(); ++it_a) {
      cout << "Multiply " << *it_a << " * " << *it_b << endl;
      int temp = *it_a * *it_b;
      cout << "Answer: " << temp << endl;

      // Check for carry
      if (carry > 0) {
        temp += carry;
        cout << "Adding the carry: " << carry << endl;
        carry = 0;
        carry_vector.clear();
      }
      // Check if numbers need to be carried then add to the partial product
      if (temp > 9) {
        carryDigits(carry_vector, temp);
        carry = carry_vector.at(0);
        cout << "Carrying a " << carry << endl;
        cout << "Adding " << carry_vector.at(1) << " to partial product" << endl;
        partialProduct.insert(partialProduct.begin(), carry_vector.at(1));
      } else {
        cout << "Adding " << temp << " to partial product" << endl;
        partialProduct.insert(partialProduct.begin(), temp);
      }
    }
    // Check for extra carry
    if (carry > 0) {
      cout << "Extra Cary: " << carry << " adding it to partial product" << endl;
      partialProduct.insert(partialProduct.begin(), carry);
      carry = 0;
      carry_vector.clear();
    }
    // Add the partial product to the final answer c
    cout << "**********ADDING THE PARTIAL PRODUCT***********" << endl;
    addPartialProducts(partialProduct, c);
    partialProduct.clear();
    ++count;
  }
  return c;
}

int main() {
  vector<int> a;
  vector<int> b;
  vector<int> c;

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

  c = bruteForceMultiply(a, b);

  for (size_t i = 0; i < c.size(); ++i) {
    cout << c.at(i) << " ";
  }
}