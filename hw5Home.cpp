
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "IOT_Thing.h"
#include "Person.h"
#include "Thing.h"
#include <time.h>
#include "Shadow_Thing.h"

using namespace jsonrpc;
using namespace std;

// std::map (key, value pairs)
std::map<std::string, Thing *> Thing_Map;
std::map<std::string, Person *> Person_Map;

// my location
GPS_DD process_here;

class Myhw5Server : public hw5Server
{
public:
  Myhw5Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value move(const std::string& action,
			   const std::string& class_id,
			   const Json::Value& json_object,
			   const Json::Value& location,
			   const std::string& object_id);
  virtual Json::Value search(const std::string& action,
			     const std::string& class_id,
			     const std::string& object_id);
  virtual Json::Value dump2JSON(const std::string& action,
				const std::string& arguments,
				const std::string& class_id,
				const std::string& host_url,
				const std::string& object_id);
};

Myhw5Server::Myhw5Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Server(connector, type)
{
  std::cout << "Myhw5Server Object created" << std::endl;
}

// member functions

Json::Value
Myhw5Server::move
(const std::string& action, const std::string& class_id,
 const Json::Value& json_object, const Json::Value& location,
 const std::string& object_id)
{
  int error_code = 0;
  Json::Value result;
  std::string strJson;

  if (class_id != "Person" && class_id != "Thing")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
      error_code = -1;
    }

  if (object_id.empty())
    {
      result["status"] = "failed";
      strJson = ( "object_id null ");
      result["reason"] = strJson;
      error_code = -2;
    }

  GPS_DD incoming_location;
  if ((location.isNull() == true) ||
      (location.isObject() == false))
    {
      result["status"] = "failed";
      strJson = ( "location parsing error " );
      result["reason"] = strJson;
      error_code = -3;
    }

  if ((json_object.isNull() == true) ||
      (json_object.isObject() == false))
    {
      result["status"] = "failed";
      strJson = ( "person parsing error " );
      result["reason"] = strJson;
      error_code = -4;
    }

  if (error_code == 0)
    {
      incoming_location.JSON2Object(location);
      if (!(process_here == incoming_location))
	{
	  result["status"] = "failed";
	  strJson = ( "location mismatched" );
	  result["reason"] = strJson;
	  error_code = -5;
	}
      else
	{
        if (class_id == "Person"){
            Person * lv_person_ptr;
            if (Person_Map.find(object_id) != Person_Map.end())
            {
                lv_person_ptr = Person_Map[object_id];
            }
            else
            {
                lv_person_ptr = new Person {};
                Person_Map[object_id] = lv_person_ptr;
            }
            lv_person_ptr->JSON2Object(json_object);
        }
        else {
            Thing * lv_thing_ptr;
            if(Thing_Map.find(object_id) != Thing_Map.end())
            {
                lv_thing_ptr = Thing_Map[object_id];
            }
            else{
                lv_thing_ptr = new Thing {};
                Thing_Map[object_id] = lv_thing_ptr;
            }
            lv_thing_ptr->JSON2Object(json_object);
        }
        result["status"] = "successful";
	}
    }

  std::cout << result.toStyledString() << std::endl;
  return result;
}

Json::Value
Myhw5Server::search
(const std::string& action, const std::string& class_id,
 const std::string& object_id)
{
  int error_code = 0;
  int rc;
  Json::Value result;
  std::string strJson;

  if (class_id != "Person" && class_id != "Thing")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
      error_code = -1;
    }

  if (object_id.empty())
    {
      result["status"] = "failed";
      strJson = ( "object_id null ");
      result["reason"] = strJson;
      error_code = -2;
    }

  if(class_id == "Person")
    {
      Person * lv_person_ptr;
      if (Person_Map.find(object_id) != Person_Map.end())
        {
          lv_person_ptr = Person_Map[object_id];
          Json::Value json_object = lv_person_ptr->dump2JSON();
          json_object["current location"] = process_here.dump2JSON();
          result["object"] = json_object;
          result["status"] = "successful";
        }
      else
        {
          result["status"] = "failed";
          strJson = ( "object_id not found ");
          result["reason"] = strJson;
        }
    }
    else{
        Thing * lv_thing_ptr;
        if (Thing_Map.find(object_id) != Thing_Map.end()){
            lv_thing_ptr = Thing_Map[object_id];
            Json::Value json_object = lv_thing_ptr->dump2JSON();
            json_object["current location"] = process_here.dump2JSON();
            result["object"] = json_object;
            result["status"] = "successful";
        }
        else{
          result["status"] = "failed";
          strJson = ( "object_id not found ");
          result["reason"] = strJson;
        }
    }

  return result;
}

Json::Value
Myhw5Server::dump2JSON
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id)
{
  // a pointer to Thing
  Thing *thing_ptr; // now a local variable
  // a pointer to Person
  Thing *person_ptr; // now a local variable

  Json::Value result;
  std::cout << action << " " << arguments << std::endl;
  std::string strJson;

  if (class_id != "Thing" && class_id != "Person")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
    }
  else
    {
    if(class_id == "Thing"){
        if (Thing_Map.find(object_id) != Thing_Map.end())
        {
        thing_ptr = Thing_Map[object_id];
        result = thing_ptr->dump2JSON();
        result["status"] = "successful";
        }
        else
        {
        result["status"] = "failed";
        strJson = ( "object " + object_id + " unknown");
        result["reason"] = strJson;
        }
    }
    else{
        if (Person_Map.find(object_id) != Person_Map.end())
        {
        person_ptr = Person_Map[object_id];
        result = person_ptr->dump2JSON();
        result["status"] = "successful";
        }
        else
        {
        result["status"] = "failed";
        strJson = ( "object " + object_id + " unknown");
        result["reason"] = strJson;
        }
    }
    }

  return result;
}

int main()
{ 
  HttpServer httpserver(7375);
  Myhw5Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}