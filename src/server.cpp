#include "ros/ros.h"
#include "std_msgs/Int32.h"
#include <actionlib/server/simple_action_server.h>
#include "ros_motor/stepAction.h"
#include <iostream>
#include <sstream>
#include <ctime>
#include "math.h"
/*    **ACTION STRUCTURE**
#Goals
float32 qi
float32 qd
float32 wmax
float32 dtime
---
#Results
float32 qf
---
#Feedback
float current_p

*/
using namespace std;
class action_class {

	private:
  	ros::NodeHandle nh_;
  	
  	actionlib::SimpleActionServer<ros_motor::stepAction> as; 
  	
		ros_motor::stepFeedback feedback;
		ros_motor::stepResult result;

  	std::string action_name;
  	int goal;
  	int progress;

	public:
		action_class(std::string name) :
  	  as(nh_, name, boost::bind(&action_class::executeCB, this, _1), false),
  	  action_name(name) {
				as.registerPreemptCallback(boost::bind(&action_class::preemptCB, this));
				as.start();
  		}
	
		void preemptCB(){
			ROS_WARN("%s got preempted!", action_name.c_str());
			result.qf = progress;
			as.setPreempted(result,"I got Preempted"); 
  	}
  
		void executeCB(const ros_motor::stepGoalConstPtr &goal) 
		{
			if(!as.isActive() || as.isPreemptRequested()) return;
			ros::Rate rate(10);
			ROS_INFO("%s is processing the goal %f", action_name.c_str(), goal->qi);
			ROS_INFO("Request data action %f , %f, %f, %f.", goal->qi, goal->qd, goal->wmax, goal->dtime);
			 
			float a;
			a=2*(goal->qd-goal->qi)/((goal->dtime)*(goal->dtime));
			
			cout<<"Uniform acceleration "<<a<<endl;
			float cur_speed=0;
			float cur_p;
			if(!as.isActive() || as.isPreemptRequested())
			{
				return;
			}	
			int current_time=1;
			//float old_q;
			
			while(progress<goal->qd)
			{
				//old_q=progress;//posizione istante precedente
				progress = goal->qi + 0.5*a*(current_time*current_time); //posizione corrente
				
				
				//cur_p=(progress)-old_q;
				cur_speed=a*current_time;
				if(cur_speed>=goal->wmax)cur_speed=goal->wmax;
				
				feedback.current_p = progress;
				as.publishFeedback(feedback);
				ROS_INFO("Current Speed %f \nCurrent position %f",cur_speed,feedback.current_p);
				current_time = current_time+1;
				
				

	                }
			if(current_time > goal->dtime){
					result.qf = progress;
					as.setAborted(result,"I failed !");
					ROS_INFO("%s Shutting down",action_name.c_str());
					
			}else{
	                
	                result.qf= progress;
			as.setSucceeded(result);
	                ROS_INFO("%s Succeeded to reach desired final position %f", action_name.c_str(), result.qf);
			rate.sleep();	              			
                	}
                }
};

int main(int argc, char** argv)
{

  ros::init(argc, argv, "step_action");
  ROS_INFO("Starting Motor Action Server");
  action_class step_action_obj(ros::this_node::getName());
  ros::spin();
  return 0;
}
