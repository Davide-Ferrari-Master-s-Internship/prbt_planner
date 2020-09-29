#include "prbt_cmd_controller/prbt_cmd_controller.h"


int main(int argc, char **argv) {

    ros::init(argc, argv, "prbt_cmd_Controller");

    controller_functions cf;

    while (ros::ok()) {

        ros::Duration(2).sleep();
        cf.spinner();
        // ros::shutdown();

    }

}
