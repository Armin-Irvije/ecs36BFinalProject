#include "Thing.h"

using namespace std;

Thing::Thing (void){
  this->description = "";
  // this->owner = Person {};
  // this->given_to_child = JvTime {};
  // this->given_to_grandma = JvTime {};
  this->location = GPS_DD {};
}

Thing::Thing (string description){
  this->description = description;
  // this->owner = Person {};
  // this->given_to_child = JvTime {};
  // this->given_to_grandma = JvTime {};
  this->location = GPS_DD {};
}

Thing::Thing (string description, /*Person owner, JvTime child, JvTime grandma,*/ GPS_DD location){
  this->description = description;
  // this->owner = owner;
  // this->given_to_child = child;
  // this->given_to_grandma = grandma;
  this->location = location;
}

Json::Value Thing::dump2JSON(void){
  Json::Value result { };
  
  if (this->description != ""){
    result["description"] = this->description;
  }

  Json::Value jv_result;
  
  // jv_result = (this->owner).dump2JSON();
  // if(!jv_result.isNull()){
  //   result["owner"] = jv_result;
  // }
  // jv_result = (this->given_to_child).dump2JSON();
  // if((result["given to child"]).isNull() == true){
  //   result["given to child"] = jv_result;
  // }

  // jv_result = (this->given_to_grandma).dump2JSON();
  // if((result["given to grandma"]).isNull() == true){
  //   result["given to grandma"] = jv_result;
  // }

  jv_result = (this->location).dump2JSON();
  if(!jv_result.isNull()){
    result["location"] = jv_result;
  }
  // std::cout << jv_result.toStyledString() << std::endl;

  return result;
}

bool Thing::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  // if ((arg_jv["description"]).isNull() == true || (arg_jv["descrption"]).isString() != true) {
  //   return false;
  // }
  this->description = (arg_jv["description"]).asString();


  // if ((arg_jv["owner"]).isNull() == true || (arg_jv["owner"]).isObject() != true){
  //   return false;
  // }
  // (this->owner).JSON2Object(arg_jv["owner"]);


  // if ((arg_jv["location"]).isNull() == true || (arg_jv["location"]).isObject() != true){
  //   return false;
  // } 
  (this->location).JSON2Object(arg_jv["location"]);

  return true;
}