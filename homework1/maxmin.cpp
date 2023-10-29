#include <iostream>
#include <string>

int main(int arg_qanak, char* argument[]) {
    if (arg_qanak != 4) {
        std::cerr << "Using: " << argument[0] << " a b c" << std::endl;
        return 1;
    }

    int a = std::stoi(argument[1]);
    int b = std::stoi(argument[2]);
    int c = std::stoi(argument[3]);

    int max = a;
    int min = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }

    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }

    std::cout << "Max: " << max << std::endl;
    std::cout << "Min: " << min << std::endl;

    return 0;
}
