#ifndef LIDARMEASUREMENT_H
#define LIDARMEASUREMENT_H

#include <ekf_bicycle_tracker/MeasurementType.h>
#include <iostream>
#include <ros/ros.h>

class LidarMeasurement : public MeasurementType
{
private:
  
  Eigen::MatrixXd H_,R_;
  Eigen::VectorXd mmnt_vec_;
  int n_,u_,m_; //sizes of state-space, control vector and measurement vector 

public:
  LidarMeasurement();
  Eigen::VectorXd getMeasurementVector();
  void setMeasurementVector(const Eigen::VectorXd);

  Eigen::VectorXd convertMeasurementToStateSpace(const Eigen::VectorXd&);
  Eigen::MatrixXd calculateJacobian(const Eigen::VectorXd&);
  Eigen::MatrixXd getHMatrix(const Eigen::VectorXd&);
  void setHMatrix(const Eigen::MatrixXd);
  Eigen::MatrixXd getMeasurementNoise();

  virtual ~LidarMeasurement();


};
#endif /* LIDARMEASUREMENT_H */
