#pragma once
#include "reserve.hpp"
class District
{
private:
    int status;
    string name;
    vector<string> neighbors;
    friend class App;
    friend class Check;
    friend class GET;
public:

    District(vector<string> data_line)
    {
        for(int i=0;i<data_line.size();i++)
        {
            if(i==0)
            {
                name=data_line[i];
                continue;
            }
            neighbors.push_back(data_line[i]);
        }
    }

    string get_name(){return name;}


};
