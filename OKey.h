
#ifndef _OKEY_H_
#define _OKEY_H_

// OKey.h
#include "Core.h"
#include "Post.h"

class Post;

class OKey : public Core
{
 private:
 protected:
 public:
  std::string okey;
  std::vector<Post *> * posts;

  OKey()                     { this->okey = "";       this->posts = NULL; }
  OKey(std::string arg_okey) { this->okey = arg_okey; this->posts = NULL; }

  bool operator==(OKey&);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _OKEY_H_ */
