
#include "Post.h"
#include "ecs36bserver.h"
#include "ecs36bclient.h"

#include <jsonrpccpp/server/connectors/httpserver.h>

extern const char *ecs36b_errors[];

using namespace jsonrpc;
using namespace std;

class Myecs36bServer : public ecs36bServer
{
public:
  Myecs36bServer(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value update(const std::string& updating_json);
  virtual Json::Value search(const std::string& search_clause);
};

Myecs36bServer::Myecs36bServer(AbstractServerConnector &connector, serverVersion_t type)
  : ecs36bServer(connector, type)
{
  std::cout << "Myecs36bServer Object created" << std::endl;
}

// member functions

Json::Value
Myecs36bServer::update(const std::string& updating_json)
{
  Json::Value result_json;
  char fname_buf[1024];
  FILE * post_f_ptr;
  int rc = ECS36B_ERROR_NORMAL;
  bool brc = false;
  Post * post_ptr = NULL;

#ifdef _ECS36B_DEBUG_
  std::cout << "update" << " " << updating_json << std::endl;
#endif /* _ECS36B_DEBUG_ */

  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  try
    {
      if ((updating_json.c_str())[0] != '{')
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update first character";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = ECS36B_ERROR_JSON_PARSING;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
      
      myPrintLog(updating_json, "ecs36bserver_update.log");

      Json::Value myv_message;
      rc = checkBigID(updating_json);
      if (rc != ECS36B_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update check Big ID";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      rc = myParseJSON(updating_json, &myv_message);
      if (rc != ECS36B_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update parse JSON";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      // set the json_post file name
      if (((myv_message["id"]).isNull() == true) &&
	  ((myv_message["id"]).isString() == false) &&
	  (checkPostID((myv_message["id"]).asString()) != 0))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update check Post ID";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = ECS36B_ERROR_JSON_POST_NO_ID;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      bzero(fname_buf, 1024);
      snprintf(fname_buf,
	       strlen("./posts/post_.json") +
	       strlen(((myv_message["id"]).asString()).c_str()) + 1,
	       "./posts/post_%s.json", ((myv_message["id"]).asString()).c_str());
  
      std::cout << "name: " << fname_buf << std::endl;
      
      // before we do anything, let us check the history section
      if (((myv_message["history"]).isNull() != true) &&
	  ((myv_message["history"]["data"]).isNull() != true) &&
	  ((myv_message["history"]["data"]).isArray() == true) &&
	  ((myv_message["history"]["data"]).size() > 0) &&
	  ((myv_message["history"]["count"]).isInt() == true) &&
	  ((myv_message["history"]["count"]).asInt() > 0))
	{
	  int i;
	  for (i = 0; i < (myv_message["history"]["data"]).size(); i++)
	    {
	      Json::Value l_jv = myv_message["history"]["data"][i];

	      if (((l_jv["vsID"]).isNull() == true) ||
		  ((l_jv["vsID"]).isString() != true))
		{
		  ei_ptr = new Exception_Info {};
		  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
		  ei_ptr->which_string = "update history VSID error";
		  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
		  ei_ptr->what_code = ECS36B_ERROR_VSID_HISTORY;
		  (lv_exception_ptr->info_vector).push_back(ei_ptr);
		  // this vsID cannot be retrieved.
		}
	    }
	}

      // check vsID portion of id
      {
	char idstr[1024];
	bzero(idstr, 1024);
	snprintf(idstr, strlen(((myv_message["id"]).asString()).c_str()) + 1,
		 "%s", ((myv_message["id"]).asString()).c_str());

	char c_prof_buf[256];
	char c_post_buf[256];
	bzero(c_prof_buf, 256);
	bzero(c_post_buf, 256);
	sscanf(idstr, "%[^_]_%s", c_prof_buf, c_post_buf);
	std::string s_vsID { c_prof_buf };
      }

      post_ptr = new Post((Person *) NULL, (Message *) NULL);

      Json::Value pjf_v;
      rc = myFile2JSON(fname_buf, &pjf_v);
      
      if (rc != ECS36B_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "update File2JSON from file";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	}
      else
	{
	  try
	    {
	      post_ptr->JSON2Object(&pjf_v);
	    }
	  catch(ecs36b_Exception e)
	    {
	      int i;
	      for (i = 0; i < (e.info_vector).size(); i++)
		{
		  Exception_Info * ei_ptr_copy = new Exception_Info {};
		  (*ei_ptr_copy) = (*((e.info_vector)[i]));
		  (lv_exception_ptr->info_vector).push_back(ei_ptr_copy);
		}
	      e.myDestructor();
	    }
	}
      
      std::cout << (&myv_message) << std::endl;
      
      try
	{
	  post_ptr->JSON2Object(&myv_message);
	}
      catch(ecs36b_Exception e)
	{
	  int i;
	  for (i = 0; i < (e.info_vector).size(); i++)
	    {
	      Exception_Info * ei_ptr_copy = new Exception_Info {};
	      (*ei_ptr_copy) = (*((e.info_vector)[i]));
	      (lv_exception_ptr->info_vector).push_back(ei_ptr_copy);
	    }
	  e.myDestructor();
	}

      // try to get the keys (to the key files)
      if (post_ptr->keys == NULL)
	{
	  post_ptr->keys = new vector<OKey *> ();
	}
      
      int i;
      for (i = 0; i < (post_ptr->keys)->size(); i++)
	{
	  OKey * okey_ptr = (*(post_ptr->keys))[i];
	  
	  char fn_buf[256];
	  bzero(fn_buf, 256);
	  snprintf(fn_buf, strlen("./okeys/okey_.list") + strlen((okey_ptr->okey).c_str()) + 1,
		   "./okeys/okey_%s.list", (okey_ptr->okey).c_str());

	  // std::cout << fn_buf << std::endl;
	  std::string target_buf = (post_ptr->id).get();
	  // std::cout << target_buf << std::endl;

	  FILE *okey_f   = NULL;
	  int found_flag = 0;
	  int null_flag  = 1; // usually new okey

	  okey_f = fopen(fn_buf, "r");

	  if (okey_f != NULL)
	    {
	      null_flag = 0;
	      char post_id_buf[1024];
	      int okey_loop_flag = 1;
	      while (okey_loop_flag)
		{
		  bzero(post_id_buf, 1024);
		  int rc = fscanf(okey_f, "%[^\n]", post_id_buf);
		  if (rc == EOF)
		    {
		      okey_loop_flag = 0; // leaving the loop
		    }
		  else
		    {
		      // std::cout << post_id_buf << std::endl;
		      if (strcmp(target_buf.c_str(), post_id_buf) == 0)
			{
			  found_flag = 1;
			  okey_loop_flag = 0;
			}
		    }
		  fgetc(okey_f);
		}
	      fclose(okey_f);
	    }

	  if ((null_flag == 1) || (found_flag == 0))
	    {
	      FILE *okey_f = fopen(fn_buf, "a");
	      if (okey_f != NULL)
		{
		  fprintf(okey_f, "%s\n", ((post_ptr->id).get()).c_str());
		  fclose(okey_f);
		}
	      else
		{
		  // throw...
		  std::cout << "need to throw okey\n";
		}
	    }
	}

      if ((lv_exception_ptr->info_vector).size() != 0)
	{
	  throw (*lv_exception_ptr);
	}
    }
  catch (ecs36b_Exception e)
    {
      int erc = produceErrorJSON(e, "ecs36bserver_update.log", &result_json, 0);
      if (erc != ECS36B_ERROR_NORMAL)
	myPrintLog("{\"location\":\"produce Error catch\"}", "ecs36bserver_update.log");
    }

  // write it back
  // std::cout << fname_buf <<  std::endl;
  if (post_ptr == NULL)
    {
      myPrintLog("{\"location\":\"before write back POST_PTR null\"}", "ecs36bserver_update.log");
      return result_json;
    }
  
  Json::Value *rj_ptr = post_ptr->dump2JSON();
  delete post_ptr;
  
  rc = myJSON2File(fname_buf, rj_ptr);
  return (*rj_ptr);
}

int
simpleChecksum
(const char *data, int length)
{
  int *int_ptr = (int *) data;
  int int_array_size = length / sizeof(int);
  int i;
  int result = 95616; // very weak key
  for (i = 0; i < int_array_size; i++)
    {
      result ^= int_ptr[i];
    }
  return result;
}

Json::Value
Myecs36bServer::search
(const std::string& search_clause)
{
  Json::Value result_json;
  int rc = ECS36B_ERROR_NORMAL;
  bool brc = false;

#ifdef _ECS36B_DEBUG_
  std::cout << "search" << " " << search_clause << std::endl;
#endif /* _ECS36B_DEBUG_ */

  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  try
    {
      if ((search_clause.c_str())[0] != '{')
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search first character";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = ECS36B_ERROR_JSON_PARSING;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
      myPrintLog(search_clause, "ecs36bserver_search.log");

      Json::Value myv_message;
      rc = myParseJSON(search_clause, &myv_message);
      if (rc != ECS36B_ERROR_NORMAL)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search clause parse";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = rc;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      if (myv_message.isObject() != true)
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search clause not object";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = ECS36B_ERROR_BAD_KEYWORD_FORMAT;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}

      if (((myv_message["keyword"]).isNull() == true) &&
	  ((myv_message["id"]).isNull() == true))
	{
	  ei_ptr = new Exception_Info {};
	  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	  ei_ptr->which_string = "search clause keyword null";
	  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	  (lv_exception_ptr->info_vector).push_back(ei_ptr);
	  throw (*lv_exception_ptr);
	}
      
      int  post_count = 0;
      Json::Value json_data;

      if ((myv_message["keyword"]).isNull() == false)
	{
	  if ((myv_message["keyword"]).isString() == false)
	    {
	      ei_ptr = new Exception_Info {};
	      ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	      ei_ptr->which_string = "search clause keyword null";
	      ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	      ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	      (lv_exception_ptr->info_vector).push_back(ei_ptr);
	      throw (*lv_exception_ptr);
	    }

	  // let us check if there is file around for this keyword
	  // adding the post_id to the Keyword object file

	  char fn_buf[256];
	  bzero(fn_buf, 256);

	  // bug: const char * test_str = ((myv_message["keyword"]).asString()).c_str();

	  char test_str[1024];
	  bzero(test_str, 1024);
	  snprintf(test_str, strlen((myv_message["keyword"]).asString().c_str()) + 1,
		   "%s", ((myv_message["keyword"]).asString()).c_str());

	  // coverting the keyword to lower case
	  char cbuf[1024];
	  bzero(cbuf, 1024);

	  int ii;
	  for (ii = 0; ii < strlen(test_str); ii++)
	    {
	      if ((test_str[ii] >= 'A') && (test_str[ii] <= 'Z'))
		cbuf[ii] = tolower(test_str[ii]);
	      else
		cbuf[ii] = test_str[ii];	    
	    }

	  snprintf(fn_buf, strlen("./okeys/okey_.list") + strlen(cbuf) + 1,
		   "./okeys/okey_%s.list", cbuf);

	  std::string s = fn_buf;
	  myPrintLog(s, "ecs36bserver_search.log");

	  FILE *okey_f = fopen(fn_buf, "r");
	  if (okey_f == NULL)
	    {
	      ei_ptr = new Exception_Info {};
	      ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	      ei_ptr->which_string = "search clause okey file null";
	      ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	      ei_ptr->what_code = ECS36B_ERROR_NO_OKEY;
	      (lv_exception_ptr->info_vector).push_back(ei_ptr);
	      throw (*lv_exception_ptr);
	    }

	  char post_id_buf[1024];
	  int  okey_flag  = 1;

	  while(okey_flag)
	    {
	      bzero(post_id_buf, 1024);
	      int f_rc = fscanf(okey_f, "%[^\n]", post_id_buf);
	      std::cout << post_id_buf << std::endl;
	      std::string post_id_string = post_id_buf;
	      
	      if (f_rc == EOF)
		{
		  okey_flag = 0; // leaving the loop
		}
	      else
		{
		  if (checkPostID(post_id_string) == 0)
		    {
		      char pfn_buf[1024];
		      bzero(pfn_buf, 1024);
		      snprintf(pfn_buf, strlen("./posts/post_.json") + strlen(post_id_buf) + 1,
			       "./posts/post_%s.json", post_id_buf);
		      std::cout << pfn_buf << std::endl;

		      Json::Value pjf_v;
		      rc = myFile2JSON(pfn_buf, &pjf_v);
		      if (rc != ECS36B_ERROR_NORMAL)
			{
			  ei_ptr = new Exception_Info {};
			  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
			  ei_ptr->which_string = "search clause post myFile2JSON";
			  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
			  ei_ptr->what_code = rc;
			  (lv_exception_ptr->info_vector).push_back(ei_ptr);
			}
		      else
			{
			  Post *post_ptr = new Post((Person *) NULL, (Message *) NULL);
			  try
			    {
			      post_ptr->JSON2Object(&pjf_v);
			    }
			  catch(ecs36b_Exception e)
			    {
			      int i;
			      for (i = 0; i < (e.info_vector).size(); i++)
				{
				  Exception_Info * ei_ptr_copy = new Exception_Info {};
				  (*ei_ptr_copy) = (*((e.info_vector)[i]));
				  (lv_exception_ptr->info_vector).push_back(ei_ptr_copy);
				}
			      e.myDestructor();
			    }
			  // add to the result data
			  json_data[post_count] = *(post_ptr->dump2JSON());
			  post_count++;
			  delete post_ptr;
			}
		    }
		}
	      fgetc(okey_f);
	    }
	  fclose(okey_f);

	  result_json["data"]  = json_data;
	  result_json["court"] = post_count;
	}
      else
	{
	  // "id" related search
	  if ((myv_message["id"]).isString() == false)
	    {
	      ei_ptr = new Exception_Info {};
	      ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
	      ei_ptr->which_string = "search clause id not a string";
	      ei_ptr->how_code = ECS36B_ERROR_NORMAL;
	      ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	      (lv_exception_ptr->info_vector).push_back(ei_ptr);
	      throw (*lv_exception_ptr);
	    }

	  // extracting the "id" object
	  vector<std::string> matched = matchDirent("posts/.", "post",
						    (myv_message["id"]).asString());

	  int j;
	  for (j = 0; j < matched.size(); j++)
	    {
	      char pfn_buf[1024];
	      bzero(pfn_buf, 1024);
	      snprintf(pfn_buf, strlen("./posts/") + strlen((matched[j]).c_str()) + 1,
		       "./posts/%s", (matched[j]).c_str());
	      std::cout << pfn_buf << std::endl;

	      Json::Value pjf_v;
	      rc = myFile2JSON(pfn_buf, &pjf_v);
	      if (rc != ECS36B_ERROR_NORMAL)
		{
		  ei_ptr = new Exception_Info {};
		  ei_ptr->where_code = ECS36B_ERROR_JSONRPC_SERVER;
		  ei_ptr->which_string = "search clause post myFile2JSON";
		  ei_ptr->how_code = ECS36B_ERROR_NORMAL;
		  ei_ptr->what_code = rc;
		  (lv_exception_ptr->info_vector).push_back(ei_ptr);
		}
	      else
		{
		  Post *post_ptr = new Post((Person *) NULL, (Message *) NULL);
		  try
		    {
		      post_ptr->JSON2Object(&pjf_v);
		    }
		  catch(ecs36b_Exception e)
		    {
		      int i;
		      for (i = 0; i < (e.info_vector).size(); i++)
			{
			  Exception_Info * ei_ptr_copy = new Exception_Info {};
			  (*ei_ptr_copy) = (*((e.info_vector)[i]));
			  (lv_exception_ptr->info_vector).push_back(ei_ptr_copy);
			}
		      e.myDestructor();
		    }
		  // add to the result data
		  json_data[post_count] = *(post_ptr->dump2JSON());
		  post_count++;
		  delete post_ptr;
		}
	    }

	  result_json["data"]  = json_data;
	  result_json["court"] = post_count;
	}
      
      if ((lv_exception_ptr->info_vector).size() != 0)
	{
	  throw (*lv_exception_ptr);
	}
    }
  catch (ecs36b_Exception e)
    {
      int erc = produceErrorJSON(e, "ecs36bserver_search.log", &result_json, 0);
      if (erc != ECS36B_ERROR_NORMAL)
	myPrintLog("{\"location\":\"produce Error catch\"}", "ecs36bserver_search.log");
      e.myDestructor();
    }

  return result_json;
}

int
main(int argc, char *argv[])
{
  if (argc != 1) exit(-1);
  // HttpServer httpserver(8384);
  HttpServer httpserver(8384);
  // HttpServer httpserver(55408);
  Myecs36bServer s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
