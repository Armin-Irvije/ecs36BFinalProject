#include "ClassHierarchy.h"

using namespace std;

ClassHierarchy::ClassHierarchy(void)
{
  this->description = "";
}

ClassHierarchy::ClassHierarchy(string description)
{
  this->description = description;
}

void ClassHierarchy::setInfo(double speed, double weight, double wheels, double cap)
{
  SpeedofVehicle = speed;
  WeightofVehicle = weight;
  NumberofWheels = wheels;
  Capacity = cap;
}

void ClassHierarchy::setName(string name)
{
  this->name = name;
}

void ClassHierarchy::alert(string alertsend)
{
  this->alertsend = alertsend;
}

double Car::getFatalityRisk(Motorcycle moto)
{
  return (moto.SpeedofVehicle + moto.WeightofVehicle + moto.NumberofWheels + moto.Capacity) / 4;
}

void Motorcycle::MotorcycleSeatEjector(string eject)
{
  this->eject = eject;
}

Json::Value ClassHierarchy::dump2JSON(void)
{
  Json::Value result{};

  if (this->alertsend != "")
  {
    result["Alert"] = this->alertsend;
  }
  if (this->name != "")
  {
    result["Vehicle"] = this->name;
  }
  if (this->SpeedofVehicle != 0)
  {
    result["Speed (miles/hr)"] = this->SpeedofVehicle;
  }
  if (this->WeightofVehicle != 0)
  {
    result["Weight (lbs)"] = this->WeightofVehicle;
  }
  if (this->NumberofWheels != 0)
  {
    result["Number of Wheels"] = this->NumberofWheels;
  }
  if (this->Capacity != 0)
  {
    result["Capacity"] = this->Capacity;
  }
  if (this->eject != "")
  {
    result["_Ejection Status_"] = this->eject;
  }

  return result;
}

bool ClassHierarchy::JSON2Object(Json::Value arg_jv)
{

  if ((arg_jv.isNull() == true) || (arg_jv.isObject() != true))
  {
    return false;
  }

  this->name = (arg_jv["Vehicle"]).asString();
  this->alertsend = (arg_jv["Alert"]).asString();
  this->eject = (arg_jv["_Ejection Status_"]).asString();
  this->SpeedofVehicle = (arg_jv["Speed (miles/hr)"]).asDouble();
  this->WeightofVehicle = (arg_jv["Weight (lbs)"]).asDouble();
  this->NumberofWheels = (arg_jv["Number of Wheels"]).asDouble();
  this->Capacity = (arg_jv["Capacity"]).asDouble();

  return true;
}