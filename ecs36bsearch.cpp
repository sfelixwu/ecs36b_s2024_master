
#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include "ecs36bclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "Post.h"

using namespace jsonrpc;
using namespace std;

int
main(int argc, char *argv[])
{
  if (argc != 2)
    {
      char arg_string[] = " <search_clause_json>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }
  Json::Value jv;
  int rc = myFile2JSON(argv[1], &jv);

  HttpClient httpclient("https://ethikos.ngrok.io");
  // HttpClient httpclient("http://localhost:8384");
  // HttpClient httpclient("http://169.237.6.102:55407");
  ecs36bClient myClient(httpclient, JSONRPC_CLIENT_V2);

  Json::Value result_json;

  try {
    result_json = myClient.search(jv.toStyledString());
    std::cout << result_json.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  // write the received posts back out to json files

  if ((result_json["data"].isNull() != true) &&
      (result_json["data"].isArray() == true))
    {
      // write the received posts back out to json files
      for ( int i = 0; i < (result_json["data"]).size(); i ++ )
	{
	  if ((result_json["data"][i]).isObject() == true)
	    {
	      try
		{
		  char fname_buf[1024];
		  bzero(fname_buf, 1024);

		  snprintf(fname_buf, strlen("post_.json") +
			   strlen((result_json["data"][i]["id"]).asString().c_str()) + 1,
			   "post_%s.json",
			   (result_json["data"][i]["id"]).asString().c_str());

		  Post * post_ptr = new Post((Person *) NULL, (Message *) NULL);
		  post_ptr->JSON2Object(&(result_json["data"][i]));
		  rc = myJSON2File(fname_buf, post_ptr->dump2JSON());
		}
	      catch(ecs36b_Exception e)
		{
		  std::cout << "ecs36b_Exception caught\n";
		  int erc = produceErrorJSON(e, "ecs36bclient_search.log", &result_json, 0);
		  if (erc != ECS36B_ERROR_NORMAL)
		    myPrintLog("{\"location\":\"produce Error catch\"}", "ecs36bclient_search.log");
		  e.myDestructor();
		}
	    }
	}
    }
  return 0;
}
