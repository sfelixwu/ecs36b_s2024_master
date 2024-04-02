
#ifndef _REACTION_H_
#define _REACTION_H_

// Reaction.h
#include "Core.h"
#include "Person.h"
#include "JvTime.h"

class Reaction : public Core
{
 private:
 protected:
 public:
  std::string type;
  Person * author;
  JvTime * created;

  Reaction();
  ~Reaction();
  Reaction(std::string arg_type, Person * arg_author, JvTime * arg_created);
  
  bool operator==(Reaction& aReaction);
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _REACTION_H_ */
