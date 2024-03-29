#include "ClassHierarchy.h"

using namespace std;


ClassHierarchy::ClassHierarchy (void){
    this->description = "";
 }

ClassHierarchy::ClassHierarchy (string description){
 this->description = description;
 }

void ClassHierarchy::setInfo(double speed, double weight, double wheels, double cap){
  SpeedofVehicle = speed;
  WeightofVehicle = weight;
  NumberofWheels = wheels;
  Capacity = cap;
}

void ClassHierarchy::setDescription (string description){
  this->description = description;

}

void ClassHierarchy::setDescriptionL (string descriptionL){
  this->descriptionL = descriptionL;

}

void ClassHierarchy::setDescriptionR (string descriptionR){
  this->descriptionR = descriptionR;

}

void ClassHierarchy::setName (string name){
  this->name = name;
}

void ClassHierarchy::alert(string alertsend){
  this->alertsend = alertsend;

}

bool Car::getFatalityRisk(){
double speedL = 67;
double speedR = 76;
double weightL = 736;
double weightR = 842;
double wheelsL = 2;
double wheelsR = 2;
double capL = 1;
double capR = 2;
bool risk;

double riskL = (speedL + weightL + wheelsL + capL) / 4;
double riskR = (speedR + weightR + wheelsR + capR) / 4;

if (riskL > riskR){
  risk = false;
} else {
  risk = true;
}
  return risk;
}

void Motorcycle::MotorcycleSeatEjector(string eject){
  this->eject = eject;
}


Json::Value ClassHierarchy::dump2JSON(void){
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

  if (this->alertsend != ""){
    result["Alert"] = this->alertsend;
  }
  if (this->name != ""){
    result["Item"] = this->name;
  }
  if (this->SpeedofVehicle != -1){
    result["Speed (miles/hr)"] = this->SpeedofVehicle;
  }
  if (this->WeightofVehicle != -1){
    result["Weight (lbs)"] = this->WeightofVehicle;
  }
  if (this->NumberofWheels != -1){
    result["Number of Wheels"] = this->NumberofWheels;
  }
  if (this->Capacity != -1){
    result["Capacity"] = this->Capacity;
  }
   if (this->eject != ""){
    result["_Ejection Status_"] = this->eject;
  }
  

  return result;
}



bool ClassHierarchy::JSON2Object(Json::Value arg_jv){

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true)){
    return false;
  }

  this->description = (arg_jv["Item"]).asString();

  this->name = (arg_jv["Item"]).asString();

  return true;

}