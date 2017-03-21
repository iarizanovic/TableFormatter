#ifndef __TABLE_CELL__HH__
#define __TABLE_CELL__HH__

#include "TableFormatting.h"

class TableCell {
  // Store value for cell, three type values
  double doubleValue;
  long long llValue;
  std::string strValue;

  // Color of cell
  TableFormatterColor color;

  static std::vector<std::string> ColorVector;

  enum TypeContainingValue{
    DOUBLE = 1, LLONG = 2, STRING = 3
  };

  // Indicator which value is carrying information
  TypeContainingValue selectedValue;

  // Making sure that cell will not be created with no arguments
  // or proper handling.
  TableCell() = delete;


  void Init();

public:
  TableCell(int value, TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(float value, TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(double value, TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(long long, TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(std::string&, TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(const char* val, TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(const TableCell& cell);

  // Operators
  TableCell operator=(const TableCell& rhs);
  operator double() const;
  operator float() const;
  operator long() const;
  operator int() const;
  operator std::string() const;

  // Setting values, implementled with guards, preventing one Cell to have
  // any other value than initially set.
  void SetValue(double val);
  void SetValue(long long val);
  void SetValue(std::string& val);

  // Setting color
  inline void SetColor(TableFormatterColor& col) { color = col; }

  // Printing to stream. This is needed as class will dump data into stringstream
  // or anything overloading std::stringstream.
  void Print(std::ostream& ostream, size_t width = 0) const;

  size_t Length();


};

std::ostream& operator<<(std::ostream& stream, const TableCell& cell);


#endif //__TABLE_CELL__HH__