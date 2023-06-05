#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Wrong number of arguments. Must be: "
                     "<program name> <input_file>";
        return -1;
    }

    std::ifstream inputFile(argv[1]);
    if (inputFile.is_open()) {
        std::string str;
        std::vector<std::string> data;

        while (std::getline(inputFile, str)) {
            data.emplace_back(str);
            str.clear();
        }

        for (const std::string &row : data) {
            std::cout << row << std::endl;
        }

        inputFile.close();
    } else {
        throw std::runtime_error("Failed to open input data file");
    }

    return 0;
}
