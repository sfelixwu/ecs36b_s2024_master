
#ifndef _HOLDABLE_H_
#define _HOLDABLE_H_

// Holdable.h

#include "Locatable.h"
#include "Person.h"

using namespace std;

class Holdable : public Locatable
{
 private:
 protected:
 public:

  Person     * holder;
  
  Holdable(void);
  ~Holdable(void);
  bool operator==(Holdable&);
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value * arg_json_ptr);
};

#endif /* _HOLDABLE_H_ */
