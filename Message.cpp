
#include "Message.h"

Message::Message
(void)
{
  this->class_name = "Message";

  this->content = "";
}

Message::Message(std::string arg_s)
{
  this->class_name = "Message";

  this->content = arg_s;
}

void
Message::setContent
(std::string arg_s)
{
  this->content = arg_s;  
}

std::string
Message::getContent
(void)
{
  return this->content;
}
  
Json::Value *
Message::dump2JSON
(void)
{
  if (this->content != "")
    {
      Json::Value *result_ptr = new Json::Value();
      (*result_ptr)["content"] = this->content;
      return result_ptr;
    }
  else
    {
      return (Json::Value *) NULL;
    }
}

void
Message::JSON2Object
(Json::Value *arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_MESSAGE);

  if (((*arg_json_ptr)["content"].isNull() == true) ||
      ((*arg_json_ptr)["content"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_MESSAGE;
      ei_ptr->which_string = "content";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["content"].isNull() == true)
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
      this->content = ((*arg_json_ptr)["content"]).asString();
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
