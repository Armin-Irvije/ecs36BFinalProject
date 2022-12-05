#include "Person.h"


//   int SpeedofVehicle;
//   int WeightofVehicle;
//   int SpeedofVehicle;
//   int NumberofWheels;
//   int Capacity;
//   bool sensor;


using namespace std;

Person::Person(string arg_name){
  this->description = arg_name;
}

Person::Person(){
  this->description = "";
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
    result["Person"] = this->description;
  }

  return result;
}

bool Person::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  this->description = (arg_jv["Person"]).asString();

  return true;
}