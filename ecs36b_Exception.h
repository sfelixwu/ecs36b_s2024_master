//

#ifndef _ECS36B_EXCEPTION_
#define _ECS36B_EXCEPTION_

#include "ecs36b_Common.h"

class Exception_Info
{
private:
protected:
public:
  int where_code;
  int what_code;
  std::string which_string;
  int how_code;
  unsigned int array_index;
  Exception_Info() { array_index = 0; }
  Exception_Info& operator=(Exception_Info& aExceptionInfo)
  {
    this->where_code   = aExceptionInfo.where_code;    // location, which class
    this->what_code    = aExceptionInfo.what_code;     // error content
    this->which_string = aExceptionInfo.which_string;  // which attribute
    this->how_code     = aExceptionInfo.how_code;      // which function pointer (future)
    this->array_index  = aExceptionInfo.array_index;
    // std::cout << "copy Exception_Info\n";
    return (*this);
  }
};

class ecs36b_Exception : public std::exception
{
private:
protected:
public:
  std::vector<Exception_Info *> info_vector; // we could consider map or Json::Value
  
  void myDestructor(void);
  ~ecs36b_Exception() throw () {}
  virtual const char* what() const throw () { return "ecs36b exception"; }
  virtual Json::Value * dump2JSON(void);  
};

int produceErrorJSON(ecs36b_Exception, const char [], Json::Value *, int);
void JSON2Object_precheck(Json::Value *, ecs36b_Exception *, int);
void JSON2Object_appendEI(ecs36b_Exception&, ecs36b_Exception *, unsigned int);

#endif /* _ECS36B_EXCEPTION_ */
