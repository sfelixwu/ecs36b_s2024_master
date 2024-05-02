
#include "Timed_Location.h"

Timed_Location::Timed_Location()
{
  GPS_DD lv_location {0.0, 0.0};
  const char zero_str[] = "0000-00-00T00:00:00+0000";    
  JvTime lv_time { zero_str };
  
  this->location = lv_location;
  this->time = lv_time;
}

Timed_Location::Timed_Location
(GPS_DD arg_location, JvTime arg_time)
{
  this->location = arg_location;
  this->time = arg_time;
}

Json::Value *
Timed_Location::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  (*result_ptr)["location"] = (this->location).dump2JSON();
  (*result_ptr)["time"]     = (this->time).dump2JSON();
  return result_ptr;
}

void
Timed_Location::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception *lv_exception_ptr = new ecs36b_Exception();

  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_GPS_DD;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;
      ei_ptr->what_code = ECS36B_ERROR_NULL_JSON_PTR;
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
      throw (*lv_exception_ptr);
    }
  
  if ((arg_json_ptr->isNull() == true) ||
      (arg_json_ptr->isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_GPS_DD;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if (arg_json_ptr->isNull() == true)
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
      throw (*lv_exception_ptr);
    }

  if ((((*arg_json_ptr)["location"]).isNull() == true) ||
      (((*arg_json_ptr)["location"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TIMED_LOCATION;
      ei_ptr->which_string = "location";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["location"].isNull() == true)
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      try
	{
	  (this->location).JSON2Object(&((*arg_json_ptr)["location"]));
	}
      catch(ecs36b_Exception e)
	{
	  int i;
	  for (i = 0; i < (e.info_vector).size(); i++)
	    {
	      Exception_Info * ei_ptr_copy = new Exception_Info {};
	      (*ei_ptr_copy) = (*((e.info_vector)[i]));
	      (lv_exception_ptr->info_vector).push_back(ei_ptr_copy);
	    }
	  e.myDestructor();
	}
    }

  if ((((*arg_json_ptr)["time"]).isNull() == true) ||
      (((*arg_json_ptr)["time"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TIMED_LOCATION;
      ei_ptr->which_string = "time";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["time"].isNull() == true)
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      try
	{
	  (this->time).JSON2Object(&((*arg_json_ptr)["time"]));
	}
      catch(ecs36b_Exception e)
	{
	  int i;
	  for (i = 0; i < (e.info_vector).size(); i++)
	    {
	      Exception_Info * ei_ptr_copy = new Exception_Info {};
	      (*ei_ptr_copy) = (*((e.info_vector)[i]));
	      (lv_exception_ptr->info_vector).push_back(ei_ptr_copy);
	    }
	  e.myDestructor();
	}
    }
  
  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
