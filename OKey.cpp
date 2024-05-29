
#include "OKey.h"

bool
OKey::operator==
(OKey aOKey)
{
  return (this->okey == aOKey.okey);
}

Json::Value *
OKey::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();

  if (this->okey != "")
    {
      (*result_ptr)["key"] = this->okey;
      return result_ptr;
    }
  else
    {
      return (Json::Value *) NULL;
    }
}

void
OKey::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_OKEY);

  if (((*arg_json_ptr)["key"].isNull() == true) ||
      ((*arg_json_ptr)["key"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_OKEY;
      ei_ptr->which_string = "key";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["key"].isNull() == true)
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
      this->okey = ((*arg_json_ptr)["key"]).asString();
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
