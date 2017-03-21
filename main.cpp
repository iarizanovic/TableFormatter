#include <iostream>
#include <utility>
#include "TableCell.hh"
#include "TableFormatterBase.hh"

void print_test(TableCell test){
  std::cout << "print_test: " << test << std::endl;
}

void print_double(double in){
  std::cout << "print_double: " << in << std::endl;
}

void print_string(std::string in){
  std::cout << "print_string: " << in << std::endl;
}

int main(int argc, char **argv) {
    TableFormatterBase test;
    test.SetHeader({{"Drapsin", 16}, {"Ivan", 8}, {"Bane", 5}});
    test.AddRow(1,
                std::make_pair(2, TableFormatterColor::RED),
                std::make_pair(3, TableFormatterColor::GREEN));
    test.AddCustomRow(std::make_pair(4, 12), std::make_pair("nesto", 16));
    test.AddRow(4,5,6);
    test.GenerateTable();
    std::cout << test.GetTable() << std::endl;
    try{
      TableFormatterBase test2;
      test2.SetHeader({{"Ivan",6}});
      test2.AddRow(std::make_pair("test", TableFormatterColor::YELLOW));
      test2.GenerateTable();

      std::cout << test2.GetTable() << std::endl;

    }
    catch(std::string msg){
      std::cout << "Error " << msg << std::endl;
    }
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
