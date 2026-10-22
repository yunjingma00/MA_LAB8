
#include "Calculator.h"
#include <string>

// Add two non-negative integer strings
static std::string addAbsolute(const std::string& a, const std::string& b) {
    std::string result = "";
    int i = static_cast<int>(a.length()) - 1;
    int j = static_cast<int>(b.length()) - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;

        if (i >= 0) {
            sum += a[i] - '0';
            i--;
        }

        if (j >= 0) {
            sum += b[j] - '0';
            j--;
        }

        result = char(sum % 10 + '0') + result;
        carry = sum / 10;
    }

    return result;
}

// Compare two non-negative integer strings
static int compareAbsolute(const std::string& a, const std::string& b) {
    if (a.length() > b.length()) {
        return 1;
    }

    if (a.length() < b.length()) {
        return -1;
    }

    if (a > b) {
        return 1;
    }

    if (a < b) {
        return -1;
    }

    return 0;
}

// Subtract b from a, assuming a >= b
static std::string subtractAbsolute(const std::string& a,
                                   const std::string& b) {
    std::string result = "";
    int i = static_cast<int>(a.length()) - 1;
    int j = static_cast<int>(b.length()) - 1;
    int borrow = 0;

    while (i >= 0) {
        int digitA = a[i] - '0' - borrow;
        int digitB = 0;

        if (j >= 0) {
            digitB = b[j] - '0';
        }

        if (digitA < digitB) {
            digitA += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = char(digitA - digitB + '0') + result;
        i--;
        j--;
    }

    int start = 0;

    while (start < static_cast<int>(result.length()) - 1 &&
           result[start] == '0') {
        start++;
    }

    return result.substr(start);
}

// Add two valid decimal number strings
std::string addNumbers(const std::string& a, const std::string& b) {
    std::string numA = a;
    std::string numB = b;
    bool negativeA = false;
    bool negativeB = false;

    // Read the signs
    if (numA[0] == '+' || numA[0] == '-') {
        negativeA = (numA[0] == '-');
        numA = numA.substr(1);
    }

    if (numB[0] == '+' || numB[0] == '-') {
        negativeB = (numB[0] == '-');
        numB = numB.substr(1);
    }

    // Split the integer and decimal parts
    std::string intA = numA;
    std::string intB = numB;
    std::string fractionA = "";
    std::string fractionB = "";

    std::size_t dotA = numA.find('.');
    std::size_t dotB = numB.find('.');

    if (dotA != std::string::npos) {
        intA = numA.substr(0, dotA);
        fractionA = numA.substr(dotA + 1);
    }

    if (dotB != std::string::npos) {
        intB = numB.substr(0, dotB);
        fractionB = numB.substr(dotB + 1);
    }

    // Align the decimal places
    while (fractionA.length() < fractionB.length()) {
        fractionA += '0';
    }

    while (fractionB.length() < fractionA.length()) {
        fractionB += '0';
    }

    int decimalPlaces = static_cast<int>(fractionA.length());

    // Combine the digits
    std::string digitsA = intA + fractionA;
    std::string digitsB = intB + fractionB;

    // Remove leading zeros
    int startA = 0;
    int startB = 0;

    while (startA < static_cast<int>(digitsA.length()) - 1 &&
           digitsA[startA] == '0') {
        startA++;
    }

    while (startB < static_cast<int>(digitsB.length()) - 1 &&
           digitsB[startB] == '0') {
        startB++;
    }

    digitsA = digitsA.substr(startA);
    digitsB = digitsB.substr(startB);

    // Add or subtract according to the signs
    std::string result;
    bool negativeResult = false;

    if (negativeA == negativeB) {
        result = addAbsolute(digitsA, digitsB);
        negativeResult = negativeA;
    } else {
        int comparison = compareAbsolute(digitsA, digitsB);

        if (comparison == 0) {
            result = "0";
        } else if (comparison > 0) {
            result = subtractAbsolute(digitsA, digitsB);
            negativeResult = negativeA;
        } else {
            result = subtractAbsolute(digitsB, digitsA);
            negativeResult = negativeB;
        }
    }

    // Restore the decimal point
    if (decimalPlaces > 0) {
        while (static_cast<int>(result.length()) <= decimalPlaces) {
            result = '0' + result;
        }

        result.insert(result.length() - decimalPlaces, ".");

        // Remove trailing zeros after the decimal point
        while (!result.empty() && result.back() == '0') {
            result.pop_back();
        }

        if (!result.empty() && result.back() == '.') {
            result.pop_back();
        }
    }

    // Remove unnecessary leading zeros
    std::size_t dotPosition = result.find('.');
    std::size_t integerEnd =
        (dotPosition == std::string::npos) ? result.length() : dotPosition;

    std::size_t start = 0;

    while (start + 1 < integerEnd && result[start] == '0') {
        start++;
    }

    result.erase(0, start);

    // Return zero without a negative sign
    bool isZero = true;

    for (char digit : result) {
        if (digit >= '1' && digit <= '9') {
            isZero = false;
            break;
        }
    }

    if (isZero) {
        return "0";
    }

    if (negativeResult) {
        result = "-" + result;
    }

    return result;
}

