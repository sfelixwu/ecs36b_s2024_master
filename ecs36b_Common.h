
#ifndef _ECS36B_COMMON_H_
#define _ECS36B_COMMON_H_

// ecs36b_Common.h

#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <ctime>
#include <exception> 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

// c library
#include <arpa/inet.h>

using namespace std;
#include "ecs36b_Exception.h"

// utility functions
void myPrintLog(std::string content, std::string fname);
int myParseJSON(std::string input, Json::Value * jv_ptr);
char *myFile2String(char *f_name);
int myFile2JSON(char *f_name, Json::Value * jv_ptr);
int myJSON2File(char *f_name, Json::Value * jv_ptr);
int checkPostID(std::string);
int checkBigID(std::string);
const char * error_string(int);
bool check_JSON_Keys(vector<std::string>, Json::Value);
vector<std::string> matchDirent(std::string, std::string, std::string);

class JvTime;

class JSON_Diff
{
private:
protected:
public:
  unsigned int order;
  vector<std::string> key_path; // including array index?
  std::string type;
  Json::Value diff;
  JvTime *updated;
  JSON_Diff(void) { this->order = 0; this->type = ""; this->updated = NULL;}
  ~JSON_Diff(void);
  Json::Value * dump2JSON(void);
};

vector<JSON_Diff *> * JSON_Difference(Json::Value, Json::Value, vector<std::string>);

// for profile, post, comment IDs.
class Identifier
{
private:
protected:
public:
  std::string                  profile;
  std::string                  post;
  std::string                  comment;

  Identifier(void) { this->profile = ""; this->post = ""; this->comment = ""; };
  std::string get(void);
  int setPP(std::string);
  int setPPC(std::string);
  
  bool operator==(Identifier aIdentifier);
};

// error code
#define ECS36B_ERROR_NORMAL                         0
#define ECS36B_ERROR_VSID_HISTORY                  -1
#define ECS36B_ERROR_VSID_POST_ID                  -2
#define ECS36B_ERROR_JSON_POST_MERGING             -3
#define ECS36B_ERROR_LRESULT_LSIZE                 -4
#define ECS36B_ERROR_JSON_PARSING                  -5
#define ECS36B_ERROR_JSON_2_POST                   -6
#define ECS36B_ERROR_JSON_POST_NO_ID               -7
#define ECS36B_ERROR_NULL_JSON_PTR                 -8
#define ECS36B_ERROR_FILE_NOT_EXIST                -9
#define ECS36B_ERROR_FILE_READ                    -10
#define ECS36B_ERROR_FILE_NAME_PTR_NULL           -11
#define ECS36B_ERROR_FILE_WRITE                   -12
#define ECS36B_ERROR_LESS_THAN_20                 -13
#define ECS36B_ERROR_NO_SEARCH_KEYWORD            -14
#define ECS36B_ERROR_NO_OKEY                      -15
#define ECS36B_ERROR_NO_OKEY_STRANGE              -16
#define ECS36B_ERROR_SMACK_STACK_DETECTED         -17
#define ECS36B_ERROR_BAD_KEYWORD_FORMAT           -18
#define ECS36B_ERROR_SET_STD_TM                   -19
#define ECS36B_ERROR_NULL_CPP_PTR                 -20
#define ECS36B_ERROR_POST_ID_MISMATCHED           -21
#define ECS36B_ERROR_SUSPICIOUS                   -22
#define ECS36B_ERROR_JSON2OBJECT_ACTION           -23
#define ECS36B_ERROR_JSON2OBJECT_COMMENT          -24
#define ECS36B_ERROR_JSON2OBJECT_COMMUTABLE       -25
#define ECS36B_ERROR_JSON2OBJECT_CORE             -26
#define ECS36B_ERROR_JSON2OBJECT_GPS_DD           -27
#define ECS36B_ERROR_JSON2OBJECT_HOLDABLE         -28
#define ECS36B_ERROR_JSON2OBJECT_JVTIME           -29
#define ECS36B_ERROR_JSON2OBJECT_LABELED_GPS      -30
#define ECS36B_ERROR_JSON2OBJECT_LINK             -31
#define ECS36B_ERROR_JSON2OBJECT_LOCATABLE        -32
#define ECS36B_ERROR_JSON2OBJECT_MESSAGE          -33
#define ECS36B_ERROR_JSON2OBJECT_OKEY             -34
#define ECS36B_ERROR_JSON2OBJECT_PERSON           -35
#define ECS36B_ERROR_JSON2OBJECT_POST             -36
#define ECS36B_ERROR_JSON2OBJECT_REACTION         -37
#define ECS36B_ERROR_JSON2OBJECT_RECORD           -38
#define ECS36B_ERROR_JSON2OBJECT_TAG              -39
#define ECS36B_ERROR_JSON2OBJECT_TEAM             -40
#define ECS36B_ERROR_JSON2OBJECT_THING            -41
#define ECS36B_ERROR_JSON_KEY_MISSING             -42
#define ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED     -43
#define ECS36B_ERROR_TIME_STRING_FORMAT           -44
#define ECS36B_ERROR_POST_ID_CHECK_FAILED         -45
#define ECS36B_ERROR_JSONRPC_SERVER               -46
#define ECS36B_ERROR_JSONRPC_CLIENT               -47
#define ECS36B_ERROR_STRLEN_GE_1023               -48
#define ECS36B_ERROR_ID_SET_TWICE                 -49
#define ECS36B_ERROR_JSON2OBJECT_TIMED_LOCATION   -50
#define ECS36B_ERROR_JSON2OBJECT_PERSONAL_TIMED_GPS_RECORD   -51
#define ECS36B_ERROR_MAX                          -52

extern const vector<std::string> keys_Thing;
extern const vector<std::string> keys_Locatable;
extern const vector<std::string> keys_Holdable;

#endif /* _ECS36B_COMMON_H_ */
