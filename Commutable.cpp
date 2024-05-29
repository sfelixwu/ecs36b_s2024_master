
#include "Commutable.h"

Commutable::Commutable()
{
  this->class_name = "Commutable";
}

Json::Value *
Commutable::dump2JSON
(void)
{
  Json::Value * result_ptr = new Json::Value();
  (*result_ptr)["class name"] = "Commutable";
  return result_ptr;
}

void
Commutable::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception * lv_exception_ptr = new ecs36b_Exception();

  JSON2Object_precheck(arg_json_ptr, lv_exception_ptr,
		       ECS36B_ERROR_JSON2OBJECT_COMMUTABLE);

  // work on this more later...
  
  if ((lv_exception_ptr->info_vector).size() != 0)
    {
      throw (*lv_exception_ptr);
    }

  return;
}

