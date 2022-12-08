// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>
#include "ecs36b_Exception.h"

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
// #include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "ClassHierarchy.h"
#include <time.h>

using namespace jsonrpc;
using namespace std;

class MyServer : public hw5Server
{
public:
  MyServer(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value move(const std::string &action,
                           const std::string &class_id,
                           const Json::Value &json_object,
                           const Json::Value &location,
                           const std::string &object_id);
  virtual Json::Value obtain(const std::string &action,
                             const std::string &class_id,
                             const std::string &object_id);
  virtual Json::Value done();
  virtual void insert(const std::string &action,
                      const std::string key, 
                      Json::Value &jv_moto);
  std::map<std::string, Car *> Car_Map;
  std::map<std::string, Motorcycle *> Moto_Map;
  bool is_done = false;
};

MyServer::MyServer(AbstractServerConnector &connector, serverVersion_t type)
    : hw5Server(connector, type)
{
  std::cout << "Server created" << std::endl;
}

// member functions
void MyServer::insert(const std::string &action, const std::string key, Json::Value &jv_moto)
{
  Motorcycle *lv_Moto_ptr;
  Motorcycle k{};
  k.JSON2Object(jv_moto);
  lv_Moto_ptr = &k;
  Moto_Map[key] = lv_Moto_ptr;
}

Json::Value
MyServer::obtain(const std::string &action, const std::string &class_id,
                 const std::string &object_id)
{
  int rc = 0;
  int error_code = 0;
  Json::Value result;

  try
  {
    if (action != "obtain")
    {
      error_code = -1;
      exit(-1);
    }

    if (class_id != "Motorcycle")
    {
      error_code = -2;
      exit(-2);
    }

    result["Vehicle Info"] = Moto_Map[object_id]->dump2JSON();
  }
  catch (ecs36b_Exception &e)
  {
    std::cerr << e.what() << std::endl;
    result["reason"] = e.what();
    result["error_code"] = error_code;
    result["status"] = "failed";
  }

  return result;
}

Json::Value
MyServer::move(const std::string &action, const std::string &class_id,
               const Json::Value &json_object, const Json::Value &location,
               const std::string &object_id)
{
  int error_code = 0;
  Json::Value result;
  string strJson;

  if (class_id != "Car" && class_id != "Motorcycle")
  {
    result["status"] = "failed";
    strJson = ("class" + class_id + " unknown");
    result["reason"] = strJson;
    error_code = -1;
  }

  if (object_id.empty())
  {
    result["status"] = "failed";
    strJson = ("object_id null");
    result["reason"] = strJson;
    error_code = -2;
  }

  if (json_object.isNull() == true || json_object.isObject() == false)
  {
    result["status"] = "failed";
    strJson = ("person parsing error");
    result["reason"] = strJson;
    error_code = -3;
  }

  if (error_code == 0)
  {
    result = json_object;
    if (class_id == "Car")
    {
      Car *lv_Car_ptr;

      if (Car_Map.find(object_id) != Car_Map.end())
      {
        lv_Car_ptr = Car_Map[object_id];
      }
      else
      {
        Car k{};
        k.JSON2Object(json_object);
        lv_Car_ptr = &k;
        Car_Map[object_id] = lv_Car_ptr;
      }

      lv_Car_ptr->JSON2Object(json_object);
      std::cout << "result: " << result.toStyledString() << std::endl;
    }
    else
    {
      Motorcycle *lv_Moto_ptr;

      if (Moto_Map.find(object_id) != Moto_Map.end())
      {
        lv_Moto_ptr = Moto_Map[object_id];
      }
      else
      {
        Motorcycle q{};
        q.JSON2Object(json_object);
        lv_Moto_ptr = &q;

        Moto_Map[object_id] = lv_Moto_ptr;
      }

      lv_Moto_ptr->JSON2Object(json_object);
    }
  }

  // std::cout << "result: " << result.toStyledString() << std::endl;
  return result;
}

Json::Value
MyServer::done()
{
  Json::Value result;
  result["Done"] = "The data has been sent to the next server.";
  // std::cout << "result: " << result.toStyledString() << std::endl;
  is_done = true;
  return result;
}

/*
changed ; for throw exceptions
changed result["Vehicle Info"] = Moto_Map[object_id].dump2JSON();
    to  result["Vehicle Info"] = Moto_Map[object_id]->dump2JSON();
*/