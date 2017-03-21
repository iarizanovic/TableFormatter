#include "TableFormatterBase.hh"


TableFormatterBase::TableFormatterBase()
: m_sink(" ")
{

}

std::string TableFormatterBase::GenerateSeparator(std::string left, std::string center, std::string right, std::string line) {
  std::string separator = left;
  for(size_t i = 0, size = m_header.size(); i < size; ++i) {
    for (size_t i2 = 0; i2 < m_header[i].second; i2++)
      separator += line;
    if (i < size-1) separator+= center;
  }
  separator += right;
  return separator;
}

void TableFormatterBase::GenerateHeader()
{
  //Top edge of Header
  m_sink << GenerateSeparator(border_head[0],border_head[1],border_head[2],border_head[3]);
  m_sink << std::endl;
  for(size_t i = 0, size = m_header.size(); i < size; ++i) {
    if (i == 0) m_sink<< border_head[4];
    m_sink.width(m_header[i].second);
    m_sink << m_header[i].first;
    if (i < size-1) m_sink << border_head[5];
  }
  //Right edge of Header
  m_sink << border_head[6];
  //Bottom edge of Header
  m_sink << std::endl;
  m_sink << GenerateSeparator(border_head[7],border_head[8],border_head[9],border_head[10]);
  m_sink << std::endl;
}

void TableFormatterBase::GenerateBody()
{
  size_t custom_rows = 0;
  for(auto row : m_data){

    //Genarate CustomRows
    if(row.empty()){
      bool custom = false;
      int i = 0;
      size_t row_lenght = 0;
      for(auto cell : m_custom_rows[custom_rows++]) {
        custom = true;
        //Left edge of CustomRows
        if (i++ == 0) {
          m_sink << border_body[0];
          row_lenght += border_body[0].length();
        }
        //Generate CustomRow cell
        cell.first.Print(m_sink, (size_t)cell.second);
        row_lenght += cell.second + cell.first.Length();

        //Right edge of CustomRows cell
        if (i < m_custom_rows[custom_rows-1].size()) {
          m_sink << border_body[1];
          row_lenght += border_body[1].length();
        }
      }
      //Right edge of CustomRows
      row_lenght += border_body[2].length();
      if (custom && row_lenght <= GenerateSeparator(border_body[0],border_body[1],border_body[2]," ").length())
        m_sink << std::string(GenerateSeparator(border_body[0],border_body[1],border_body[2]," ").length() - row_lenght, ' ') << border_body[2];

      //Generate Separator
      if (!custom)
        m_sink<< GenerateSeparator(border_sep[0],border_sep[1],border_sep[2],border_sep[3]);

    }
    //Genarate ClassicRows
    else {
      for(size_t i = 0, size = m_header.size(); i < size; ++i) {
        if (i == 0) m_sink << border_body[0];
        row[i].Print( m_sink, (size_t)m_header[i].second - (size_t)row[i].Length() );
        if (i < size-1) m_sink << border_body[1];
      }
      //Right edge of ClassicRows
      m_sink << border_body[2];
    }
    m_sink << std::endl;
  }
  //Bottom edge
  m_sink<< GenerateSeparator(border_body[3],border_body[4],border_body[5],border_body[6]) << std::endl;

}

void TableFormatterBase::GenerateTable()
{
  GenerateHeader();
  GenerateBody();
}

void TableFormatterBase::SetHeader(const TableHeader& header)
{
  if(m_header.empty()){
    m_header = header;

    for(size_t i = 0; i < m_header.size(); ++i)
      if (m_header[i].second < m_header[i].first.length())
        m_header[i].second = m_header[i].first.length();
  }
  else
    throw std::string("There is already defined header!");
}

void TableFormatterBase::AddSeparator()
{
  m_data.emplace_back();
  m_custom_rows.emplace_back();
}

void TableFormatterBase::ProcessRow(TableCell& cell)
{
  if(!m_rowCreationInProcess){
    Row row;
    m_data.push_back(row);
    m_rowCreationInProcess = true;
  }

  m_data.back().push_back( cell );

  if(cell.Length() > m_header[m_data.back().size() - 1].second)
    m_header[m_data.back().size() - 1].second = cell.Length();
}

void TableFormatterBase::ProcessCustomRow(TableCell& cell, int width)
{
  if(!m_rowCreationInProcess){
    m_rowCreationInProcess = true;
    m_data.emplace_back();
    CustomRow row;
    m_custom_rows.push_back(row);
  }

  if(width <= 0 && cell.Length() > m_header[m_custom_rows.back().size()].second)
    width = 1;

  m_custom_rows.back().push_back(
    std::make_pair(
      cell,
      width <= 0 ? m_header[m_custom_rows.back().size()].second -cell.Length() : width <= cell.Length() ? 0 : width-cell.Length()
    )
  );
}
