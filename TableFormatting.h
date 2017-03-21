#ifndef __TABLE__FORMATTING__HH__
#define __TABLE__FORMATTING__HH__

#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <utility>
#include <exception>
#include <typeinfo>
#include <queue>

class TableCell;

// Typedefs for easier reading and understanding, and in general
using HeadCell = std::pair<std::string, unsigned>;
using Row = std::vector<TableCell>;
using TableHeader = std::vector<HeadCell>;
using TableData = std::vector<Row>;
using Widths = std::vector<unsigned>;
using CustomRow = std::vector<std::pair<TableCell, unsigned>>;


enum TableFormatterColor {
  DEFAULT  = 0,
  RED      = 1,
  GREEN    = 2,
  YELLOW   = 3 };

#endif //__TABLE__FORMATTING__HH__