
#include "Personal_Timed_GPS_Record.h"

#include "ecs36b_Common.h"
#include "ecs36b_Exception.h"

#include <stdlib.h>
#include "hw3ref3server.h"
#include <iostream>
#include <jsonrpccpp/server/connectors/httpserver.h>

using namespace std;
using namespace jsonrpc;

class myhw3ref3Server : public hw3ref3Server
{
public:
  myhw3ref3Server(jsonrpc::AbstractServerConnector &conn, jsonrpc::serverVersion_t type);

  virtual Json::Value upload(const Json::Value& location_jv);
  virtual Json::Value question(const Json::Value& question_jv);
  virtual Json::Value dump2json(const std::string& identity);
};

myhw3ref3Server::myhw3ref3Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw3ref3Server(connector, type)
{
  std::cout << "myhw3ref3Server Object created" << std::endl;
}

// std::map
// two columns: first, second
// first  --> a string
// second --> an PTGR object
std::map<std::string, Personal_Timed_GPS_Record> hw3_PTGR_map;

Json::Value
myhw3ref3Server::upload
(const Json::Value& location_jv)
{
  Json::Value result;

  // the following part is just for logging of information for the server
  std::cout << "upload" << " " << location_jv << std::endl;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  // above is for logginhg
  
  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;
  std::string id_str;
  Personal_Timed_GPS_Record * ptgr_ptr = NULL;
  Personal_Timed_GPS_Record ptgr_data {};
  
  if ((location_jv["identity"].isNull() != true) &&
      (location_jv["identity"].isString() == true) &&
      (location_jv["traces"].isNull() != true) &&
      (location_jv["traces"].isArray() == true))
    {
      id_str = location_jv["identity"].asString();

      // check whether the ID (id_str) exists in hw3_PTGR_map
      if (hw3_PTGR_map.find(id_str) != hw3_PTGR_map.end())
	{
	  // not equal (from the above line) ==> it exists
	  // if the key doesn't exist, it will create a new entry for that key
	  // ptgr_ptr = &(hw3_PTGR_map[id_str]);
	  // if the key doesn't exist, it won't create a new entry for that key
	  ptgr_ptr = &((hw3_PTGR_map.find(id_str))->second);
	}
      else
	{
	  ptgr_ptr = &ptgr_data;
	}

      Json::Value my_jv = location_jv;
      ptgr_ptr->JSON2Object(&my_jv);

      TL_Sort(ptgr_ptr->traces);
      std::vector<Timed_Location> * unique_ptr = NULL;
      unique_ptr = TL_Unique(ptgr_ptr->traces);
      (hw3_PTGR_map[id_str]).traces = (*unique_ptr);
      delete unique_ptr;
  
      // dump the MAP
      for (const auto& n : hw3_PTGR_map)
	{
	  std::cout << '[' << n.first << ']' << std::endl;
	  Personal_Timed_GPS_Record x = n.second;
	  Json::Value *jvp = x.dump2JSON();
	  std::cout << (*jvp) << std::endl;
	  delete jvp;
	}

      result["status"] = "successful";
    }
  else
    {
      result["status"] = "failed";
    }
  return result;
}

Json::Value
myhw3ref3Server::question
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
  std::string id_str;

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
      result["status"] = "failed";
      return result;
    }

  JvTime jvt_question { jvt_s.c_str() };
  Personal_Timed_GPS_Record * ptgr_ptr = NULL;
  GPS_DD answer {0.0, 0.0};
  
  id_str = question_jv["identity"].asString();

  if (hw3_PTGR_map.find(id_str) != hw3_PTGR_map.end())
    {
      ptgr_ptr = &((hw3_PTGR_map.find(id_str))->second);
      answer = ptgr_ptr->question(jvt_question);
      std::cout << answer.latitude << std::endl;
      std::cout << answer.longitude << std::endl;      
      result["status"] = "successful";
    }
  else
    {
      result["status"] = "failed";
    }

  return result;
}

Json::Value
myhw3ref3Server::dump2json
(const std::string& arg_identity)
{
  Json::Value result;

  std::cout << "dump2json" << " " << arg_identity << std::endl;

  time_t ticks; 
  ticks = time(NULL);
  struct std::tm * my_tm_ptr = gmtime(&ticks);

  char buffer[128];
  bzero(buffer, 128);
  std::strftime(buffer, 32, "%Y-%m-%dT%H:%M:%S", my_tm_ptr);
  printf("at %s\n", buffer);

  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;
  Personal_Timed_GPS_Record * ptgr_ptr = NULL;

  if (hw3_PTGR_map.find(arg_identity) != hw3_PTGR_map.end())
    {
      ptgr_ptr = &((hw3_PTGR_map.find(arg_identity))->second);
      jv_ptr = ptgr_ptr->dump2JSON();
      result = (*jv_ptr);
      delete jv_ptr;
    }
  else
    {
      result["status"] = "failed";
    }

  return result;
}

int
main(int argc, char *argv[])
{
  HttpServer httpserver(8300);
  myhw3ref3Server s(httpserver,
		    JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
