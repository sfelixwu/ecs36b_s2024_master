
#include <iostream>

// JSON RPC part
#include <stdlib.h>
#include "ecs36bclient.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "Post.h"

using namespace jsonrpc;
using namespace std;

int
main
(int argc, char *argv[])
{
  if (argc != 2)
    {
      char arg_string[] = " <update_json>";
      std::cout << "usage: " << argv[0] << arg_string << std::endl; 
      return -1;
    }

  // [flow]
  // file             w/history
  // read file in     w/history
  // parse_json       w/history
  // json_2_post      w/o history
  // post_pointer     w/o history
  // validate ==> dumpJ ==> post_ptr  w/o history

  // [simplified flow]
  // file             w/history
  // read file in (s)    w/history
  // validate ==> (s) w history

  // [update]
  // assume that you have a Post JSON file that you like to update
  // (1) read the file in, make it a String, s
  // (2) result_json = myClient.update(s);
  // (3) print out result_json, and see if there is any error status
  
  // [search]
  // assume that you have a Search Clause JSON file that you like to search
  // {"keyword":"happy"}
  // (1) read the file in, make it a String, s
  // (2) result_json = myClient.search(s);
  // (3) print out result_json, and see if there is any error status
  //     result_json {"count": <number of posts>,
  //                  "data": [{.post..},{...},...{...}]}
  // (4) save each of Post, into a separate file so you can append your history
  //     record, and validate/update
  
  // [validate]
  // assume that you have a Post JSON file with five history records, that you like to validate
  // (1) read the file in, make it a String, s
  // (2) result_json = myClient.validate(s);
  // (3) save result_json ("validated": code, postive/negative or 95616),
  //     and see if there is any error status
  //
  // {"status" : "failed -13 Less Than 5 History Records [current history size = 13]"}
  // Post post_123_456.json
  // copy on Server (post_123_456.json [13 history records])
  // Client validate copy of post_123_456.json [4 history records]
  // you should do a search, and get the newest copy of post_123_456.json
  // check if your own vsID is there?
  // submit that for validation
  // append your own history record to the copy you just obtained, and update it (14)
  // submit for validation
  
  // char *jf1_ptr = myFile2String(argv[1]);
  // if (checkBigID(jf1_ptr) != 0)
  //   {
  //     printf("big\n");
  //     exit(-1);
  //   }
  // free(jf1_ptr);

  // testing JSON_Difference
  Json::Value lv_1st;
  Json::Value lv_2nd;
  vector<std::string> lv_prefix;

  lv_1st["1st"] = "First";
  lv_1st["2nd"] = "Second1";
  lv_1st["4th"] = "Fourth";
  lv_2nd["1st"] = "First";
  lv_2nd["2nd"] = "Second2";
  lv_2nd["3rd"] = "Third";

  vector<JSON_Diff *> *lv_diff = JSON_Difference(lv_1st, lv_2nd, lv_prefix);

  // std::cout << "Difference Begin\n";
  int i;
  for (i = 0; i < lv_diff->size(); i++)
    {
      // std::cout << (*(((*lv_diff)[i])->dump2JSON())) << std::endl;
    }
  // std::cout << "Difference End\n";

  // start
  Json::Value jv;
  int rc = myFile2JSON(argv[1], &jv);

  fprintf(stdout, "rc = %d\n", rc);
  // std::cout << jv << std::endl;
  
  // vector<basic_string<char, char_traits<char>, std::allocator<char>>> members;
  vector<std::string> members;
  members = jv.getMemberNames();
  int k;
  for (k = 0; k < members.size(); k++)
    {
      // fprintf(stdout, "%d\n", k);
      // std::cout << members[k] << std::endl;
      // fflush(stdout);
    }

  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception {};

  Post * post_ptr = new Post((Person *) NULL, (Message *) NULL);
  try
    {
      post_ptr->JSON2Object(&jv);
    }
  catch(ecs36b_Exception& e)
    {
      // std::cout << "post JSON2Object exception\n";
      JSON2Object_appendEI(e, lv_exception_ptr, 0);
    }

  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      std::cout << (lv_exception_ptr->info_vector).size() << std::endl;
      std::cout << *(lv_exception_ptr->dump2JSON()) << std::endl;
      lv_exception_ptr->myDestructor();
    }

  // Json::Value *jv2 = post_ptr->dump2JSON();
  // if (jv2 != NULL)
  // {
      // std::cout << *jv2 << std::endl;
  // }
  // else
  // {
      // printf("jv2 NULL\n");
  // }
  //  delete post_ptr;
  //  std::cout << jv << std::endl;
  //  return 0;
  
  HttpClient httpclient("https://ethikos.ngrok.io");
  // HttpClient httpclient("http://localhost:8384");
  // HttpClient httpclient("http://169.237.6.102:55407");
  // HttpClient httpclient("http://169.237.6.102:55408");
  ecs36bClient myClient(httpclient, JSONRPC_CLIENT_V2);

  Json::Value result_json;

  try {
    // std::cout << (post_ptr->dump2JSON())->toStyledString() << std::endl;
    // result_json = myClient.update((post_ptr->dump2JSON())->toStyledString());
    result_json = myClient.update(jv.toStyledString());
    std::cout << result_json.toStyledString() << endl;
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  return 0;
}
