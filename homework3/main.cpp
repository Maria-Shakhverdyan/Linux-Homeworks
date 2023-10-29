#include <iostream>
#include <vector>
#include "ComplexNum.hpp"

void bubbleSort(std::vector<ComplexNumber>& numbers) {
    int n = numbers.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (numbers[j] < numbers[j + 1]) {
                std::swap(numbers[j], numbers[j + 1]);
            }
        }
    }
}

int main() {
    std::vector<ComplexNumber> complexNumbers;
    complexNumbers.push_back(ComplexNumber(3, 4));
    complexNumbers.push_back(ComplexNumber(1, 2));
    complexNumbers.push_back(ComplexNumber(5, 1));

    std::cout << "Unsorted" << std::endl;
    for (const ComplexNumber& num : complexNumbers) {
        std::cout << num << std::endl;
    }

    bubbleSort(complexNumbers);

    std::cout << "\nSorted:" << std::endl;
    for (const ComplexNumber& num : complexNumbers) {
        std::cout << num << std::endl;
    }

    return 0;
}
