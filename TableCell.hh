//------------------------------------------------------------------------------
// File: TableCell.hh
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

#ifndef __TABLE_CELL__HH__
#define __TABLE_CELL__HH__

#include "TableFormatting.hh"

class TableCell {
protected:
  //------------------------------------------------------------------------------
  // Store value for cell
  //------------------------------------------------------------------------------
  unsigned long long int ullValue = 0;
  long long int llValue = 0;
  double doubleValue = 0.f;
  std::string strValue = "";
  std::string format;
  std::string unit;

  //------------------------------------------------------------------------------
  // Color of cell
  //------------------------------------------------------------------------------
  void Init();
  TableFormatterColor color;
  static std::vector<std::string> ColorVector;
  std::vector<std::string> TableFormatterColorContainer = {
    "\33[0m", "\33[31m", "\33[32m", "\33[33m", "\33[34m", "\33[35m", "\33[36m", "\33[37m",
    "\33[1;0m", "\33[1;31m", "\33[1;32m", "\33[1;33m", "\33[1;34m", "\33[1;35m", "\33[1;36m", "\33[1;37m",
    "\33[47;0m", "\33[47;31m", "\33[47;32m", "\33[47;33m", "\33[47;34m", "\33[47;35m", "\33[47;36m", "\33[47;37m",
    "\33[1;47;0m", "\33[1;47;31m", "\33[1;47;32m", "\33[1;47;33m", "\33[1;47;34m", "\33[1;47;35m", "\33[1;47;36m", "\33[1;47;37m"
  };

  //------------------------------------------------------------------------------
  // Three type values
  //------------------------------------------------------------------------------
  enum TypeContainingValue{
    UINT   = 1,
    INT    = 2,
    DOUBLE = 3,
    STRING = 4
  };
  // Indicator which value is carrying information
  TypeContainingValue selectedValue;


  //------------------------------------------------------------------------------
  // Making sure that cell will not be created with no arguments or proper handling.
  //------------------------------------------------------------------------------
  TableCell() = delete;

public:
  //------------------------------------------------------------------------------
  // Inputs (unsigned int, unsigned long long, int, long long, float, double, char, string)
  //------------------------------------------------------------------------------
  TableCell(unsigned int value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(unsigned long long int value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);

  TableCell(int value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(long long int value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);

  TableCell(float value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(double value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);

  TableCell(const char* value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);
  TableCell(std::string& value, std::string format, std::string unit = "",
            TableFormatterColor col = TableFormatterColor::DEFAULT);

  //------------------------------------------------------------------------------
  // Setting values (convert into K,M,G,T,P,E scale), implementled with guards,
  // preventing one Cell to have any other value than initially set.
  //------------------------------------------------------------------------------
  void SetValue(unsigned long long int value);
  void SetValue(long long int value);
  void SetValue(double value);
  void SetValue(std::string& value);

  //------------------------------------------------------------------------------
  // Print tablecell
  //------------------------------------------------------------------------------
  // Printing to stream. This is needed as class will dump data into stringstream
  // or anything overloading std::stringstream.
  void Print(std::ostream& ostream, size_t width_left = 0, size_t width_right = 0) const;

  //------------------------------------------------------------------------------
  // Calculating print width of tablecell
  //------------------------------------------------------------------------------
  size_t Length();

};


#endif //__TABLE_CELL__HH__
