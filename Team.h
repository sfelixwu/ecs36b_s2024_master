
#ifndef _TEAM_H_
#define _TEAM_H_

// Team.h

#include "Commutable.h"
#include "Person.h"

class Team : public Commutable
{
 private:
 protected:
 public:

  std::string              name;
  std::vector<Person *>  * members;
  
  Team(void);
  bool setName(const std::string&);
  bool addAMember(Person *);
  virtual Json::Value * dump2JSON(void); // print the content of the object
  virtual void JSON2Object(Json::Value *);
};

#endif /* _TEAM_H_ */
