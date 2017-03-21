#ifndef __TABLE__FORMATTER__HH__
#define __TABLE__FORMATTER__HH__

#include "TableFormatting.h"
#include "TableCell.hh"
#include <queue>
#include <tuple>


class TableFormatterBase {
  std::stringstream m_sink;
  TableHeader m_header;
  TableData m_data;
  std::vector<CustomRow> m_custom_rows;


  void GenerateHeader();
  void GenerateBody();

  bool m_rowCreationInProcess;

  void ProcessRow(TableCell& cell);
  void ProcessCustomRow(TableCell& cell, unsigned width){
    if(!m_rowCreationInProcess){
      m_rowCreationInProcess = true;
      m_data.emplace_back();
      std::vector<std::pair<TableCell, unsigned>> row;
      m_custom_rows.push_back(row);
    }
    m_custom_rows.back().push_back(
      std::make_pair(
        cell,
        cell.Length() > width ? cell.Length() : width
      )
    );
  }

public:
  TableFormatterBase();

  void GenerateTable();

  void SetHeader(const TableHeader& header);

  void SetHeadCellTitle(const std::string& title, const size_t index);
  void SetHeadCellSize(const size_t size, const size_t index);

  HeadCell GetHeadCell(size_t index);

  inline std::string GetTable(){ return m_sink.str(); }

  template<typename T, typename... Args>
  void AddRow(const T& t, const Args& ... args)
  {
    TableCell cell(t);
    ProcessRow(cell);
    AddRow(args...);
  }

  template<typename T, typename... Args>
  void AddRow(const std::pair<T, TableFormatterColor>& t, const Args&... args){
    TableCell cell(t.first, t.second);
    ProcessRow(cell);
    AddRow(args...);
  }


  template<typename T>
  void AddRow(const std::pair<T, TableFormatterColor>& t){
    TableCell cell(t.first, t.second);
    ProcessRow(cell);

    m_rowCreationInProcess = false;

    if(m_data.back().size() != m_header.size())
      throw std::string("Not matched number of arguments with header!");
  }

  template<typename T>
  void AddRow(const T& t)
  {
    TableCell cell(t);
    ProcessRow(cell);

    m_rowCreationInProcess = false;

    if(m_data.back().size() != m_header.size())
      throw std::string("Not matched number of arguments with header!");
  }

  template<typename T, typename... Args>
  void AddCustomRow(const std::pair<T, int>& t, const Args& ... args){
    // Check
    TableCell cell(t.first);
    ProcessCustomRow(cell, t.second);
    AddCustomRow(args...);

  }

  template<typename T>
  void AddCustomRow(const std::pair<T, int>& t){
    TableCell cell = TableCell(t.first);
    ProcessCustomRow(cell, t.second);
    m_rowCreationInProcess = false;
  }

};

#endif // __TABLE__FORMATTER__HH__