
#ifndef _TAG_H_
#define _TAG_H_

// Tag.h
#include "Core.h"
#include "Person.h"

class Tag : public Core
{
 private:
 protected:
 public:
  int index;
  Person * tagged;
  std::string comment;

  Tag(void);
  Tag(int arg_index, Person * arg_tagged, std::string arg_comment);
  ~Tag(void);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _TAG_H_ */
