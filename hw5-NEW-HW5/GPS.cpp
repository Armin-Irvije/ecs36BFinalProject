
#include "GPS.h"

using namespace std;

GPS_DD::GPS_DD(){
  this->location = "";
}

GPS_DD::GPS_DD(string arg_location){
  this->location = arg_location;
}

string GPS_DD::getLocation(){
  return this->location;
}

Json::Value GPS_DD::dump2JSON(){
  
  Json::Value result;
  if (this->location != "")
    {
      result["location"] = this->location;
    }
    
  return result;
}

bool GPS_DD::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  // if ((arg_jv["location"]).isNull() == true || (arg_jv["location"]).isString() != true) {
  //   return false;
  // }

  this->location = (arg_jv["location"]).asString();

  return true;
}