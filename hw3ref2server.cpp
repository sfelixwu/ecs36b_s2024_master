
#include "Timed_Location.h"

#include "ecs36b_Common.h"
#include "ecs36b_Exception.h"

#include <stdlib.h>
#include "hw3ref2server.h"
#include <iostream>
#include <jsonrpccpp/server/connectors/httpserver.h>

using namespace std;
using namespace jsonrpc;

class myhw3ref2Server : public hw3ref2Server
{
public:
  myhw3ref2Server(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);

  virtual Json::Value upload(const Json::Value& location_jv);
  virtual Json::Value question(const Json::Value& question_jv);
};

myhw3ref2Server::myhw3ref2Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw3ref2Server(connector, type)
{
  std::cout << "myhw3ref2Server Object created" << std::endl;
}

std::vector<Timed_Location> hw3_TL_vector;

Json::Value
myhw3ref2Server::upload
(const Json::Value& location_jv)
{
  Json::Value result;
  
  std::cout << "upload" << " " << location_jv << std::endl;
  std::string strJson;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;

  if ((location_jv["identity"].isNull() != true) &&
      (location_jv["identity"].isString() == true) &&
      (location_jv["traces"].isNull() != true) &&
      (location_jv["traces"].isArray() == true))
    {
      for (i = 0; i < location_jv["traces"].size(); i++)
	{
	  // let us check if the JSON has the right content
	  if (((location_jv["traces"][i]["location"]).isNull() != true)                &&
	      ((location_jv["traces"][i]["location"]).isObject() == true)              &&
	      ((location_jv["traces"][i]["location"]["latitude"]).isNull() != true)    &&
	      ((location_jv["traces"][i]["location"]["latitude"]).isDouble() == true)  &&
	      ((location_jv["traces"][i]["location"]["longitude"]).isNull() != true)   &&
	      ((location_jv["traces"][i]["location"]["longitude"]).isDouble() == true) &&
	      ((location_jv["traces"][i]["time"]).isNull() != true)                    &&
	      ((location_jv["traces"][i]["time"]).isObject() == true)                  &&
	      ((location_jv["traces"][i]["time"]["time"]).isNull() != true)            &&
	      ((location_jv["traces"][i]["time"]["time"]).isString() == true))
	    {
	      double lv_latitude;
	      double lv_longitude;
	      lv_latitude  = (location_jv["traces"][i]["location"]["latitude"]).asDouble();
	      lv_longitude = (location_jv["traces"][i]["location"]["longitude"]).asDouble();
	      // std::cout << "[" << i << "] latitude  = " << lv_latitude  << std::endl;
	      // std::cout << "[" << i << "] longitude = " << lv_longitude << std::endl;

	      GPS_DD lv_gps_object { lv_latitude, lv_longitude };

	      std::string time_s { (location_jv["traces"][i]["time"]["time"]).asString() };
	      JvTime lv_jvt_object { time_s.c_str() };

	      Timed_Location lv_TL { lv_gps_object, lv_jvt_object };
	      (hw3_TL_vector).push_back(lv_TL);
	    }
	  else
	    {
	      std::cout << "JSON content error" << std::endl;
	      return -1;
	    }
	}
    }
  else
    {
      std::cout << "JSON content error" << std::endl;
      return -1;
    }

  result["status"] = "successful";
  return result;
}

Json::Value
myhw3ref2Server::question
(const Json::Value& question_jv)
{
  Json::Value result;
  
  std::cout << "question" << " " << question_jv << std::endl;
  std::string strJson;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;

  std::string jvt_s;
  
  if (((question_jv["time"]).isNull() != true)    &&
      ((question_jv["time"]).isObject() == true)  &&
      ((question_jv["identity"]).isNull() != true)    &&
      ((question_jv["identity"]).isString() == true)  &&
      ((question_jv["time"]["time"]).isNull() != true)    &&
      ((question_jv["time"]["time"]).isString() == true))
    {
      jvt_s = (question_jv["time"]["time"]).asString();
    }
  else
    {
      std::cout << "question JSON content error" << std::endl;
      return -1;
    }

  JvTime jvt_question { jvt_s.c_str() };

  std::cout << "hw3_TL_vector:\n";

  for (i = 0; i < hw3_TL_vector.size(); i++)
    {
      std::cout << "array index = " << i << std::endl;
      
      jv_ptr = (hw3_TL_vector[i]).dump2JSON();
      std::cout << *jv_ptr << std::endl;
      delete jv_ptr;

      // t1 and t2
      // t1 a later/newer timestamp than t2
      // timediff = t1 - t2;
      // if t1 is newer, then the "value" of the time should have been greater
      // if t2 is older, then the "value" of the time should have been smaller
      // (t1 - t2) is going to be a positive value
      // otherwise, it will be a negative value (in seconds).
      
      double time_diff = jvt_question - ((hw3_TL_vector[i]).time);
      std::cout << "the difference is " << time_diff << std::endl;
      std::cout << std::endl;
    }
  
  result["status"] = "successful";
  return result;
}

int
main(int argc, char *argv[])
{
  HttpServer httpserver(8300);
  myhw3ref2Server s(httpserver,
		    JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
