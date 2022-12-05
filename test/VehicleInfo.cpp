#include "VehicleInfo.h"

using namespace std;

VehicleInfo::VehicleInfo (void){
  this->description = "";

}

VehicleInfo::VehicleInfo (string description){
  this->description = description;

}

void VehicleInfo::setDescription (string description){
  this->description = description;

}

void VehicleInfo::setDescriptionL (string descriptionL){
  this->descriptionL = descriptionL;

}

void VehicleInfo::setDescriptionR (string descriptionR){
  this->descriptionR = descriptionR;

}

void VehicleInfo::setName (string name){
  this->name = name;
}

Json::Value VehicleInfo::dump2JSON(void){
  Json::Value result { };
  
  if (this->description != ""){
    result["Autonomous Vehicle"] = this->description;
  }

   if (this->descriptionL != ""){
    result["Left Motorcycle"] = this->descriptionL;
  }

   if (this->descriptionR != ""){
    result["Right Motorcycle"] = this->descriptionR;
  }

  if (this->name != ""){
    result["Item"] = this->name;
  }

  return result;
}

bool VehicleInfo::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  this->description = (arg_jv["Item"]).asString();

  this->name = (arg_jv["Item"]).asString();

  return true;
}