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
  padLeft(a, c.size() - a.size());

  for (size_t i = c.size(); i > 0; --i) {
    int temp = a.at(i - 1) + c.at(i - 1);

    // Check for numbers to be carried
    if (carry > 0) {
      temp += carry;
      carry = 0;
      carry_vector.clear();
    }
    if (temp > 9) {
      carryDigits(carry_vector, temp);
      carry = carry_vector.at(0);
      c.at(i - 1) += carry_vector.at(1);
    } else {
      c.at(i - 1) += temp;
    }
  }
  if (carry > 0) {
    c.insert(c.begin(), carry);
  } 
}

// TODO Helper function to add partial products
// This function can't handle carrying in the addition
vector<int> bruteForceMultiply(vector<int> a, vector<int> b) {
  int carry = 0;
  vector<int> carry_vector;
  vector<int> c;

  // Initalize c with all 0's
  if (a.size() < b.size()) {
    for (size_t i = 0; i < b.size(); ++i) {
      c.push_back(0);
    }
  } else {
    for (size_t i = 0; i < a.size(); ++i) {
      c.push_back(0);
    }
  }

  int count = 0;
  for (int j = b.size() - 1 ; j >= 0; --j) {
    cout << "***********OUTER LOOP **************" << endl;
    carry_vector.clear();
    vector<int>::reverse_iterator it = c.rbegin() + count;
    for (int i = a.size() - 1; i >= 0; --i) {
      cout << "Multiply " << a.at(i) << " * " << b.at(j) << endl;
      int temp = a.at(i) * b.at(j);
      cout << "Answer: " << temp << endl;
      // Check for numbers to be carried
      if (carry > 0) {
        temp += carry;
        cout << "Adding the carry: " << carry << endl;
        carry = 0;
        carry_vector.clear();
      }
      if (temp > 9) {
        carryDigits(carry_vector, temp);
        carry = carry_vector.at(0);
        cout << "Carrying a " << carry << endl;
        cout << "Adding " << carry_vector.at(1) << " to " << *it << endl;
        *it += carry_vector.at(1);
        cout << "Partial Product: " << *it << endl;
      } else {
        *it += temp;
        cout << "Partial Product: " << *it << endl;
      }
      ++it;
      if (it == c.rend()) {
        if (carry > 0) {
          c.insert(c.begin(), carry);
          carry = 0;
        }
      }
      // DEBUG
      cout << "C looks like: ";
      for (size_t i = 0; i < c.size(); ++i) {
        cout << c.at(i) << " ";
      }
      cout << endl;
      cout << "i is " << i << endl;
      cout << "j is " << j << endl;
    }
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