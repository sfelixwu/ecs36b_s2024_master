
#ifndef _COMMENT_H_
#define _COMMENT_H_

// Comment.h
#include "Core.h"
#include "Tag.h"
#include "Reaction.h"
#include "Message.h"
#include "Person.h"
#include "JvTime.h"

class Comment : public Core
{
 private:
 protected:
 public:
  Identifier                id;
  Person                  * author;
  Message                 * msg;
  JvTime                  * created;

  std::vector<Reaction *> * reactions;
  std::vector<Tag *>      * tags;

  Comment();
  Comment(std::string arg_profile_id, std::string arg_post_id, std::string arg_comment_id,
	  Person * arg_author, Message * arg_msg, JvTime * arg_created);
  ~Comment();
  bool operator==(Comment& aComment);
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _COMMENT_H_ */
