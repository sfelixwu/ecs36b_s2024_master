
#ifndef _COMMUTABLE_H_
#define _COMMUTABLE_H_

// Commutable.h

#include "Core.h"

class Commutable : public Core
{
private:
public:
  Commutable();
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif  /* _COMMUTABLE_H_ */
