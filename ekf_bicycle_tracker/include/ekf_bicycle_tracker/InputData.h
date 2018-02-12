/*
* @author ParitoshKelkar 
*
* @version 
*
* @brief an object of this class holds all the data that is provided in the csv file - it will be broken up into ego vehicle values, measurements and ground truth
*
*/


#ifndef INPUTDATA_H
#define INPUTDATA_H

#include <iostream>

#include <ros/ros.h>
#include <ekf_bicycle_tracker/LidarMeasurement.h>
#include <ekf_bicycle_tracker/RadarMeasurement.h>

struct InertialData
{
  double x,y;
  double vx, vy;
};

class InputData
{
private:

  MeasurementType* mmnt_data;
  InertialData inertial_data_;
  double timestamp;


public:
  InputData();
  virtual ~InputData();


  /**
  * @brief  ** self explanatory **
  *
  * @param  const ekf_bicycle_tracker::RowData&
  *
  * @return InputData - TODO value or ref
  * 
  * @throws Exception
  */
  InputData parse(const ekf_bicycle_tracker::RowData&);


};

#endif /* INPUTDATA_H */
