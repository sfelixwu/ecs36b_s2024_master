
#include "Personal_Timed_GPS_Record.h"

Personal_Timed_GPS_Record::Personal_Timed_GPS_Record()
{
  this->identity = "N/A";
}

bool
Personal_Timed_GPS_Record::upload
(Json::Value arg_jv)
{
  try
    {
      this->JSON2Object(&arg_jv);
    }
  catch(ecs36b_Exception e)
    {
      return false;
    }

  return true;
}

GPS_DD
Personal_Timed_GPS_Record::question
(JvTime arg_jvt)
{
  GPS_DD default_gps { 0.0, 0.0 };
  
  int i;
  Json::Value *jv_ptr = (Json::Value *) NULL;

  std::string jvt_s;
  std::string id_str;

  for (i = 0; i < this->traces.size(); i++)
    {
      double time_diff = arg_jvt - ((this->traces)[i]).time;
      if (time_diff > 0)
	{
	  default_gps = ((this->traces)[i]).location;
	}
    }

  return default_gps;
}

Personal_Timed_GPS_Record *
Personal_Timed_GPS_Record::operator->
(void)
{
  return this;
}

Json::Value *
Personal_Timed_GPS_Record::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  Json::Value * jv_ptr     = NULL;
  
  (*result_ptr)["identity"] = this->identity;

  int i;
  for (i = 0; i < (this->traces).size(); i++)
    {
      jv_ptr = ((this->traces)[i]).dump2JSON();
      if (jv_ptr != NULL)
	{
	  (*result_ptr)["traces"][i] = (*jv_ptr);
	  delete jv_ptr;
	}
    }
  return result_ptr;
}

void
Personal_Timed_GPS_Record::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception lv_exception {};
  ecs36b_Exception * lv_exception_ptr = &lv_exception;

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_PERSONAL_TIMED_GPS_RECORD);

  if ((((*arg_json_ptr)["identity"]).isNull() == true) ||
      (((*arg_json_ptr)["identity"]).isString() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_PERSONAL_TIMED_GPS_RECORD;
      ei_ptr->which_string = "identity";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["identity"].isNull() == true)
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
	  this->identity = ((*arg_json_ptr)["identity"]).asString();
	}
      catch(ecs36b_Exception& e)
	{
	  JSON2Object_appendEI(e, lv_exception_ptr, 0);
	}
    }

  if ((((*arg_json_ptr)["traces"]).isNull() == true) ||
      (((*arg_json_ptr)["traces"]).isArray() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_PERSONAL_TIMED_GPS_RECORD;
      ei_ptr->which_string = "traces";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["traces"].isNull() == true)
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
      int ai;
      for (ai = 0; ai < ((*arg_json_ptr)["traces"]).size(); ai++)
	{
	  try
	    {
	      Timed_Location *lvTL_ptr = new Timed_Location();
	      lvTL_ptr->JSON2Object(&((*arg_json_ptr)["traces"][ai]));
	      this->traces.push_back(*(lvTL_ptr));
	      delete lvTL_ptr;
	    }
	  catch(ecs36b_Exception& e)
	    {
	      JSON2Object_appendEI(e, lv_exception_ptr, ai);
	    }
	}
    }
  
  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}

Shadow_Record::Shadow_Record()
{
  this->identity = "N/A";
}

bool
Shadow_Record::upload
(Json::Value arg_jv)
{
  HttpClient httpclient((this->host_url).c_str());
  hw3ref3Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  try {
    result = myClient.upload(arg_jv);

    std::cout << result << std::endl;
    
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  // std::cout << result << std::endl;
  return true;
}

GPS_DD
Shadow_Record::question
(JvTime arg_jvt)
{
  HttpClient httpclient((this->host_url).c_str());
  hw3ref3Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  Json::Value *jv_ptr = new Json::Value ();
  
  try {
    (*jv_ptr)["time"] = *(arg_jvt.dump2JSON());
    (*jv_ptr)["identity"] = this->identity;
    result = myClient.question(*jv_ptr);
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  if (jv_ptr != NULL) delete jv_ptr;
  
  GPS_DD answer;
  // std::cout << result << std::endl;
  if ((result["latitude"].isNull() == true)   ||
      (result["latitude"].isDouble() != true) ||
      (result["longitude"].isNull() == true)   ||
      (result["longitude"].isDouble() != true)
      )
    {
      answer.latitude  = 0.0;
      answer.longitude = 0.0;
    }
  else
    {
      answer.JSON2Object(&result);
    }

  // std::cout << result << std::endl;
  
  return answer;
}

Personal_Timed_GPS_Record *
Shadow_Record::operator->
(void)
{
  // make sure that we avoid the pointer operator here!!
  HttpClient httpclient(((*this).host_url).c_str());
  hw3ref3Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  try {
    result = myClient.dump2json((*this).identity);
    // let us copy from the remote
    Personal_Timed_GPS_Record::JSON2Object(&result);
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  // std::cout << (result["traces"]).size() << std::endl;
  // std::cout << ((*this).traces).size() << std::endl;

  return this;
}

Json::Value *
Shadow_Record::dump2JSON
(void)
{
  HttpClient httpclient((this->host_url).c_str());
  hw3ref3Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value result;

  try {
    result = myClient.dump2json((*this).identity);
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  Json::Value * result_ptr = new Json::Value();
  (*result_ptr) = result;
  return result_ptr;
}

void
Shadow_Record::JSON2Object
(Json::Value * arg_json_ptr)
{
  // TBDLr
  return;
}
