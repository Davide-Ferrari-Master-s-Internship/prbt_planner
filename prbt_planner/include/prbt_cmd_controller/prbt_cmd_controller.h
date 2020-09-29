#ifndef PRBT_CMD_CONTROLLER_H
#define PRBT_CMD_CONTROLLER_H

#include "ros/ros.h"

#include "prbt_planner/prbt_planner.h"

#include "std_msgs/Bool.h"
#include "geometry_msgs/Twist.h"
#include "geometry_msgs/Pose.h"
#include "trajectory_msgs/JointTrajectory.h"

#include "prbt_planner/PlanJointSpace.h"
#include "prbt_planner/PlanCartesianSpace.h"
#include "prbt_planner/SetPlannerParameters.h"
#include "prbt_planner/SetPlannerDynamics.h"
#include "prbt_planner/ComputeEndEffectorPosition.h"
#include "prbt_planner/GetManipulatorInfo.h"
#include "prbt_planner/GetManipulatorLinkNames.h"
#include "prbt_planner/GetManipulatorTrajectory.h"

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <time.h>
#include <math.h>


class controller_functions {

    public:

        controller_functions();
        
        void spinner();

    private:

        ros::NodeHandle nh;

        ros::ServiceClient plan_joint_space_client;
        ros::ServiceClient plan_cartesian_space_client;
        ros::ServiceClient set_planner_parameters_client;
        ros::ServiceClient set_planner_dynamics_client;
        ros::ServiceClient compute_end_effector_position_client;
        ros::ServiceClient get_manipulator_info_client;
        ros::ServiceClient get_manipulator_link_names_client;
        ros::ServiceClient get_manipulator_trajectory_client;
        
        prbt_planner::PlanJointSpace plan_joint_space_srv;
        prbt_planner::PlanCartesianSpace plan_cartesian_space_srv;
        prbt_planner::SetPlannerParameters set_planner_parameters_srv;
        prbt_planner::SetPlannerDynamics set_planner_dynamics_srv;
        prbt_planner::ComputeEndEffectorPosition compute_end_effector_position_srv;
        prbt_planner::GetManipulatorInfo get_manipulator_info_srv;
        prbt_planner::GetManipulatorLinkNames get_manipulator_link_names_srv;
        prbt_planner::GetManipulatorTrajectory get_manipulator_trajectory_srv;

        trajectory_msgs::JointTrajectory planned_trajectory;

        std::vector<double> joint_position;
        float time;

        void prbt_Planning_Request (void);
        void prbt_Plan (void);

};

#endif /* PRBT_CMD_CONTROLLER_H */