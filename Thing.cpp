
#include "Thing.h"

Thing::Thing
(void)
{
  this->class_name = "Thing";
  this->url = "";
  this->model = "";
  this->description = "";
  this->sequence_num = 0;
}

bool
Thing::operator==
(Thing another)
{
  // std::cout << "Thing::operator == was called\n";
  return ((this->sequence_num == another.sequence_num) &&
	  (this->url == another.url) &&
	  (this->model == another.model) &&
	  (this->description == another.description));
}

Json::Value *
Thing::dump2JSON
()
{
  Json::Value * result_ptr = this->Core::dump2JSON();
  
  if (this->sequence_num != 0)
    {
      (*result_ptr)["sequence num"] = this->sequence_num;
    }

  if (this->url != "")
    {
      (*result_ptr)["url"] = this->url;
    }

  if (this->model != "")
    {
      (*result_ptr)["model"] = this->model;
    }

  if (this->description != "")
    {
      (*result_ptr)["description"] = this->description;
    }

  return result_ptr;
}

void
Thing::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  
  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_THING);
  
  try
    {
      this->Core::JSON2Object(arg_json_ptr);
    }
  catch(ecs36b_Exception e)
    {
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }
  
  // "url"
  if (((*arg_json_ptr)["url"].isNull() == true) ||
      ((*arg_json_ptr)["url"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_THING;
      ei_ptr->which_string = "url";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["url"].isNull() == true)
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
      this->url = ((*arg_json_ptr)["url"]).asString();
    }

  // "model"
  if (((*arg_json_ptr)["model"].isNull() == true) ||
      ((*arg_json_ptr)["model"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_THING;
      ei_ptr->which_string = "model";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["model"].isNull() == true)
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
      this->model = ((*arg_json_ptr)["model"]).asString();
    }

  // "description"
  if (((*arg_json_ptr)["description"].isNull() == true) ||
      ((*arg_json_ptr)["description"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_THING;
      ei_ptr->which_string = "description";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["description"].isNull() == true)
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
      this->description = ((*arg_json_ptr)["description"]).asString();
    }

  // "sequence num"
  if (((*arg_json_ptr)["sequence num"].isNull() == true) ||
      ((*arg_json_ptr)["sequence num"].isInt() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_THING;
      ei_ptr->which_string = "sequence num";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["sequence num"].isNull() == true)
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
      this->sequence_num = ((*arg_json_ptr)["sequence num"]).asInt();
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}

