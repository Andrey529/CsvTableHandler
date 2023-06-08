#include <iostream>
#include "CsvTable/CsvTable.h"
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

        std::cout << csvTable.getElem("A", 2) << std::endl;
        std::cout << csvTable.getElem("B", 2) << std::endl;
        std::cout << csvTable.getElem("B", 30) << std::endl;
        std::cout << csvTable.getElem("Cell", 30) << std::endl;

        CsvTableHandler::CsvTableCalculator::calculate(csvTable);

        std::cout << csvTable;
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }

    return 0;
}
