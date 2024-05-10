
#include "Labeled_GPS.h"

Labeled_GPS::Labeled_GPS
()
{
  this->class_name = "Labeled_GPS";

  this->label = "default";
}

Labeled_GPS::Labeled_GPS
(double arg_latitude, double arg_longitude, std::string arg_label)
  : GPS_DD(arg_latitude, arg_longitude)
{
  this->class_name = "Labeled_GPS";

  this->label = arg_label;
}

bool
Labeled_GPS::setGPSLabel
(std::string arg_label)
{
  this->label = arg_label;
  return true;
}

bool
Labeled_GPS::operator==
(Labeled_GPS another)
{
  return((this->latitude == another.getLatitude()) &&
	 (this->longitude == another.getLongitude()) &&
	 (this->label == another.label));
}

Json::Value *
Labeled_GPS::dump2JSON
()
{
  // option #1
  // v-table pointer will link to the class GPS_DD (becuase of object creation)
  // GPS_DD parent_copy = (*this);
  // parent_copy is a GPS_DD object without the Labeled_GPS derived portion
  // Json::Value result = parent_copy.dump2JSON();

  // option #2
  // force the compiler to link to the parent version of dump2JSON()
  Json::Value * result_ptr = this->GPS_DD::dump2JSON();
  if (result_ptr == NULL) return NULL;
  
  // the following is a wrong option
  // Json::Value result = ((GPS_DD *) this)->dump2JSON();
  // Json::Value result = ((GPS_DD&) (*this)).dump2JSON();
  // Json::Value result = (*((GPS_DD *) this)).dump2JSON();
  
  if (this->label != "default")
    {
      (*result_ptr)["label"] = this->label;
    }

  return result_ptr;
}

void
Labeled_GPS::JSON2Object
(Json::Value * arg_json_ptr)
{
  Exception_Info * ei_ptr = NULL;
  ecs36b_Exception lv_exception {};

  if (arg_json_ptr == ((Json::Value *) NULL))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_LABELED_GPS;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;
      ei_ptr->what_code = ECS36B_ERROR_NULL_JSON_PTR;
      (lv_exception.info_vector).push_back(ei_ptr);
      throw lv_exception;
    }

  if ((arg_json_ptr->isNull() == true) ||
      (arg_json_ptr->isObject() != true))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_LABELED_GPS;
      ei_ptr->which_string = "default";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if (arg_json_ptr->isNull() == true)
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      (lv_exception.info_vector).push_back(ei_ptr);
      throw lv_exception;
    }

  try
    {
      // segmentation fault: this->JSON2Object(arg_json_ptr);
      this->GPS_DD::JSON2Object(arg_json_ptr);
    }
  catch(ecs36b_Exception e)
    {
      int i;
      for (i = 0; i < (e.info_vector).size(); i++)
	{
	  (lv_exception.info_vector).push_back((e.info_vector)[i]);
	}
    }
  
  if (((*arg_json_ptr)["label"].isNull() == true) ||
      ((*arg_json_ptr)["label"].isString() == false))
    {
      ei_ptr = new Exception_Info {};
      ei_ptr->where_code = ECS36B_ERROR_JSON2OBJECT_LABELED_GPS;
      ei_ptr->which_string = "label";
      ei_ptr->how_code = ECS36B_ERROR_NORMAL;

      if ((*arg_json_ptr)["label"].isNull() == true)
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_MISSING;
	}
      else
	{
	  ei_ptr->what_code = ECS36B_ERROR_JSON_KEY_TYPE_MISMATCHED;
	}
      (lv_exception.info_vector).push_back(ei_ptr);
    }
  else
    {
      this->label = ((*arg_json_ptr)["label"]).asString();
    }

  if ((lv_exception.info_vector).size() != 0)
    {
      throw lv_exception;
    }

  return;
}
