#ifndef EXTENDEDKF_H
#define EXTENDEDKF_H

#include <ros/ros.h>
#include <iostream>
#include <string>
#include <Eigen/Dense>
#include <exception>

// custom 
#include <ekf_bicycle_tracker/MeasurementType.h>

class ExtendedKf
{
private:

  Eigen::MatrixXd A_,B_,Q_,R_,P_,K_;
  Eigen::VectorXd state_vec_;

public:
  ExtendedKf(const int,const int,const int);
  virtual ~ExtendedKf();

  /**
  * @brief  ** self explanatory **
  *
  * @param  const Eigen::MatrixXd& - the transistion matrix 
  *
  * @return  void
  */
  void setTransistionMatrix(const Eigen::MatrixXd&);
  void setProcessNoise(const Eigen::MatrixXd&);
  void setMeasurementNoise(const Eigen::MatrixXd&);

  /**
  * @brief  ** self explanatory **
  *
  * @param  const Eigen::VectorXd& - the control vector; will be used only if necessary
  *                                  variables are set
  *         Eigen::MatrixXd& - to return the state after prediction 
  *
  * @return  bool
  * 
  * @throws Exception
  */
  bool predict(const Eigen::VectorXd&, Eigen::MatrixXd&,double dt);


  /**
  * @brief  ** self explanatory **
  *
  * @param  const MmntType&
  *         Eigen::MatrixXd&
  *
  * @return  bool
  * 
  * @throws Exception
  */
  // TODO - the apppropriate namespace 
  bool update(const MmntType&, Eigen::MatrixXd&);



};

#endif /* EXTENDEDKF_H */
