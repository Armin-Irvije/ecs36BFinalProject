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
#include "hw5server.cpp"
#include "hw5server.h"
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>


using namespace jsonrpc;
using namespace std;

int main() {

  Car myCar;
  myCar.alert("I'm going to hit you, get out the way");


  HttpClient httpclient("http://127.0.0.1:7375"); //left vehicle port
  hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value leftv;
  Json::Value Leftvehicle;
  Leftvehicle["location"] = "Left Motorcycle";
 
  try {
    leftv = myClient.move("move", "VehicleInfo",
			myCar.dump2JSON(),
			Leftvehicle,
			"left.alert");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << leftv.toStyledString() << std::endl; 

  HttpClient httpclient2("http://127.0.0.1:7380"); //right vehicle port
  hw5Client myClient2(httpclient2, JSONRPC_CLIENT_V2);
  Json::Value rightv;
  Json::Value Rightvehicle;
  Rightvehicle["location"] = "Right Motorcycle";

  try {
    rightv = myClient2.move("move", "VehicleInfo",
			myCar.dump2JSON(),
			Rightvehicle,
			"right.alert");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << rightv.toStyledString() << std::endl;
  if (myCar.getFatalityRisk() == true) {

    myCar.alert("Im going to hit you now");
    try {
      leftv = myClient.move("move", "VehicleInfo",
			  myCar.dump2JSON(),
			  Leftvehicle,
			  "left.alert");
      } catch (JsonRpcException &e) {
      cerr << e.what() << endl;
      }
  } else {
    myCar.alert("Im going to hit you now");
    try {
      rightv = myClient2.move("move", "VehicleInfo",
			  myCar.dump2JSON(),
			  Rightvehicle,
			  "right.alert");
      } catch (JsonRpcException &e) {
      cerr << e.what() << endl;
      }
  }
  
  Json::Value finish, finish2;

   try {
    finish = myClient.done();
    finish2 = myClient2.done(); 
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  HttpServer httpserver(7374); //home server port
  MyServer s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();


  s.StopListening();



  return 0;
}