#ifndef UR10E_CMD_CONTROLLER_H
#define UR10E_CMD_CONTROLLER_H

#include "ros/ros.h"

#include "trajectory_msgs/JointTrajectory.h"



class controller_functions {

    public:

        controller_functions();
        ~controller_functions();
        
        void spinner();

    private:

        ros::NodeHandle nh;
        ros::Publisher ur10e_Planned_Trajectory_publisher;

        trajectory_msgs::JointTrajectory planned_trajectory;

        std::vector<double> joint_position;
        float time;

        void prbt_Planning_Request (void);
        void prbt_Plan (void);

};

#endif /* UR10E_CMD_CONTROLLER_H */