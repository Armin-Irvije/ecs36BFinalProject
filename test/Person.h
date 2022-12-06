#ifndef _PERSON_H_
#define _PERSON_H_


// Person.h

#include "JvTime.h"
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>


using namespace std;

class Person
{
 private:
  string description;

public:
//new code
  string SpeedofVehicle;
  int WeightofVehicle;
  int NumberofWheels;
  int Capacity;
  bool Sensor;  
  void alert(string);
  Person(string);
  Person();
  bool operator==(Person& aPerson);
  string getName();
  void setDescription(string);
  Json::Value dump2JSON();
  bool JSON2Object(Json::Value);
};

#endif  /* _PERSON_H_ */
