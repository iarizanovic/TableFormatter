#include "TableCell.hh"

std::vector<std::string> TableCell::ColorVector;

TableCell::TableCell(int value, TableFormatterColor col)
: doubleValue(0.f), color(col), llValue((long long)value), strValue(""),
selectedValue(TypeContainingValue::LLONG)
{
  Init();
}

TableCell::TableCell(float value, TableFormatterColor col)
: doubleValue(value), color(col), llValue(0), strValue(""),
selectedValue(TypeContainingValue::DOUBLE)
{
  Init();
}


TableCell::TableCell(double value, TableFormatterColor col)
: doubleValue(value), color(col), llValue(0), strValue(""),
selectedValue(TypeContainingValue::DOUBLE)
{
  Init();
}

TableCell::TableCell(long long value, TableFormatterColor col)
: doubleValue(0.f), color(col), llValue(value), strValue(""),
selectedValue(TypeContainingValue::LLONG)
{
  Init();
}

TableCell::TableCell(std::string& value, TableFormatterColor col)
: doubleValue(0.f), color(col), llValue(0), strValue(value),
selectedValue(TypeContainingValue::STRING)
{
  Init();
}

TableCell::TableCell(const char* val, TableFormatterColor col)
: doubleValue(0.f), color(col), llValue(0), strValue(val),
selectedValue(TypeContainingValue::STRING)
{

}


TableCell::TableCell(const TableCell& cell) {
  this->doubleValue = cell.doubleValue;
  this->strValue = cell.strValue;
  this->llValue = cell.llValue;
  this->color = cell.color;
  this->selectedValue = cell.selectedValue;
}

TableCell TableCell::operator=(const TableCell& rhs)
{
  if(this->selectedValue != rhs.selectedValue){
    throw std::string("TableFormatterTableCell: Assiging with different value types!");
  }

  this->selectedValue = rhs.selectedValue;
  this->color = rhs.color;
  this->doubleValue = rhs.doubleValue;
  this->llValue = rhs.llValue;
  this->strValue = rhs.strValue;

  return *this;
}

void TableCell::Init()
{
  if(ColorVector.empty())
    ColorVector =
    std::vector<std::string> { "\33[0m", "\33[31m", "\33[32m", "\33[33m"};
}


void TableCell::SetValue(double val)
{
  if(selectedValue == TypeContainingValue::DOUBLE){
    doubleValue =  val;
  }
}

void TableCell::SetValue(long long int val)
{
  if(selectedValue == TypeContainingValue::LLONG){
    llValue =  val;
  }
}

void TableCell::SetValue(std::string& val)
{
  if(selectedValue == TypeContainingValue::STRING){
    strValue =  val;
  }
}

void TableCell::Print(std::ostream& ostream, size_t width) const
{
  if(width){
    // because of escape characters
    if(color == TableFormatterColor::DEFAULT)
      ostream.width(width+3);
    if(color ==TableFormatterColor::RED)
      ostream.width(width+4);
    if(color==TableFormatterColor::GREEN)
      ostream.width(width+1);
    if(color == TableFormatterColor::YELLOW)
      ostream.width(width+1);
    ostream.fill(' ');
  }

  ostream << ColorVector[color];
  if(selectedValue == TypeContainingValue::DOUBLE)
    ostream << doubleValue;
  if(selectedValue == TypeContainingValue::LLONG)
    ostream << llValue;
  if(selectedValue == TypeContainingValue::STRING)
    ostream << strValue;
  ostream << *ColorVector.begin();
}

// Operators
std::ostream& operator<<(std::ostream& stream, const TableCell& cell)
{
  cell.Print(stream);
  return stream;
}

TableCell::operator int() const {
  if(this->selectedValue == TypeContainingValue::LLONG){
    return (int) llValue;
  }

  if(this->selectedValue == TypeContainingValue::DOUBLE){
    return (int) doubleValue;
  }
  throw std::bad_cast();
}

TableCell::operator double() const{
  if(this->selectedValue == TypeContainingValue::LLONG)
    return (double) llValue;

  if(this->selectedValue == TypeContainingValue::DOUBLE)
    return (double) doubleValue;

  throw std::bad_cast();
}

TableCell::operator float() const{
  if(this->selectedValue == TypeContainingValue::LLONG)
    return (float) llValue;

  if(this->selectedValue == TypeContainingValue::DOUBLE)
    return (float) doubleValue;

  throw std::bad_cast();
}

TableCell::operator long() const{
  if(this->selectedValue == TypeContainingValue::LLONG)
    return (long) llValue;

  if(this->selectedValue == TypeContainingValue::DOUBLE)
    return (long) doubleValue;

  throw std::bad_cast();
}

TableCell::operator std::string() const{
  if(selectedValue == TypeContainingValue::STRING)
    return strValue;

  throw std::bad_cast();
}

size_t TableCell::Length()
{
  size_t ret = 0;
  // Get length of string if its string value stored.
  if(selectedValue == TypeContainingValue::STRING)
    ret = strValue.length();

  // Get length of integer value
  if(selectedValue == TypeContainingValue::LLONG){
    long long temp = llValue;
    while(temp != 0){
      ++ret;
      temp /= 10;
    }
  }

  // Get length of double value
  if(selectedValue == TypeContainingValue::DOUBLE){
    double temp = llValue;
    while(temp > 1){
      ++ret;
      temp /= 10;
    }
    // Add three additional spaces for decimal numbers (. and two numbers)
    ret += 3;
  }

  // If ret value is not zero, add two more spaces for padding
  // Otherwise return 0, in case of unrecognized type.
  return ret ? ret + 2 : 0;
}


