//------------------------------------------------------------------------------
// File: TableFormatterBase.cc
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

#include "TableFormatterBase.hh"

TableFormatterBase::TableFormatterBase()
: m_sink("")
{
}

//------------------------------------------------------------------------------
// Generate Table
//------------------------------------------------------------------------------
std::string TableFormatterBase::GenerateTable(int style)
{
  Style(style);
  //Generate monitoring information in line (option "-m")
  if (!m_header.empty() && std::get<2>(m_header[0]).find("o") != std::string::npos)
    GenerateMonitoring();

  //Generate classic table (with/without second table)
  if (!m_header.empty() && std::get<2>(m_header[0]).find("o") == std::string::npos) {
    WidthCorrection();
    GenerateHeader();
    GenerateBody();
  }
  //Generate string (e.g.second table)
  if (m_header.empty())
    GenerateBody();

  return m_sink.str();
}

void TableFormatterBase::GenerateMonitoring()
{
  for(auto row : m_data){
    if(!row.empty()) {
      for(size_t i = 0, size = m_header.size(); i < size; ++i) {
        m_sink << std::get<0>(m_header[i]) << "=";
        row[i].Print( m_sink);
        m_sink << " | ";
      }
      m_sink << "\n";
    }
  }
}

void TableFormatterBase::WidthCorrection()
{
  for(auto row : m_data)
    if(!row.empty())
      for(size_t i = 0, size = m_header.size(); i < size; i++){
        if (std::get<1>(m_header[i]) < std::get<0>(m_header[i]).length())
          std::get<1>(m_header[i]) = std::get<0>(m_header[i]).length();
        if (std::get<1>(m_header[i]) < row[i].Length())
          std::get<1>(m_header[i]) = row[i].Length();
      }
}

std::string TableFormatterBase::GenerateSeparator(std::string left, std::string center,
                                                  std::string right, std::string line)
{
  std::string separator = left;
  for(size_t i = 0, size = m_header.size(); i < size; ++i) {
    for (size_t i2 = 0; i2 < std::get<1>(m_header[i]); i2++)
      separator += line;
    if (i < size-1) separator+= center;
  }
  separator += right;
  return separator;
}

void TableFormatterBase::GenerateHeader()
{
  //Top edge of header
  m_sink << GenerateSeparator(border_head[0],border_head[1],border_head[2],border_head[3])
         << std::endl;

  for(size_t i = 0, size = m_header.size(); i < size; ++i) {
    //Left edge of header
    if (i == 0)
      m_sink << border_head[4];

    //Generate cell
    if (std::get<2>(m_header[i]).find("-") == std::string::npos)
      m_sink.width(std::get<1>(m_header[i]));

    m_sink << std::get<0>(m_header[i]);

    if (std::get<2>(m_header[i]).find("-") != std::string::npos)
      m_sink.width(std::get<1>(m_header[i]) - std::get<0>(m_header[i]).length() + border_head[5].length());

    //Center edge of header
    if (i < size-1)
      m_sink << border_head[5];
  }

  //Right edge of Header
  m_sink << border_head[6] << std::endl;

  //Bottom edge of Header
  m_sink << GenerateSeparator(border_head[7],border_head[8],border_head[9],border_head[10])
         << std::endl;
}

void TableFormatterBase::GenerateBody()
{
  size_t row_size = 0;
  size_t string_size = 0;
  for(auto row : m_data){
    if(row.empty()){
      //Generate String
      if (!m_string[string_size].empty()) {
        //Bottom edge for last table
        if (row_size >0 && !m_data[row_size-1].empty())
          m_sink << GenerateSeparator(border_body[3],border_body[4],border_body[5],border_body[6])
                 << std::endl;

        m_sink << m_string[string_size];
      }

      //Generate Separator
      else
        m_sink << GenerateSeparator(border_sep[0],border_sep[1],border_sep[2],border_sep[3])
               << std::endl;

      string_size++;
    }
    //Genarate Rows
    if(!row.empty() && !m_header.empty() ) {
      if (row_size >0 && m_data[row_size-1].empty() &&
          string_size>0 && !m_string[string_size-1].empty())
        GenerateHeader();

      for(size_t i = 0, size = m_header.size(); i < size; ++i) {
        //Left edge
        if (i == 0)
          m_sink << border_body[0];

        //Generate cell
        if (std::get<2>(m_header[i]).find("-") == std::string::npos)
          row[i].Print( m_sink, std::get<1>(m_header[i]) - row[i].Length() );
        else
          row[i].Print( m_sink, 0, std::get<1>(m_header[i]) - row[i].Length() + border_body[1].length());

        //Right edge of cell
        if (i < size-1)
          m_sink << border_body[1];
      }
      //Right edge
      m_sink << border_body[2] << std::endl;
    }
    row_size++;
  }
  //Bottom edge
  if(!m_header.empty() && !m_data[m_data.size()-1].empty())
    m_sink << GenerateSeparator(border_body[3],border_body[4],border_body[5],border_body[6])
           << std::endl;
}

//------------------------------------------------------------------------------
// Creation Process
//------------------------------------------------------------------------------

void TableFormatterBase::SetHeader(const TableHeader& header)
{
  if(m_header.empty())
    m_header = header;
}

void TableFormatterBase::AddSeparator()
{
  m_data.emplace_back();
  m_string.emplace_back();
}

void TableFormatterBase::AddRows(const TableData& body)
{
  std::copy( body.begin(), body.end(), std::back_inserter(m_data) );
}

void TableFormatterBase::AddString(std::string string)
{
  m_data.emplace_back();
  m_string.push_back(string);
}

//------------------------------------------------------------------------------
// Style
//------------------------------------------------------------------------------

void TableFormatterBase::Style(int style)
{
  switch (style) {
    case 0: //DEFAULT - Full normal border ("│","┌","┬","┐","├","┼","┤","└","┴","┘","─")
    {
      std::string head [11] = {"┌","┬","┐","─",
                               "│","│","│",
                               "├","┴","┤","─"};
      std::string sep [4]   = {"│","-","│","-"};
      std::string body [7]  = {"│"," ","│",
                               "└","─","┘","─"};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 1: //Full bold border ("┃","┏","┳","┓","┣","╋","┫","┗","┻","┛","━")
    {
      std::string head [11] = {"┏","┳","┓","━",
                               "┃","┃","┃",
                               "┣","┻","┫","━"};
      std::string sep [4]   = {"┃","-","┃","-"};
      std::string body [7]  = {"┃"," ","┃",
                               "┗","━","┛","━"};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 2: //Full double border ("║","╔","╦","╗","╠","╬","╣","╚","╩","╝","═")
    {
      std::string head [11] = {"╔","╦","╗","═",
                               "║","║","║",
                               "╠","╩","╣","═"};
      std::string sep [4]   = {"║","-","║","-"};
      std::string body [7]  = {"║"," ","║",
                               "╚","═","╝","═"};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 3: //Header normal border ("│","┌","┬","┐","├","┼","┤","└","┴","┘","─")
    {
      std::string head [11] = {"┌","┬","┐","─",
                               "│","│","│",
                               "└","┴","┘","─"};
      std::string sep [4]   = {" ","-"," ","-"};
      std::string body [7]  = {" "," "," "};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 4: //Header bold border ("┃","┏","┳","┓","┣","╋","┫","┗","┻","┛","━")
    {
      std::string head [11] = {"┏","┳","┓","━",
                               "┃","┃","┃",
                               "┗","┻","┛","━"};
      std::string sep [4]   = {" ","-"," ","-"};
      std::string body [7]  = {" "," "," "};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 5: //Header double border ("║","╔","╦","╗","╠","╬","╣","╚","╩","╝","═")
    {
      std::string head [11] = {"╔","╦","╗","═",
                               "║","║","║",
                               "╚","╩","╝","═"};
      std::string sep [4]   = {" ","-"," ","-"};
      std::string body [7]  = {" "," "," "};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 6: //Minimal style
    {
      std::string head [11] = {" ","  "," ","-",
                               " ","  "," ",
                               " ","  "," ","-"};
      std::string sep [4]   = {" ","  "," ","-"};
      std::string body [7]  = {" ","  "," "};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 7: // Old style
    {
      std::string head [11] = {"#-","--","-","-",
                               "# ","# ","#",
                               "#-","--","-","-"};
      std::string sep [4]   = {" -","--"," ","-"};
      std::string body [7]  = {"  ","  "," "};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
    case 8: // Old style - wide
    {
      std::string head [11] = {"#-","---","--","-",
                               "# "," # "," #",
                               "#-","---","--","-"};
      std::string sep [4]   = {" -","---","- ","-"};
      std::string body [7]  = {"  ","   ","  "};
      std::copy(head, head+11, border_head);
      std::copy(sep, sep+4, border_sep);
      std::copy(body, body+7, border_body);
      break;
    }
  }
}
