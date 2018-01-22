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

void CSVFileReader::populate_pkey_map(std::map<std::string,int>& param_to_col_num_map,std::vector<std::string> h_row)
{
  for (std::map<std::string,int>::iterator it_map = param_to_col_num_map.begin(); it_map!=param_to_col_num_map.end(); ++it_map)
  {
    bool header_found = false;
    for (std::vector<std::string>::iterator it_vs = h_row.begin(); it_vs!=h_row.end(); ++it_vs)
    {
      //ROS_INFO("AT FIELD %s ",it_vs->c_str());
      if (it_vs->compare(it_map->first) == 0)
        {     
          it_map->second = it_vs - h_row.begin(); // index of header 
           header_found = true; 
           //ROS_INFO("THE HEADER FIELD %s FOUND AT %d ",it_map->first.c_str(),it_map->second);
        }
    }
      if (!header_found)
              ROS_ERROR("CSVFileReader::THE HEADER FIELD %s was not found",it_map->first.c_str());
  }
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
