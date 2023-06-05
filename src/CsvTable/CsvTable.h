#ifndef CSVHANDLER_CSVTABLE_H
#define CSVHANDLER_CSVTABLE_H

#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

namespace CsvTableHandler {
    class CsvTable {
    private:
        std::string fileName_;
        std::unordered_map<std::string, int> columnHeaders_; // <key, column index>
        std::unordered_map<int, int> rowHeaders_;            // <key, row index>
        std::vector<std::vector<std::string>> data_;

        void readFirstString(std::ifstream &inputFile);
        void readDataStrings(std::ifstream &inputFile);
    public:
        CsvTable();
        ~CsvTable();
        void readTable(const std::string &fileName);
        std::string getElem(const std::string &column, const int &row);
    };

} // namespace CsvTableHandler


#endif //CSVHANDLER_CSVTABLE_H
