
#ifndef _THING_H_
#define _THING_H_

// Thing.h

#include "Core.h"

using namespace std;

class Thing : public Core
{
 private:
 protected:
 public:
  
  std::string url;
  std::string model;
  std::string description;
  unsigned int sequence_num;

  Thing(void);
  bool operator==(const Thing&);
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _THING_H_ */
