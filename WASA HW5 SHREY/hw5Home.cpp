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
#include "Thing.h"
#include <time.h>
#include "hw5server.cpp"
#include "hw5server.h"
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int main() {

  Person girl;
  girl.setDescription("a dear little girl");

  Thing cap;

  cap.setName("cap");
  cap.setDescription("little, red velvet");

  Thing cake, wine;
  cake.setName("Piece of Cake");
  wine.setName("Bottle of Wine");

  HttpClient httpclient("http://127.0.0.1:7375");
  hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;
  Json::Value gps;
  gps["location"] = "forest";

  try {
    myv = myClient.move("move", "Person",
			girl.dump2JSON(),
			gps,
			"girl");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;



  HttpServer httpserver(7374);
  Myhw5Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();

  return 0;
}