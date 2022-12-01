
#ifndef _JVTIME_H_
#define _JVTIME_H_

// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>

using namespace std;

class JvTime
{
 private:
  string time;
 protected:
 public:
  JvTime();
  JvTime(string);

  string getTime();
  Json::Value dump2JSON();
  bool JSON2Object(Json::Value);
};

#endif /* _JVTIME_H_ */
