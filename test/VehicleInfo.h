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

class VehicleInfo //vehicleinfo
{
 private:
  string name;
  string description;
  string descriptionL;
  string descriptionR;

 public:  
  string SpeedofVehicle;
  int WeightofVehicle;
  int NumberofWheels;
  int Capacity;
  bool Sensor;  

//old code
  VehicleInfo(void);
  VehicleInfo(string);

  void setName(string);
  void setDescription(string);
  void setDescriptionL(string);
  void setDescriptionR(string);
  Json::Value dump2JSON(); // print the content of the object
  bool JSON2Object(Json::Value);
};

#endif /* _VEHICLEINFO_H_ */
