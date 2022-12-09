
// ecs36b first program

#include <iostream>
#include <fstream>
#include "ecs36b_Exception.h"

// JSON RPC part
#include "hw6client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>

using namespace jsonrpc;
using namespace std;

bool hasImpossible(char current[6], string impossible)
{

  string str = current;
  int y = 0;

  while (current)
  {
    for (int i = 0; i < impossible.size(); i++)
    {
      if (impossible[i] == current[y])
        return true;
    }
    y++;
  }

  return false;
}

string update(string myv, string guess){

  string impossible;

  for(int i = 0; i < 5; i++){
    if(myv[i] == '_'){
      impossible += guess[i];
    }
  }

  return impossible;
}

int main()
{
  // distributed wordle demo for 11/23/2022
  HttpClient httpclient("http://localhost:8384");
  // https://76ab88348bda.ngrok.io
  // HttpClient httpclient("https://2ada-73-66-168-157.ngrok.io");
  //HttpClient httpclient("https://76ab88348bda.ngrok.io");
  hw6Client myClient(httpclient, JSONRPC_CLIENT_V2);
  Json::Value myv;
  Json::Value jv_list;

  jv_list[0] = "917581829";
  jv_list[1] = "921459206";
  jv_list[2] = "918502182";
  jv_list[3] = "919909111";

  string impossible;
  // obtain and new
  try
  {
    myv = myClient.obtain("obtain", "Wordle", "00000000");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  try
  {
    // jumpy
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
                         "jumpy");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }
  // std::cout << myv.toStyledString() << std::endl;
  impossible += update(myv["check_word"].asString(), "jumpy");

  try
  {
    // bling
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
                         "bling");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }
  // std::cout << myv.toStyledString() << std::endl;
  impossible += update(myv["check_word"].asString(), "bling");

  try
  {
    // track
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
                         "track");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }
  // std::cout << myv.toStyledString() << std::endl;
  impossible += update(myv["check_word"].asString(), "track");

  try
  {
    // waqfs
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
                         "waqfs");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }
  // std::cout << myv.toStyledString() << std::endl;
  impossible += update(myv["check_word"].asString(), "waqfs");

  try
  {
    // vozhd
    myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
                         "vozhd");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;
  impossible += update(myv["check_word"].asString(), "vozhd");


  // finished filling impossible array
  // iterate through list next to find actual word


  string str = myv["check_word"].asString();

  FILE *fSol;
  fSol = fopen("./lists/SOLUTION.TXT", "r");
  int seek = 0;
  char currentWord[6];

  while (str != "#####")
  {
  
    fseek(fSol, seek , SEEK_SET);
    // getline(&fSol, currentWord);
    // fgets(currentWord, 6, fSol);
    // seek++;
    
    while (hasImpossible(currentWord, impossible))
    {
      //cout << currentWord << endl;
      fgets(currentWord, seek, fSol);
      seek++;
    }

    try
    {
      myv = myClient.guess("guess", "Wordle", myv["game_id"].asString(),
                           currentWord);
    }
    catch (JsonRpcException &e)
    {
      cerr << e.what() << endl;
    }

    impossible += update(myv["check_word"].asString(), currentWord);
    str = myv["check_word"].asString();
    std::cout << myv.toStyledString() << std::endl;
  }

  try
  {
    myv = myClient.submit("submit", "19056_2022-11-24T20:26:16+0000", "WASA");
  }
  catch (JsonRpcException &e)
  {
    cerr << e.what() << endl;
  }
  std::cout << myv.toStyledString() << std::endl;

  
  return 0;
}