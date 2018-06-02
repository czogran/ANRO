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
  message_generation
)
add_service_files(
  FILES
  service.srv
 ointservice.srv
 inverse.srv
 invser.srv
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

add_executable(int src/int.cpp)
 target_link_libraries(int ${catkin_LIBRARIES})
add_dependencies(int ramie_generate_messages_cpp)

add_executable(control src/control.cpp)
 target_link_libraries(control ${catkin_LIBRARIES})
add_dependencies(control ramie_generate_messages_cpp)

add_executable(jint src/jint.cpp)
 target_link_libraries(jint ${catkin_LIBRARIES})
add_dependencies(jint ramie_generate_messages_cpp)

add_executable(oint_service src/oint_service.cpp)
 target_link_libraries(oint_service ${catkin_LIBRARIES})
add_dependencies(oint_service ramie_generate_messages_cpp)

add_executable(oint src/oint.cpp)
 target_link_libraries(oint ${catkin_LIBRARIES})
add_dependencies(oint ramie_generate_messages_cpp)


add_executable(inverse1 src/inverse1.cpp)
 target_link_libraries(inverse1 ${catkin_LIBRARIES})
add_dependencies(inverse1 ramie_generate_messages_cpp)

add_executable(inverse_service src/inverse_service.cpp)
 target_link_libraries(inverse_service ${catkin_LIBRARIES})
add_dependencies(inverse_service ramie_generate_messages_cpp)


add_executable(lab5_oint src/lab5_oint.cpp)
 target_link_libraries(lab5_oint ${catkin_LIBRARIES})
add_dependencies(lab5_oint ramie_generate_messages_cpp)



