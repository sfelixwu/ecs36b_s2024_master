
#ifndef _LOCATABLE_H_
#define _LOCATABLE_H_

// Locatable.h

#include "Thing.h"
#include "GPS.h"

using namespace std;

class Locatable : public Thing
{
 private:
 protected:
 public:

  GPS_DD      * location;
  
  Locatable(void);
  ~Locatable(void);

  bool operator==(Locatable&);
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _LOCATABLE_H_ */
