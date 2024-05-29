
#include "Action.h"

Action::Action(void)
{
  this->class_name = "Action";
  this->name = "";
}

Action::Action(std::string core_arg_host_url,
	       std::string core_arg_class_name, std::string core_arg_object_id,
	       std::string arg_name)
  : Core { core_arg_host_url, core_arg_class_name, core_arg_object_id }
{
  this->class_name = "Action";
  this->name = arg_name;
}

bool
Action::operator==
(Action aAction)
{
  return ((this->name) == aAction.name);
}

Json::Value *
Action::dump2JSON
(void)
{
  Json::Value * result_ptr = this->Core::dump2JSON();

  if (this->name != "")
    {
      (*result_ptr)["name"] = this->name;
      return result_ptr;
    }
  else
    {
      return (Json::Value *) NULL;
    }
}

void
Action::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_ACTION);

  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_ACTION;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;
      ei_ptr->what_code = ECS36B_ERROR_NULL_JSON_PTR;
      ei_ptr->array_index = 0;
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
      throw (*lv_exception_ptr);
    }

  if ((arg_json_ptr->isNull() == true) ||
      (arg_json_ptr->isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_ACTION;
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

      ei_ptr->array_index = 0;

      (lv_exception_ptr->info_vector).push_back(ei_ptr);
      throw (*lv_exception_ptr);
    }

  try
    {
      this->Core::JSON2Object(arg_json_ptr);
    }
  catch(ecs36b_Exception e)
    {
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }

  if (((*arg_json_ptr)["name"].isNull() == true) ||
      ((*arg_json_ptr)["name"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_ACTION;
      ei_ptr->which_string = "name";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["name"].isNull() == true)
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
      this->name = ((*arg_json_ptr)["name"]).asString();
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
