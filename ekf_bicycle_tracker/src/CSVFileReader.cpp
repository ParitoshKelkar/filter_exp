#include <coop_filter/CSVFileReader.h>

bool CSVFileReader::extractData(const std::string f_name, std::vector<std::vector<double>>& csv_data, std::map<std::string,int>& pkey_map)
{

  if (!file_exists(f_name))
  {
       ROS_ERROR("CSVFileReader:: FILE %s NOT FOUND",f_name.c_str());
       return false;
  }

  // get the header row 
  f_handle.open(f_name,std::ifstream::in);
  
  std::string row;
  std::string el;
  int row_number = 0;
  std::vector<std::string> header_row;
  while (std::getline(f_handle,row))
  { 
    std::istringstream ss(row);
    std::string column;

    
    // for every row, split into individual numbers 
    std::vector<double> temp;
    while (std::getline(ss, el, ','))
    {
      if (row_number > 0){
           temp.push_back(std::stod(el));
           //csv_data[row_number-1].push_back(std::stod(el));
           pushing_num++;}

      else
      {
         header_row.push_back(el);
      }
    }

    if (row_number == 0)
      populate_pkey_map(pkey_map,header_row);
    else
       csv_data.push_back(temp);

  }

  return true;
}


CSVFileReader::CSVFileReader(std::map<std::string,int>& pkey_map)
{
    ROS_ERROR("CSVFileReader::CONSTRUCTOR NOT IMPLEMENTED");
}

CSVFileReader::CSVFileReader()
{
}

CSVFileReader::~CSVFileReader()
{
    // perform validity checks before closing?
    f_handle.close();
}
