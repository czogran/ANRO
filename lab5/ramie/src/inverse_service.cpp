#include "ros/ros.h"
#include "ramie/service.h"
#include "ramie/inverse.h"
#include <cstdlib>


#include <sstream>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#include <iostream>
#include <string>
#include <math.h>




#include <iostream>
#include <string>

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

void own_move( ramie::inverse &srv);

int main(int argc, char **argv)
{
 

  ros::init(argc, argv, "service");
  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<ramie::inverse>("oint_srv");
 ramie::inverse srv;
 
while (ros::ok())
  {
	     std::system("clear");
	ROS_INFO("podaj pozycje");
	//srv.request.type="poly";
	std::cin>>srv.request.type;
	 std::cin>>srv.request.a;
	  std::cin>>srv.request.b;
	 std::cin>>srv.request.c;
		   
		//own_move(srv);
	if (client.call(srv))
	  {
	    ROS_INFO("RESPONSE %s", srv.response.status.c_str());
	  }
	  else
	  {
	    ROS_ERROR("Failed to call service add_two_ints");
	    return 1;
	  }

	  
	    ros::spinOnce();
	 
}
  return 0;
}

















void own_move( ramie::inverse &srv)
{
 char pozycja;
 std::string kierunek;
 std::string joint1_left="q";
 std::string joint1_right="e";
 std::string joint2_left="a";
 std::string joint2_right="d";
 std::string griper_up="w";
 std::string griper_down="s";
 std::string time_up="u";
 std::string time_down="j";
 float j1,j2,grip,time;
 j1=j2=grip=0;



 pozycja=getch();
   	 kierunek=pozycja;
	
  if (kierunek ==joint1_right)
	{
		j1+=0.01;
	}
    else if(kierunek ==joint1_left){
	j1+=-0.01;
	}
    else if(kierunek ==joint2_right){
	j2+=0.01;
	}
   else if(kierunek ==joint2_left){
	j2+=-0.01;
	}
  else if(kierunek ==griper_up){
	grip+=-0.01;
	}
 else if(kierunek ==griper_down){
	grip+=0.01;
	}
else if(kierunek ==time_down){
	time-=0.1;
	}
else if(kierunek ==time_up){
	time+=0.1;
	}
 else{
   // ROS_INFO("type %s", srv.request.type.c_str());
//srv.request.type="poly";
 //std::cin>>srv.request.type;
  srv.request.x = j1;
  srv.request.y =j2;
 srv.request.z = grip;



}

}

