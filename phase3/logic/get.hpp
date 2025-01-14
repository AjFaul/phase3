#pragma once
#include "post.hpp"
class GET
{
private:
    Output_msg err;
    Check check;

    void districts(string district_name,App& app)
    {
        if(app.distritcs.size()==0)
        {
            err.Empty();
            return;
        }

        if(district_name=="NULL")
        {
            for(int i=0 ; i<app.distritcs.size();i++)
            {
                cout<<app.distritcs[i].get_name()<<":";
                for(int j=0; j<app.distritcs[i].neighbors.size();j++)
                {
                    cout<<" "<<app.distritcs[i].neighbors[j];
                    if((j+1)!=app.distritcs[i].neighbors.size())
                        cout<<",";
                }
                cout<<endl;
            }
            

        }else
        {
            for(int i=0;i<app.distritcs.size();i++)
            {
                if(app.distritcs[i].get_name()==district_name)
                {
                    cout<<district_name<<":";
                    for(int j=0;j<app.distritcs[i].neighbors.size();j++)
                    {
                        cout<<" "<<app.distritcs[i].neighbors[j];
                        if((j+1)!=app.distritcs[i].neighbors.size())
                            cout<<",";
                    }
                    cout<<endl;
                    return;
                }
            }
            err.Not_Found();
        }
    }

    void restaurants(string food_name, App& app,Client client)
    {
        if(client.district.size()==0)
        {
            err.Not_Found();
            return;
        }

        if(app.restaurants.size()==0)
        {
            err.Empty();
            return;
        }
        vector<string> visited;
        visited.push_back(client.district);
        vector<string> neighbors;
        neighbors.push_back(client.district);
        visited=check.bfs_function(neighbors,visited,app);
        bool cmd_type=(food_name=="NULL")?true:false;
        int num=0;
        for(int i=0;i<visited.size();i++)
        {
            for(int j=0;j<app.restaurants.size();j++)
            {
                if(app.restaurants[j].district==visited[i])
                {
                    if(app.restaurants[j].menu_item[food_name]!=0 || cmd_type)
                    {
                        cout<<app.restaurants[j].name<<" ("<<app.restaurants[j].district<<")"<<endl;
                        num++;
                    }
                }
            }
        }
        if(num==0)
            err.Empty();
    }

    friend class Serverr;
public:
    GET(){}
};
