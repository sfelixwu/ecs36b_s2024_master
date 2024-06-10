
#ifndef _ACTION_H_
#define _ACTION_H_

#include "Core.h"

class Action : public Core
{
 private:
 protected:
 public:
  std::string name;
  Action();
  Action(std::string, std::string, std::string, std::string);

  bool operator==(Action& aAction);
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _ACTION_H_ */
