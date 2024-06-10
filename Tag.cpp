
#include "Tag.h"

Tag::Tag
()
{
  this->class_name = "Tag";

  this->index = 0;
  this->tagged = NULL;
  this->comment = "";
}

Tag::~Tag
()
{
  // return;
  
  if (this->tagged != NULL) delete this->tagged;
}

Tag::Tag
(int arg_index, Person * arg_tagged, std::string arg_comment)
{
  this->index   = arg_index;
  this->tagged  = arg_tagged;
  this->comment = arg_comment;
}

Json::Value *
Tag::dump2JSON
(void)
{
  if (this->index == 0)
    {
      return (Json::Value *) NULL;
    }

  Json::Value *result_ptr = new Json::Value();
  Json::Value *jv_ptr = NULL;
  
  (*result_ptr)["index"] = this->index;

  if (this->tagged != NULL)
    {
      jv_ptr = (this->tagged)->dump2JSON();
      if (jv_ptr != NULL)
	{
	  (*result_ptr)["tagged"]  = (*jv_ptr);
	  delete jv_ptr;
	}
    }

  // The following bug, fixed, was discovered by ecs36b f2020 students!! Thanks.
  if ((this->comment).size()  != 0) // was: ( ...size() == 0)
    {
      (*result_ptr)["comment"] = this->comment;
    }

  return result_ptr;
}

void
Tag::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_TAG);

  if (((*arg_json_ptr)["comment"].isNull() == true) ||
      ((*arg_json_ptr)["comment"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TAG;
      ei_ptr->which_string = "comment";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["comment"].isNull() == true)
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
      this->comment = ((*arg_json_ptr)["comment"]).asString();
    }

  if (((*arg_json_ptr)["index"].isNull() == true) ||
      ((*arg_json_ptr)["index"].isInt() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TAG;
      ei_ptr->which_string = "index";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["index"].isNull() == true)
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
      this->index = ((*arg_json_ptr)["index"]).asInt();
    }

  if (((*arg_json_ptr)["tagged"].isNull() == true) ||
      ((*arg_json_ptr)["tagged"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TAG;
      ei_ptr->which_string = "tagged";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["tagged"].isNull() == true)
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
	  if (this->tagged == NULL)
	    {
	      this->tagged = new Person();
	    }

	  (this->tagged)->JSON2Object(&((*arg_json_ptr)["tagged"]));
	}
      catch(ecs36b_Exception& e)
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
