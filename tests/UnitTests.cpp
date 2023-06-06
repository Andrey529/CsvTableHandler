#include "gtest/gtest.h"

#include "../src/CsvTable/CsvTable.h"
#include "../src/CsvTable/CsvTable.cpp"

TEST(CsvTable, getElem_1) {
    CsvTableHandler::CsvTable csvTable;
    std::string fileName("../../tests/files/test_1.csv");
    csvTable.readTable(fileName);

    GTEST_ASSERT_EQ(csvTable.getElem("A", 1), "1");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 2), "2");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 30), "0");

    GTEST_ASSERT_EQ(csvTable.getElem("B", 1), "0");
    GTEST_ASSERT_EQ(csvTable.getElem("B", 2), "=A1+Cell30");
    GTEST_ASSERT_EQ(csvTable.getElem("B", 30), "=B1+A1");

    GTEST_ASSERT_EQ(csvTable.getElem("Cell", 1), "1");
    GTEST_ASSERT_EQ(csvTable.getElem("Cell", 2), "0");
    GTEST_ASSERT_EQ(csvTable.getElem("Cell", 30), "5");

}

TEST(CsvTable, getElem_2) {
    CsvTableHandler::CsvTable csvTable;
    std::string fileName("../../tests/files/test_2.csv");
    csvTable.readTable(fileName);

    GTEST_ASSERT_EQ(csvTable.getElem("A", 1), "1");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 2), "4");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 3), "7");

    GTEST_ASSERT_EQ(csvTable.getElem("B", 1), "2");
    GTEST_ASSERT_EQ(csvTable.getElem("B", 2), "5");
    GTEST_ASSERT_EQ(csvTable.getElem("B", 3), "8");

    GTEST_ASSERT_EQ(csvTable.getElem("C", 1), "3");
    GTEST_ASSERT_EQ(csvTable.getElem("C", 2), "6");
    GTEST_ASSERT_EQ(csvTable.getElem("C", 3), "9");
}

TEST(CsvTable, getElem_3) {
    CsvTableHandler::CsvTable csvTable;
    std::string fileName("../../tests/files/test_3.csv");
    csvTable.readTable(fileName);

    GTEST_ASSERT_EQ(csvTable.getElem("A", 1), "=A3+6");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 2), "4");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 3), "7");

    GTEST_ASSERT_EQ(csvTable.getElem("B", 1), "2");
    GTEST_ASSERT_EQ(csvTable.getElem("B", 2), "=B3*9");
    GTEST_ASSERT_EQ(csvTable.getElem("B", 3), "8");

    GTEST_ASSERT_EQ(csvTable.getElem("C", 1), "3");
    GTEST_ASSERT_EQ(csvTable.getElem("C", 2), "6");
    GTEST_ASSERT_EQ(csvTable.getElem("C", 3), "=2-C1");
}

TEST(CsvTable, getElem_4_out_of_range) {
    CsvTableHandler::CsvTable csvTable;
    std::string fileName("../../tests/files/test_1.csv");
    csvTable.readTable(fileName);

    GTEST_ASSERT_EQ(csvTable.getElem("A", 4), "");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 10), "");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 100), "");
}

TEST(CsvTable, getElem_5_empty_table) {
    CsvTableHandler::CsvTable csvTable;

    GTEST_ASSERT_EQ(csvTable.getElem("A", 4), "");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 10), "");
    GTEST_ASSERT_EQ(csvTable.getElem("A", 100), "");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}