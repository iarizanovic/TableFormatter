//------------------------------------------------------------------------------
// File: TableCell.cc
// Author: Ivan Arizanovic & Stefan Isidorovic - Comtrade
//------------------------------------------------------------------------------

/************************************************************************
 * EOS - the CERN Disk Storage System                                   *
 * Copyright (C) 2011 CERN/Switzerland                                  *
 *                                                                      *
 * This program is free software: you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * This program is distributed in the hope that it will be useful,      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.*
 ************************************************************************/

#include "TableCell.hh"

std::vector<std::string> TableCell::ColorVector;

//------------------------------------------------------------------------------
// Inputs (unsigned int, unsigned long long, int, long long, float, double, char, string)
//------------------------------------------------------------------------------
TableCell::TableCell(unsigned int value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col)
{
  Init();
  if (format.find("l") != std::string::npos) {
    selectedValue = TypeContainingValue::UINT;
    SetValue((unsigned long long int)value);
  }
  if (format.find("f") != std::string::npos) {
    selectedValue = TypeContainingValue::DOUBLE;
    SetValue((double)value);
  }
  if (format.find("s") != std::string::npos) {
    std::string value_temp = std::to_string(value);
    selectedValue = TypeContainingValue::STRING;
    SetValue(value_temp);
  }
}

TableCell::TableCell(unsigned long long int value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col)
{
  Init();
  if (format.find("l") != std::string::npos) {
    selectedValue = TypeContainingValue::UINT;
    SetValue(value);
  }
  if (format.find("f") != std::string::npos) {
    selectedValue = TypeContainingValue::DOUBLE;
    SetValue((double)value);
  }
  if (format.find("s") != std::string::npos) {
    selectedValue = TypeContainingValue::STRING;
    std::string value_temp = std::to_string(value);
    SetValue(value_temp);
  }
}

TableCell::TableCell(int value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col)
{
  Init();
  if (format.find("l") != std::string::npos) {
    selectedValue = TypeContainingValue::INT;
    SetValue((long long int)value);
  }
  if (format.find("f") != std::string::npos) {
    selectedValue = TypeContainingValue::DOUBLE;
    SetValue((double)value);
  }
  if (format.find("s") != std::string::npos) {
    selectedValue = TypeContainingValue::STRING;
    std::string value_temp = std::to_string(value);
    SetValue(value_temp);
  }
}

TableCell::TableCell(long long int value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col)
{
  Init();
  if (format.find("l") != std::string::npos) {
    selectedValue = TypeContainingValue::INT;
    SetValue(value);
  }
  if (format.find("f") != std::string::npos) {
    selectedValue = TypeContainingValue::DOUBLE;
    SetValue((double)value);
  }
  if (format.find("s") != std::string::npos) {
    selectedValue = TypeContainingValue::STRING;
    std::string value_temp = std::to_string(value);
    SetValue(value_temp);
  }
}

TableCell::TableCell(float value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col)
{
  Init();
  if (format.find("l") != std::string::npos) {
    selectedValue = TypeContainingValue::INT;
    SetValue((long long int)value);
  }
  if (format.find("f") != std::string::npos) {
    selectedValue = TypeContainingValue::DOUBLE;
    SetValue((double)value);
  }
  if (format.find("s") != std::string::npos) {
    selectedValue = TypeContainingValue::STRING;
    std::string value_temp = std::to_string(value);
    SetValue(value_temp);
  }
}

TableCell::TableCell(double value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col)
{
  Init();
  if (format.find("l") != std::string::npos) {
    selectedValue = TypeContainingValue::INT;
    SetValue((long long int)value);
  }
  if (format.find("f") != std::string::npos) {
    selectedValue = TypeContainingValue::DOUBLE;
    SetValue(value);
  }
  if (format.find("s") != std::string::npos) {
    selectedValue = TypeContainingValue::STRING;
    std::string value_temp = std::to_string(value);
    SetValue(value_temp);
  }
}

TableCell::TableCell(const char* value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col),
selectedValue(TypeContainingValue::STRING)
{
  Init();
  std::string value_temp(value);
  SetValue(value_temp);
}

TableCell::TableCell(std::string& value, std::string format,
                     std::string unit, TableFormatterColor col)
: format(format), unit(unit), color(col),
selectedValue(TypeContainingValue::STRING)
{
  Init();
  SetValue(value);
}

//------------------------------------------------------------------------------
// Color of cell
//------------------------------------------------------------------------------
void TableCell::Init()
{
  if(ColorVector.empty())
    ColorVector = TableFormatterColorContainer;
}

//------------------------------------------------------------------------------
// Setting values, implementled with guards,
// preventing one Cell to have any other value than initially set.
//------------------------------------------------------------------------------
void TableCell::SetValue(unsigned long long int value)
{
  if(selectedValue == TypeContainingValue::UINT){
    //Convert value into K,M,G,T,P,E scale
    if (format.find("+") != std::string::npos && value != 0) {
      if(value >= 1000ll*1000*1000*1000*1000*1000) {unit.insert(0,"E"); value /= 1000ll*1000*1000*1000*1000*1000; }
      else if(value >= 1000ll*1000*1000*1000*1000) {unit.insert(0,"P"); value /= 1000ll*1000*1000*1000*1000; }
           else if(value >= 1000ll*1000*1000*1000) {unit.insert(0,"T"); value /= 1000ll*1000*1000*1000; }
                else if(value >= 1000ll*1000*1000) {unit.insert(0,"G"); value /= 1000ll*1000*1000; }
                     else if(value >= 1000ll*1000) {unit.insert(0,"M"); value /= 1000ll*1000; }
                          else if(value >= 1000ll) {unit.insert(0,"K"); value /= 1000ll; }
    }

    ullValue = value;
  }
}

void TableCell::SetValue(long long int value)
{
  if(selectedValue == TypeContainingValue::INT){
    //Convert value into K,M,G,T,P,E scale
    if (format.find("+") != std::string::npos && value != 0) {
      bool value_negativ = false;
      if (value < 0) {
        value *= -1;
        value_negativ = true;
      }
      if(value >= 1000ll*1000*1000*1000*1000*1000) {unit.insert(0,"E"); value /= 1000ll*1000*1000*1000*1000*1000; }
      else if(value >= 1000ll*1000*1000*1000*1000) {unit.insert(0,"P"); value /= 1000ll*1000*1000*1000*1000; }
           else if(value >= 1000ll*1000*1000*1000) {unit.insert(0,"T"); value /= 1000ll*1000*1000*1000; }
                else if(value >= 1000ll*1000*1000) {unit.insert(0,"G"); value /= 1000ll*1000*1000; }
                     else if(value >= 1000ll*1000) {unit.insert(0,"M"); value /= 1000ll*1000; }
                          else if(value >= 1000ll) {unit.insert(0,"K"); value /= 1000ll; }
      if (value_negativ)
        value *= -1;
    }

    llValue = value;
  }
}

void TableCell::SetValue(double value)
{
  if(selectedValue == TypeContainingValue::DOUBLE){
    //Convert value into K,M,G,T,P,E scale
    if (format.find("+") != std::string::npos && value != 0) {
      bool value_negativ = false;
      if (value < 0) {
        value *= -1;
        value_negativ = true;
      }
      if(value >= 1000ll*1000*1000*1000*1000*1000) {unit.insert(0,"E"); value /= 1000ll*1000*1000*1000*1000*1000; }
      else if(value >= 1000ll*1000*1000*1000*1000) {unit.insert(0,"P"); value /= 1000ll*1000*1000*1000*1000; }
           else if(value >= 1000ll*1000*1000*1000) {unit.insert(0,"T"); value /= 1000ll*1000*1000*1000; }
                else if(value >= 1000ll*1000*1000) {unit.insert(0,"G"); value /= 1000ll*1000*1000; }
                     else if(value >= 1000ll*1000) {unit.insert(0,"M"); value /= 1000ll*1000; }
                          else if(value >= 1000ll) {unit.insert(0,"K"); value /= 1000ll; }
      if (value_negativ)
        value *= -1;
    }

    doubleValue =  value;
  }
}

void TableCell::SetValue(std::string& value)
{
  if(selectedValue == TypeContainingValue::STRING)
    strValue = value;
}

//------------------------------------------------------------------------------
// Operators
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const TableCell& cell)
{
  cell.Print(stream);
  return stream;
}

//------------------------------------------------------------------------------
// Print tablecell
//------------------------------------------------------------------------------
void TableCell::Print(std::ostream& ostream, size_t width_left, size_t width_right) const
{
  ostream.fill(' ');
  //Left space before cellValue
  if(width_left){
    // Because of escape characters
    // Normal display
    if(color == TableFormatterColor::DEFAULT)
      ostream.width(width_left+4);
    if(TableFormatterColor::RED <= color && color <= TableFormatterColor::WHITE)
      ostream.width(width_left+5);

    // Bold display
    if(color == TableFormatterColor::BDEFAULT)
      ostream.width(width_left+6);
    if(TableFormatterColor::BRED <= color && color <= TableFormatterColor::BWHITE)
      ostream.width(width_left+7);

    // Normal display with white BackGround
    if(color == TableFormatterColor::BGDEFAULT)
      ostream.width(width_left+7);
    if(TableFormatterColor::BGRED <= color && color <= TableFormatterColor::BGWHITE)
      ostream.width(width_left+8);

    // Bold display with white BackGround
    if(color == TableFormatterColor::BBGDEFAULT)
      ostream.width(width_left+9);
    if(TableFormatterColor::BBGRED <= color && color <= TableFormatterColor::BBGWHITE)
      ostream.width(width_left+10);
  }

  ostream << ColorVector[color];

  //Value
  if(selectedValue == TypeContainingValue::UINT)
    ostream << ullValue;
  if(selectedValue == TypeContainingValue::INT)
    ostream << llValue;
  if(selectedValue == TypeContainingValue::DOUBLE)
    ostream << std::setprecision (2) << std::fixed << doubleValue;
  if(selectedValue == TypeContainingValue::STRING)
    ostream << strValue;

  ostream << *ColorVector.begin();

  if (unit != "")
    ostream << " " << unit;

  //Right space after cellValue
  if(width_right)
    ostream.width(width_right);
}

//------------------------------------------------------------------------------
// Calculating print width of tablecell
//------------------------------------------------------------------------------
size_t TableCell::Length()
{
  size_t ret = 0;
  // Get length of unsigned integer value
  if(selectedValue == TypeContainingValue::UINT){
    unsigned long long int temp = ullValue;
    if (temp == 0)
      ret = 1;
    while(temp != 0){
      ++ret;
      temp /= 10;
    }
    if (unit !="")
      ret += unit.length() +1;
  }

  // Get length of integer value
  if(selectedValue == TypeContainingValue::INT){
    long long int temp = llValue;
    if (temp <= 0)
      ret = 1;
    while(temp != 0){
      ++ret;
      temp /= 10;
    }
    if (unit !="")
      ret += unit.length() +1;
  }

  // Get length of double value
  if(selectedValue == TypeContainingValue::DOUBLE){
    std::stringstream temp;
    temp << std::setprecision (2) << std::fixed << doubleValue;
    ret = temp.str().length() ;
    if (unit !="")
      ret += unit.length() +1;
  }

  // Get length of string if its string value stored.
  if(selectedValue == TypeContainingValue::STRING) {
    ret = strValue.length();
    if (unit !="")
      ret += unit.length() +1;
  }

  return ret;
}
