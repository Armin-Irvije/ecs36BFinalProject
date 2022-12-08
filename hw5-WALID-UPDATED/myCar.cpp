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

int main()
{

  Car myCar {};
  myCar.alert("I might hit you!");
  myCar.setName("My Car");

  HttpClient httpclient("http://127.0.0.1:7375"); // left vehicle port
  hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value jv_myCar;
  Json::Value jv_leftv; // left bike
  Json::Value jv_rightv; // right bike
  Json::Value jv_l; // location
  jv_l["location"] = "Left Motorcycle";

  try
  {
    jv_myCar = myClient.move("move", "Car",
                          myCar.dump2JSON(),
                          jv_l,
                          "myCar");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }

  HttpClient httpclient2("http://127.0.0.1:7380"); // right vehicle port
  hw5Client myClient2(httpclient2, JSONRPC_CLIENT_V2);
  jv_l["location"] = "Right Motorcycle";

  try
  {
    jv_myCar = myClient2.move("move", "Car",
                            myCar.dump2JSON(),
                            jv_l,
                            "myCar");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }

  try{
    jv_leftv = myClient.obtain("obtain", "Motorcycle", "left_motorcycle");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  try{
    jv_rightv = myClient2.obtain("obtain", "Motorcycle", "right_motorcycle");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  cout << jv_leftv.toStyledString() << endl;
  cout << jv_rightv.toStyledString() << endl;

  Motorcycle left {};
  left.JSON2Object(jv_leftv);

  Motorcycle right {};
  right.JSON2Object(jv_rightv);


  double riskL = myCar.getFatalityRisk(left);
  double riskR = myCar.getFatalityRisk(right);

  myCar.alert("I will hit you");
  if (riskR >= riskL)
  {
    jv_l["location"] = "Left Motorcycle";
    try
    {
      jv_myCar = myClient.move("move", "Car",
                            myCar.dump2JSON(),
                            jv_l,
                            "myCar");
    }
    catch (JsonRpcException &e)
    {
      cerr << e.what() << endl;
    }
  }
  else
  {
    jv_l["location"] = "Right Motorcycle";
    try
    {
      jv_myCar = myClient2.move("move", "Car",
                              myCar.dump2JSON(),
                              jv_l,
                              "myCar");
    }
    catch (JsonRpcException &e)
    {
      cerr << e.what() << endl;
    }
  }

  return 0;
}