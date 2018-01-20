#include <filter_exp/LinearKF.h>

LinearKF::LinearKF(const int n, const int u, const int m)
{
  // resize all the matrices 
  // this allocates space but doesnt initialize 
  A_.resize(n,n);
  B_.resize(n,u); // TODO - fault checking '0' size initialization 
  C_.resize(m,n);
  P_.resize(n,n);
  K_,resize(n,m); 
  Q_.resize(m,m); // the measurement noize cov 
  R_.resize(n,n); // the process noise 

}

bool LinearKF::predict(const Eigen::MatrixXd& control_vec, Eigen::VectorXd& predicted_state)
{
  // mean predict 
  predicted_state = A_*state_vec_ + B_*control_vec;

  // covariance 
  try
  {
    P_ = A_*P_*A_.transpose() + R_;
  }
  catch(std::Exception& e) {
    ROS_ERROR("LinearKF::%s",e.what);
    return false; 
  }

  return true;
}

bool LinearKF::update(const Eigen::VectorXd& mmnt_vec, Eigen::VectorXd& predicted_state)
{
  // TODO exception handling 
  try{

      // the kalman gain 
      K_ = P_*C_.transpose()*((C_*P_*C_.transpose() + Q_).inverse());

      // the new state 
      predicted_state = state_vec_ + K_*(mmnt_vec - C_*state_vec_);

      // the new state cov 
      Eigen::MatrixXd::Identity(state_vec_.rows(),state_vec_.rows());
      P_ = (I - K_*C_)*P_;

  }
  catch(std::Exception& e) {
    ROS_ERROR("LinearKF::%s",e.what());
    return false; 
  }

  return true;

}
