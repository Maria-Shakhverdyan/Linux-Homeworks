#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

void func(const std::string& filename, int num1, int num2, const std::string& op) {
    int result;
    if (op == "s") {
        result = num1 + num2;
    } else if (op == "m") {
        result = num1 * num2;
    } else if (op == "ss") {
        result = num1 * num1 + num2 * num2;
    } else {
        std::cerr << op << std::endl;
        return;
    }

    std::ofstream outFile;
    while (true) {
        outFile.open(filename, std::ios::out | std::ios::app);
        if (outFile.is_open()) {
            break;
        } else {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }

    outFile << num1 << " " << op << " " << num2 << " = " << result << std::endl;

    outFile.close();
}

int main() {
    int N;
    std::cin >> N;

    std::vector<std::thread> threads;

    for (int i = 0; i < N; ++i) {
        int num1, num2;
        std::string op, filename;

        std::cin >> num1 >> num2 >> op;

        filename = "out_" + std::to_string(i + 1);

        threads.emplace_back(func, filename, num1, num2, op);
    }


    return 0;
}
