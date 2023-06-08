#ifndef CSVHANDLER_CSVTABLECALCULATOR_H
#define CSVHANDLER_CSVTABLECALCULATOR_H

#include "../CsvTable/CsvTable.h"
#include <iostream>

namespace CsvTableHandler {
    class CsvTableCalculator {
    private:
        struct pairhash {
        public:
            template <typename T, typename U>
            std::size_t operator()(const std::pair<T, U> &x) const
            {
                return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
            }
        };

        static std::pair<std::string, int> parseOperand(const std::string &operand); // return std::pair<columnn, row>
    public:
        static bool calculate(CsvTableHandler::CsvTable &table);
    };

} // namespace CsvTableHandler


#endif //CSVHANDLER_CSVTABLECALCULATOR_H
