
#ifndef _PERSON_H_
#define _PERSON_H_

// Person.h

#include "Commutable.h"

#include "GPS.h"
#include "JvTime.h"

using namespace std;

// class Person : public Commutable

class Person : public Core
{
private:
protected:
public:
  std::string vsID;
  std::string name;
  GPS_DD * home;
  
  Person(std::string, std::string);
  Person(std::string, std::string, GPS_DD *);
  Person();
  ~Person();
  
  void setHome(GPS_DD *);
  std::string getvsID();
  std::string getName();
  GPS_DD * getHome();

  bool operator==(Person& aPerson);

  virtual Json::Value * dump2JSON(void);
  virtual void JSON2Object(Json::Value *);
};

#endif  /* _PERSON_H_ */
