//------------------------------------------------------------------------------
// File: TableFormatting.hh
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

#ifndef __TABLE__FORMATTING__HH__
#define __TABLE__FORMATTING__HH__

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <exception>
#include <typeinfo>
#include <queue>
#include <tuple>

class TableCell;

//------------------------------------------------------------------------------
// Typedefs for easier reading and understanding, and in general
//------------------------------------------------------------------------------
using HeadCell = std::tuple<std::string, unsigned, std::string>;
using TableHeader = std::vector<HeadCell>;

using Row = std::vector<TableCell>;
using TableData = std::vector<Row>;

using TableString = std::vector<std::string>;

enum TableFormatterColor {
  //Normal display
  DEFAULT     =  0,
  RED         =  1,
  GREEN       =  2,
  YELLOW      =  3,
  BLUE        =  4,
  MARGARITA   =  5,
  CYAN        =  6,
  WHITE       =  7,
  //Bold display (B...)
  BDEFAULT    =  8,
  BRED        =  9,
  BGREEN      = 10,
  BYELLOW     = 11,
  BBLUE       = 12,
  BMARGARITA  = 13,
  BCYAN       = 14,
  BWHITE      = 15,
  //Normal display with white BackGround (BG...)
  BGDEFAULT   = 16,
  BGRED       = 17,
  BGGREEN     = 18,
  BGYELLOW    = 19,
  BGBLUE      = 20,
  BGMARGARITA = 21,
  BGCYAN      = 22,
  BGWHITE     = 23,
  //Bold display with white BackGround (BBG...)
  BBGDEFAULT  = 24,
  BBGRED      = 25,
  BBGGREEN    = 26,
  BBGYELLOW   = 27,
  BBGBLUE     = 28,
  BBGMARGARITA= 29,
  BBGCYAN     = 30,
  BBGWHITE    = 31
};

//------------------------------------------------------------------------------
// Operators
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& stream, const TableCell& cell);

#endif //__TABLE__FORMATTING__HH__
