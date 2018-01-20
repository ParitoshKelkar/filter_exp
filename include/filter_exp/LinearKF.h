#ifndef LINEARKF_H
#define LINEARKF_H

#include <ros/ros.h>
#include <iostream>
#include <Eigen/Dense>

class LinearKF
{
private:

     Eigen::VectorXd state_vec_;
     Eigen::MatrixXd A_, B_, C_, K_, P_;
     Eigen::MatrixXd R_, Q_;
        

public:
        LinearKF();
        virtual ~LinearKF();


        /**
        * @brief  constructor taking in initializing params 
        *
        * @param  int - state vector size 
        *       : int - control vector size 
        *       : int - mmnt vector size 
        *
        * @return  
        */
        LinearKF(const int, const int,const int);

        /**
        * @brief  ** self explanatory **
        *
        * @param  const Eigen::MatrixXd&
        *
        * @return  void
        */
        void setStateTransitionMatrix(const Eigen::MatrixXd&);
        void setMeasurementMatrix(const Eigen::MatrixXd&);

        /*
         *Assume these are time independent for now. 
         *TODO - integrate better noise estimates 
         */
        void setProcessNoise(const Eigen::MatrixXd&); 
        void setMeasurementNoise(const Eigen::MatrixXd); 


        /**
        * @brief  ** self explanatory **
        *
        * @param  const Eigen::MatrixXd - the control Matrix 
        *         const Eigen::VectorXd& - the predicted state vector 
        *
        * @return  bool
        *
        * @throws std::Exception - matrix 
        */
        bool predict(const Eigen::MatrixXd&, Eigen::VectorXd&);


        /**
        * @brief  ** self explanatory **
        *
        * @param  const Eigen::VectorXd&
        *         Eigen::MatrixXd&
        *
        * @return  bool
        */
        bool update(const Eigen::VectorXd&, Eigen::MatrixXd&);



};

#endif /* LINEARKF_H */

