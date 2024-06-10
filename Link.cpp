
#include "Link.h"

Link::Link
(void)
{
  this->class_name = "Link";
  this->url = "";
}

Link::Link
(std::string arg_url)
{
  this->class_name = "Link";
  this->url = arg_url;
}

bool
Link::operator==
(Link& aLink)
{
  return (this->url == aLink.url);
}

Json::Value *
Link::dump2JSON
(void)
{
  Json::Value * result_ptr = this->Core::dump2JSON();

  if (result_ptr != NULL)
    {
      // printf("Link dump2JSON from Core --\n");
      // std::cout << (*result_ptr) << std::endl;
    }
  else
    {
      if (this->url != "")
	{
	  result_ptr = new Json::Value ();
	}
      else
	{
	  return NULL;
	}
    }
  
  if (this->url != "")
    {
      (*result_ptr)["url"] = this->url;
      return result_ptr;
    }
  else
    {
      if (result_ptr != NULL) delete result_ptr;
      return (Json::Value *) NULL;
    }
}

void
Link::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_LINK);

  try
    {
      this->Core::JSON2Object(arg_json_ptr);
    }
  catch(ecs36b_Exception& e)
    {
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }
  
  if (((*arg_json_ptr)["url"].isNull() == true) ||
      ((*arg_json_ptr)["url"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_LINK;
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
      (lv_exception_ptr->info_vector).push_back(ei_ptr);
    }
  else
    {
      this->url = ((*arg_json_ptr)["url"]).asString();
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
