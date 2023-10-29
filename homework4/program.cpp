#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main() {

    std::ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(input_file, line)) {
        lines.push_back(line);
    }

    int num_lines = lines.size();
    std::cout << "String q-ty:  " << num_lines << std::endl;

    std::ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    for (int i = num_lines - 1; i >= 0; i--) {
        output_file << lines[i] << std::endl;
    }

    input_file.close();
    output_file.close();

    return 0;
}
