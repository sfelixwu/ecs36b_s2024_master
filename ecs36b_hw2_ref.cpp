
#include "JvTime.h"
#include "GPS.h"

// high-level design of hw2 part 2
// 1. check whether we indeed have three arguments
// 2. File(s) ==> JSONs (JSON::Value) [ecs36b_JSON.cpp -- myFile2JSON() -- check whether it is a valid JSON from syntax]
// 3. Check whether the JSON is valid for HW#2
//    array, each element 2 key-value pairs, GPS_DD and Time, GPS_DD -> latitude and longitude

// JSON and C++/Java
// JSON is an intermediate representation language for objects


using namespace std;

// 4. establish some record to put the GPS info together with the timestamp
struct hw2_item
{
  GPS_DD gps;
  JvTime jvt;
};

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
  std::cout << location_jv << std::endl;
  if (rc != 0)
    {
      std::cout << "error arg1 " << rc << std::endl;
      return -1;
    }
  
  Json::Value question_jv;
  rc = myFile2JSON(argv[2], &question_jv);
  std::cout << question_jv << std::endl;
  if (rc != 0)
    {
      std::cout << "error arg2 " << rc << std::endl;
      return -1;
    }

  // step 3: process the array
  int i;
  struct hw2_item * hw2_item_array = (struct hw2_item *) NULL;
  Json::Value *jv_ptr = (Json::Value *) NULL;
  
  if (location_jv.isArray() == true)
    {
      // allocate memory for hw2_item array
      hw2_item_array = (struct hw2_item *)
	malloc(sizeof(struct hw2_item) * location_jv.size());
      
      for (i = 0; i < location_jv.size(); i++)
	{
	  // let us check if the JSON has the right content
	  if (((location_jv[i]["GPS_DD"]).isNull() != true)                &&
	      ((location_jv[i]["GPS_DD"]).isObject() == true)              &&
	      ((location_jv[i]["GPS_DD"]["latitude"]).isNull() != true)    &&
	      ((location_jv[i]["GPS_DD"]["latitude"]).isDouble() == true)  &&
	      ((location_jv[i]["GPS_DD"]["longitude"]).isNull() != true)   &&
	      ((location_jv[i]["GPS_DD"]["longitude"]).isDouble() == true) &&
	      ((location_jv[i]["Time"]).isNull() != true)                  &&
	      ((location_jv[i]["Time"]).isString() == true))
	    {
	      double lv_latitude;
	      double lv_longitude;
	      lv_latitude  = (location_jv[i]["GPS_DD"]["latitude"]).asDouble();
	      lv_longitude = (location_jv[i]["GPS_DD"]["longitude"]).asDouble();
	      // std::cout << "[" << i << "] latitude  = " << lv_latitude  << std::endl;
	      // std::cout << "[" << i << "] longitude = " << lv_longitude << std::endl;

	      GPS_DD lv_gps_object { lv_latitude, lv_longitude };
	      (hw2_item_array[i]).gps = lv_gps_object;
	      // jv_ptr = ((hw2_item_array[i]).gps).dump2JSON();
	      // std::cout << *jv_ptr << std::endl;
	      // delete jv_ptr;
	      
	      std::string time_s { (location_jv[i]["Time"]).asString() };
	      JvTime lv_jvt_object { time_s.c_str() };
	      (hw2_item_array[i]).jvt = lv_jvt_object; 
	      // jv_ptr = ((hw2_item_array[i]).jvt).dump2JSON();
	      // std::cout << *jv_ptr << std::endl;
	      // delete jv_ptr;	      
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

  // 5. handle the question
  // 5.1. correct question
  
  std::string jvt_s;
  
  if (((question_jv["Time"]).isNull() != true)    &&
      ((question_jv["Time"]).isString() == true))
    {
      jvt_s = (question_jv["Time"]).asString();
    }
  else
    {
      std::cout << "question JSON content error" << std::endl;
      return -1;
    }

  // 5.2. create a JvTime object for comparison
  JvTime jvt_question { jvt_s.c_str() };

  // now check the timestamps
  std::cout << "hw2_item_array:\n";

  // 5.3. compare every element in the array, until we found the correct element and its GPS location
  
  for (i = 0; i < location_jv.size(); i++)
    {
      std::cout << "array index = " << i << std::endl;
      
      jv_ptr = ((hw2_item_array[i]).gps).dump2JSON();
      // std::cout << *jv_ptr << std::endl;
      delete jv_ptr;
      
      jv_ptr = ((hw2_item_array[i]).jvt).dump2JSON();
      // std::cout << *jv_ptr << std::endl;
      delete jv_ptr;

      double time_diff = jvt_question - ((hw2_item_array[i]).jvt);
      std::cout << "the difference is " << time_diff << std::endl;
      
      std::cout << std::endl;
    }

  return 0;
}
