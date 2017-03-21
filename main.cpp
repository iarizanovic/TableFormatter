#include <iostream>
#include <utility>
#include "TableFormatterBase.hh"

// void print_test(TableCell test){
//   std::cout << "print_test: " << test << std::endl;
// }
//
// void print_double(double in){
//   std::cout << "print_double: " << in << std::endl;
// }
//
// void print_string(std::string in){
//   std::cout << "print_string: " << in << std::endl;
// }

int main(int argc, char **argv) {
  try{
    TableFormatterBase test;
    test.SetHeader({{"Drapsin", 10},
                    {"Ivan", 6},
                    {"Bane", 5},
                    {"Bane", 5},
                    {"Stefan", 12}});
    test.AddRow(std::make_pair(10, TableFormatterColor::RED),
                std::make_pair(20, TableFormatterColor::GREEN),
                std::make_pair(3, TableFormatterColor::YELLOW),
                std::make_pair(3, TableFormatterColor::YELLOW),
                std::make_pair(80884488.222, TableFormatterColor::BLUE));
    test.AddRow(std::make_pair(10, TableFormatterColor::RED),
                20,
                std::make_pair(300, TableFormatterColor::YELLOW),
                std::make_pair(30000000, TableFormatterColor::YELLOW),
                std::make_pair(40, TableFormatterColor::BLUE));
    test.AddRow(std::make_pair(10, TableFormatterColor::RED),
                std::make_pair(20, TableFormatterColor::GREEN),
                std::make_pair(20, TableFormatterColor::GREEN),
                std::make_pair(2147483647, TableFormatterColor::YELLOW),
                std::make_pair(40, TableFormatterColor::BLUE));
    test.AddSeparator();
    test.AddCustomRow(std::make_pair(44, RED),
                      std::make_pair("nesto", 33));
    test.AddCustomRow(std::make_pair(4444, 5),
                      4444,
                      std::make_pair("nesto", BLUE));
    test.AddRow(std::make_pair(10, TableFormatterColor::RED),
                std::make_pair(20, TableFormatterColor::GREEN),
                std::make_pair(20, TableFormatterColor::GREEN),
                std::make_pair(300000, TableFormatterColor::YELLOW),
                std::make_pair(40, TableFormatterColor::BLUE));
    test.AddCustomRow(std::make_tuple("nesto", TableFormatterColor::BLUE, 0),
                      std::make_tuple("nesto", TableFormatterColor::BLUE, 6),
                      std::make_tuple("nesto", TableFormatterColor::BLUE, 1),
                      std::make_tuple("nesto", TableFormatterColor::BLUE, 1),
                      std::make_tuple("nesto", TableFormatterColor::RED, 1));
    test.AddCustomRow(3,4,1234,4);
    test.AddRow(3,1234,"",2147483647.,4);
    test.GenerateTable();
    std::cout << test.GetTable() << std::endl;
  }
  catch(std::string msg){
    std::cout << "\33[31mError: \33[0m" << msg << std::endl;
  }

  try{
    TableFormatterBase test2;
    test2.SetHeader({{"Ivan",6}});
    test2.AddRow(std::make_pair("test", YELLOW));
    test2.GenerateTable();

    std::cout << test2.GetTable() << std::endl;

  }
  catch(std::string msg){
    std::cout << "\33[31mError: \33[0m" << msg << std::endl;
  }
  return 0;
}
