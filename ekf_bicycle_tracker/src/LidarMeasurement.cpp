#include <ekf_bicycle_tracker/LidarMeasurement.h>


bool LidarMeasurement::convertMeasurementToStateSpace(const Eigen::VectorXd& X, Eigen::VectorXd& output)
{
  try
  {
    output = H_*X;

  }catch(std::Exception& e) {
    ROS_INFO("LidarMeasurement - %s",e.what());
    return false;
  }

  return true;
}
  
Eigen::VectorXd LidarMeasurement::getMeasurementVector()
{
  return mmnt_vec_;
}

void LidarMeasurement::getHMatrix()
{
  return H_;
}

void LidarMeasurement::setHMatrix(const Eigen::MatrixXd H)
{
  H_ = H;
}

bool calculateJacobian(Eigen::MatrixXd& m, const Eigen::MatrixXd& s)
{
  ROS_ERROR("LidarMeasurement::calculateJacobian() NOT MEANT TO BE INVOKED FOR LIDAR");
  return false;
}
