
#include "Holdable.h"

Holdable::Holdable
(void)
{
  this->class_name = "Holdable";
  this->holder = (Person *) NULL;
}

Holdable::~Holdable
(void)
{
  if (this->holder != (Person *) NULL)
    {
      delete this->holder;
    }
}

bool
Holdable::operator==
(Holdable another)
{
  std::cout << "Holdable::operator == was called\n";
  return ((*(this->holder) == *(another.holder)) &&
	  (((Locatable) (*this)) == ((Locatable) another)));
}

Json::Value *
Holdable::dump2JSON
(void)
{
  Json::Value * result_ptr = this->Locatable::dump2JSON();

  if (result_ptr == NULL)
    {
      result_ptr = new Json::Value();
    }
  
  if (this->holder != NULL) 
    (*result_ptr)["holder"] = *((this->holder)->dump2JSON());
  
  return result_ptr;
}

void
Holdable::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_HOLDABLE);
  
  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_HOLDABLE;
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
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_HOLDABLE;
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
      this->Locatable::JSON2Object(arg_json_ptr);
    }
  catch(ecs36b_Exception e)
    {
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }
  
  if (((*arg_json_ptr)["holder"].isNull() == true) ||
      ((*arg_json_ptr)["holder"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_HOLDABLE;
      ei_ptr->which_string = "holder";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["holder"].isNull() == true)
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
	  if (this->holder == NULL)
	    {
	      this->holder = new Person();
	    }
	  (this->holder)->JSON2Object(&((*arg_json_ptr)["holder"]));
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
