
#ifndef _CORE_H_
#define _CORE_H_

// Core.h

#include "ecs36b_Common.h"
#include "ecs36b_Exception.h"

using namespace std;

class Core
{
 private:
 public:
  static unsigned int core_count;

  std::string host_url;
  std::string class_name;
  std::string object_id;
  std::string owner_vsID;
  
  Json::Value json_repr; // typically output from dump2JSON
  
  Core(void);
  Core(std::string, std::string, std::string);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif  /* _CORE_H_ */
