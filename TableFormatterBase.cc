#include "TableFormatterBase.hh"


TableFormatterBase::TableFormatterBase()
: m_sink("")
{

}


void TableFormatterBase::GenerateHeader()
{
  m_sink.fill(' ');
  m_sink << std::endl;
  for(HeadCell cell : m_header){
    m_sink.width(cell.second);
    m_sink << cell.first;
  }
  m_sink << std::endl;
}

void TableFormatterBase::GenerateBody()
{
  size_t custom_rows = 0;

  for(auto row : m_data){
    if(row.empty()){
      // logic custom row
      // NOTE: Check this.
      for(auto cell : m_custom_rows[custom_rows++])
        cell.first.Print(m_sink, (size_t)cell.second);

      m_sink << std::endl;
      continue;
    }

    for(size_t i = 0, size = m_header.size(); i < size; ++i)
      row[i].Print(m_sink, (size_t)m_header[i].second);

    m_sink << std::endl;

  }
}

void TableFormatterBase::SetHeader(const TableHeader& header)
{
  if(m_header.empty()){
    m_header = header;
  }
  else
    throw std::string("There is already defined header!");
}

void TableFormatterBase::SetHeadCellSize(const size_t size, const size_t index)
{
  if(m_header.size() > index){
    m_header[index].second = size;
  }
  else{
    throw std::string("There is no head cell with given index: ") + std::to_string(index);
  }
}

void TableFormatterBase::SetHeadCellTitle(const std::string& title, const size_t index)
{
  if(m_header.size() > index){
    m_header[index].first = title;
  }
  else{
    throw std::string("There is no head cell with given index: ") + std::to_string(index);
  }
}

HeadCell TableFormatterBase::GetHeadCell(size_t index)
{
  if(m_header.size() > index){
    return m_header[index];
  }
  else{
    throw std::string("There is no head cell with given index: ") + std::to_string(index);
  }
}

void TableFormatterBase::GenerateTable()
{
  GenerateHeader();
  GenerateBody();
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

