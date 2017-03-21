#ifndef __TABLE__FORMATTER__HH__
#define __TABLE__FORMATTER__HH__

#include "TableCell.hh"



class TableFormatterBase {
protected:
  //Style ("│","┌","┬","┐","├","┼","┤","└","┴","┘","─")
  std::string border_head [11] = {"┌─","─┬─","─┐","─",
                                  "│ "," │ "," │",
                                  "├─","─┴─","─┤","─"};
  std::string border_sep [4]   = {"├─","───","─┤","─"};
  std::string border_body [7]  = {"│ ","   "," │",
                                  "└─","───","─┘","─"};
//   //Style ("┃","┏","┳","┓","┣","╋","┫","┗","┻","┛","━")
//   std::string border_head [11] = {"┏━","━┳━","━┓","━",
//                                   "┃ "," ┃ "," ┃",
//                                   "┣━","━━━","━┫","━"};
//   std::string border_sep [4]   = {"┣━","━━━","━┫","━"};
//   std::string border_body [7]  = {"┃ ","   "," ┃",
//                                   "┗━","━━━","━┛","━"};
  std::stringstream m_sink;
  TableHeader m_header;
  TableData m_data;
  std::vector<CustomRow> m_custom_rows;

  std::string GenerateSeparator(std::string left, std::string center, std::string right, std::string line);
  void GenerateHeader();
  void GenerateBody();

  bool m_rowCreationInProcess;

  void ProcessRow(TableCell& cell);
  void ProcessCustomRow(TableCell& cell, int width);

public:
  TableFormatterBase();

  void GenerateTable();

  void SetHeader(const TableHeader& header);
  void AddSeparator();

  void SetHeadCellTitle(const std::string& title, const size_t index);
  void SetHeadCellSize(const size_t size, const size_t index);

  HeadCell GetHeadCell(size_t index);


  /// Output

  inline std::string GetTable()
  {
    return m_sink.str();
  }


  /// Input - AddRow

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


  /// Input - Ends of AddRow

  template<typename T>
  void AddRow(const std::pair<T, TableFormatterColor>& t)
  {
    TableCell cell(t.first, t.second);
    ProcessRow(cell);
    m_rowCreationInProcess = false;

    if(m_data.back().size() != m_header.size())
      throw std::string("Not matched number of arguments with header!\nYou can use \'AddCustomRow\'.");
  }

  template<typename T>
  void AddRow(const T& t)
  {
    TableCell cell(t);
    ProcessRow(cell);
    m_rowCreationInProcess = false;

    if(m_data.back().size() != m_header.size())
      throw std::string("Not matched number of arguments with header!\nYou can use \'AddCustomRow\'.");
   }


  /// Input - CustomRow

  template<typename T, typename... Args>
  void AddCustomRow(const T& t, const Args& ... args)
  {
    TableCell cell(t);
    ProcessCustomRow(cell, 0);
    AddCustomRow(args...);

    if(m_custom_rows.back().size() > m_header.size())
      throw std::string("Not matched number of arguments with header.\nYou need to set size of other cells in CustomRow!");
  }

  template<typename T, typename... Args>
  void AddCustomRow(const std::pair<T, int>& t, const Args& ... args)
  {
    TableCell cell(t.first);
    ProcessCustomRow(cell, t.second);
    AddCustomRow(args...);
  }

  template<typename T, typename... Args>
  void AddCustomRow(const std::pair<T, TableFormatterColor>& t, const Args& ... args)
  {
    TableCell cell(t.first, t.second);
    ProcessCustomRow(cell, 0);
    AddCustomRow(args...);

    if(m_custom_rows.back().size() > m_header.size())
      throw std::string("Not matched number of arguments with header.\nYou need to set size of other cells in CustomRow!");
  }

  template<typename T, typename... Args>
  void AddCustomRow(const std::tuple<T, int, TableFormatterColor>& t, const Args& ... args)
  {
    TableCell cell(std::get<0>(t),std::get<2>(t));
    ProcessCustomRow(cell, std::get<1>(t));
    AddCustomRow(args...);
  }

  template<typename T, typename... Args>
  void AddCustomRow(const std::tuple<T, TableFormatterColor, int>& t, const Args& ... args)
  {
    TableCell cell(std::get<0>(t),std::get<1>(t));
    ProcessCustomRow(cell, std::get<2>(t));
    AddCustomRow(args...);
  }


  /// Input - Ends of CustomRow

  template<typename T>
  void AddCustomRow(const T& t)
  {
    TableCell cell = TableCell(t);
    ProcessCustomRow(cell, 0);
    m_rowCreationInProcess = false;

    if(m_custom_rows.back().size() > m_header.size())
      throw std::string("Not matched number of arguments with header.\nYou need to set size of other cells in CustomRow!");
  }

  template<typename T>
  void AddCustomRow(const std::pair<T, int>& t)
  {
    TableCell cell = TableCell(t.first);
    ProcessCustomRow(cell, t.second);
    m_rowCreationInProcess = false;
  }

  template<typename T>
  void AddCustomRow(const std::pair<T, TableFormatterColor>& t)
  {
    TableCell cell = TableCell(t.first, t.second);
    ProcessCustomRow(cell, 0);
    m_rowCreationInProcess = false;

    if(m_custom_rows.back().size() > m_header.size())
      throw std::string("Not matched number of arguments with header.\nYou need to set size of other cells in CustomRow!");
  }

  template<typename T>
  void AddCustomRow(const std::tuple<T, int, TableFormatterColor>& t)
  {
    TableCell cell(std::get<0>(t),std::get<2>(t));
    ProcessCustomRow(cell, std::get<1>(t));
    m_rowCreationInProcess = false;
  }

  template<typename T>
  void AddCustomRow(const std::tuple<T, TableFormatterColor, int>& t)
  {
    TableCell cell(std::get<0>(t),std::get<1>(t));
    ProcessCustomRow(cell, std::get<2>(t));
    m_rowCreationInProcess = false;
  }

};



#endif // __TABLE__FORMATTER__HH__