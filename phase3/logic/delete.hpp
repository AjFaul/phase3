#pragma once
#include "put.hpp"
class DELETE
{
private:
    Output_msg err;
public:
    DELETE(){}

    int del_func(string restaurant_name, int reserve_id,App& app)
    {
        int x;
        for(int i=0;i<app.restaurants.size();i++)
        {
            if(app.restaurants[i].name ==restaurant_name)
            {
                for(int j=0;j<app.restaurants[i].reserves.size();j++)
                {
                    if(app.restaurants[i].reserves[j].get_reserve_id()==reserve_id)
                    {
                        x=app.restaurants[i].reserves[j].delete_reserve();
                        return x;
                    }
                }
                err.Not_Found();
                return false;
            }
        }
        err.Not_Found();
        return false;
    }


};
