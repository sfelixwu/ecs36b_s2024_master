
#include "Personal_Timed_GPS_Record.h"

#include "ecs36b_Common.h"
#include "ecs36b_Exception.h"

#include <stdlib.h>
#include "hw3ref3client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace std;
using namespace jsonrpc;

int
main(int argc, char *argv[])
{

  // step 1
  if (argc != 3)
    {
      char arg_string[] = " <location_json> <question_json>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }

  int rc;

  // step 2: process the input
  Json::Value location_jv;
  rc = myFile2JSON(argv[1], &location_jv);
  // std::cout << location_jv << std::endl;
  if (rc != 0)
    {
      std::cout << "error arg1 " << rc << std::endl;
      return -1;
    }
  
  Json::Value question_jv;
  rc = myFile2JSON(argv[2], &question_jv);
  // std::cout << question_jv << std::endl;
  if (rc != 0)
    {
      std::cout << "error arg2 " << rc << std::endl;
      return -1;
    }

  int i;
  std::vector<Timed_Location> hw3_TL_vector;
  Json::Value *jv_ptr = (Json::Value *) NULL;

#ifdef EEE
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
	      // std::cout << "..\n";
	    }
	  else
	    {
	      std::cout << "JSON content error" << std::endl;
	      return -1;
	    }
	}
      // std::cout << "checked\n";
    }
  else
    {
      std::cout << "JSON content error" << std::endl;
      return -1;
    }

#endif /* EEE*/
  
  std::string jvt_s;
  // check question JSON
  if (((question_jv["time"]).isNull() != true)    &&
      ((question_jv["time"]).isObject() == true)  &&
      ((question_jv["identity"]).isNull() != true)    &&
      ((question_jv["identity"]).isString() == true)  &&
      ((question_jv["time"]["time"]).isNull() != true)    &&
      ((question_jv["time"]["time"]).isString() == true))
    {
      // std::cout << "checked\n";
      jvt_s = (question_jv["time"]["time"]).asString();
    }
  else
    {
      std::cout << "question JSON content error" << std::endl;
      return -1;
    }

  JvTime jvt_question { jvt_s.c_str() };

  Personal_Timed_GPS_Record *x_ptr;
  
  // now proxy object (Real object at URL)
  Shadow_Record shadow_object_1001;
  shadow_object_1001.host_url = "http://localhost:8300";
  shadow_object_1001.identity = location_jv["identity"].asString();
  
  x_ptr = &shadow_object_1001;

  // at this point ==> pointer to an PTGR object
  x_ptr->upload(location_jv);
  
  GPS_DD my_remote_answer = x_ptr->question(jvt_question);
  
  std::cout << *(my_remote_answer.dump2JSON()) << std::endl;

  return 0;
}
