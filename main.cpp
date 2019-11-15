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
}