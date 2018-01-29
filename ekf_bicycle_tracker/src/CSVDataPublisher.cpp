#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <boost/algorithm/string.hpp>

#include <ros/ros.h>
#include <ekf_bicycle_tracker/RowData.h>

class CSVReader
{
	std::string fileName;
	std::string delimeter;

public:
	CSVReader(std::string filename, std::string delm = ",") :
			fileName(filename), delimeter(delm)
	{ }

	// Function to fetch data from a CSV File
	std::vector<std::vector<std::string> > getData();
};

/*
* Parses through csv file line by line and returns the data
* in vector of vector of strings.
*/

std::vector<std::vector<std::string> > CSVReader::getData()
{
	std::ifstream file(fileName);
 
	std::vector<std::vector<std::string> > dataList;
 
	std::string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		std::vector<std::string> vec;
		boost::algorithm::split(vec, line, boost::is_any_of(delimeter));
		dataList.push_back(vec);
	}
	// Close the File
	file.close();
 
	return dataList;
}


int main(int argc, char** argv)
{

        ros::init(argc,argv,"csv_data_publisher");
        ros::NodeHandle nh;
        ros::Publisher pub_csv_data = nh.advertise<ekf_bicycle_tracker::RowData>("/row_data",100);
        ros::Rate rate(40); //40 Hz

	// Creating an object of CSVWriter
	CSVReader reader("example.csv");

	// Get the data from CSV File
	std::vector<std::vector<std::string> > dataList = reader.getData();

	// Print the content of row by row on screen
	for(std::vector<std::string> vec : dataList)
	{

          ekf_bicycle_tracker::RowData temp;
          for(std::string data : vec)
          {
            temp.rowElements.push_back(data);
          }

          pub_csv_data.publish(temp);
          rate.sleep();

          

	}
	return 0;

}
