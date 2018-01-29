/*
* @author ParitoshKelkar 
*
* @version 
*
* @brief is the interface for the reader and the filter itself 
*
*/
#ifndef TRACKER_H
#define TRACKER_H

#include <ekf_bicycle_tracker/CSVFileReader.h>
#include <ekf_bicycle_tracker/ExtendedKf.h>

#include <ros/ros/.h>
#include <iostream>
#include <string>

class Tracker
{
private:
  

public:
  Tracker();
  virtual ~Tracker();

  /**
  * @brief  Uses the string to initiate the reader 
  *         Also initializes the filter - TODO - for now assume, filter 
  *         dimensions etc are known here 
  *
  * @param  std::string - the filename 
  *
  * @return 
  * 
  * @throws 
  */
  Tracker(std::string);


};

#endif /* TRACKER_H */
