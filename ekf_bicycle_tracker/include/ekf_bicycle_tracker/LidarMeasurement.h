#ifndef LIDARMEASUREMENT_H
#define LIDARMEASUREMENT_H

#include <ekf_bicycle_tracker/MeasurementType.h>
#include <iostream>
#include <ros/ros.h>

class LidarMeasurement : MeasurementType
{
private:
  
  const Eigen::MatrixXd H_;
  int n_,u_,m_; //sizes of state-space, control vector and measurement vector 

public:
  LidarMeasurement(int, int, int);
  virtual ~LidarMeasurement();


};
#endif /* LIDARMEASUREMENT_H */
