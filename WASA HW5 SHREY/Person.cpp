#include "Person.h"

using namespace std;

Person::Person(string arg_name){
  this->description = arg_name;
  // this->home = arg_home;
}

Person::Person(){
  this->description = "";
  // this->home = GPS_DD {};
}

string Person::getName(){
  return this->description;
}

void Person::setDescription(string str){
  this->description = str;
}

bool Person::operator == (Person& aPerson){
  return (this->description == aPerson.getName());
}

Json::Value Person::dump2JSON(void){
  Json::Value result { };

  if (this->description != "")
  {
    result["description"] = this->description;
  }

  // Json::Value jv_result;
  
  // jv_result = (this->home).dump2JSON();
  // if(!jv_result.isNull()){
  //   result["home"] = jv_result;
  // }  
  // jv_result = (this->location).dump2JSON();
  // if(!jv_result.isNull()){
  //   result["location"] = jv_result;
  // }
  // jv_result = (this->since_when).dump2JSON();
  // if(!jv_result.isNull()){
  //   result["since_when"] = jv_result;
  // }
  return result;
}

bool Person::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  // if ((arg_jv["name"]).isNull() == true || (arg_jv["name"]).isString() != true) {
  //   return false;
  // }
  this->description = (arg_jv["description"]).asString();


  // if ((arg_jv["home"]).isNull() == true || (arg_jv["home"]).isObject() != true){
  //   return false;
  // }
  // (this->home).JSON2Object(arg_jv["home"]);


  // if ((arg_jv["location"]).isNull() == true || (arg_jv["location"]).isObject() != true){
  //   return false;
  // }
  // (this->location).JSON2Object(arg_jv["location"]);


  // if ((arg_jv["since_when"]).isNull() == true || (arg_jv["since_when"]).isObject() != true){
  //   return false;
  // }
  // (this->since_when).JSON2Object(arg_jv["since_when"]);


  return true;
}