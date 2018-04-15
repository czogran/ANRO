cmake_minimum_required(VERSION 2.8.3)
project(ramie)

find_package(catkin REQUIRED)
catkin_package()

if(CATKIN_ENABLE_TESTING)
  find_package(roslaunch REQUIRED)
  roslaunch_add_file_check(launch)
endif()

install(DIRECTORY images meshes launch rviz urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})


add_executable(parser src/parser.cpp)
 target_link_libraries(parser ${catkin_LIBRARIES})
