
#include "Person.h"

Person::Person(std::string arg_vsID, std::string arg_name)
{
  this->class_name = "Person";
  this->vsID = arg_vsID;
  this->name = arg_name;
  this->home = NULL;
}

Person::Person(std::string arg_vsID, std::string arg_name, GPS_DD * arg_home_ptr)
{
  this->class_name = "Person";
  this->vsID = arg_vsID;
  this->name = arg_name;
  // was: this->home = arg_home_ptr;
  this->home = new GPS_DD { arg_home_ptr->latitude, arg_home_ptr->longitude };

}

Person::Person()
{
  this->class_name = "Person";
  this->vsID = "";
  this->name = "";
  this->home = NULL;
}

Person::~Person()
{
  if (this->home != NULL)
    {
      delete this->home;
    }
}

void
Person::setHome
(GPS_DD * arg_home_ptr)
{
  // was: this->home = arg_home_ptr;
  this->home = new GPS_DD { arg_home_ptr->latitude, arg_home_ptr->longitude };
}

GPS_DD *
Person::getHome
(void)
{
  return this->home;
}

std::string
Person::getvsID()
{
  return this->vsID;
}

std::string
Person::getName()
{
  return this->name;
}

// function prototype
bool
Person::operator==
(Person aPerson)
// (Person& aPerson)
// (Person * aPerson)
{
  printf("Person::operator==\n");
  return (this->vsID == aPerson.getvsID());

  // return ((this->vsID == aPerson.getvsID()) &&
  // 	     (this->name == aPerson.getName());
}

Json::Value *
Person::dump2JSON
()
{
  Json::Value * result_ptr = new Json::Value();
  
  if (this->name != "")
    {
      (*result_ptr)["name"] = this->name;
    }

  if (this->vsID != "")
    {
      (*result_ptr)["vsID"] = this->vsID;
    }

  if (this->home != NULL)
    {
      Json::Value *jv_ptr = (this->home)->dump2JSON();
      if (jv_ptr != NULL)
	{
	  (*result_ptr)["home"] = *jv_ptr;
	}
      delete jv_ptr;
    }

  return result_ptr;
}

void
Person::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;

  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_PERSON);
    
  if (((*arg_json_ptr)["vsID"].isNull() == true) ||
      ((*arg_json_ptr)["vsID"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_PERSON;
      ei_ptr->which_string = "vsID";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["vsID"].isNull() == true)
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
      this->vsID = ((*arg_json_ptr)["vsID"]).asString();
    }

  if (((*arg_json_ptr)["name"].isNull() == true) ||
      ((*arg_json_ptr)["name"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_PERSON;
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

  if ((((*arg_json_ptr)["home"]).isNull() == true) &&
      (((*arg_json_ptr)["home"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_PERSON;
      ei_ptr->which_string = "home";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["home"].isNull() == true)
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
	  if (this->home == NULL)
	    {
	      this->home = new GPS_DD();
	    }
	  (this->home)->JSON2Object(&((*arg_json_ptr)["home"]));
	}
      catch(ecs36b_Exception e)
	{
	  printf("Person Home exp\n");
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}

