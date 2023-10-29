#include <iostream>

int main(int arg_kolichestvo, char* argument[]) {
    for (int i = arg_kolichestvo - 1; i > 0; --i) {
        std::cout << argument[i] << std::endl;
    }

    return 0;
}
