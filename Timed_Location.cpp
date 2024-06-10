
#include "Timed_Location.h"

void
TL_Sort
(std::vector<Timed_Location>& arg_TL)
{
  int i, j;
  Timed_Location lv_tmp;

  std::cout << "Before SORTing\n";
  for (i = 0; i < (arg_TL.size()); i++)
    {
      Json::Value *jv_ptr = (arg_TL[i]).dump2JSON();
      std::cout << (*jv_ptr) << std::endl;
    }
  

  bool swapped;
  for (i = 0; i < (arg_TL.size() - 1); i++)
    {
      swapped = false;
      for (j = 0; j < (arg_TL.size() - i - 1); j++)
	{
	  if (arg_TL[j] > arg_TL[j + 1])
	    {
	      lv_tmp = arg_TL[j];
	      arg_TL[j] = arg_TL[j+1];
	      arg_TL[j+1] = lv_tmp;
	      swapped = true;
	      std::cout << "swapped\n";
            }
        }

        // If no two elements were swapped
        // by inner loop, then break
      if (swapped == false) break;
    }

  std::cout << "After  SORTing\n";
  for (i = 0; i < (arg_TL.size()); i++)
    {
      Json::Value *jv_ptr = (arg_TL[i]).dump2JSON();
      std::cout << (*jv_ptr) << std::endl;
    }
  
  return;
}

std::vector<Timed_Location> *
TL_Unique
(std::vector<Timed_Location>& arg_TL)
{
  std::vector<Timed_Location> * result_ptr = new std::vector<Timed_Location>;
  int i;
  
  int previous_index = 0;
  result_ptr->push_back(arg_TL[0]);

  for (i = 1; i < arg_TL.size(); i++)
    {
      if (arg_TL[i] != arg_TL[previous_index])
	{
	  result_ptr->push_back(arg_TL[i]);
	  previous_index = i;
	}
    }

  return result_ptr;
}

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

bool
Timed_Location::operator==
(Timed_Location& another)
{
  return ((this->time == another.time) &&
	  (this->location == another.location));
}

bool
Timed_Location::operator!=
(Timed_Location& another)
{
  return !((*this) == another);
}

bool
Timed_Location::operator<
(Timed_Location& another)
{
  if (this->time < another.time) return true;

  if ((this->time == another.time) &&
      (this->location < another.location))
    return true;

  return false;
}

bool
Timed_Location::operator>
(Timed_Location& another)
{
  return (((*this) != another) &&
	  (!((*this) < another)));
}

Json::Value *
Timed_Location::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  Json::Value * jv_ptr = NULL;

  jv_ptr = (this->location).dump2JSON();
  if (jv_ptr != NULL)
    {
      (*result_ptr)["location"] = (*jv_ptr);
      delete jv_ptr;
    }

  jv_ptr = (this->time).dump2JSON();
  if (jv_ptr != NULL)
    {
      (*result_ptr)["time"]     = (*jv_ptr);
      delete jv_ptr;
    }
  
  // {"location": {}, "time": {}}
  // {"location": {"latitude": 1.0, "logitude": -2.1}, "time": {"time": "..."}}
  // values: string, number, true, false, null, {}, []
  return result_ptr;
}

void
Timed_Location::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;  
  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_TIMED_LOCATION);
  
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
      
      ei_ptr->array_index = 0;

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
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
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
      
      ei_ptr->array_index = 0;

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
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }
  
  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
