#include "ur10e_cmd_controller/ur10e_cmd_controller.h"

controller_functions::controller_functions() {

    // Trajectory Publisher
    ur10e_Planned_Trajectory_publisher = nh.advertise<trajectory_msgs::JointTrajectory>("/scaled_pos_joint_traj_controller/command", 1);

    joint_position.resize(6);

}

controller_functions::~controller_functions() {

    std::terminate();

}

void controller_functions::prbt_Planning_Request (void) {

    std::cout << "\n -- Start Planning -- \n\n" << "Insert Joint Position (6 Joints):\n\n";
    std::cin >> joint_position[0];

    if (joint_position[0] == 999) {

        std::cout << "\n";
        ROS_INFO("ROS Shutdown \n");
        ros::shutdown();
        
    } else {

        std::cin >> joint_position[1] >> joint_position[2] >> joint_position[3] >> joint_position[4] >> joint_position[5];
        std::cout << "\n";

        std::cout << "Insert Movement Time: ";
        time = 1;
        std::cin >> time;
        std::cout << "\n";
            
    }
 
}

void controller_functions::prbt_Plan (void) {


    planned_trajectory.joint_names = {"shoulder_pan_joint", "shoulder_lift_joint", "elbow_joint", "wrist_1_joint", "wrist_2_joint", "wrist_3_joint"};
    planned_trajectory.points.resize(1);
    planned_trajectory.points[0].positions = {joint_position[0], joint_position[1], joint_position[2], joint_position[3], joint_position[4], joint_position[5]};
    planned_trajectory.points[0].time_from_start = ros::Duration(time);

    ROS_INFO("PRBT GOTO (%.2f;%.2f;%.2f;%.2f;%.2f;%.2f)", joint_position[0], joint_position[1], joint_position[2], joint_position[3], joint_position[4], joint_position[5]);
    ROS_INFO("Movement Time (%.2f)", time);

    ur10e_Planned_Trajectory_publisher.publish(planned_trajectory);


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
