#include <ekf_bicycle_tracker/ExtendedKf.h>


ExtendedKf::ExtendedKf()
{
  int n = 4; // x,y,px,py
  int u = 0;
  A_.setIdentity(n,n);
  B_.setIdentity(n,u); // TODO - fault checking '0' size initialization 
  P_.setIdentity(n,n);

  Q_.setIdentity(n,n); // the process noise 

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

void ExtendedKf::predict(const Eigen::VectorXd& u, Eigen::VectorXd& pred_state, double dt)
{
  try
  {
    // the state evolution 
    A_(0,2) = dt; A_(1,3) = dt;
    state_vec_ = A_*state_vec_ + B_*u;

    // the covariance evolution 
    P_ = A_*P_*A_.transpose() + Q_; // TODO - confirm Transpose()

    pred_state = state_vec_;
    
  }
  catch(std::exception& e)
  {
    ROS_ERROR("ExtendedKf::%s",e.what());
    return;
  }
  return;
}


Eigen::VectorXd ExtendedKf::update(MmntType *mmnt)
{

  Eigen::VectorXd state_posterior(5);

  try
  {
    Eigen::MatrixXd H = mmnt->getHMatrix(state_vec_); // this will return a mmnt specific matrix 
    Eigen::MatrixXd R = mmnt->getMeasurementNoise();
    Eigen::MatrixXd S = (H*P_*H.transpose() + R).inverse();

    K_ = P_*H.transpose()*S;


    Eigen::VectorXd inno = mmnt->getMeasurementVector() - mmnt->convertMeasurementToStateSpace(state_vec_);

    state_vec_ = state_vec_ + K_*inno;

    Eigen::MatrixXd I(state_vec_.rows(), state_vec_.rows());
    I.setIdentity();

    P_ = (I-K_*H)*P_;

    state_posterior = state_vec_;
  }
  catch(std::exception& e)
  {
    ROS_ERROR("ExtendedKf%s",e.what());
  }

  return state_posterior;
}

ExtendedKf::~ExtendedKf()
{}

