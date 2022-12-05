
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
//#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "Person.h"
#include "VehicleInfo.h"
#include <time.h>

using namespace jsonrpc;
using namespace std;

class MyServer : public hw5Server
{
public:
  MyServer(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value move(const std::string& action,
			   const std::string& class_id,
			   const Json::Value& json_object,
			   const Json::Value& location,
			   const std::string& object_id);
  virtual Json::Value done();
  std::map<std::string, VehicleInfo *> VehicleInfo_Map;
  std::map<std::string, Person *> Person_Map;
  std::map<std::string, Person *> Other_Map;
  bool is_done = false;
};


MyServer::MyServer(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Server(connector, type)
{
  std::cout << "Server created" << std::endl;
}

// member functions

Json::Value
MyServer::move
(const std::string& action, const std::string& class_id,
 const Json::Value& json_object, const Json::Value& location,
 const std::string& object_id)
{
  // int error_code = 0;
  Json::Value result;
if (class_id == "Person")
{	Person * lv_person_ptr;
    
	if (Person_Map.find(object_id) != Person_Map.end()) {
	  lv_person_ptr = Person_Map[object_id];
	} else {
	  lv_person_ptr = new Person {};
	  Person_Map[object_id] = lv_person_ptr;
	}
	  
  lv_person_ptr->JSON2Object(json_object);} 
  
  else if (class_id == "VehicleInfo") {


	VehicleInfo * lv_VehicleInfo_ptr;
    
	if (VehicleInfo_Map.find(object_id) != VehicleInfo_Map.end()) {
	  lv_VehicleInfo_ptr = VehicleInfo_Map[object_id];
	} else {
	  lv_VehicleInfo_ptr = new VehicleInfo {};
	  VehicleInfo_Map[object_id] = lv_VehicleInfo_ptr;
	}
	  
  lv_VehicleInfo_ptr->JSON2Object(json_object);

  }

  result = json_object;

  std::cout << "result: " << result.toStyledString() << std::endl;
  return result;
}

Json::Value
MyServer::done()
{
  Json::Value result;
  result["Done"] = "The data has been sent to the next server.";
  std::cout << "result: " << result.toStyledString() << std::endl;
  is_done = true;
  return result;
}
