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
        csvTable.readTable(argv[1]);

        CsvTableHandler::CsvTableCalculator::calculate(csvTable);

        std::cout << csvTable;
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    return 0;
}
