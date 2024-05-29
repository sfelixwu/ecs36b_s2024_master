
#include "ecs36b_Exception.h"

void
ecs36b_Exception::myDestructor
(void)
{
  int i;

  // std::cout << "my destructor ecs36b_Exception\n";
  // std::cout << this << std::endl;

  for (i = 0; i < (this->info_vector).size(); i++)
    {
      if (info_vector[i] != NULL)
	{
	  delete info_vector[i];
	}
    }
  
  return;
}

Json::Value *
ecs36b_Exception::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  int i;
  
  Json::Value json_info;
  Json::Value json_info_array;

  for (i = 0; i < (this->info_vector).size(); i++)
    {
      Json::Value * dumpjv_ptr = new Json::Value();
      (*dumpjv_ptr)["where"]  = error_string(((this->info_vector)[i])->where_code);
      (*dumpjv_ptr)["what"]   = error_string(((this->info_vector)[i])->what_code);
      (*dumpjv_ptr)["which"]  = ((this->info_vector)[i])->which_string;
      (*dumpjv_ptr)["how"]    = error_string(((this->info_vector)[i])->how_code);
      (*dumpjv_ptr)["index"]  = ((this->info_vector)[i])->array_index;
      json_info[i] = (*dumpjv_ptr);
      delete dumpjv_ptr;
    }
  json_info_array["data"] = json_info;
  json_info_array["count"] = ((int) (this->info_vector).size());
  (*result_ptr)["ecs36b exceptions"] = json_info_array;
  return result_ptr;
}
