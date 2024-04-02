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
  Exception_Info() { }
  Exception_Info& operator=(Exception_Info& aExceptionInfo)
  {
    this->where_code   = aExceptionInfo.where_code;
    this->what_code    = aExceptionInfo.what_code;
    this->which_string = aExceptionInfo.which_string;
    this->how_code     = aExceptionInfo.how_code;
    // std::cout << "copy Exception_Info\n";
    return (*this);
  }
};

class ecs36b_Exception : public std::exception
{
private:
protected:
public:
  std::vector<Exception_Info *> info_vector;
  
  void myDestructor(void);
  ~ecs36b_Exception() throw () {}
  virtual const char* what() const throw () { return "ecs36b exception"; }
  virtual Json::Value * dump2JSON(void);  
};

int produceErrorJSON(ecs36b_Exception, const char [], Json::Value *, int);

#endif /* _ECS36B_EXCEPTION_ */
