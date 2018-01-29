#ifndef MEASUREMENTTYPE_H
#define MEASUREMENTTYPE_H

#include <ros/ros.h>
#include <iostream>
#include <string>
#include <Eigen/Dense>

class MeasurementType
{
  private:

  protected:
    Eigen::VectorXd mmnt_vec_;
    Eigen::MatrixXd H_;

  public:
    virtual MeasurementType(int,int,int);
    virtual ~MeasurementType();
  
    virtual Eigen::VectorXd getMeasurementVector() = 0;

    /**
    * @brief  ** self explanatory **
    *
    * @param  const Eigen::VectorXd& - the state space 
    *         Eigen::VectorXd& - the converted vector 
    *
    * @return bool
    * 
    * @throws Exception - regarding dimension mismatch TODO
    */
    virtual bool convertMeasurementToStateSpace(const Eigen::VectorXd&, Eigen::VectorXd&) = 0;

    /**
    * @brief  the equations of the jacobian matrix will be different from 
    *         sensor to sensor; will be precomputed and kept 
    * 
    * @param  Eigen::MatrixXd&
    *         const Eigen::VectorXd& - the state space value 
    *
    * @return bool
    * 
    * @throws Exception - An exception is thrown if the jacobian is to be 
    *                     calculated for linear mmnt sensor 
    */
    virtual bool calculateJacobian(Eigen::MatrixXd&,const Eigen::VectorXd&) = 0;


    /**
    * @brief  either returns the jacobian or returns the standard H matrix 
    *
    * @param  
    *
    * @return Eigen::MatrixXd
    * 
    * @throws Exception
    */
    virtual Eigen::MatrixXd getHMatrix() = 0;
    virtual Eigen::MatrixXd setHMatrix(const Eigen::MatrixXd) = 0;



  
};

#endif /* MEASUREMENTTYPE_H */
