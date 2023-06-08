#include "CsvTableCalculator.h"

bool CsvTableHandler::CsvTableCalculator::calculate(CsvTableHandler::CsvTable &table) {
    auto rowHeaders = table.getRowHeaders();
    auto columnHeaders = table.getColumnHeaders();
    auto tableElements = table.getElementsInTable();


    std::unordered_map<std::pair<int, int>, std::string, pairhash> valuesThatNeedCalculate;

    // search values that need to calculate
    for (int i = 0; i < tableElements.size(); ++i) {
        for (int j = 0; j < tableElements[i].size(); ++j) {
            std::string elem = tableElements[i][j];
            if (elem[0] == '=') {
                valuesThatNeedCalculate.emplace(std::pair<int, int>(i, j), elem);
            }
        }
    }


    for (const auto &item : valuesThatNeedCalculate) {
        int rowIndex = item.first.first;
        int columnIndex = item.first.second;
        std::string elem = item.second;

        char mathOperator;
        if (elem.find('+') != std::string::npos) {
            mathOperator = '+';
        } else if (elem.find('-') != std::string::npos) {
            mathOperator = '-';
        } else if (elem.find('*') != std::string::npos) {
            mathOperator = '*';
        } else {
            mathOperator = '/';
        }

        auto mathOperatorPosition = elem.find(mathOperator);
        std::string firstOperand = elem.substr(1, mathOperatorPosition - 1);
        std::string secondOperand = elem.substr(mathOperatorPosition + 1);

        std::pair<std::string, int> parsedFirstOperand = parseOperand(firstOperand);
        std::string firstOperandColumn = parsedFirstOperand.first;
        int firstOperandRow = parsedFirstOperand.second;

        std::pair<std::string, int> parsedSecondOperand = parseOperand(secondOperand);
        std::string secondOperandColumn = parsedSecondOperand.first;
        int secondOperandRow = parsedSecondOperand.second;

        int firstOperandValue, secondOperandValue;

        if (!firstOperandColumn.empty() && !secondOperandColumn.empty()) {
            firstOperandValue = std::stoi(table.getElem(firstOperandColumn, firstOperandRow));
            secondOperandValue = std::stoi(table.getElem(secondOperandColumn, secondOperandRow));
        } else if (!firstOperandColumn.empty()) {
            firstOperandValue = std::stoi(table.getElem(firstOperandColumn, firstOperandRow));
            secondOperandValue = secondOperandRow;
        } else if (!secondOperandColumn.empty()) {
            firstOperandValue = firstOperandRow;
            secondOperandValue = std::stoi(table.getElem(secondOperandColumn, secondOperandRow));
        } else {
            firstOperandValue = firstOperandRow;
            secondOperandValue = secondOperandRow;
        }

        int result;
        if (mathOperator == '+') {
            result = firstOperandValue + secondOperandValue;
        } else if (mathOperator == '-') {
            result = firstOperandValue - secondOperandValue;
        } else if (mathOperator == '*') {
            result = firstOperandValue * secondOperandValue;
        } else if (secondOperandValue == 0) {
            return false;
        } else {
            result = firstOperandValue / secondOperandValue;
        }

        int rowHeadValue = -1;
        for (const auto &rowHead : rowHeaders) {
            if (rowHead.second == rowIndex) {
                rowHeadValue = rowHead.first;
                break;
            }
        }

        std::string columnHeadValue;
        for (const auto &columnHead : columnHeaders) {
            if (columnHead.second == columnIndex) {
                columnHeadValue = columnHead.first;
                break;
            }
        }

        table.setElem(columnHeadValue, rowHeadValue, std::to_string(result));

    }


    return true;
}

std::pair<std::string, int> CsvTableHandler::CsvTableCalculator::parseOperand(const std::string &operand) {
    std::string operandColumn;
    std::string operandRow;
    int operandRowPos = 0;
    for (int i = 0; i < operand.size(); ++i) {
        if (operand[i] == '0' || operand[i] == '1' || operand[i] == '2'
            || operand[i] == '3' || operand[i] == '4' || operand[i] == '5'
            || operand[i] == '6' || operand[i] == '7' || operand[i] == '8'
            || operand[i] == '9') {
            operandRowPos = i;
            break;
        } else {
            operandColumn += operand[i];
        }
    }
    operandRow = operand.substr(operandRowPos);
    return {operandColumn, std::stoi(operandRow)};
}
