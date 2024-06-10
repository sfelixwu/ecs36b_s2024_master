
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
  // return;
  if (this->home != NULL)
    {
      // printf("destruct home = %p\n", this->home);
      // Json::Value *jp = (this->home)->dump2JSON();
      // if (jp != NULL)
      //	{
      //	  std::cout << (*jp) << std::endl;
      //  printf("jp = %p\n", jp);
      //  delete jp;
      //}
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
(Person& aPerson)
// (Person& aPerson)
// (Person * aPerson)
{
  printf("MMMMMM Person::operator==\n");
  return (this->vsID == aPerson.getvsID());

  // return ((this->vsID == aPerson.getvsID()) &&
  // 	     (this->name == aPerson.getName());
}

Json::Value *
Person::dump2JSON
()
{
  // printf("Person dump2JSON start\n");

  if ((this->name == "") &&
      (this->vsID == "") &&
      (this->home == NULL))
    {
      // printf("Person dump2JSON start empty here\n");
      return NULL;
    }
  
  Json::Value * result_ptr = new Json::Value();

  // printf("Person dump2JSON name\n");
  if (this->name != "")
    {
      (*result_ptr)["name"] = this->name;
    }

  // printf("Person dump2JSON vsID\n");
  if (this->vsID != "")
    {
      (*result_ptr)["vsID"] = this->vsID;
    }

  // printf("Person dump2JSON home %p\n", this->home);
  if (this->home != NULL)
    {
      // fflush(stdout);
      // printf("Person dump2JSON home 1 %p\n", this->home);
      
      Json::Value *jv_ptr = (this->home)->dump2JSON();
      
      // debug line -- Json::Value *jv_ptr = (this->home)->GPS_DD::dump2JSON();
      // printf("Person dump2JSON home 2 %p\n", jv_ptr);
      // std::cout << (*jv_ptr) << std::endl;
      
      if (jv_ptr != NULL)
	{
	  (*result_ptr)["home"] = *jv_ptr;
	  delete jv_ptr;
	}
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

  // printf("Person Here 1\n");
  // std::cout << (*arg_json_ptr) << std::endl;
  
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
	  // printf("Person Here 2\n");
	  // std::cout << (*arg_json_ptr)["home"] << std::endl;
	  (this->home)->JSON2Object(&((*arg_json_ptr)["home"]));
	}
      catch(ecs36b_Exception& e)
	{
	  // printf("Person Home exp\n");
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
      // Json::Value * jvtmp_ptr = (this->home)->dump2JSON();
      // printf("Person Home dump2JSON %p %p\n", this->home, jvtmp_ptr);
      // if (jvtmp_ptr != NULL)
      // {
      //  std::cout << (*jvtmp_ptr) << std::endl;
      //  delete jvtmp_ptr;
      // }
    }

  // printf("Person Here 3\n");
  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      // printf("Person Here 3.1\n");
      throw (*lv_exception_ptr);
    }

  // printf("Person Here 4\n");
  return;
}

