#include "ros/ros.h"
#include "ramie/ointservice.h"
#include <cstdlib>


#include <sstream>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>


char getch() {

        char buf = 0;
        struct termios old = {0};
        if (tcgetattr(0, &old) < 0)
                perror("tcsetattr()");
        old.c_lflag &= ~ICANON;
        old.c_lflag &= ~ECHO;
        old.c_cc[VMIN] = 1;
        old.c_cc[VTIME] = 0;
        if (tcsetattr(0, TCSANOW, &old) < 0)
                perror("tcsetattr ICANON");
        if (read(0, &buf, 1) < 0)
                perror ("read()");
        old.c_lflag |= ICANON;
        old.c_lflag |= ECHO;
        if (tcsetattr(0, TCSADRAIN, &old) < 0)
                perror ("tcsetattr ~ICANON");        
     std::system("clear");
        return (buf);
}




int main(int argc, char **argv)
{
 char pozycja;
 std::string kierunek;
 std::string x_minus="q";
 std::string x_plus="e";
 std::string y_minus="a";
 std::string y_plus="d";
 std::string z_plus="w";
 std::string z_minus="s";

 std::string time_up="u";
 std::string time_down="j";

 std::string roll_minus="r";
 std::string roll_plus="y";
 std::string yaw_minus="t";
 std::string yaw_plus="g";
 std::string pitch_plus="f";
 std::string pitch_minus="h";

 float x,y,z,roll,pitch,yaw,time;
 x=y=z=roll=pitch=yaw=time=0;


  ros::init(argc, argv, "oint_service");
  ros::NodeHandle n;
 ramie::ointservice srv;
  ros::ServiceClient client = n.serviceClient<ramie::ointservice>("oint_control_srv");


while (ros::ok())
  {
ROS_INFO("x y z roll pitch yaw time\n");
ROS_INFO("x:%f   y:%f   z:%f  roll:%f pitch:%f    yaw:%f time:%f \n",x,y,z,roll, pitch,yaw,time);
   

    pozycja=getch();

    kierunek=pozycja;
    if (kierunek ==x_plus)
	{
		x+=0.01;
	}
    else if(kierunek ==x_minus){
	x+=-0.01;
	}
    else if(kierunek ==y_plus){
	y+=0.01;
	}
   else if(kierunek ==y_minus){
	y+=-0.01;
	}
  else if(kierunek ==z_minus){
	z+=-0.01;
	}
 else if(kierunek ==z_plus){
	z+=0.01;
	}
else if(kierunek ==roll_plus){
	roll+=0.01;
	}
  else if(kierunek ==roll_minus){
	roll+=-0.01;
	}
    else if(kierunek ==yaw_plus){
	yaw+=0.01;
	}
   else if(kierunek ==yaw_minus){
	yaw+=-0.01;
	}
  else if(kierunek ==pitch_minus){
	pitch+=-0.01;
	}
 else if(kierunek ==pitch_plus){
	pitch+=0.01;
	}
 else if(kierunek ==time_up){
	time+=0.1;
	}
else if(kierunek ==time_down){
	time-=0.1;
	}

 else{
std::cin>>srv.request.type;

  srv.request.x = x;
  srv.request.y =y;
 srv.request.z = z;
  srv.request.roll = roll;
  srv.request.pitch =pitch;
 srv.request.yaw = yaw;
  srv.request.time = time;
  if (client.call(srv))
  {
    ROS_INFO("Sum: %s", srv.response.status);
  }
  else
  {
    ROS_ERROR("Failed to call service add_two_ints");
    return 1;
  }
    ros::spinOnce();
 }
}
  return 0;
}
