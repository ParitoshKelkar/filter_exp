#include <ekf_bicycle_tracker/RadarMeasurement.h>

Eigen::MatrixXd RadarMeasurement::calculateJacobian(const Eigen::VectorXd& x_state) {

  Eigen::MatrixXd Hj(3,4);

    //recover state parameters
    float px = x_state(0,1);
    float py = x_state(1,1);
    float vx = x_state(2,1);
    float vy = x_state(3,1);

    //pre-compute a set of terms to avoid repeated calculation
    float c1 = px*px+py*py;
    float c2 = sqrt(c1);
    float c3 = (c1*c2);

    //check division by zero
    if(fabs(c1) < 0.0001){
      std::cout << "CalculateJacobian () - Error - Division by Zero";
            return Hj;
    }

    //compute the Jacobian matrix
    Hj << (px/c2), (py/c2), 0, 0,
              -(py/c1), (px/c1), 0, 0,
              py*(vx*py - vy*px)/c3, px*(px*vy - py*vx)/c3, px/c2, py/c2;
    return Hj;

}

Eigen::MatrixXd RadarMeasurement::getMeasurementNoise()
{
  return R_;
}

void RadarMeasurement::setMeasurementVector(const Eigen::VectorXd data)
{

}

Eigen::MatrixXd RadarMeasurement::getHMatrix(const Eigen::VectorXd& state_vec)
{
  H_ =  calculateJacobian(state_vec);
  return H_;
}

RadarMeasurement::RadarMeasurement()
{
  H_.resize(3,4);
  R_.resize(3,3); R_.setIdentity(3,3);

}

RadarMeasurement::~RadarMeasurement()
{}


Eigen::VectorXd RadarMeasurement::convertMeasurementToStateSpace(const Eigen::VectorXd& mmnt)
{
  Eigen::VectorXd temp(4);
  return temp;

}

void RadarMeasurement::setHMatrix(const Eigen::MatrixXd mat)
{

}

Eigen::VectorXd RadarMeasurement::getMeasurementVector()
{
  return mmnt_vec_;
}

