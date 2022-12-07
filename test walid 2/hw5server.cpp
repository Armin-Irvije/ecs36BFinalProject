
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

Json::Value
MyServer::obtain(const std::string &action, const std::string &class_id,
                    const std::string &object_id)
{
  // Json::Value lv_log;
  // lv_log["arg action"] = action;
  // lv_log["arg class_id"] = class_id;
  // lv_log["arg game_id"] = game_id;
  // myPrintLog(lv_log.toStyledString(), "./config/hw6server.log");

  int rc = 0;
  int error_code = 0;
  Json::Value result;

  try
  {
    if (action != "obtain"){
      error_code = -1;
      throw ecs36b_Exception{("action " + action + " mismatched");
      }
    }

    if (class_id != "Motorcycle")
    {
      error_code = -2;
      throw ecs36b_Exception{("class " + class_id + " unknown");}
    }
    
    result["Vehicle Info"] = Motorcycle_Map[object_id].dump2JSON();
    


    // char buf_fname[256];
    // char buf_gid[256];
    // FILE *target;

    // if (game_id == "00000000")
    //   {
    //     // new game
    //     unsigned int my_rand = rand();
    //     my_rand = my_rand % 100000;

    //     JvTime * my_now_ptr = getNowJvTime();
    //     std::string *my_now_str = my_now_ptr->getTimeString();

    //     bzero(buf_gid, 256);
    //     snprintf(buf_gid, 255, "%d_%s",
    //        my_rand, my_now_str->c_str());

    //     bzero(buf_fname, 256);
    //     snprintf(buf_fname, 255, "./games/wordle_%s.json",
    //        buf_gid);
    //     target = fopen(buf_fname, "a");
    //     if (target == NULL)
    // {
    //   error_code = -4;
    //   throw ecs36b_Exception { "cannot open the target Wordle game!" };
    // }
    //     fclose(target);

    //     result["game_id"] = buf_gid;
    //     result["remaining_score"] = 100;
    //     result["score_distributed"] = false;

    //     // try to find the solution word
    //     my_rand = rand();
    //     my_rand = my_rand % 2314;

    //     int pi = pickWord(word, my_rand);
    //     if (pi != my_rand)
    // {
    //   error_code = -5;
    //   throw ecs36b_Exception { "pickWord mismatching error" };
    // }
    //     result["word"] = word;
    //     result["check_word"] = "_____";

    //     rc = myJSON2File(buf_fname, &result);
    //     if (rc == 0)
    // {
    //   result["status"] = "successful";
    // }
    //     else
    // {
    //   error_code = rc;
    //   throw ecs36b_Exception { "myJSON2File error" };
    // }
    //   }
    // else
    // {
    // trying to retrieve an existing game
  //   bzero(buf_fname, 256);
  //   snprintf(buf_fname, 255, "./games/wordle_%s.json", game_id.c_str());
  //   rc = myFile2JSON(buf_fname, &result);
  //   if (rc == 0)
  //   {
  //     result["status"] = "successful";
  //   }
  //   else
  //   {
  //     error_code = rc;
  //     throw ecs36b_Exception{"myJSON2File error"};
  //   }
  //   // }
  }
  catch (ecs36b_Exception &e)
  {
    std::cerr << e.what() << std::endl;
    result["reason"] = e.what();
    result["error_code"] = error_code;
    result["status"] = "failed";
  }

  // remember to mask the real solution before returning
  // result["word"] = "?????";

  // lv_log["result"] = result;
  // myPrintLog(lv_log.toStyledString(), "./config/hw6server.log");

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
 
  
    if (class_id == "Car")
    {
      Car *lv_Car_ptr;

      if (Car_Map.find(object_id) != Car_Map.end())
      {
        lv_Car_ptr = Car_Map[object_id];
      }
      else
      {
        lv_Car_ptr = new Car{};
        Car_Map[object_id] = lv_Car_ptr;
      }

      lv_Car_ptr->JSON2Object(json_object);
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
        lv_Moto_ptr = new Car{};
        Moto_Map[object_id] = lv_Moto_ptr;
      }

      lv_Car_ptr->JSON2Object(json_object);
    

    result = json_object;
  }

  std::cout << "result: " << result.toStyledString() << std::endl;
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

// // for Json::value
// #include <json/json.h>
// #include <json/reader.h>
// #include <json/writer.h>
// #include <json/value.h>
// #include <string>

// // for JsonRPCCPP
// #include <iostream>
// #include "hw5server.h"
// #include <jsonrpccpp/server/connectors/httpserver.h>
// //#include "hw5client.h"
// #include <jsonrpccpp/client/connectors/httpclient.h>
// #include <stdio.h>

// // ecs36b
// #include "ClassHierarchy.h"
// #include <time.h>

// using namespace jsonrpc;
// using namespace std;

// class MyServer : public hw5Server
// {
// public:
//   MyServer(AbstractServerConnector &connector, serverVersion_t type);
//   virtual Json::Value move(const std::string& action,
// 			   const std::string& class_id,
// 			   const Json::Value& json_object,
// 			   const Json::Value& location,
// 			   const std::string& object_id);
//   virtual Json::Value done();
//   std::map<std::string, ClassHierarchy *> ClassHierarchy_Map;
//   bool is_done = false;
// };

// MyServer::MyServer(AbstractServerConnector &connector, serverVersion_t type)
//   : hw5Server(connector, type)
// {
//   std::cout << "Server created" << std::endl;
// }

// // member functions

// Json::Value
// MyServer::move
// (const std::string& action, const std::string& class_id,
//  const Json::Value& json_object, const Json::Value& location,
//  const std::string& object_id)
// {
//   // int error_code = 0;
//   Json::Value result;
// if (class_id == "ClassHierarchy")
// {

// 	ClassHierarchy * lv_ClassHierarchy_ptr;

// 	if (ClassHierarchy_Map.find(object_id) != ClassHierarchy_Map.end()) {
// 	  lv_ClassHierarchy_ptr = ClassHierarchy_Map[object_id];
// 	} else {
// 	  lv_ClassHierarchy_ptr = new ClassHierarchy {};
// 	  ClassHierarchy_Map[object_id] = lv_ClassHierarchy_ptr;
// 	}

//   lv_ClassHierarchy_ptr->JSON2Object(json_object);

//   }

//   result = json_object;

//   std::cout << "result: " << result.toStyledString() << std::endl;
//   return result;

// }

// Json::Value
// MyServer::done()
// {
//   Json::Value result;
//   result["Done"] = "The data has been sent to the next server.";
//   //std::cout << "result: " << result.toStyledString() << std::endl;
//   is_done = true;
//   return result;
// }
