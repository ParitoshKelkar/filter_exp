
/*
* @author ParitoshKelkar 
*
* @version 
*
* @brief 
*
*/
#ifndef RADARMEASUREMENT_H
#define RADARMEASUREMENT_H

#include<ekf_bicycle_tracker/MeasurementType.h>
#include <iostream>
#include<ros/ros.h>

class RadarMeasurement : public MeasurementType
{
private:

  Eigen::MatrixXd H_,R_;
  Eigen::VectorXd mmnt_vec_;
  

public:
  RadarMeasurement();
  virtual ~RadarMeasurement();

  Eigen::VectorXd getMeasurementVector();
  Eigen::VectorXd convertMeasurementToStateSpace(const Eigen::VectorXd&);
  void setHMatrix(const Eigen::MatrixXd);
  Eigen::MatrixXd getHMatrix(const Eigen::VectorXd&) const;

  Eigen::MatrixXd calculateJacobian(const Eigen::VectorXd&);
  Eigen::MatrixXd getHMatrix(const Eigen::VectorXd&);
  void setMeasurementVector(const Eigen::VectorXd);
  Eigen::MatrixXd getMeasurementNoise();
};


#endif /* RADARMEASUREMENT_H */

  

