#include <ekf_bicycle_tracker/LidarMeasurement.h>


LidarMeasurement::~LidarMeasurement()
{
}

void LidarMeasurement::setMeasurementVector(const Eigen::VectorXd ip)
{

  mmnt_vec_ = ip;
}

Eigen::VectorXd LidarMeasurement::convertMeasurementToStateSpace(const Eigen::VectorXd& X)
{
  Eigen::VectorXd output;
  try
  {
    output = H_*X;

  }catch(std::exception& e) {
    ROS_INFO("LidarMeasurement - %s",e.what());
  }

  return output;
}
  
Eigen::VectorXd LidarMeasurement::getMeasurementVector()
{
  return mmnt_vec_;
}

Eigen::MatrixXd LidarMeasurement::getHMatrix(const Eigen::VectorXd& state_vec) 
{
  return H_;
}

void LidarMeasurement::setHMatrix(const Eigen::MatrixXd H)
{
  H_ = H;
}

Eigen::MatrixXd LidarMeasurement::calculateJacobian(const Eigen::VectorXd& s)
{
  ROS_ERROR("LidarMeasurement::calculateJacobian() NOT MEANT TO BE INVOKED FOR LIDAR");
  Eigen::MatrixXd r;
  return r;
}

Eigen::MatrixXd LidarMeasurement::getMeasurementNoise()
{
  return R_;
}

LidarMeasurement::LidarMeasurement()
{
  H_ .resize(2,4);
  H_<<1,0,0,0,
      0,1,0,0;
  R_.resize(2,2);
  R_.setIdentity(2,2);
}
