#include "BigNum.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <vector>

using namespace std;

BigNum::BigNum() {
    // Default constructor initializes to '0'
    digits.push_back('0');
    isNegative = false;
}

// Copy constructor
BigNum::BigNum(const BigNum& bigNum) {
    digits = bigNum.digits;
    isNegative = bigNum.isNegative;
}

// String constructor (e.g. "348723482")
BigNum::BigNum(const string& bigStr) {
    isNegative = (bigStr[0] == '-');
    if (isNegative) {
        digits.assign(bigStr.begin() + 1, bigStr.end()); // Skip the negative sign
    } else {
        digits.assign(bigStr.begin(), bigStr.end());
    }
    removeLeadingZeros();
}

// Integer constructor
BigNum::BigNum(const int num) {
    if (num < 0) {
        isNegative = true;
        // Assign characters from the string representation of -num to digits
        digits.assign(to_string(-num).begin(), to_string(-num).end());
    } else {
        isNegative = false;
        // Assign characters from the string representation of num to digits
        digits.assign(to_string(num).begin(), to_string(num).end());
    }
}

// Destructor
BigNum::~BigNum() {
    clear(); // Clear the dynamic memory (if any)
}

// Helper function to clear data
void BigNum::clear() {
    digits.clear(); // Clear the digits
}

// Function to reset the number to zero
void BigNum::zerofy() {
    digits.assign(1, '0');  // Assign a single character '0' to the digits vector
    isNegative = false;
}


// Function to input from user
void BigNum::input() {
    string inputStr;
    cin >> inputStr;
    *this = BigNum(inputStr); // Use the string constructor for input
}

// Function to print the number with comma-separated formatting
void BigNum::print() {
    if (isNegative) cout << '-';
    int n = digits.size();
    for (int i = 0; i < n; i++) {
        cout << digits[i];
        if ((n - i - 1) % 3 == 0 && i != n - 1) {
            cout << ',';
        }
    }
    cout << endl;
}

// File input
void BigNum::inputFromFile(const string& fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string fileNum;
        file >> fileNum;
        *this = BigNum(fileNum); // Load from file
        file.close();
    } else {
        cout << "Error opening file" << endl;
    }
}

// File output
void BigNum::printToFile(const string& fileName) {
    ofstream file(fileName);
    if (file.is_open()) {
        if (isNegative) file << '-';
        for (char digit : digits) {
            file << digit;  // Write each character from the vector
        }
        file.close();
    } else {
        cout << "Error opening file" << endl;
    }
}
void BigNum::removeLeadingZeros() {
    while (digits.size() > 1 && digits[0] == '0') {
        digits.erase(digits.begin()); // Remove the first character if it's a leading zero
    }
}
 

// Copy from another BigNum object
void BigNum::copy(const BigNum& bigNum) {
    *this = bigNum; // Simply use the assignment operator
}

// Assignment operator
void BigNum::operator=(const BigNum& bigNum) {
    digits = bigNum.digits;
    isNegative = bigNum.isNegative;
}

// Increment operation (adds 1)
void BigNum::increment() {
    BigNum one(1);
    *this = add(one);
}

// Decrement operation (subtracts 1)
void BigNum::decrement() {
    BigNum one(1);
    *this = subtract(one);
}


// Helper function to reverse a string
string reverseString(const string& str) {
    string reversed = str;
    reverse(reversed.begin(), reversed.end());
    return reversed;
}

// Add two BigNum objects
BigNum BigNum::add(const BigNum& bigNum) {
    BigNum result;
    result.isNegative = false; // We're not handling negative numbers in this simple example

    int carry = 0;
    int thisLen = digits.size();
    int otherLen = bigNum.digits.size();
    int maxLen = max(thisLen, otherLen);
    
    // Reverse both strings to facilitate addition from the least significant digit
std::vector<char> thisReversed = digits;
std::vector<char> otherReversed = bigNum.digits;
std::reverse(thisReversed.begin(), thisReversed.end());
std::reverse(otherReversed.begin(), otherReversed.end());
    for (int i = 0; i < maxLen; i++) {
        int digit1 = (i < thisLen) ? thisReversed[i] - '0' : 0;
        int digit2 = (i < otherLen) ? otherReversed[i] - '0' : 0;

        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result.digits.push_back((sum % 10) + '0');
    }

    if (carry > 0) {
        result.digits.push_back(carry + '0');
    }

    // Reverse the result to get the correct order
    reverse(result.digits.begin(), result.digits.end());
    result.removeLeadingZeros();  // Remove any leading zeros
    return result;
}

// Subtract two BigNum objects
BigNum BigNum::subtract(const BigNum& bigNum) {
    BigNum result;
    result.isNegative = false;

    int borrow = 0;
    int thisLen = digits.size();
    int otherLen = bigNum.digits.size();

    std::vector<char> thisReversed = digits;
    std::vector<char> otherReversed = bigNum.digits;

    std::reverse(thisReversed.begin(), thisReversed.end());
    std::reverse(otherReversed.begin(), otherReversed.end());
    for (int i = 0; i < thisLen; i++) {
        int digit1 = thisReversed[i] - '0';
        int digit2 = (i < otherLen) ? otherReversed[i] - '0' : 0;

        int diff = digit1 - digit2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result.digits.push_back(diff + '0');
    }

    // Reverse the result to get the correct order
    reverse(result.digits.begin(), result.digits.end());
    result.removeLeadingZeros();  // Remove any leading zeros
    return result;
}

// Multiplication
BigNum BigNum::multiply(const BigNum& bigNum) {
    BigNum result;
    result.digits = vector<char>(digits.size() + bigNum.digits.size(), '0');
    
    for (int i = digits.size() - 1; i >= 0; --i) {
        int carry = 0;
        for (int j = bigNum.digits.size() - 1; j >= 0; --j) {
            int product = (digits[i] - '0') * (bigNum.digits[j] - '0') + carry + (result.digits[i + j + 1] - '0');
            result.digits[i + j + 1] = (product % 10) + '0';
            carry = product / 10;
        }
        result.digits[i] += carry;
    }

    result.removeLeadingZeros();
    return result;
}


// Division (integer division)
BigNum BigNum::div(const BigNum& bigNum) {
    BigNum result;
    BigNum current;

    for (char digit : digits) {
        current.digits.push_back(digit);
        current.removeLeadingZeros();

        int count = 0;
        while (current.greaterThan(bigNum) || current.equals(bigNum)) {
            current = current.subtract(bigNum);
            count++;
        }
        result.digits.push_back(count + '0');
    }

    result.removeLeadingZeros();
    return result;
}

// Modulus operation
BigNum BigNum::mod(const BigNum& bigNum) {
    BigNum quotient = this->div(bigNum);
    BigNum product = quotient.multiply(bigNum);
    return this->subtract(product);
}

//Helper function
bool BigNum::equals(const BigNum& bigNum) {
    return (isNegative == bigNum.isNegative) && (digits == bigNum.digits);
}

bool BigNum::greaterThan(const BigNum& bigNum) {
    if (isNegative != bigNum.isNegative) {
        return !isNegative; // Positive is always greater than negative
    }

    if (digits.size() != bigNum.digits.size()) {
        return digits.size() > bigNum.digits.size(); // Compare sizes
    }

    for (size_t i = 0; i < digits.size(); ++i) {
        if (digits[i] != bigNum.digits[i]) {
            return digits[i] > bigNum.digits[i]; // Compare digit by digit
        }
    }

    return false; // They are equal
}




int main() {
    // Example 1
    BigNum num1("1111111111111111111111111");
    BigNum num2("1111111111111111111111111");

    BigNum sum = num1.add(num2);
    cout << "Addition (Example 1): ";
    sum.print(); // Expected: 2,222,222,222,222,222,222,222,222

    BigNum diff = num1.subtract(num2);
    cout << "Subtraction (Example 1): ";
    diff.print(); // Expected: 0

    BigNum product = num1.multiply(num2);
    cout << "Multiplication (Example 1): ";
    product.print(); // Expected: 1,234,567,901,234,567,901,234,567,654,320,987,654,320,987,654,321

    BigNum quotient = num1.div(num2);
    cout << "Division (Example 1): ";
    quotient.print(); // Expected: 1

    BigNum remainder = num1.mod(num2);
    cout << "Modulus (Example 1): ";
    remainder.print(); // Expected: 0

    cout << endl;

    // Example 2
    num1 = BigNum("987654321987654321987654321987654321");
    num2 = BigNum("123456789123456789123456789123456789");

    sum = num1.add(num2);
    cout << "Addition (Example 2): ";
    sum.print(); // Expected: 1,111,111,111,111,111,111,111,111,111,111,111,110

    diff = num1.subtract(num2);
    cout << "Subtraction (Example 2): ";
    diff.print(); // Expected: 864,197,532,864,197,532,864,197,532,864,197,532

    product = num1.multiply(num2);
    cout << "Multiplication (Example 2): ";
    product.print(); // Expected: 121,932,631,356,500,531,591,068,431,825,636,331,816,338,969,581,771,069,347,203,169,112,635,269

    quotient = num1.div(num2);
    cout << "Division (Example 2): ";
    quotient.print(); // Expected: 8

    remainder = num1.mod(num2);
    cout << "Modulus (Example 2): ";
    remainder.print(); // Expected: 9,000,000,009,000,000,009,000,000,009

    return 0;
}
