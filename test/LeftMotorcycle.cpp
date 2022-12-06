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
#include "hw5server.cpp"
#include "hw5server.h"
#include "hw5client.h"

//LEFT MOTORCYCLE

using namespace jsonrpc;
using namespace std;

int main() {
//recieving OG message
  HttpServer httpserver(7375); //left motorcycle
  MyServer s(httpserver,
	JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  
  while(s.is_done == false) {
  s.StartListening();
  }
  s.StopListening();



//client for sending info
  HttpClient httpclientL("http://127.0.0.1:7374"); //myCar
  hw5Client myClientL(httpclientL, JSONRPC_CLIENT_V2);
  Json::Value myCarL;
  Json::Value ogCarL;
  ogCarL["which vehicle"] = "back to home";
//sending info and alert
  Motorcycle LeftMotorcycle;
  LeftMotorcycle.alert("This is the left motorcycle information");
  LeftMotorcycle.setInfo(67, 736, 2, 1);
  LeftMotorcycle.MotorcycleSeatEjector("Ejection Successfull, Rider is safe");
  
  try {
  myCarL = myClientL.move("move", "VehicleInfo",
		LeftMotorcycle.dump2JSON(),
		ogCarL,
		"alertbacktohomeL");
    }catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  


}


