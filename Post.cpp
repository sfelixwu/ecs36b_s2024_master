
#include "Post.h"

Post::Post
(void)
{
  this->class_name = "Post";

  this->author = NULL;
  this->msg = NULL;

  // very critical ==> portable to different platforms
  this->receivers = NULL;
  this->links = NULL;
  this->actions = NULL;
  this->reactions = NULL;
  this->comments = NULL;
  this->created = NULL;
  this->keys = NULL;
  this->updated = NULL;
  this->location = NULL;
  this->is_published = false;
}

Post::Post
(Person * arg_author, Message * arg_msg)
{
  this->class_name = "Post";

  this->author = arg_author;
  this->msg = arg_msg;

  // very critical ==> portable to different platforms
  this->receivers = NULL;
  this->links = NULL;
  this->actions = NULL;
  this->reactions = NULL;
  this->comments = NULL;
  this->created = NULL;
  this->keys = NULL;
  this->updated = NULL;
  this->location = NULL;
  this->is_published = false;
}

Post::~Post
(void)
{
  if (this->author != NULL) delete this->author;
  if (this->msg != NULL) delete this->msg;
  if (this->created != NULL) delete this->created;
  if (this->updated != NULL) delete this->updated;
  if (this->location != NULL) delete this->location;

  int i;

  // this->reactions
  if (this->reactions != NULL)
    {
      for (i = 0; i < (this->reactions)->size(); i++)
	{
	  Reaction *r_ptr = (*(this->reactions))[i];
	  if (r_ptr != NULL)
	    {
	      delete r_ptr;
	    }
	}
      delete this->reactions;
    }

  // this->receivers
  if (this->receivers != NULL)
    {
      for (i = 0; i < (this->receivers)->size(); i++)
	{
	  Person *p_ptr = (*(this->receivers))[i];
	  if (p_ptr != NULL)
	    {
	      delete p_ptr;
	    }
	}
      delete this->receivers;
    }

  // this->links
  if (this->links != NULL)
    {
      for (i = 0; i < (this->links)->size(); i++)
	{
	  Link *l_ptr = (*(this->links))[i];
	  if (l_ptr != NULL)
	    {
	      delete l_ptr;
	    }
	}
      delete this->links;
    }

  // this->actions
  if (this->actions != NULL)
    {
      for (i = 0; i < (this->actions)->size(); i++)
	{
	  Action *a_ptr = (*(this->actions))[i];
	  if (a_ptr != NULL)
	    {
	      delete a_ptr;
	    }
	}
      delete this->actions;
    }

  // this->comments;
  if (this->comments != NULL)
    {
      for (i = 0; i < (this->comments)->size(); i++)
	{
	  Comment *c_ptr = (*(this->comments))[i];
	  if (c_ptr != NULL)
	    {
	      delete c_ptr;
	    }
	}
      delete this->comments;
    }
  
  // this->keys
  if (this->keys != NULL)
    {
      for (i = 0; i < (this->keys)->size(); i++)
	{
	  OKey *o_ptr = (*(this->keys))[i];
	  if (o_ptr != NULL)
	    {
	      delete o_ptr;
	    }
	}
      delete this->keys;
    }
}

bool
Post::operator==
(Post aPost)
{
  return (this->id == aPost.id);
}

Json::Value *
Post::dump2JSON
(void)
{
  int i;

  Json::Value * result_ptr = new Json::Value();
  Json::Value * dumpjv_ptr = NULL;

  // "keys"
  if ((this->keys != NULL) &&
      ((this->keys)->size() > 0))
    {
      Json::Value json_keys;
      Json::Value json_keys_array;

      for (i = 0; i < (this->keys)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->keys))[i])->dump2JSON();
	  if (dumpjv_ptr != NULL)
	    {
	      json_keys[i] = *(dumpjv_ptr);
	    }
	  delete dumpjv_ptr;
	}
      json_keys_array["data"] = json_keys;
      json_keys_array["count"] = ((int) (*(this->keys)).size());
      (*result_ptr)["keys"] = json_keys_array;
    }
  
  // "actions"
  if ((this->actions != NULL) &&
      ((this->actions)->size() > 0))
    {
      Json::Value json_actions;
      Json::Value json_actions_array;

      for (i = 0; i < (this->actions)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->actions))[i])->dump2JSON();
	  if (dumpjv_ptr != NULL)
	    {
	      json_actions[i] = *(dumpjv_ptr);
	    }
	  delete dumpjv_ptr;
	}
      json_actions_array["data"] = json_actions;
      json_actions_array["count"] = ((int) (*(this->actions)).size());
      (*result_ptr)["actions"] = json_actions_array;
    }
  
  // "comments"
  if ((this->comments != NULL) &&
      ((this->comments)->size() > 0))
    {
      Json::Value json_comments;
      Json::Value json_comments_array;
      for (i = 0; i < (this->comments)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->comments))[i])->dump2JSON();
	  if (dumpjv_ptr != NULL)
	    {
	      json_comments[i] = (*dumpjv_ptr);
	    }
	  delete dumpjv_ptr;
	}
      json_comments_array["data"] = json_comments;
      json_comments_array["count"] = ((int) (*(this->comments)).size());
      (*result_ptr)["comments"] = json_comments_array;
    }

  // "links"
  if ((this->links != NULL) &&
      ((this->links)->size() > 0))
    {
      Json::Value json_links;
      Json::Value json_links_array;
      for (i = 0; i < (this->links)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->links))[i])->dump2JSON();
	  if (dumpjv_ptr != NULL)
	    {
	      json_links[i] = (*dumpjv_ptr);
	    }
	  delete dumpjv_ptr;
	}
      json_links_array["data"] = json_links;
      json_links_array["count"] = ((int) (*(this->links)).size());
      (*result_ptr)["links"] = json_links_array;
    }

  // "message"
  if (this->msg != NULL)
    {
      (*result_ptr)["message"] = (this->msg)->dump2JSON();
    }

  // "reactions"
  if ((this->reactions != NULL) &&
      ((this->reactions)->size() > 0))
    {
      Json::Value json_reactions;
      Json::Value json_reactions_array;
      for (i = 0; i < (this->reactions)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->reactions))[i])->dump2JSON();
	  if (dumpjv_ptr != NULL)
	    {
	      json_reactions[i] = (*dumpjv_ptr);
	    }
	  delete dumpjv_ptr;
	}
      json_reactions_array["data"] = json_reactions;
      json_reactions_array["count"] = ((int) (*(this->reactions)).size());
      (*result_ptr)["reactions"] = json_reactions_array;
    }

  // "id"
  (*result_ptr)["id"] = (this->id).get();

  // "from"
  if (this->author != NULL)
    {
      dumpjv_ptr = (this->author)->dump2JSON();
      if (dumpjv_ptr != NULL)
	{
	  (*result_ptr)["from"] = (*dumpjv_ptr);
	}
      delete dumpjv_ptr;
    }

  // "to"
  if ((this->receivers != NULL) &&
      ((this->receivers)->size() > 0))
    {
      Json::Value json_tos;
      Json::Value json_tos_array;
      for (i = 0; i < (this->receivers)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->receivers))[i])->dump2JSON();
	  if (dumpjv_ptr != NULL)
	    {
	      json_tos[i] = (*dumpjv_ptr);
	    }
	  delete dumpjv_ptr;
	}
      json_tos_array["data"] = json_tos;
      json_tos_array["count"] = ((int) (*(this->receivers)).size());
      (*result_ptr)["to"] = json_tos_array;
    }
  
  // "created"
  if (this->created != NULL)
    {
      (*result_ptr)["created"] = *((this->created)->dump2JSON());
    }

  // "updated"
  if (this->updated != NULL)
    {
      (*result_ptr)["updated"] = *((this->updated)->dump2JSON());
    }

  // "location"
  if (this->location != NULL)
    {
      (*result_ptr)["location"] = *((this->location)->dump2JSON());
    }

  // "is published"
  (*result_ptr)["is published"] = this->is_published;

  return result_ptr;
}

int
checkPostID
(std::string id_string)
{
  // check if an id string is all numerical
  
  char idstr[1024 * 128];
  bzero(idstr, 1024 * 128);
  snprintf(idstr, strlen(id_string.c_str()) + 1, "%s", id_string.c_str());
  if (idstr[0] == '\0') return -1;

  char c_prof_buf[256 * 128];
  char c_post_buf[256 * 128];
  bzero(c_prof_buf, 256 * 128);
  bzero(c_post_buf, 256 * 128);
  sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);

  int i;
  if ((strlen(c_prof_buf) == 0) ||
      (strlen(c_post_buf) == 0) ||
      (strlen(c_prof_buf) > 64) ||
      (strlen(c_post_buf) > 64))
    return -1;
  
  for(i = 0; i < strlen(c_prof_buf); i++)
    {
      if ((c_prof_buf[i] < '0') || (c_prof_buf[i] > '9'))
	return -1;
    }

  for(i = 0; i < strlen(c_post_buf); i++)
    {
      if ((c_post_buf[i] < '0') || (c_post_buf[i] > '9'))
	return -1;
    }
  return 0;
}

int
checkBigID
(std::string s)
{
  int i, j;
  const char *s_ptr = s.c_str();
  void *data_ptr = (void *) s_ptr;
  char *ss_ptr = (char *) data_ptr;
  for (i = 0; i < strlen(ss_ptr); i++)
    {
      char buff[64];
      bzero(buff, 64);
      strncpy(buff, &(ss_ptr[i]), 4);
      if (strcmp(buff, "\"id\"") == 0)
	{
	  char *sd_ptr = (&(ss_ptr[i])) + 4;
	  char buff2[64];
	  bzero(buff2, 64);
	  sscanf(sd_ptr, "%[^\"]", buff2);
	  sd_ptr += strlen(buff2) + 1;
	  
	  for (j = 0; j < strlen(sd_ptr); j++)
	    {
	      if ((sd_ptr[j] == '\"') &&
		  (j > 0) &&
		  (j < 128))
		{
		  return ECS36B_ERROR_NORMAL;
		}

	      if (j >= 128)
		{
		  return ECS36B_ERROR_VSID_POST_ID;
		}

	      if (((sd_ptr[j] < '0') || (sd_ptr[j] > '9')) && (sd_ptr[j] != '_'))
		{
		  return ECS36B_ERROR_VSID_POST_ID;
		}
	    }
	}
    }
  return ECS36B_ERROR_VSID_POST_ID;
}

void
Post::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_POST);

  // "id"
  if ((((*arg_json_ptr)["id"]).isNull() == true) ||
      (((*arg_json_ptr)["id"]).isString() == false) ||
      ((((*arg_json_ptr)["id"]).asString()).size() < 0) ||
      ((((*arg_json_ptr)["id"]).asString()).size() > 255))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "id";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["id"].isNull() == true)
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
      if (checkPostID(((*arg_json_ptr)["id"]).asString()) != 0)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "id";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = ECS36B_ERROR_POST_ID_CHECK_FAILED;
	  ei_ptr->array_index = 0;
	  
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      // Post ID can be only set once!!
      int rc = (this->id).setPP(((*arg_json_ptr)["id"]).asString());
      if (rc != ECS36B_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "id";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  ei_ptr->array_index = 0;

	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
    }

  // "from"
  if (((*arg_json_ptr)["from"].isNull() == true) ||
      ((*arg_json_ptr)["from"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "from";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["from"].isNull() == true)
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
	  if (this->author == NULL)
	    {
	      this->author = new Person();
	    }
	  (this->author)->JSON2Object(&((*arg_json_ptr)["from"]));
	}
      catch(ecs36b_Exception e)
	{
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }

  // "to"
  if ((((*arg_json_ptr)["to"]).isNull() == true) ||
      (((*arg_json_ptr)["to"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "to";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["to"].isNull() == true)
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
      if ((((*arg_json_ptr)["to"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["to"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "to::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["to"]["data"]).isNull() == true)
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
	  if (this->receivers == NULL)
	    {
	      this->receivers = new vector<Person *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["to"]["data"]).size(); ai++)
	    {
	      Json::Value l_jv_to = (*arg_json_ptr)["to"]["data"][ai];
	      Person *l_to_ptr = new Person();
	      try
		{
		  l_to_ptr->JSON2Object(&(l_jv_to));
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // now check if the receiver already exist
	      int flag_rr = 0;
	      vector<Person *>::iterator my_it_rr;
	      for (my_it_rr = (*(this->receivers)).begin();
		   my_it_rr < (*(this->receivers)).end(); my_it_rr++)
		{
		  // within a given post, each person should only receive once
		  // operator== for Person
		  if ((*(*my_it_rr)) == (*(l_to_ptr)))
		    {
		      // this is a duplicated reaction as one person can only have one reaction
		      flag_rr = 1;
		    }
		}

	      if (flag_rr == 0)
		{
		  (*(this->receivers)).push_back(l_to_ptr);
		}
	      else
		{
		  delete l_to_ptr;
		}
	    }
	}
    }

  // "message"
  if (((*arg_json_ptr)["message"].isNull() == true) ||
      ((*arg_json_ptr)["message"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "message";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["message"].isNull() == true)
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
	  if (this->msg == NULL)
	    {
	      this->msg = new Message();
	    }
	  (this->msg)->JSON2Object(&((*arg_json_ptr)["message"]));
	}
      catch(ecs36b_Exception e)
	{
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }

  // "keys"
  if ((((*arg_json_ptr)["keys"]).isNull() == true) ||
      (((*arg_json_ptr)["keys"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "keys";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["keys"].isNull() == true)
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
      if ((((*arg_json_ptr)["keys"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["keys"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "keys::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["keys"]["data"]).isNull() == true)
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
	  if (this->keys == NULL)
	    {
	      this->keys = new vector<OKey *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["keys"]["data"]).size(); ai++)
	    {
	      Json::Value l_jv_key = (*arg_json_ptr)["keys"]["data"][ai];
	      OKey * l_key_ptr = new OKey();
	      try
		{
		  l_key_ptr->JSON2Object(&(l_jv_key));
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // now check if the key already exist
	      int flag_ky = 0;
	      vector<OKey *>::iterator my_it_ky;
	      for (my_it_ky = (*(this->keys)).begin();
		   my_it_ky < (*(this->keys)).end(); my_it_ky++)
		{
		  // operator== for OKey
		  if ((*(*my_it_ky)) == (*(l_key_ptr)))
		    {
		      flag_ky = 1;
		    }
		}

	      if (flag_ky == 0)
		{
		  (*(this->keys)).push_back(l_key_ptr);
		}
	      else
		{
		  delete l_key_ptr;
		}
	    }
	}
    }

  // "actions"
  if ((((*arg_json_ptr)["actions"]).isNull() == true) ||
      (((*arg_json_ptr)["actions"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "actions";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["actions"].isNull() == true)
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
      if ((((*arg_json_ptr)["actions"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["actions"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "actions::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["actions"]["data"]).isNull() == true)
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
	  if (this->actions == NULL)
	    {
	      this->actions = new vector<Action *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["actions"]["data"]).size(); ai++)
	    {
	      Json::Value l_jv_action = (*arg_json_ptr)["actions"]["data"][ai];
	      Action *l_action_ptr = new Action();
	      try
		{
		  l_action_ptr->JSON2Object(&(l_jv_action));
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // now check if the action already exist
	      int flag_ac = 0;
	      vector<Action *>::iterator my_it_ac;
	      for (my_it_ac = (*(this->actions)).begin();
		   my_it_ac < (*(this->actions)).end(); my_it_ac++)
		{
		  // operator== for Action
		  if ((*(*my_it_ac)) == (*(l_action_ptr)))
		    {
		      flag_ac = 1;
		    }
		}

	      if (flag_ac == 0)
		{
		  (*(this->actions)).push_back(l_action_ptr);
		}
	      else
		{
		  delete l_action_ptr;
		}
	    }
	}
    }

  // "comments"
  if ((((*arg_json_ptr)["comments"]).isNull() == true) ||
      (((*arg_json_ptr)["comments"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "comments";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["comments"].isNull() == true)
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
      if ((((*arg_json_ptr)["comments"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["comments"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "comments::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["comments"]["data"]).isNull() == true)
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
	  if (this->comments == NULL)
	    {
	      this->comments = new vector<Comment *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["comments"]["data"]).size(); ai++)
	    {
	      Json::Value l_jv_comment = (*arg_json_ptr)["comments"]["data"][ai];
	      Comment *l_comment_ptr = new Comment();
	      try
		{
		  l_comment_ptr->JSON2Object(&(l_jv_comment));
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // now check if the comment already exist
	      int flag_co = 0;
	      vector<Comment *>::iterator my_it_co;
	      for (my_it_co = (*(this->comments)).begin();
		   my_it_co < (*(this->comments)).end(); my_it_co++)
		{
		  // Comment operator==
		  if ((*(*my_it_co)) == (*(l_comment_ptr)))
		    {
		      flag_co = 1;
		    }
		}

	      if (flag_co == 0)
		{
		  (*(this->comments)).push_back(l_comment_ptr);
		}
	      else
		{
		  delete l_comment_ptr;
		}
	    }
	}
    }

  // "links"
  if ((((*arg_json_ptr)["links"]).isNull() == true) ||
      (((*arg_json_ptr)["links"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "links";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["links"].isNull() == true)
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
      if ((((*arg_json_ptr)["links"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["links"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "links::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["links"]["data"]).isNull() == true)
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
	  if (this->links == NULL)
	    {
	      this->links = new vector<Link *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["links"]["data"]).size(); ai++)
	    {
	      Json::Value l_jv_link = (*arg_json_ptr)["links"]["data"][ai];
	      Link *l_link_ptr = new Link();
	      try
		{
		  l_link_ptr->JSON2Object(&(l_jv_link));
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // now check if the link already exist
	      int flag_lk = 0;
	      vector<Link *>::iterator my_it_lk;
	      for (my_it_lk = (*(this->links)).begin();
		   my_it_lk < (*(this->links)).end(); my_it_lk++)
		{
		  // Link operator==
		  
		  if ((*(*my_it_lk)) == (*(l_link_ptr)))
		    {
		      flag_lk = 1;
		    }
		}

	      if (flag_lk == 0)
		{
		  (*(this->links)).push_back(l_link_ptr);
		}
	      else
		{
		  delete l_link_ptr;
		}
	    }
	}
    }

  // "reactions"
  if ((((*arg_json_ptr)["reactions"]).isNull() == true) ||
      (((*arg_json_ptr)["reactions"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "reactions";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["reactions"].isNull() == true)
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
      if ((((*arg_json_ptr)["reactions"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["reactions"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
	  ei_ptr->which_string = "reactions::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["reactions"]["data"]).isNull() == true)
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
	  if (this->reactions == NULL)
	    {
	      this->reactions = new vector<Reaction *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["reactions"]["data"]).size(); ai++)
	    {
	      Json::Value l_jv_reaction = (*arg_json_ptr)["reactions"]["data"][ai];
	      Reaction *l_reaction_ptr = new Reaction();
	      try
		{
		  l_reaction_ptr->JSON2Object(&(l_jv_reaction));
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // now check if the reaction already exist
	      int flag_rt = 0;
	      vector<Reaction *>::iterator my_it_rt;
	      for (my_it_rt = (*(this->reactions)).begin();
		   my_it_rt < (*(this->reactions)).end(); my_it_rt++)
		{
		  // within a given comment, each person can only have one reaction
		  // operator== for Person
		  // reaction operator==
		  if ((*(*my_it_rt)) == (*(l_reaction_ptr)))
		    {
		      // this is a duplicated reaction as one person can only have one reaction
		      flag_rt = 1;
		    }
		}

	      if (flag_rt == 0)
		{
		  (*(this->reactions)).push_back(l_reaction_ptr);
		}
	      else
		{
		  delete l_reaction_ptr;
		}
	    }
	}
    }

  // "created"
  if (((*arg_json_ptr)["created"].isNull() == true) ||
      ((*arg_json_ptr)["created"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "created";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["created"].isNull() == true)
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
	  if (this->created == NULL)
	    {
	      this->created = new JvTime();
	    }
	  (this->created)->JSON2Object(&((*arg_json_ptr)["created"]));
	}
      catch(ecs36b_Exception e)
	{
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }
  
  // "updated"
  if (((*arg_json_ptr)["updated"].isNull() == true) ||
      ((*arg_json_ptr)["updated"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "updated";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["updated"].isNull() == true)
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
	  if (this->updated == NULL)
	    {
	      this->updated = new JvTime();
	    }
	  (this->updated)->JSON2Object(&((*arg_json_ptr)["updated"]));
	}
      catch(ecs36b_Exception e)
	{
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }

  // "location"
  if (((*arg_json_ptr)["location"].isNull() == true) ||
      ((*arg_json_ptr)["location"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
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

  // "is published"
  if (((*arg_json_ptr)["is published"].isNull() == true) ||
      ((*arg_json_ptr)["is published"].isBool() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_POST;
      ei_ptr->which_string = "is published";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["is published"].isNull() == true)
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
      this->is_published = ((*arg_json_ptr)["is_published"]).asBool();
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
