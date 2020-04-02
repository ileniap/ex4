#include "ros/ros.h"
#include <iostream>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include "ros_motor/stepAction.h"
using namespace std;
int main (int argc, char **argv) {

	ros::init(argc, argv, "step_action_client");
	cout<<argc<<endl;
  	/*if(argc != 5){
		ROS_INFO("%d",argc);
		ROS_WARN("Usage: step_action_client <goal1> <goal2> <goal3> <goal4>");
		return 1;
	}
*/
  
  actionlib::SimpleActionClient<ros_motor::stepAction> ac("step_action", true);
  /*
  ros_motor::stepGoal goal;
  goal.qi = atoi(argv[1]);
  goal.qd = atoi(argv[2]);
  goal.wmax = atoi(argv[3]);
  goal.dtime = atoi(argv[4]);

*/
  float a; //initial_position;
  float b;	//desid
  float c; 	//wmax
  float d; //dtime
  cout<<"Insert value of initial position"<<endl;
  cin>>a;
  cout<<"qf"<<endl;
  cin>>b;
  cout<<"wmax"<<endl;
  cin>>c;
  cout<<"dtime"<<endl;
  cin>>d;
  ros_motor::stepGoal goal;
  goal.qi = a;
  goal.qd = b;
  goal.wmax = c;
  goal.dtime = d;

  ROS_INFO("Waiting for action server to start.");

  // wait for the action server to start
  ac.waitForServer(); //will wait for infinite time

  ROS_INFO("Action server started, sending goal.");

  
  ROS_INFO("Sending initial position [%f] and desidered final position [%f] with speed max= [%f] and time = [%f]",goal.qi, goal.qd, goal.wmax, goal.dtime);
  ac.sendGoal(goal);

   
  return 0;
}
