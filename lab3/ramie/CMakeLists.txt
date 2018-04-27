cmake_minimum_required(VERSION 2.8.3)
project(ramie)

find_package(catkin REQUIRED COMPONENTS
geometry_msgs
  kdl_conversions
  roscpp
  rospy
  sensor_msgs
  std_msgs
  tf
  genmsg

)

generate_messages(DEPENDENCIES std_msgs)

catkin_package()

if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch)
endif()

install(DIRECTORY images meshes launch rviz urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

add_executable(parser src/parser.cpp)
 target_link_libraries(parser ${catkin_LIBRARIES})
#add_dependencies(parser turtle_generate_messages_cpp)
add_executable(non src/non.cpp)
 target_link_libraries(non ${catkin_LIBRARIES})
add_dependencies(non ramie_generate_messages_cpp)


add_executable(kdl src/kdl.cpp)
 target_link_libraries(kdl ${catkin_LIBRARIES})
add_dependencies(kdl ramie_generate_messages_cpp)




