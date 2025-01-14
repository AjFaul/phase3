#pragma once
#include "analysisInput.hpp"
class Reserve
{
private:
    int status;
    string restaurant_name;
    int table_id;
    vector<string> foods_name;
    vector<int> prices;
    int reserve_id;
    int start_time,end_time;
    int final_price=0;
    friend class Client;
    
public:
    Reserve(){status=1;}

    Reserve(string rest_name,int t_id,int s_time,int e_time,vector<string>foodd_name)
    {
        status=1;
        restaurant_name=rest_name;
        table_id=t_id;
        start_time=s_time;
        end_time=e_time;
        foods_name=foodd_name;
    }

    void set_price(vector<int> price_foods)
    {
        prices=price_foods;
    }

    int delete_reserve()
    {
        status=0;
        return final_price;
    }

    int get_status(){return status;}

    void set_reserve_id(int id){reserve_id=id;}

    int get_table_id(){return table_id;}

    int get_start_time(){return start_time;}
    
    int get_end_time(){return end_time;}

    int get_reserve_id(){return reserve_id;}

    vector<int> get_prices(){return prices;}

    int get_price()
    {
        int x=0;
        for(int i=0;i<prices.size();i++)
        {
            x+=prices[i];   
        }
        return x;
    }
    
    string get_restaurant_name(){return restaurant_name;}

    void set_final_price(int x)
    {
        final_price=x;
    }

    int get_final_price(){return final_price;}

    int get_inital_price()
    {
        int x=0; 
        for(int i=0;i<prices.size();i++)
        {
            x+=prices[i];
        }
        return x;
    }
};
