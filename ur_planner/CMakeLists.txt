cmake_minimum_required(VERSION 2.8.3)
project(ur_planner)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  trajectory_msgs
)

catkin_package(
  INCLUDE_DIRS include
)


include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

##################################################################################################

# Executable

add_executable(ur10e_cmd_controller_Node 
	src/ur10e_cmd_controller/ur10e_cmd_controller_Node.cpp 
	src/ur10e_cmd_controller/ur10e_cmd_controller.cpp)
target_link_libraries(ur10e_cmd_controller_Node ${catkin_LIBRARIES})
add_dependencies(ur10e_cmd_controller_Node ${catkin_EXPORTED_TARGETS} ${${PROJECT_NAME}_EXPORTED_TARGETS})

##################################################################################################
