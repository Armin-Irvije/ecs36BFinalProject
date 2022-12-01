
#include "Record.h"

Record::Record(){
  this->description = "";
  this->location = GPS_DD {};
  this->when = JvTime {};
  this->what = Thing {};
  this->who = Person {};
}

Record::Record(string arg_description, GPS_DD arg_where, JvTime arg_when, Thing thing, Person person ){
  this->description = arg_description;
  this->location = arg_where;
  this->when = arg_when;
  this->what = thing;
  this->who = person;
}

// bool Record::operator == (Record& aRecord){
//   return (this->when) == aRecord.getTime();
// }

Json::Value Record::dump2JSON (void){

  Json::Value result { };

  if(this->description != ""){
    result["description"] = this->description;
  }

  Json::Value jv_result;
    
  jv_result = (this->location).dump2JSON();
  if(!jv_result.isNull()){
    result["location"] = jv_result;
  }

  jv_result = (this->when).dump2JSON();
  if(!jv_result.isNull()){
    result["when"] = jv_result;
  }

  jv_result = (this->what).dump2JSON();
  if(!jv_result.isNull()){
    result["what"] = jv_result;
  }

  jv_result = (this->who).dump2JSON();
  if(!jv_result.isNull()){
    result["who"] = jv_result;
  }
  return result;
}

bool Record::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  // if ((arg_jv["description"]).isNull() == true || (arg_jv["description"]).isString() != true) {
  //   return false;
  // }
  this->description = (arg_jv["description"]).asString();


  // if ((arg_jv["location"]).isNull() == true || (arg_jv["location"]).isObject() != true){
  //   return false;
  // }
  (this->location).JSON2Object(arg_jv["location"]);


  // if ((arg_jv["what"]).isNull() == true || (arg_jv["what"]).isObject() != true){
  //   return false;
  // }
  (this->what).JSON2Object(arg_jv["what"]);


  // if ((arg_jv["when"]).isNull() == true || (arg_jv["when"]).isObject() != true){
  //   return false;
  // }
  (this->when).JSON2Object(arg_jv["when"]);


  // if ((arg_jv["who"]).isNull() == true || (arg_jv["who"]).isObject() != true){
  //   return false;
  // }
  (this->who).JSON2Object(arg_jv["who"]);
  
  return true;
}