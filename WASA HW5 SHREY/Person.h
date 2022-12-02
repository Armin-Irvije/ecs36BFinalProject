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
  // GPS_DD home;
  // GPS_DD location;
  // JvTime since_when; 
  
public:
  Person(string);
  Person();
  // void setHome(GPS_DD);
  // void setLocation(GPS_DD, JvTime);
  // void setLocation(GPS_DD);

  bool operator==(Person& aPerson);
  string getName();
  void setDescription(string);
  // GPS_DD getHome();
  // GPS_DD getLocation();
  // JvTime getLocationTime();
  Json::Value dump2JSON();
  bool JSON2Object(Json::Value);
};

#endif  /* _PERSON_H_ */
