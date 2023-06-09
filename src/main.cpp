#include <iostream>
#include "CsvTableCalculator/CsvTableCalculator.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Wrong number of arguments. Must be: "
                     "<program name> <input_file>";
        return -1;
    }

    CsvTableHandler::CsvTable csvTable;

    try {
        if (!csvTable.readTable(argv[1])) {
            std::cout << "Failed to read the table from the file, it has invalid parameters\n";
        } else {
            if (CsvTableHandler::CsvTableCalculator::calculate(csvTable)) {
                std::cout << csvTable;
            } else {
                std::cout << "There was a mistake, the table could not be calculated\n";
            }
        }

    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    return 0;
}
