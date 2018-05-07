

#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <sensor_msgs/JointState.h>
#include <visualization_msgs/Marker.h>
#include <math.h>
#include <geometry_msgs/Quaternion.h>
#include <kdl/segment.hpp>
#include <kdl/frames.hpp>
#include <kdl/joint.hpp>
#include <kdl/chain.hpp>
#include <kdl/chainfksolverpos_recursive.hpp>


ros::Publisher chatter_pub; 
//geometry_msgs::PoseStamped position_to_rviz;
double h_base,l1,l2,h_griper,h_box;

using namespace KDL;

void jointCallback(const sensor_msgs::JointState & msg)
{
  geometry_msgs::Point point;
  geometry_msgs::Pose pose;
  geometry_msgs::PoseStamped position_to_rviz;
  geometry_msgs::Quaternion quat;
   


 Segment s0 =Segment(Joint(Joint::RotZ),
                Frame(Rotation::RPY(0.0,0.0,0),
                          Vector(l1,0.0,0.0) )
                    );

 Segment s1 =Segment(Joint(Joint::RotZ),
                Frame(Rotation::RPY(0.0,0.0,0),
                          Vector(l2,0.0,0.0) )
                    );
Segment s2 =Segment(Joint(Joint::TransZ),
                Frame(Rotation::RPY(3.14,0.0,0.0),
                          Vector(0.0,0.0,(h_box+h_base)/2-h_griper) )
                    );


Chain chain1;
chain1.addSegment(s0);
chain1.addSegment(s1);
chain1.addSegment(s2);
 //quat=createQuaternionFromRPY(0, 0, 0);
 //http://orocos.org/kdl/UserManual/kinematic_solvers
 //position_to_rviz.pose.orientation=quat; 

ChainFkSolverPos_recursive fksolver(chain1);
JntArray q(3);//(chain1.getNrOfJoints());
q(0)=msg.position[0];
q(1)=msg.position[1];
q(2)=-msg.position[2];

Frame F_result;
fksolver.JntToCart(q,F_result);
//q=...


//fksolver.JntToCart(q,F_result,segment_nr);

 //position_to_rviz.pose=s.pose(l1);
position_to_rviz.header.frame_id="base_link";
	position_to_rviz.header.stamp = ros::Time::now();

	position_to_rviz.pose.position.x=F_result.p.data[0];
	position_to_rviz.pose.position.y=F_result.p.data[1];
	position_to_rviz.pose.position.z=F_result.p.data[2];

	double x, y, z, w;
	F_result.M.GetQuaternion(x, y, z, w);

	position_to_rviz.pose.orientation.x=x;
	position_to_rviz.pose.orientation.y=y;
	position_to_rviz.pose.orientation.z=z;
	position_to_rviz.pose.orientation.w=w; 

if(q(0)<0.5&&q(0)>-0.5&&q(1)<0.5&&q(1)>-0.5&&q(2)<0.099&&q(2)>-0.099){
chatter_pub.publish(position_to_rviz);
}else
{
ROS_INFO("Uwaga, przekroczono dopuszczalny zakres ruchu kdl!\n");
}
 




}

using namespace std;
int main(int argc, char **argv)
{

 
	
 ros::init(argc, argv, "NONKDL_DKIN");
     ros::NodeHandle n;
n.param<double>("l1",l1,0.6);
 n.param<double>("l2",l2,0.6);
 n.param<double>("h_base",h_base,0.6);
 n.param<double>("h_griper",h_griper,0.2);
 n.param<double>("h_box",h_box,0.2);

 chatter_pub = n.advertise<geometry_msgs::PoseStamped>("to_rviz_kdl", 1000);
 ros::Subscriber sub = n.subscribe("joint_states", 1000, jointCallback);


 //n.param<float>("l1",l1,0.6);
 //n.param<float>("l2",l2,0.6);
 //n.param<float>("h_base",h_base,0.6);
 //n.param<float>("h_gripper",h_gripper,0.2);

 ros::spin();
 return 0;
}



//https://github.com/orocos/orocos_kinematics_dynamics/blob/master/orocos_kdl/src/chainfksolvervel_recursive.hpp

//http://www.orocos.org/kdl-chains

//https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

/*

class Frame {
public:
    Vector p;       //!< origine of the Frame
    Rotation M;     //!< Orientation of the Frame



    void Rotation::GetQuaternion(double& x,double& y,double& z, double& w) const
    {
        double trace = (*this)(0,0) + (*this)(1,1) + (*this)(2,2);
        double epsilon=1E-12;
        if( trace > epsilon ){
            double s = 0.5 / sqrt(trace + 1.0);
            w = 0.25 / s;
            x = ( (*this)(2,1) - (*this)(1,2) ) * s;
            y = ( (*this)(0,2) - (*this)(2,0) ) * s;
            z = ( (*this)(1,0) - (*this)(0,1) ) * s;
        }else{
            if ( (*this)(0,0) > (*this)(1,1) && (*this)(0,0) > (*this)(2,2) ){
                double s = 2.0 * sqrt( 1.0 + (*this)(0,0) - (*this)(1,1) - (*this)(2,2));
                w = ((*this)(2,1) - (*this)(1,2) ) / s;
                x = 0.25 * s;
                y = ((*this)(0,1) + (*this)(1,0) ) / s;
                z = ((*this)(0,2) + (*this)(2,0) ) / s;
            } else if ((*this)(1,1) > (*this)(2,2)) {
                double s = 2.0 * sqrt( 1.0 + (*this)(1,1) - (*this)(0,0) - (*this)(2,2));
                w = ((*this)(0,2) - (*this)(2,0) ) / s;
                x = ((*this)(0,1) + (*this)(1,0) ) / s;
                y = 0.25 * s;
                z = ((*this)(1,2) + (*this)(2,1) ) / s;
            }else {
                double s = 2.0 * sqrt( 1.0 + (*this)(2,2) - (*this)(0,0) - (*this)(1,1) );
                w = ((*this)(1,0) - (*this)(0,1) ) / s;
                x = ((*this)(0,2) + (*this)(2,0) ) / s;
                y = ((*this)(1,2) + (*this)(2,1) ) / s;
                z = 0.25 * s;
            }
        }    
    }
*/





