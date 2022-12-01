
#include "JvTime.h"
#include "string.h"

using namespace std;

JvTime::JvTime()
{
  this->time = "";
}

JvTime::JvTime(string arg_time)
{
  this->time = arg_time;
}

string JvTime::getTime(){
  return this->time;
}

Json::Value JvTime::dump2JSON(){
  Json::Value result;
  
  if(this->time != ""){
    result["time"] = this->getTime();
  }
  return result;
}

bool JvTime::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  // if ((arg_jv["time"]).isNull() == true || (arg_jv["time"]).isString() != true) {
  //   return false;
  // }

  this->time = (arg_jv["time"]).asString();

  return true;
}