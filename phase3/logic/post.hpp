#pragma once
#include "check.hpp"
class POST 
{
private:
    int status;
    Output_msg err;
    Analysis_input analysis;
    void signup(vector<string> username_password,App& app)
    {
        Client client(username_password[0], username_password[1]);
        app.Add_client(client);
    }

    Client login(vector<string> user_pass)
    {
        Client client(user_pass[0], user_pass[1]);
        return client;
    }

    bool reserve(vector<string> words , App& app,Client& client)
    {
        for(int i=0;i<app.restaurants.size();i++)
        {
            if(words[0]==app.restaurants[i].name)
            {
                vector<string>foods=analysis.separate_food(words);
                if(app.restaurants[i].Add_reserve(stoi(words[1]),stoi(words[2]),stoi(words[3]),foods,client.get_budget()))
                {
                    return true;
                }
            }
        }
        err.Not_Found();
        return false;
    }


    friend class Serverr;
public:
    POST(){status=1;}

};
