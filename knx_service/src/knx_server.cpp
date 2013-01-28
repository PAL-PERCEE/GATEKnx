#include "ros/ros.h"
#include "knx_service/KnxSet.h"

#include <stdio.h>
#include <stdlib.h>


/*SET SEND*/
std::string sendKNX(std::string target, int value){

 std::ostringstream os;
 std::stringstream CMD;
 std::string cmd_c;

 int state;
 char hex[3]="";

        if(strcmp(target.c_str(),"1/7/1")==0 || strcmp(target.c_str(),"1/7/3")==0){
	sprintf(hex,"%x",value);
	CMD<<"/usr/bin/groupwrite ip:192.168.0.12 "<<target<<" "<<hex;
	//std::cout<<hex<<"\n";
	}
	else
	CMD<<"/usr/bin/groupswrite ip:192.168.0.12 "<<target<<" "<<value;

	cmd_c = CMD.str();

	state = system(cmd_c.c_str());
	if(state == 0)	
	os<<"ok";
	else
	os<<"ko";



return os.str() ;
}
/*GET VAL*/
std::string getKNX(std::string target){

 std::ostringstream os;
 std::stringstream CMD;
 std::string cmd_c;

//char dec[6]="";

	CMD<<"/usr/bin/groupreadresponse_ros ip:192.168.0.12 "<<target;
	cmd_c = CMD.str();

	/*state = system(cmd_c.c_str());
	if(state == 0)	
	os<<"ok";
	else
	os<<"ko";*/


  FILE *output = popen(cmd_c.c_str(), "r");

  if (!output)
  {
	os<<"ko";
    return os.str();
  }

  char buffer[3];
  char *line_p = fgets(buffer, sizeof(buffer), output);
  pclose(output);

  //sprintf(dec,"%x",line_p);
  //os<<dec;
  os<<line_p;



return os.str();
}



bool setknxval(knx_service::KnxSet::Request  &req,
         knx_service::KnxSet::Response &res )
{

  if(strcmp(req.action.c_str(),"set")==0){
  ros::Time tstart = ros::Time::now();
  res.etat = sendKNX(req.target.c_str(),(int)req.value);
  ROS_INFO("Action: %s, Target: %s, Value: %d", req.action.c_str() ,req.target.c_str(),(int)req.value);
  ROS_INFO("sending back response: [Etat: %s]", res.etat.c_str());
  	//TEMPS D'EXECUTION
	ros::Time tfin = ros::Time::now();
	ros::Duration def = tfin - tstart;
	ROS_INFO("Temps d'exec %ds, %dns",def.sec, def.nsec);
  }
  else if(strcmp(req.action.c_str(),"get")==0){
	ros::Time tstart = ros::Time::now();
  res.xml = getKNX(req.target.c_str());
  ROS_INFO("Action: %s, Target: %s", req.action.c_str() ,req.target.c_str());
  ROS_INFO("sending back response: [Value: %s]", res.xml.c_str());
	  	//TEMPS D'EXECUTION
	ros::Time tfin = ros::Time::now();
	ros::Duration def = tfin - tstart;
	ROS_INFO("Temps d'exec %ds, %dns",def.sec, def.nsec);
  }

  return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "MADYNEGate_KnxServerNode");
  ros::NodeHandle n;

  ros::ServiceServer service = n.advertiseService("MADYNEGate/KnxServerNode/KnxAPI", setknxval);
  ROS_INFO("Ready to action ..");
  ros::spin();

  return 0;
}
