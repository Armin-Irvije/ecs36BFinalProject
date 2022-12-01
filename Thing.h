
#ifndef _THING_H_
#define _THING_H_

// Thing.h
#include "Person.h"
#include "GPS.h"
#include "JvTime.h"

using namespace std;

class Thing
{
 private:
  string description;
  // Person owner;
  GPS_DD location;

 public:  
  Thing(void);
  Thing(string);
  Thing(string, /*Person, JvTime, JvTime,*/ GPS_DD);

  Json::Value dump2JSON(); // print the content of the object
  bool JSON2Object(Json::Value);
};

#endif /* _THING_H_ */
