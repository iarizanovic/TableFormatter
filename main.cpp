#include "TableFormatterBase.hh"

int main() {

    TableFormatterBase test;

    //header creator
    std::string mListFormat = "header=1:key=host:width=24:format=S|sep= (|key=port:width=4:format=-s|sep=) |key=id:width=6:format=s|sep= |key=path:width=32:format=s|sep= |key=schedgroup:width=16:format=s|sep= |key=stat.geotag:width=16:format=s|sep= |key=stat.boot:width=12:format=s|sep= |key=configstatus:width=14:format=s|sep= |key=stat.drain:width=12:format=s|sep= |key=stat.active:width=8:format=s|sep= |key=stat.health:width=16:format=s";
    TableHeader header;
    size_t key_end = 0;
    size_t width_end = 0;
    while (mListFormat.find("key=",key_end) != std::string::npos) {
      size_t key = mListFormat.find("key=",key_end)+4;
      key_end = mListFormat.find(":",key);
      std::string header_name = mListFormat.substr(key,key_end - key);
      if (header_name.find("stat.") != std::string::npos)
        header_name.erase(0,5);

      size_t width = mListFormat.find("width=",width_end)+6;
      width_end = mListFormat.find(":",width);
      int header_width = std::stoi( mListFormat.substr(width,width_end - width) );

//       std::cout << header_name.c_str() << header_width << "\n";
      header.push_back( std::make_tuple(header_name,header_width, "+") );
    }

    //input
    TableData body;
    TableData body2;
//     //unsigned
//     for (int k=0 ; k<1; k++) {
//       body.emplace_back();
//       for (unsigned int i=1 ; i<=13; i++) {
//         TableCell cell(i, "l", "", RED);
//         body.back().push_back( cell );
//       }
//     }
//     for (int k=0 ; k<1; k++) {
//       body.emplace_back();
//       for (int i=1 ; i<=13; i++) {
//         body.back().push_back( TableCell( (unsigned long long int)(i+10)*100000*100000000, "+fo", "", BRED ));
// //         TableCell cell((uint64_t)(i+10)*10000000000*100000000, "", RED);
// //         body.back().push_back( cell );
//       }
//     }
//     //int
//     for (int k=0 ; k<1; k++) {
//       body.emplace_back();
//       for (int i=1 ; i<=13; i++) {
//         TableCell cell((i)*-1000, "+lo", "", BGRED);
//         body.back().push_back( cell );
//       }
//     }
//     for (int k=0 ; k<1; k++) {
//       body.emplace_back();
//       for (int i=1 ; i<=13; i++) {
//         body.back().push_back( TableCell( (long long int)(i)*-1000000*100000000, "+so", "", BBGRED ));
// //         TableCell cell((uint64_t)(i+10)*10000000000*100000000, "", RED);
// //         body.back().push_back( cell );
//       }
//     }
//     //double
//     for (int k=0 ; k<1; k++) {
//       body.emplace_back();
//       for (int i=1 ; i<=13; i++) {
//         TableCell cell((double)i*1000/3, "+lo", "u", BLUE);
//         body.back().push_back( cell );
//       }
//     }
//     for (int k=0 ; k<1; k++) {
//       body.emplace_back();
//       for (int i=1 ; i<=13; i++) {
//         TableCell cell((float)i*100/3, "fo", "j", BLUE);
//         body.back().push_back( cell );
//       }
//     }
    //string
    for (int k=0 ; k<1; k++) {
      body.emplace_back();
      for (int i=1 ; i<=13; i++) {
        char* kk = "string";
        TableCell cell(kk, "+so", "");
        body.back().push_back( cell );
      }
    }
    for (int k=0 ; k<1; k++) {
      body.emplace_back();
      body2.emplace_back();
      for (int i=1 ; i<=13; i++) {
        std::string str = "string";
        TableCell cell(str, "+so", "");
        body.back().push_back( cell );
        body2.back().push_back( cell );
      }
    }

//     //std::cout test
//     for(auto row : body) {
//         for(size_t i = 0; i < 10; ++i)
//             std::cout << row[i] << "-" << row[i].Length() << "\t" ;
//         std::cout << "\n";
//     }
//     for(auto row : body) {
//         for(auto ro : row)
//             std::cout << ro << "-" << ro.Length() << "\t" ;
//         std::cout << "\n";
//     }
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

    //string
    std::string string = "┌──────────┬────────────────────────────────┬────────────────┬──────────┬────────────┬──────┬──────────┬────────┬────────┬────────────────┬─────┐\n│      type│                        hostport│          geotag│    status│      status│  txgw│ gw-queued│  gw-ntx│ gw-rate│  heartbeatdelta│ nofs│\n├──────────┴────────────────────────────────┴────────────────┴──────────┴────────────┴──────┴──────────┴────────┴────────┴────────────────┴─────┤\n│hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhooo\n└───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘\n";

    //table input
    test.AddRows(body);
    test.AddSeparator();
    test.AddRows(body2);
    test.AddString(string);
    test.SetHeader (header);

    std::cout << test.GenerateTable(3);

    return 0;
}
