
// ecs36b first program

#include <iostream>
#include "ecs36b_Exception.h"

// JSON RPC part
#include "hw6client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int
main()
{
  // distributed wordle demo for 11/23/2022
  HttpClient httpclient("http://localhost:8384");
  //  HttpClient httpclient("https://2ada-73-66-168-157.ngrok.io");
  hw6Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;
  Json::Value jv_list;
  
  jv_list[0] = "917581829";
  jv_list[1] = "921459206";
  jv_list[2] = "918502182";
  jv_list[3] = "919909111";
  
  //
  // try {
  //   myv = myClient.set_name("set_name", jv_list, "WASA");
  // } catch (JsonRpcException &e) {
  //   cerr << e.what() << endl;
  // }
  // std::cout << myv.toStyledString() << std::endl;
  

  // obtain and new
  try {
    myv = myClient.obtain("obtain", "Wordle", "00000000");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  try {
    // jumpy
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			 "jumpy");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;


  try {
    // bling
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			 "bling");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;

  try {
    // track
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			 "track");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;

  try {
    // waqfs
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			 "waqfs");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  //std::cout << myv.toStyledString() << std::endl;

  try {
    // vozhd
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			 "vozhd");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

 


  exit(-1);

  


  


  try {
    // worry
    myv = myClient.submit("submit", "19056_2022-11-24T20:26:16+0000", "WASA");
  } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  
  
  
  

  
  // guess
  if ((myv["game_id"].isNull() == false) &&
      (myv["game_id"].isString() == true))
    {
      try {
	// bling
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "earth");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      try {
	// jumpy
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "mound");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      try {
	// track
	myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
			     "sicky");
      } catch (JsonRpcException &e) {
	cerr << e.what() << endl;
      }

      std::cout << myv.toStyledString() << std::endl;
    }
  return 0;
}

//bling
//jumpy
//track
//vozhd
//waqfs
