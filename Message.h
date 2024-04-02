
#ifndef _MESSAGE_H_
#define _MESSAGE_H_

// Message.h
#include "Core.h"
#include "JvTime.h"

class Message : public Core
{
 private:
 protected:
 public:
  
  std::string content;
  Message(void);
  Message(std::string arg_s);
  void setContent(std::string arg_s);
  std::string getContent(void);
  
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _MESSAGE_H_ */
