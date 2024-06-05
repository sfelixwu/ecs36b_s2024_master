
#include "Comment.h"

Comment::Comment
(void)
{
  this->class_name = "Comment";

  this->author     = (Person *)  NULL;
  this->msg        = (Message *) NULL;
  this->created    = (JvTime *)  NULL;

  // very critical ==> portable to different platforms
  this->reactions  = (std::vector<Reaction *> *) NULL;
  this->tags       = (std::vector<Tag *> *)      NULL;

  std::cout << "Comment constructor called\n";
}

Comment::Comment
(std::string arg_profile_id, std::string arg_post_id, std::string arg_comment_id,
 Person * arg_author, Message * arg_msg, JvTime * arg_created)
{
  this->class_name = "Comment";

  (this->id).profile = arg_profile_id;
  (this->id).post    = arg_post_id;
  (this->id).comment = arg_comment_id;

  // TBD -- should we copy the content from the pointers
  this->author       = arg_author;
  this->msg          = arg_msg;
  this->created      = arg_created;

  // very critical ==> portable to different platforms
  this->reactions  = (std::vector<Reaction *> *) NULL;
  this->tags       = (std::vector<Tag *> *)      NULL;
}

Comment::~Comment
(void)
{
  if (this->author  != NULL) delete this->author;
  if (this->msg     != NULL) delete this->msg;
  if (this->created != NULL) delete this->created;

  int i;
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

  if (this->tags != NULL)
    {
      for (i = 0; i < (this->tags)->size(); i++)
	{
	  Tag *t_ptr = (*(this->tags))[i];
	  if (t_ptr != NULL)
	    {
	      delete t_ptr;
	    }
	}
      delete this->tags;
    }
}

bool
Comment::operator==
(Comment aComment)
{
  // operator== of Identifier
  return (this->id == aComment.id);
}

Json::Value *
Comment::dump2JSON
(void)
{
  int i;
  Json::Value * dumpjv_ptr = NULL;

  if (((this->id).profile == "") ||
      ((this->id).post    == "") ||
      ((this->id).comment == "") ||
      (this->author       == NULL) ||
      (this->msg          == NULL) ||
      (this->created      == NULL))
    {
      return NULL;
    }
  
  Json::Value * result_ptr = new Json::Value();

  (*result_ptr)["id"]           = (this->id).get();

  dumpjv_ptr                    = (this->author)->dump2JSON();
  (*result_ptr)["from"]         = (*dumpjv_ptr);
  delete dumpjv_ptr;
  
  dumpjv_ptr                    = (this->msg)->dump2JSON();
  (*result_ptr)["message"]      = (*dumpjv_ptr);
  delete dumpjv_ptr;

  dumpjv_ptr                    = (this->created)->dump2JSON();
  (*result_ptr)["created"]      = (*dumpjv_ptr);
  delete dumpjv_ptr;

  // adding the reaction part
  Json::Value json_c_reactions;
  Json::Value json_c_reactions_array;

  if ((this->reactions != NULL) &&
      ((this->reactions)->size() > 0))
    {
      for (i = 0; i < (this->reactions)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->reactions))[i])->dump2JSON();
	  json_c_reactions[i] = (*dumpjv_ptr);
	  delete dumpjv_ptr;
	}
      json_c_reactions_array["data"] = json_c_reactions;
      json_c_reactions_array["count"] = ((int) (*(this->reactions)).size());
      (*result_ptr)["reactions"] = json_c_reactions_array;
    }

  // adding the tag part
  Json::Value json_c_tags;
  Json::Value json_c_tags_array;

  if ((this->tags != NULL) &&
      ((this->tags)->size() > 0))
    {
      for (i = 0; i < (this->tags)->size(); i++)
	{
	  dumpjv_ptr = ((*(this->tags))[i])->dump2JSON();
	  json_c_tags[i] = (*dumpjv_ptr);
	  delete dumpjv_ptr;
	}
      json_c_tags_array["data"] = json_c_tags;
      json_c_tags_array["count"] = ((int) (*(this->tags)).size());
      (*result_ptr)["tags"] = json_c_tags_array;
    }

  return result_ptr;
}

void
Comment::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  
  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_COMMENT);

  // printf("Comment Here 1\n");

  // "id"
  if (((*arg_json_ptr)["id"].isNull() == true) ||
      ((*arg_json_ptr)["id"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
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
      int rc = (this->id).setPPC((*arg_json_ptr)["id"].asString());
      if (rc != ECS36B_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
	  ei_ptr->which_string = "id";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  ei_ptr->array_index = 0;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	}
    }

  // printf("Comment Here 2\n");
  
  // "from"
  if (((*arg_json_ptr)["from"].isNull() == true) ||
      ((*arg_json_ptr)["from"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
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

  // printf("Comment Here 3\n");

  // "message"
  if (((*arg_json_ptr)["message"].isNull() == true) ||
      ((*arg_json_ptr)["message"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
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

  // printf("Comment Here 4\n");

  // "created"
  if (((*arg_json_ptr)["created"].isNull() == true) ||
      ((*arg_json_ptr)["created"].isObject() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
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

  // printf("Comment Here 5\n");

  // now handling the reaction and tag parts
  // (1) "reactions"
  if ((((*arg_json_ptr)["reactions"]).isNull() == true) ||
      (((*arg_json_ptr)["reactions"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
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
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
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
	  // printf("Comment Here 5 1\n");
	  if (this->reactions == NULL)
	    {
	      this->reactions = new vector<Reaction *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["reactions"]["data"]).size(); ai++)
	    {
	      // printf("Comment Here 5 2\n");
	      Json::Value l_jv_reaction = (*arg_json_ptr)["reactions"]["data"][ai];
	      Reaction *l_reaction_ptr = new Reaction();
	      try
		{
		  // printf("Comment Here 5 3\n");
		  l_reaction_ptr->JSON2Object(&(l_jv_reaction));
		  // printf("Comment Here 5 4\n");
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // printf("Comment Here 5 5\n");

	      // now check if the reaction already exist
	      int flag_rt = 0;
	      vector<Reaction *>::iterator my_it_rt;
	      for (my_it_rt = (*(this->reactions)).begin();
		   my_it_rt < (*(this->reactions)).end(); my_it_rt++)
		{
		  // within a given comment, each person can only have one reaction
		  // operator== for Reaction
		  if ((*(*my_it_rt)) == (*(l_reaction_ptr)))
		    {
		      // this is a duplicated reaction as one person can only have one reaction
		      flag_rt = 1;
		    }
		}
	      // printf("Comment Here 5 6\n");

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
  // printf("Comment Here 6\n");

  // (2) tags
  if ((((*arg_json_ptr)["tags"]).isNull() == true) ||
      (((*arg_json_ptr)["tags"]).isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
      ei_ptr->which_string = "tags";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["tags"].isNull() == true)
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
      if ((((*arg_json_ptr)["tags"]["data"]).isNull() == true) ||
	  (((*arg_json_ptr)["tags"]["data"]).isArray() != true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_COMMENT;
	  ei_ptr->which_string = "tags::data";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;

	  if (((*arg_json_ptr)["tags"]["data"]).isNull() == true)
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
	  if (this->tags == NULL)
	    {
	      this->tags = new vector<Tag *>();
	    }

	  int ai;
	  for (ai = 0; ai < ((*arg_json_ptr)["tags"]["data"]).size(); ai++)
	    {
	      Json::Value l_jv_tag = (*arg_json_ptr)["tags"]["data"][ai];
	      Tag *l_tag_ptr = new Tag();
	      try
		{
		  l_tag_ptr->JSON2Object(&(l_jv_tag));
		}
	      catch(ecs36b_Exception e)
		{
		  JSON2Object_appendEI(e, lv_exception_ptr, ai);
		}

	      // now check if the tag already exist
	      // this part needs more work -- currently only check the person
	      int flag_tg = 0;
	      vector<Tag *>::iterator my_it_tg;
	      for (my_it_tg = (*(this->tags)).begin();
		   my_it_tg < (*(this->tags)).end(); my_it_tg++)
		{
		  if (((*my_it_tg)->tagged != NULL) &&
		      (l_tag_ptr->tagged   != NULL))
		    {
		      if ((*(*my_it_tg)->tagged) == (*(l_tag_ptr->tagged)))
			{
			  // this is a duplicated tag if the same person (can only be tagged once)
			  flag_tg = 1;
			}
		    }
		  else
		    {
		      if (((*my_it_tg)->index) == (l_tag_ptr->index)) 
			{
			  // this is a duplicated tag for the same index
			  flag_tg = 1;
			}
		    }
		}

	      if (flag_tg == 0)
		{
		  (*(this->tags)).push_back(l_tag_ptr);
		}
	      else
		{
		  delete l_tag_ptr;
		}
	    }
	}
    }

  // printf("Comment Here 7\n");

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}
