
#ifndef _TIMED_LOCATION_H_
#define _TIMED_LOCATION_H_

// Timed_Location.h

#include "Core.h"
#include "GPS.h"
#include "JvTime.h"

using namespace std;

class Timed_Location : public Core
{
 private:
 protected:
 public:
  GPS_DD location;
  JvTime time;

  Timed_Location();
  Timed_Location(GPS_DD, JvTime);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _TIMED_LOCATION_H_ */
