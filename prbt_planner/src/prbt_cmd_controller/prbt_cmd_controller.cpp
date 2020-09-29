#include "prbt_cmd_controller/prbt_cmd_controller.h"

controller_functions::controller_functions() {

    //Service Clients
    
    plan_joint_space_client = nh.serviceClient<prbt_planner::PlanJointSpace>("/prbt_planner/plan_joint_space_service");
    plan_cartesian_space_client = nh.serviceClient<prbt_planner::PlanCartesianSpace>("/prbt_planner/plan_cartesian_space_service");
    set_planner_parameters_client = nh.serviceClient<prbt_planner::SetPlannerParameters>("/prbt_planner/set_planner_parameters_service");
    set_planner_dynamics_client = nh.serviceClient<prbt_planner::SetPlannerDynamics>("/prbt_planner/set_planner_dynamics_service");
    compute_end_effector_position_client = nh.serviceClient<prbt_planner::ComputeEndEffectorPosition>("/prbt_planner/compute_end_effector_position_service");
    get_manipulator_info_client = nh.serviceClient<prbt_planner::GetManipulatorInfo>("/prbt_planner/get_manipulator_info_service");
    get_manipulator_link_names_client = nh.serviceClient<prbt_planner::GetManipulatorLinkNames>("/prbt_planner/get_manipulator_link_names_service");
    get_manipulator_trajectory_client = nh.serviceClient<prbt_planner::GetManipulatorTrajectory>("/prbt_planner/get_manipulator_trajectory_service");

    set_planner_dynamics_srv.request.v_factor = 0.5;
    set_planner_dynamics_srv.request.a_factor = 0.5;

    joint_position.resize(6);

}

void controller_functions::prbt_Planning_Request (void) {

    std::cout << "\nStart Planning [cm] \n\n" << "Insert Joint Position (6 Joints):\n\n";
    std::cin >> joint_position[0];

    if (joint_position[0] == 999) {

        std::cout << "\n";
        ROS_INFO("ROS Shutdown \n");
        ros::shutdown();
        
    } else {

        std::cin >> joint_position[1] >> joint_position[2] >> joint_position[3] >> joint_position[4] >> joint_position[5];
        std::cout << "\n";

        // std::cout << "Insert Movement Time: ";
        // time = 1;
        // std::cin >> time;

        std::cout << "Insert Velocity and Acceleration: ";
        std::cin >> set_planner_dynamics_srv.request.v_factor;
        std::cin >> set_planner_dynamics_srv.request.a_factor;
        std::cout << "\n";
    
    }
 
}

void controller_functions::prbt_Plan (void) {


    // planned_trajectory.joint_names = {"prbt_joint_1", "prbt_joint_2", "prbt_joint_3", "prbt_joint_4", "prbt_joint_5", "prbt_joint_6"};
    // planned_trajectory.points.resize(1);
    // planned_trajectory.points[0].positions = {joint_position[0], joint_position[1], joint_position[2], joint_position[3], joint_position[4], joint_position[5]};
    // planned_trajectory.points[0].time_from_start = ros::Duration(time);

    // ROS_INFO("Movement Time (%.2f)", time);

    // Setting Planner Dynamics   
    if (set_planner_dynamics_client.call(set_planner_dynamics_srv)) {ROS_INFO("Manipulator Dynamic Changed Succesfully! Velocity: %.2f Acceleration: %.2f", set_planner_dynamics_srv.request.v_factor, set_planner_dynamics_srv.request.a_factor);}
    else {ROS_ERROR("Failed to Call Service: \"SetPlannerDynamic\"");}
    
    // Calling Joint Space Planning Service
    plan_joint_space_srv.request.final_position = joint_position;
    plan_joint_space_srv.request.send = true;
    
    if (plan_joint_space_client.call(plan_joint_space_srv)) {ROS_INFO("PRBT GOTO (%.2f;%.2f;%.2f;%.2f;%.2f;%.2f)", joint_position[0], joint_position[1], joint_position[2], joint_position[3], joint_position[4], joint_position[5]);}
    else {ROS_ERROR("Failed to Call Service: \"PlanJointSpace\"");}

}


void controller_functions::spinner (void) {

    prbt_Planning_Request();

    if (ros::ok()) {

        prbt_Plan();

        std::cout << "\n\n" << "Continue Planning ? [y/n] ";
        std::string cp;
        std::cin >> cp;
        std::cout << "\n";

        if (cp == "n") {ros::shutdown();} 
    }
}
