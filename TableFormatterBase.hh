//------------------------------------------------------------------------------
// File: TableFormatterBase.hh
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

#ifndef __TABLE__FORMATTER__HH__
#define __TABLE__FORMATTER__HH__

#include "TableCell.hh"

class TableFormatterBase {
protected:
  std::stringstream m_sink;
  TableHeader m_header;
  TableData m_data;
  TableString m_string;

  // Style
  void Style(int style);
  std::string border_head [11];
  std::string border_sep [4];
  std::string border_body [7];

  // Generate Table
  void WidthCorrection();
  std::string GenerateSeparator(std::string left, std::string center, std::string right, std::string line);
  void GenerateHeader();
  void GenerateBody();
  void GenerateMonitoring();

public:
  TableFormatterBase();
  // Creation Process
  void SetHeader(const TableHeader& header);
  void AddRows(const TableData& body);
  void AddString (std::string string);

  void AddSeparator();

  std::string GenerateTable(int style = 0);

};
#endif // __TABLE__FORMATTER__HH__
