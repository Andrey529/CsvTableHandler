#include "CsvTable.h"

CsvTableHandler::CsvTable::CsvTable() = default;

CsvTableHandler::CsvTable::~CsvTable() = default;

bool CsvTableHandler::CsvTable::readTable(const std::string &fileName) {
    rowHeaders_.clear();
    columnHeaders_.clear();
    data_.clear();

    fileName_ = fileName;

    std::ifstream inputFile(fileName_);
    if (inputFile.is_open()) {

        // read the first line
        readFirstString(inputFile);

        // read other lines with data
        bool result = readDataStrings(inputFile);

        inputFile.close();

        return result;
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

bool CsvTableHandler::CsvTable::readDataStrings(std::ifstream &inputFile) {
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

        if (data_[rowIndex].size() != columnHeaders_.size()) {
            return false;
        }

        ++rowIndex;
        str.clear();
    }
    return true;
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

    std::vector<std::pair<int, int>> rowHeadersInArray;
    for (const auto& rowHead : rowHeaders) {
        rowHeadersInArray.emplace_back(rowHead.first, rowHead.second);
    }

    auto rowHeadersComparator = [](const std::pair<int,int> &a, const std::pair<int,int> &b){
        return a.second < b.second;
    };

    std::sort(rowHeadersInArray.begin(), rowHeadersInArray.end(), rowHeadersComparator);

    std::vector<std::pair<std::string , int>> columnHeadersInArray;
    for (const auto& columnHead : columnHeaders) {
        columnHeadersInArray.emplace_back(columnHead.first, columnHead.second);
    }

    auto columnHeadersComparator = [](const std::pair<std::string,int> &a, const std::pair<std::string,int> &b){
        return a.second < b.second;
    };

    std::sort(columnHeadersInArray.begin(), columnHeadersInArray.end(), columnHeadersComparator);


    ostream << ',';
    for (int i = 0; i < columnHeadersInArray.size() - 1; ++i) {
        ostream << columnHeadersInArray[i].first << ',';
    }
    ostream << columnHeadersInArray[columnHeadersInArray.size() - 1].first << '\n';

    for (int i = 0; i < rowHeadersInArray.size(); ++i) {
        ostream << rowHeadersInArray[i].first << ',';
        for (int j = 0; j < columnHeadersInArray.size() - 1; ++j) {
            ostream << tableElements[rowHeadersInArray[i].second][columnHeadersInArray[j].second] << ',';
        }
        ostream << tableElements[rowHeadersInArray[i].second][columnHeadersInArray[columnHeadersInArray.size() - 1].second] << '\n';
    }

    return ostream;
}
