
#ifndef _RECORD_H_
#define _RECORD_H_

#include "GPS.h"
#include "JvTime.h"
#include "Person.h"
#include "Thing.h"

using namespace std;

class Record
{
    private:
        GPS_DD location;
        JvTime when;
        Thing what;
        Person who; 
        string description;     

    public:
        Record();
        Record(string, GPS_DD, JvTime, Thing, Person);

        bool operator==(Record& aRecord);
        JvTime getTime();
        Json::Value dump2JSON();
        bool JSON2Object(Json::Value);
};

#endif /* _RECORD_H_ */