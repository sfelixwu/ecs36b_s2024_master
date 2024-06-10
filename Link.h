
#ifndef _LINK_H_
#define _LINK_H_

// Link.h
#include "Core.h"

class Link : public Core
{
 private:
 protected:
 public:
  std::string url;

  Link();
  Link(std::string arg_url);

  bool operator==(Link& aLink);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _LINK_H_ */
