#include <ekf_bicycle_tracker/ExtendedKf.h>

ExtendedKf::ExtendedKf(const int n, const int u, const int m)
{
  A_.resize(n,n);
  B_.resize(n,u); // TODO - fault checking '0' size initialization 
  P_.resize(n,n);

  Q_.resize(m,m); // the measurement noize cov 
  R_.resize(n,n); // the process noise 

  state_vec_.resize(n); // TODO - confirm this works 
}

void ExtendedKf::setTransistionMatrix(const Eigen::MatrixXd& F)
{
  A_ = F;
}

void ExtendedKf::setMeasurementNoise(const Eigen::MatrixXd& R)
{
  R_ = R;
}

void ExtendedKf::setProcessNoise(const Eigen::MatrixXd& Q)
{
  Q_ = Q;
}

bool ExtendedKf::predict(const Eigen::VectorXd& u, Eigen::MatrixXd& pred_state)
{
  try
  {
    // the state evolution 
    state_vec_ = A_*state_vec_ + B_*u;

    // the covariance evolution 
    P_ = A_*P_*A_.transpose() + R_; // TODO - confirm Transpose()

    pred_state = state_vec_;
    
  }
  catch(std::Exception& e)
  {
    ROS_ERROR("ExtendedKf::%s",e.what());
    return false;
  }
  return true;
}


bool ExtendedKf::update(const MmntType& mmnt, Eigen::MatrixXd& state_posterior)
{

  try
  {
    Eigen::MatrixXd H = mmnt.getHMatrix(); // this will return a mmnt specific matrix 
    Eigen::MatrixXd S = (H*P_*H.transpose() + Q_).inverse();

    K_ = P_*H.transpose()*S;

    state_vec_ = state_vec_ + K_*(mmnt.getMeasurementVector() - mmnt.convertMeasurementToStateSpace(state_vec_));

    Eigen::MatrixXd I(state_vec_.rows(), state_vec_.rows());
    I.setIdentity();

    P_ = (I-K_*H)*P_;

    state_posterior = state_vec_;
  }
  catch(std::Exception& e)
  {
    ROS_ERROR("ExtendedKf%s",e.what());
    return false;
  }

  return true;
}

