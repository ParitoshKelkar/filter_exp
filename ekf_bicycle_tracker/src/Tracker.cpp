#include <ekf_bicycle_tracker/Tracker.h>

Tracker::Tracker(ros::NodeHandle nh)
{
  n = nh;
  sub_csv_data_.subscribe("/csv_data",100, &Tracker::csvDataHandler,this);

}


void Tracker::csvDataHandler(const ekf_bicycle_tracker::RowData& data)
{

  // run the propogate step of the filter - measurement independent 
  Eigen::VectorXd control_vec, state_prediction;
  kf_.predict(control_vec,state_prediction,dt)

  // figure out if measurement is Laser or Radar 

}
