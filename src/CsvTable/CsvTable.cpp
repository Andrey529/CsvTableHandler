#include <iostream>
#include "CsvTable.h"

CsvTableHandler::CsvTable::CsvTable() = default;

CsvTableHandler::CsvTable::~CsvTable() = default;

void CsvTableHandler::CsvTable::readTable(const std::string &fileName) {
    fileName_ = fileName;

    std::ifstream inputFile(fileName_);
    if (inputFile.is_open()) {

        // read the first line
        readFirstString(inputFile);

        // read other lines with data
        readDataStrings(inputFile);

        inputFile.close();
    } else {
        throw std::runtime_error("Failed to open input data file");
    }

}

void CsvTableHandler::CsvTable::readFirstString(std::ifstream &inputFile) {
    std::string str;
    std::getline(inputFile, str);
    std::string columnHeader;
    int columnHeaderIndex = 0;
    for (int i = 1; i < str.size(); ++i) {
        if (str[i] == ',') {
            columnHeaders_.emplace(columnHeader, columnHeaderIndex);
            columnHeader.clear();
            ++columnHeaderIndex;
        } else {
            columnHeader += str[i];
        }
    }
    columnHeaders_.emplace(columnHeader, columnHeaderIndex);

}

void CsvTableHandler::CsvTable::readDataStrings(std::ifstream &inputFile) {
    std::string str;
    int rowIndex = 0;
    while (std::getline(inputFile, str)) {
        int columnIndex = 0;
        std::string elemRow;
        data_.emplace_back();
        for (int i = 0; i < str.size(); ++i) {
            if (str[i] == ',' && columnIndex == 0) {
                rowHeaders_.emplace(std::stoi(elemRow), rowIndex);
                ++columnIndex;
                elemRow.clear();
            } else if (str[i] == ',' && columnIndex != 0) {
                data_[rowIndex].emplace_back(elemRow);
                ++columnIndex;
                elemRow.clear();
            } else {
                elemRow += str[i];
            }
        }
        data_[rowIndex].emplace_back(elemRow);

        ++rowIndex;
        str.clear();
    }
}

std::string CsvTableHandler::CsvTable::getElem(const std::string &column, const int &row) const {
    try {
        int rowIndex = rowHeaders_.at(row);
        int columnIndex = columnHeaders_.at(column);

        return data_[rowIndex][columnIndex];
    } catch (const std::out_of_range &exception) {
        return {};
    }
}

bool CsvTableHandler::CsvTable::setElem(const std::string &column, const int &row, const std::string &value) {
    try {
        int rowIndex = rowHeaders_.at(row);
        int columnIndex = columnHeaders_.at(column);

        data_[rowIndex][columnIndex] = value;
        return true;
    } catch (const std::out_of_range &exception) {
        return false;
    }
}

std::unordered_map<std::string, int> CsvTableHandler::CsvTable::getColumnHeaders() const {
    return columnHeaders_;
}

std::unordered_map<int, int> CsvTableHandler::CsvTable::getRowHeaders() const {
    return rowHeaders_;
}

std::vector<std::vector<std::string>> CsvTableHandler::CsvTable::getElementsInTable() const {
    return data_;
}

std::ostream& CsvTableHandler::operator<<(std::ostream &ostream, const CsvTable &table) {
    auto rowHeaders = table.getRowHeaders();
    auto columnHeaders = table.getColumnHeaders();
    auto tableElements = table.getElementsInTable();

    ostream << ',';
    for (const auto &columnHead : columnHeaders) {
        ostream << columnHead.first;
    }

    return ostream;
}
