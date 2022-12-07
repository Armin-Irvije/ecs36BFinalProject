#ifndef _CLASSHIERARCHY_H_
#define _CLASSHIERARCHY_H_



#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

using namespace std;



class ClassHierarchy
{
 private:
  string name;
  string description;
  string descriptionL;
  string descriptionR;
  string alertsend;

 public:  
  string eject;
  // double SpeedofVehicle = -1;
  // double WeightofVehicle = -1;
  // double NumberofWheels = -1;
  // double Capacity = -1;
  double SpeedofVehicle;
  double WeightofVehicle;
  double NumberofWheels;
  double Capacity;
  void alert(string); //because alert is what the sensor is sending and we dont need separate method for sensor
  void setInfo(double, double, double, double);
  //old code
  ClassHierarchy(void);
  ClassHierarchy(string);
  


  void setName(string);
  void setDescription(string);
  void setDescriptionL(string);
  void setDescriptionR(string);
  Json::Value dump2JSON(); // print the content of the object
  bool JSON2Object(Json::Value);
  int JSON2Objects(Json::Value);
};
class Motorcycle: public virtual ClassHierarchy
{
  public:
  void MotorcycleSeatEjector(string); 
};
class Car: public virtual ClassHierarchy
{
  public:
  bool SteeringWheel(); // turn left or right
  double getFatalityRisk(Motorcycle);
};



#endif /* _CLASSHIERARCHY_H_ */
