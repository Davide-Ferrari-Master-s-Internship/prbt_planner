#include "ur10e_cmd_controller/ur10e_cmd_controller.h"


int main(int argc, char **argv) {

    ros::init(argc, argv, "ur10e_cmd_Controller");

    controller_functions cf;

    while (ros::ok()) {

        // ros::Duration(2).sleep();
        cf.spinner();
        // ros::shutdown();

    }

}
