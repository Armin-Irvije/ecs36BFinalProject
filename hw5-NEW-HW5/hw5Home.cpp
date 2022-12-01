
// ecs36b first program

#include <iostream>
#include "Shadow_Thing.h"
#include "Network.h"
#include "IOT_Thing.h"
#include "ecs36b_Exception.h"

// JSON RPC part
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

int
main()
{
  GPS_DD home {"Home"};
  GPS_DD forest {"Forest"};
  GPS_DD grandma_home {"Grandma home"};

  Person girl {"Little Red Riding Hood", home};

  Thing thing1 {"Cap", home};
  Thing thing2 {"Cake and wine", };

  // object mobility demo for 11/18/2022 and 11/21/2022
  HttpClient httpclient("http://127.0.0.1:4001");
  hw5Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;

  // move
  try {
    myv = myClient.move("move", "Person",
			girl.dump2JSON(),
			forest.dump2JSON(),
			"001");
    } catch (JsonRpcException &e) {
    cerr << e.what() << endl;
  }

  



  return 0;
}
