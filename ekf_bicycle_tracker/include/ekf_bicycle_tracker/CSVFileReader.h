#ifndef CSVFILEREADER_H
#define CSVFILEREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <ros/ros.h>

class CSVFileReader
{
private:

      inline bool file_exists (const std::string& name) {
      if (FILE *file = fopen(name.c_str(), "r")) {
                fclose(file);
                return true;
        } else {
                return false;
        }   
      }

        std::ifstream f_handle; // file handle
        typedef std::vector<std::vector<double>> CSVDATATYPE;
        //CSVDATATYPE csv_data;

        /**
        * @brief  populates the values of the key-column-num map 
        *
        * @param  std::vector<std::string> - the header row values 
        *
        * @return  void
        */
        void populate_pkey_map(std::map<std::string,int>&,std::vector<std::string>);


public:
        CSVFileReader(std::map<std::string,int>&);
        CSVFileReader();
        virtual ~CSVFileReader();

        /**
        * @brief  ** self explanatory **
        *
        * @param  std::string
        *         CSVDATATYPE* - this is to return the extracted values 
        *
        * @return  bool - returns False if reading file read to error 
        */
        bool extractData(const std::string f_name, std::vector<std::vector<double>>&, std::map<std::string,int>&);
};

#endif /* CSVFILEREADER_H */
