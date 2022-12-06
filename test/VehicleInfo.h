#ifndef _VEHICLEINFO_H_
#define _VEHICLEINFO_H_

//CLASS HIERARCHy

// VehicleInfo.h 

#include "Person.h"
#include "JvTime.h"
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

using namespace std;

// class VehicleInfo //vehicleinfo
// {
//  private:
//   string name;
//   string description;
//   string descriptionL;
//   string descriptionR;

//  public:  
//   string SpeedofVehicle;
//   int WeightofVehicle;
//   int NumberofWheels;
//   int Capacity;
//   bool Sensor;  

// //old code
  // VehicleInfo(void);
  // VehicleInfo(string);

  // void setName(string);
  // void setDescription(string);
  // void setDescriptionL(string);
  // void setDescriptionR(string);
  // Json::Value dump2JSON(); // print the content of the object
  // bool JSON2Object(Json::Value);
// };



class VehicleInfo
{
 private:
  string name;
  string description;
  string descriptionL;
  string descriptionR;
  string alertsend;

 public:  
  string eject;
  double SpeedofVehicle = -1;
  double WeightofVehicle = -1;
  double NumberofWheels = -1;
  double Capacity = -1;
  void alert(string); //because alert is what the sensor is sending and we dont need separate method for sensor
  void setInfo(double, double, double, double);
  //old code
  VehicleInfo(void);
  VehicleInfo(string);
  


  void setName(string);
  void setDescription(string);
  void setDescriptionL(string);
  void setDescriptionR(string);
  Json::Value dump2JSON(); // print the content of the object
  bool JSON2Object(Json::Value);
  int JSON2Objects(Json::Value);
};
class Motorcycle: public virtual VehicleInfo
{
  public:
  void MotorcycleSeatEjector(string); 
};
class Car: public virtual VehicleInfo
{
  public:
  bool SteeringWheel(); // turn left or right
  bool getFatalityRisk();
};




#endif /* _VEHICLEINFO_H_ */
