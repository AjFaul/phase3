#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

class Output_msg
{
private:
    int status=0;
    void OK(){ cout<<"OK"<<endl;}
    void Empty(){cout<<"Empty"<<endl;}
    void Not_Found(){cout<<"Not Found"<<endl;}
    void Bad_Request(){cout<<"Bad_Request"<<endl;}
    void Permission_Denied(){cout<<"Permission_Denied"<<endl;}
    friend class Analysis_input;
    friend class Serverr;
    friend class Check;
    friend class GET;
    friend class PUT;
    friend class POST;
    friend class Restaurant;
    friend class Client;
    friend class DELETE;
public:
    Output_msg(){status=1;}
};