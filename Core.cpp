
#include "Core.h"

unsigned int Core::core_count { };

Core::Core
(void)
{
  core_count++;
  host_url = "";
  class_name = "Core";
  object_id = "";
  owner_vsID = "";
}

Core::Core
(std::string arg_host_url, std::string arg_class_name, std::string arg_object_id)
 : host_url { arg_host_url }, class_name { arg_class_name }, 
   object_id { arg_object_id }
{
  core_count++; 
  owner_vsID = "";
}

Json::Value *
Core::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  if (this->host_url != "")
    {
      (*result_ptr)["host url"]    = this->host_url;
    }
  
  (*result_ptr)["class name"]      = this->class_name;

  if (this->object_id != "")
    {
      (*result_ptr)["object id"]   = this->object_id;
    }
  
  if (this->owner_vsID != "")
    {
      (*result_ptr)["owner vsID"]  = this->owner_vsID;
    }
  return result_ptr;
}

void
Core::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_CORE;
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
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_CORE;
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

  if (((*arg_json_ptr)["host url"].isNull() == true) ||
      ((*arg_json_ptr)["host url"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_CORE;
      ei_ptr->which_string = "host url";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["host url"].isNull() == true)
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
      this->host_url = ((*arg_json_ptr)["host url"]).asString();
    }

  if (((*arg_json_ptr)["class name"].isNull() == true) ||
      ((*arg_json_ptr)["class name"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_CORE;
      ei_ptr->which_string = "class name";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["class name"].isNull() == true)
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
      this->class_name = ((*arg_json_ptr)["class name"]).asString();
    }

  if (((*arg_json_ptr)["object id"].isNull() == true) ||
      ((*arg_json_ptr)["object id"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_CORE;
      ei_ptr->which_string = "object id";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["object id"].isNull() == true)
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
      this->object_id = ((*arg_json_ptr)["object id"]).asString();
    }

  if (((*arg_json_ptr)["owner vsID"].isNull() == true) ||
      ((*arg_json_ptr)["owner vsID"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_CORE;
      ei_ptr->which_string = "owner vsID";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["owner vsID"].isNull() == true)
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
      this->owner_vsID = ((*arg_json_ptr)["owner vsID"]).asString();
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }
  
  return;
}
