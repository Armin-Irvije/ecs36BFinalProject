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
// #include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "ClassHierarchy.h"
#include <time.h>
#include "hw5server.cpp"
#include "hw5server.h"
#include "hw5client.h"

// LEFT MOTORCYCLE

using namespace jsonrpc;
using namespace std;

int main()
{

  Motorcycle left_motorcycle {};
  left_motorcycle.setName("Left Motorcycle");
  left_motorcycle.setInfo(67, 736, 2, 1);

  HttpServer httpserver(7375); // left motorcycle
  MyServer s(httpserver,
             JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)

  while(s.is_done == false) {
  s.StartListening();
  }

  Json::Value left;
  left = left_motorcycle.dump2JSON();
  s.insert("insert", "left_motorcycle", left);

  s.StopListening();

  
 
}