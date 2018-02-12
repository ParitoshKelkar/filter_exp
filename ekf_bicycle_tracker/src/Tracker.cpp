#include <ekf_bicycle_tracker/Tracker.h>

Tracker::Tracker(ros::NodeHandle nh)
{
  n = nh;
  sub_csv_data_ = n.subscribe("/csv_data",100, &Tracker::csvDataHandler,this);
}

Tracker::~Tracker()
{
}

void Tracker::csvDataHandler(const ekf_bicycle_tracker::RowData& data)
{
  std::vector<std::string> st_data = data.rowElements;

  MeasurementType *mmnt;
  LidarMeasurement l_mmnt;
  // run the propogate step of the filter - measurement independent 
  Eigen::VectorXd control_vec, state_prediction(4);
  state_prediction<<1,0,0,0,0;
  double dt = std::stod(st_data[0]) - prev_time_;
  control_vec.resize(2);
  kf_.predict(control_vec,state_prediction,dt);

  // figure out if measurement is Laser or Radar 
  std::string temp = st_data[0];
  char c = temp.at(0);
  Eigen::VectorXd mmnt_vec;

  switch(c)
  {
    case 'L':
      mmnt = new LidarMeasurement;
      mmnt_vec.resize(3);
      mmnt_vec<<std::stod(st_data[1]),std::stod(st_data[2]);
      mmnt->setMeasurementVector(mmnt_vec);
      break;

    case 'R':
      mmnt = new RadarMeasurement;
      mmnt_vec.resize(3);
      mmnt_vec<<std::stod(st_data[1]),std::stod(st_data[2]),std::stod(st_data[3]);
      mmnt->setMeasurementVector(mmnt_vec);
      break;

    default:
      ROS_ERROR("Tracker::DEFAULT SWITCH - INVLAID MEASUEMENT/PARSING");
      break;
  }

  Eigen::VectorXd updated_state(4);
  updated_state = kf_.update(mmnt);
  kf_.update(mmnt);

}
