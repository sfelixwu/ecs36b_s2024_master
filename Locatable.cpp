
#include "Locatable.h"

Locatable::Locatable
(void)
{
  this->class_name = "Locatable";
  this->location = (GPS_DD *) NULL;
}

Locatable::~Locatable
(void)
{
  if (this->location != (GPS_DD *) NULL)
    {
      delete this->location;
    }
}

bool
Locatable::operator==
(Locatable another)
{
  // std::cout << "Locatable::operator == was called\n";
  if ((this->location == NULL) ||
      (another.location == NULL))
    {
      return false;
    }
  
  return ((*(this->location) == *(another.location)) &&
	  (((Thing) (*this)) == ((Thing) another)));
}

Json::Value *
Locatable::dump2JSON
()
{
  Json::Value * result_ptr = this->Thing::dump2JSON();

  if (result_ptr == NULL)
    {
      result_ptr = new Json::Value();
    }
  
  if (this->location != NULL)
    {
      (*result_ptr)["location"] = *((this->location)->dump2JSON());
    }

  return result_ptr;
}

void
Locatable::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
    
  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_LOCATABLE);

  try
    {
      this->Thing::JSON2Object(arg_json_ptr);
    }
  catch(ecs36b_Exception e)
    {
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }
  
  if ((((*arg_json_ptr)["location"]).isNull() == true) &&
      (((*arg_json_ptr)["location"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_LOCATABLE;
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
	  if (this->location == NULL)
	    {
	      this->location = new GPS_DD();
	    }
	  (this->location)->JSON2Object(&((*arg_json_ptr)["location"]));
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
