#pragma once
#include "restaurant.hpp"

class Client
{
private:
    int budget=0;
    int num_of_reserve=0;
    int status;
    string username;
    string password;
    string district;
    vector<Reserve> reserves;
    Analysis_input aaann;
    friend class App;
    friend class Check;
    friend class Serverr;
    friend class GET;
public:
    Client(){}
    Client(string name, string pass)
    {
        username=name;
        password=pass;
    }

    void set_client(string name , string password_)
    {
        username=name;
        password=password_;
    }

    void set_district(string district_name){district=district_name;}

    bool conflict_time_client(int s1,int e1,int s2 , int e2)
    {
        if(s1<1 || e1>24)
            return false;
        if(e1>s2 && e1<=e2)
            return false;
        if(s1>s2 && s1<e2)//
            return false;
        if(e2>s1 && e2<=e1)
            return false;
        if(s2>s1 && s2<e1)
            return false;
        return true;
    }


    bool Add_reserve(vector<string>&words)
    {
        int start_time=stoi(words[2]);
        int end_time=stoi(words[3]);
        for(int i=0;i<reserves.size();i++)
        {
            if(!conflict_time_client(start_time,end_time,reserves[i].get_start_time(),reserves[i].get_end_time()))
            {
                Output_msg err;
                err.Permission_Denied();
                return false;
            }
        }
        return true;
    }


    int find_price(string name, map<string , int > menu_item)
    {
        for(auto it=menu_item.begin();it!=menu_item.end();it++)
        {
            if((*it).first==name)
                return (*it).second;
        }
        return 0;
    }

    bool Add_reservetion(vector<string> words)
    {
        int start_time=stoi(words[2]);
        int end_time=stoi(words[3]);
        if(Add_reserve(words))
        {
            Reserve reserve(words[0],stoi(words[1]),start_time,end_time,aaann.separate_food(words));
            reserves.push_back(reserve);
            return true;
        }
        return false;
    }



    void show_info(string restaurant_name , string reserve_id,bool type_mode)
    {
        vector<int> perm;
        for(int i=0;i<reserves.size();i++)
        {
            if(  (restaurant_name==reserves[i].get_restaurant_name() && reserve_id==to_string(reserves[i].get_reserve_id())) || type_mode )
            {
                if(reserves[i].get_status()==1)
                    perm.push_back(reserves[i].get_start_time()+100*i);
            }
        }
        for(int i=0;i<perm.size();i++)
        {
            int index=perm[i]/100;
            cout<<reserves[index].get_reserve_id()<<": ";
            cout<<reserves[index].get_restaurant_name()<<" ";
            cout<<reserves[index].get_table_id()<<" ";
            cout<<reserves[index].get_start_time()<<" "<<reserves[index].get_end_time()<<" ";
            vector<string>visited;
            for(int j=0;j<reserves[index].foods_name.size();j++)
            {
                if(count(visited.begin(),visited.end(),reserves[index].foods_name[j])==0 )
                {
                    visited.push_back(reserves[index].foods_name[j]);
                    cout<<reserves[index].foods_name[j]<<"(";
                    cout<<count(reserves[index].foods_name.begin(),reserves[index].foods_name.end(),reserves[index].foods_name[j])<<") ";
                }
            }
            cout<<" "<<reserves[index].get_inital_price()<<" "<<reserves[index].get_final_price();

            cout<<endl;
        }
    }

    void Add_budget(int amount)
    {
        budget+=amount;
    }

    int get_budget(){return budget;}

    void decrease_budget(int num){budget=budget-num;}

    void set_num_of_reserve(int x){num_of_reserve=num_of_reserve+x;}


};
