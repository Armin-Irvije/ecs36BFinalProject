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

using namespace jsonrpc;
using namespace std;

int main() {

  HttpServer httpserver(7376);
  MyServer s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)

  while(s.is_done == false) {
  s.StartListening();
  }
  s.StopListening();
 

}
