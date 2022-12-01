
#ifndef _GPS_H_
#define _GPS_H_

// GPS.h

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

using namespace std;

class GPS_DD
{
 private:
  string location;

 public:
  GPS_DD();
  GPS_DD(string);
  
  string getLocation();
  Json::Value dump2JSON();
  bool JSON2Object(Json::Value);
};

#endif /* _GPS_H_ */
