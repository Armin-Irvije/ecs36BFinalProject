#ifndef _THING_H_
#define _THING_H_

// Thing.h
#include "Person.h"
//#include "GPS.h"
#include "JvTime.h"
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>


using namespace std;

class Thing
{
 private:
  string name;
  string description;
  // Person owner;
  // GPS_DD location;

 public:  
  Thing(void);
  Thing(string);

  void setName(string);
  void setDescription(string);
  Json::Value dump2JSON(); // print the content of the object
  bool JSON2Object(Json::Value);
};

#endif /* _THING_H_ */
