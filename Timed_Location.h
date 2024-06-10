
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

  bool operator==(Timed_Location& another);
  bool operator!=(Timed_Location& another);
  bool operator< (Timed_Location& another);
  bool operator> (Timed_Location& another);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

void TL_Sort(std::vector<Timed_Location>&);
std::vector<Timed_Location> * TL_Unique(std::vector<Timed_Location>&);

#endif /* _TIMED_LOCATION_H_ */
