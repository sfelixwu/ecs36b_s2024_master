
#ifndef _POST_H_
#define _POST_H_

// Post.h
#include "Core.h"

#include "OKey.h"
#include "Tag.h"
#include "Comment.h"
#include "Reaction.h"
#include "Message.h"
#include "Person.h"
#include "Link.h"
#include "Action.h"
#include "JvTime.h"

class OKey;

class Post : public Core
{
 private:
 protected:
 public:
  Identifier                   id;
  Person                     * author;
  std::vector<Person      *> * receivers;

  Message                    * msg;
  // std::vector<Message     *> * msg_revisions;

  std::vector<Action      *> * actions;
  std::vector<Comment     *> * comments;
  std::vector<Link        *> * links;
  std::vector<Reaction    *> * reactions;
  std::vector<OKey        *> * keys;
  std::vector<JSON_Diff   *> * differences;
  
  JvTime                     * created;
  JvTime                     * updated;
  GPS_DD                     * location;
  bool                         is_published;

  Post();
  ~Post();
  Post(Person * arg_author, Message * arg_msg);
  
  bool operator==(Post aPost);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _POST_H_ */
