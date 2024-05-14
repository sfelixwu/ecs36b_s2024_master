
#ifndef _PERSONAL_TIMED_GPS_RECORD_H_
#define _PERSONAL_TIMED_GPS_RECORD_H_

// Personal_Timed_GPS_Record.h

#include "Core.h"
#include "Timed_Location.h"

#include <stdlib.h>
#include "hw3ref3client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace std;
using namespace jsonrpc;

class Personal_Timed_GPS_Record : public Core
{
 private:
 protected:
 public:

  std::string identity;
  vector<Timed_Location> traces;

  Personal_Timed_GPS_Record();

  void sort(void);
  void unique(void);

  virtual bool upload(Json::Value);
  virtual GPS_DD question(JvTime);

  // remote ==> on a different space
  // pointer ==> some address on the same memory space
  
  virtual Personal_Timed_GPS_Record * operator->();
  
  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};


class Shadow_Record: public Personal_Timed_GPS_Record
{
 private:
 protected:
 public:

  Shadow_Record();
  
  virtual bool upload(Json::Value);
  virtual GPS_DD question(JvTime);
  virtual Personal_Timed_GPS_Record * operator->();

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif /* _PERSONAL_TIMED_GPS_RECORD_H_ */
