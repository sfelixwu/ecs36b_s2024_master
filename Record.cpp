
#include "Record.h"

Record::Record()
{
  this->class_name = "Record";

  this->label = "";
  this->where = NULL;
  this->who   = NULL;
  this->what  = NULL;
  this->when  = NULL;
}

void
Record::addWho
(Person *_p)
{
  if (this->who == NULL)
    {
      this->who = new vector<Person *>();
    }
  (this->who)->push_back(_p);
}

void
Record::addWhat
(Thing *_t)
{
  if (this->what == NULL)
    {
      this->what = new vector<Thing *>();
    }
  (this->what)->push_back(_t);
}

void
Record::setWho(std::vector<Person *> *_vp)
{
  this->who = _vp;
}

void
Record::setWhat(std::vector<Thing *> *_vt)
{
  this->what = _vt;
}

void
Record::setWhere(GPS_DD *_g)
{
  this->where = _g;
}

void
Record::setWhen(JvTime *_jt)
{
  this->when = _jt;
}

bool
Record::operator==
(Record aRecord)
{
  // to be implemented
  return false;
}

Json::Value *
Record::dump2JSON()
{
  Json::Value * result_ptr = new Json::Value();

  (*result_ptr)["label"] = this->label;
  (*result_ptr)["where"] = *((this->where)->dump2JSON());
  (*result_ptr)["when"] = *((this->when)->dump2JSON());

  int i;

  if (this->who == NULL)
    {
      this->who = new vector<Person *>();
    }
  
  for (i = 0; i < (this->who)->size(); i++)
    {
      (*result_ptr)["who"]["data"][i] = *(((*(this->who))[i])->dump2JSON());
    }
  (*result_ptr)["who"]["count"] = ((unsigned int) (this->who)->size());

  if (this->what == NULL)
    {
      this->what = new vector<Thing *>();
    }

  for (i = 0; i < (this->what)->size(); i++)
    {
      (*result_ptr)["what"]["data"][i] = *(((*(this->what))[i])->dump2JSON());
    }
  (*result_ptr)["what"]["count"] = ((unsigned int) (this->what)->size());

  return result_ptr;
}

void
Record::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception lv_exception {};

  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
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
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
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

  // "label"
  if (((*arg_json_ptr)["label"].isNull() == true) ||
      ((*arg_json_ptr)["label"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
      ei_ptr->which_string = "label";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["label"].isNull() == true)
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
      this->label = ((*arg_json_ptr)["label"]).asString();
    }

  // "who"
  if ((((*arg_json_ptr)["who"]).isNull() == true) ||
      (((*arg_json_ptr)["who"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
      ei_ptr->which_string = "who";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["who"].isNull() == true)
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
      if ((((*arg_json_ptr)["who"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["who"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
	  ei_ptr->which_string = "who::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["who"]["data"]).isNull() == true)
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
	  if (this->who == NULL)
	    {
	      this->who = new vector<Person *>();
	    }

	  int j;
	  for (j = 0; j < ((*arg_json_ptr)["who"]["data"]).size(); j++)
	    {
	      Json::Value l_jv_who = (*arg_json_ptr)["who"]["data"][j];
	      Person *l_who_ptr = new Person();
	      try
		{
		  l_who_ptr->JSON2Object(&(l_jv_who));
		}
	      catch(ecs36b_Exception e)
		{
		  int i;
		  for (i = 0; i < (e.info_vector).size(); i++)
		    {
		      (lv_exception.info_vector).push_back((e.info_vector)[i]);
		    }
		}

	      // now check if the reaction already exist
	      int flag_wo = 0;
	      vector<Person *>::iterator my_it_wo;
	      for (my_it_wo = (*(this->who)).begin();
		   my_it_wo < (*(this->who)).end(); my_it_wo++)
		{
		  // operator== for Person
		  if ((*(*my_it_wo)) == (*(l_who_ptr)))
		    {
		      // this is a duplicated reaction as one person can only have one reaction
		      flag_wo = 1;
		    }
		}

	      if (flag_wo == 0)
		{
		  (*(this->who)).push_back(l_who_ptr);
		}
	      else
		{
		  delete l_who_ptr;
		}
	    }
	}
    }

  // "what"
  if ((((*arg_json_ptr)["what"]).isNull() == true) ||
      (((*arg_json_ptr)["what"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
      ei_ptr->which_string = "what";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["what"].isNull() == true)
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
      if ((((*arg_json_ptr)["what"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["what"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
	  ei_ptr->which_string = "what::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["what"]["data"]).isNull() == true)
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
	  if (this->what == NULL)
	    {
	      this->what = new vector<Thing *>();
	    }

	  int j;
	  for (j = 0; j < ((*arg_json_ptr)["what"]["data"]).size(); j++)
	    {
	      Json::Value l_jv_what = (*arg_json_ptr)["what"]["data"][j];
	      Thing *l_what_ptr = new Thing();
	      try
		{
		  l_what_ptr->JSON2Object(&(l_jv_what));
		}
	      catch(ecs36b_Exception e)
		{
		  int i;
		  for (i = 0; i < (e.info_vector).size(); i++)
		    {
		      (lv_exception.info_vector).push_back((e.info_vector)[i]);
		    }
		}

	      int flag_wa = 0;
	      vector<Thing *>::iterator my_it_wa;
	      for (my_it_wa = (*(this->what)).begin();
		   my_it_wa < (*(this->what)).end(); my_it_wa++)
		{
		  // operator== for Person
		  if ((*(*my_it_wa)) == (*(l_what_ptr)))
		    {
		      flag_wa = 1;
		    }
		}

	      if (flag_wa == 0)
		{
		  (*(this->what)).push_back(l_what_ptr);
		}
	      else
		{
		  delete l_what_ptr;
		}
	    }
	}
    }

  // "where"
  if ((((*arg_json_ptr)["where"]).isNull() == true) &&
      (((*arg_json_ptr)["where"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
      ei_ptr->which_string = "where";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["where"].isNull() == true)
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
      try
	{
	  if (this->where == NULL)
	    {
	      this->where = new GPS_DD();
	    }
	  (this->where)->JSON2Object(&((*arg_json_ptr)["where"]));
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

  // "when"
  if (((*arg_json_ptr)["when"].isNull() == true) ||
      ((*arg_json_ptr)["when"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_RECORD;
      ei_ptr->which_string = "when";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["when"].isNull() == true)
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
      try
	{
	  if (this->when == NULL)
	    {
	      this->when = new JvTime();
	    }
	  (this->when)->JSON2Object(&((*arg_json_ptr)["when"]));
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

  if ((lv_exception.info_vector).size() != 0)
    {
      throw lv_exception;
    }

  return;
}
