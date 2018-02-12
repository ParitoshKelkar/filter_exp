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
#include <ekf_bicycle_tracker/RowData.h>
#include <ekf_bicycle_tracker/LidarMeasurement.h>
#include <ekf_bicycle_tracker/RadarMeasurement.h>


#include <ros/ros.h>
#include <iostream>
#include <string>


class Tracker
{
private:

  ros::Subscriber sub_csv_data_;
  ExtendedKf kf_;
  double prev_time_;

  ros::NodeHandle n;
  

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


  /**
  * @brief  passes the nodehandle to be able to subscribe/publish etc
  *
  * @param  ros::NodeHandle
  *
  * @return 
  * 
  * @throws Exception
  */
  Tracker(ros::NodeHandle);


  /**
  * @brief  calls the filter within it 
  *
  * @param  const ekf_bicycle_tracker::RowData&
  *
  * @return void
  * 
  * @throws Exception
  */
  void csvDataHandler(const ekf_bicycle_tracker::RowData&);


};

#endif /* TRACKER_H */
