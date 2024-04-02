#include "Team.h"

Team::Team
(void)
{
  this->class_name = "Team";
  this->members = NULL;
}

bool
Team::setName
(const std::string& _n)
{
  this->name = _n;
  return true;
}

bool
Team::addAMember
(Person *_p)
{
  if (this->members == NULL)
    {
      this->members = new vector<Person *>();
    }
  (this->members)->push_back(_p);
  return true;
}

Json::Value *
Team::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();

  (*result_ptr)["class name"] = this->class_name;
  (*result_ptr)["name"] = this->name;

  if (this->members == NULL)
    {
      this->members = new vector<Person *>();
    }

  Json::Value an_jv_array;
  int i = 0;
  for (i = 0; i < (this->members)->size(); i++)
    {
      an_jv_array[i] = ((*(this->members))[i])->dump2JSON();
    }
  (*result_ptr)["members"]["data"] = an_jv_array;
  (*result_ptr)["members"]["count"] = ((unsigned int) (this->members)->size());
  
  return result_ptr;
}

void
Team::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception lv_exception {};

  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TEAM;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;
      ei_ptr->what_code = ECS36B_ERROR_NULL_JSON_PTR;
      (lv_exception.info_vector).push_back(ei_ptr);
      throw lv_exception;
    }

  if ((arg_json_ptr->isNull() == true) ||
      (arg_json_ptr->isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TEAM;
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
      (lv_exception.info_vector).push_back(ei_ptr);
      throw lv_exception;
    }

  if (((*arg_json_ptr)["name"].isNull() == true) ||
      ((*arg_json_ptr)["name"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TEAM;
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
      (lv_exception.info_vector).push_back(ei_ptr);
    }
  else
    {
      this->name = ((*arg_json_ptr)["name"]).asString();
    }

  // "members"
  if ((((*arg_json_ptr)["members"]).isNull() == true) ||
      (((*arg_json_ptr)["members"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TEAM;
      ei_ptr->which_string = "members";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["members"].isNull() == true)
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      (lv_exception.info_vector).push_back(ei_ptr);
    }
  else
    {
      if ((((*arg_json_ptr)["members"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["members"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_TEAM;
	  ei_ptr->which_string = "members::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["members"]["data"]).isNull() == true)
	    {
	      ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	    }
	  else
	    {
	      ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	    }
	  (lv_exception.info_vector).push_back(ei_ptr);
	}
      else
	{
	  if (this->members == NULL)
	    {
	      this->members = new vector<Person *>();
	    }

	  int j;
	  for (j = 0; j < ((*arg_json_ptr)["members"]["data"]).size(); j++)
	    {
	      Json::Value l_jv_member = (*arg_json_ptr)["members"]["data"][j];
	      Person *l_member_ptr = new Person();
	      try
		{
		  l_member_ptr->JSON2Object(&(l_jv_member));

		  // now check if the reaction already exist
		  int flag_mb = 0;
		  vector<Person *>::iterator my_it_mb;
		  for (my_it_mb = (*(this->members)).begin();
		       my_it_mb < (*(this->members)).end(); my_it_mb++)
		    {
		      // operator== for Person
		      if ((*(*my_it_mb)) == (*(l_member_ptr)))
			{
			  flag_mb = 1;
			}
		    }

		  if (flag_mb == 0)
		    {
		      (*(this->members)).push_back(l_member_ptr);
		    }
		  else
		    {
		      delete l_member_ptr;
		    }
		}
	      catch(ecs36b_Exception e)
		{
		  int i;
		  for (i = 0; i < (e.info_vector).size(); i++)
		    {
		      (lv_exception.info_vector).push_back((e.info_vector)[i]);
		    }
		}
	    }
	}
    }

  if ((lv_exception.info_vector).size() != 0)
    {
      throw lv_exception;
    }

  return;
}
