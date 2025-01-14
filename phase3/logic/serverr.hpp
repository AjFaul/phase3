#pragma once
#include "delete.hpp"
class Serverr : public Check
{
private:
    int type_cmd;
    string line;
    Output_msg err;
    Analysis_input analysis;
    Client cur_client;
    void update_client(App&app)
    {
        for(int i=0;i<app.clients.size();i++)
        {
            if(app.clients[i].username== cur_client.username)
                app.clients[i]=cur_client;
        }
    }

    bool signup_server(App& app)
    {
        POST post;
        vector<string> line_tokens=analysis.Analysis_username_password(line);
        if(name_is_repeatly(line_tokens[0],app))
        {
            err.Bad_Request();
            return false;
        }
        else
        {
            cur_client.set_client(line_tokens[0], line_tokens[1]);
            post.signup(line_tokens,app);
            err.OK();
            return true;
        }
    }

    void login_server(App& app,int& login_status)
    {
        vector<string> line_tokens=analysis.Analysis_username_password(line);
        bool login_output=Check :: check_user_pass(line_tokens,app);
        login_status=(login_output)?ACTIVE:DE_ACTIVE;
        POST post;
        if(login_status)
        {
            cur_client=post.login(line_tokens);
            err.OK();
        }
    }

    void district_server(App& app)
    {
        GET get;
        vector<string> line_tokens=split_by_space(line,DELIMITER_SPACE);
        if(line_tokens.size()==3)
            get.districts("NULL",app);
        else
            get.districts(analysis.get_district_name(line_tokens),app);
    }

    void my_district_server(App& app)
    {
        PUT put;
        vector<string> line_tokens=split_by_space(line,DELIMITER_SPACE);
        string name = analysis.get_district_name(line_tokens);
        if(check_district_name(app.distritcs , name))
            put.my_district(name , cur_client);
        update_client(app);

    }

    void restaurants_server(App& app)
    {
        GET get;
        vector<string> line_tokens=split_by_space(line,DELIMITER_SPACE);
        if(line_tokens.size()==3)
            get.restaurants("NULL",app,cur_client);
        else
            get.restaurants(analysis.get_food_name(line_tokens) , app , cur_client);
    }


    float show_order_amount_discount(App&app , string restaurant_name,int original_price)
    {
        for(int i=0;i<app.restaurants.size();i++)
        {
            if(app.restaurants[i].name==restaurant_name)
            {
                cout<<"Order Amount Discount: ";
                if(app.restaurants[i].total_price_discount.type=="percent")
                {
                    cout<<stoi(app.restaurants[i].total_price_discount.value)*original_price/100<<endl;
                    return stof(app.restaurants[i].total_price_discount.value)*original_price/100;

                }else
                {
                    cout<<stoi(app.restaurants[i].total_price_discount.value)<<endl;
                    return stof(app.restaurants[i].total_price_discount.value);
                }
                
            }
        }
        return 0;
    }


    float show_total_item(App&app , string restaurant_name,vector<string> foods)
    {
        float output=0;
        for(int i=0;i<app.restaurants.size();i++)
        {
            if(app.restaurants[i].name==restaurant_name)
            {
                for(int j=0;j<app.restaurants[i].discounts.size();j++)
                {
                    if(find(foods.begin(),foods.end(),app.restaurants[i].discounts[j].name_food)!=foods.end())
                    {
                        output+=stof(app.restaurants[i].discounts[j].value);
                    }
                }
            }
        }
        
        if(output!=0)
        {
            cout<<"Total Item Specific Discount: "<<output<<endl;
            return output;
        }
        return output;
    }

    float show_first_discount(App &app , string restaurant_name)
    {
        if(cur_client.num_of_reserve>1)
            return 0;
        float output=0;
        for(int i=0;i<app.restaurants.size();i++)
        {
            if(app.restaurants[i].name==restaurant_name)
            {
                if(app.restaurants[i].first_order_discount.type!="none")
                {
                    cout<<"First Order Discount: "<<app.restaurants[i].first_order_discount.value<<endl;
                    output=stof(app.restaurants[i].first_order_discount.value);
                    return output;
                }
            }
        }
        return 0;
    }

    float show_info_reserve(vector<string> words,App& app)
    {
        cout<<"Reserve ID: "<<cur_client.reserves[cur_client.reserves.size()-1].get_reserve_id()<<endl;
        cout<<"Table "<<words[1]<<" for "<<words[2]<<" to "<<words[3]<<" in "<<words[0]<<endl;
        int price=cur_client.reserves[cur_client.reserves.size()-1].get_price();
        cout<<"Original Price: "<<price<<endl;

        float l1,l2,l3;


        l1=show_order_amount_discount(app,words[0],price);
        vector<string>foods;
        foods=analysis.separate_food(words);
        l2=show_total_item(app,words[0],foods);
        l3=show_first_discount(app,words[0]);
        cout<<"Total Discount: ";
        cout<<(l1+l2+l3)<<endl;
        cout<<"Total Price: "<<(price-(l1+l2+l3))<<endl;




        // vector<int>priceeee;
        // for(int i=0;i<app.restaurants.size();i++)
        // {
        //     if(app.restaurants[i].name==words[0])
        //     {
        //         for(auto it=app.restaurants[i].menu_item.begin() ;it!=app.restaurants[i].menu_item.end(); it++)
        //         {
        //             if(find(foods.begin(),foods.end(), (*it).first )!=foods.end())
        //             {
        //                 priceeee.push_back((*it).second);
        //             }
        //         }
        //     }
        // }


        // int takhfif;
        // for(int i=0;i<app.restaurants.size();i++)
        // {
        //     if(app.restaurants[i].name == words[0])
        //     {
        //         for(int j=0;j<foods.size();j++)
        //         {
        //             for(int k=0;k<app.restaurants[i].discounts.size();k++)
        //             {
        //                 if(app.restaurants[i].discounts[k].name_food==foods[j])
        //                 {
        //                     if(app.restaurants[i].discounts[k].type=="amount")
        //                     {
        //                         takhfif+=stoi(app.restaurants[i].discounts[k].value);
        //                     }            
        //                     if(app.restaurants[i].discounts[k].type=="percent")
        //                     {
        //                         takhfif+=stoi(app.restaurants[i].discounts[k].value) * priceeee[j];
        //                     }
        //                 }
        //             }
        //         }
        //     }
        // }



        return (price-(l1+l2+l3));


    }


    void update_client(Client& client , vector<string>words , App& app)
    {
        for(int i=0;i<app.restaurants.size();i++)
        {
            if(app.restaurants[i].name==words[0])
            {
                client.reserves[client.reserves.size()-1].set_reserve_id(app.restaurants[i].reserves[app.restaurants[i].reserves.size()-1].get_reserve_id());
                client.reserves[client.reserves.size()-1].set_price(app.restaurants[i].reserves[app.restaurants[i].reserves.size()-1].get_prices());
                client.reserves[client.reserves.size()-1].set_final_price(app.restaurants[i].reserves[app.restaurants[i].reserves.size()-1].get_final_price());
            }
        }
    }

    bool reserve_server(App& app)
    {
        vector<string> words=analysis.Analysis_reserve(line);
        POST post;
        if(post.reserve(words,app,cur_client) && cur_client.Add_reservetion(words))
        {
            int l;
            update_client(cur_client,words,app);
            l=show_info_reserve(words,app);
            cur_client.decrease_budget(l);
            cur_client.set_num_of_reserve(1);
            return true;
        }else
            return false;


    }

    void show_restaurant_detail_server(App& app)
    {
        vector<string> keys={"restaurant_name"};
        string rest_name=analysis.search_words(line,keys[0],keys);
        cout<<rest_name<<endl;
        for(int i=0;i<app.restaurants.size();i++)
        {
            if( rest_name==app.restaurants[i].name)
            {
                app.restaurants[i].show_restaurant_info();
                app.restaurants[i].show_discount();
                return;
            }
        }
        err.Not_Found();
        return;
    }

    void show_client_info(App& app)
    {
        vector<string> keys={"restaurant_name","reserve_id"};
        string restaurant_name=analysis.search_words(line,keys[0],keys);
        string reserve_id=analysis.search_words(line,keys[1],keys);
        if(cur_client.reserves.size()==0)
        {
            err.Empty();
            return;
        }
        if(reserve_id.size()>0 && restaurant_name.size()==0)
        {
            err.Bad_Request();
            return;
        }
        bool type_mode;
        if(reserve_id.size()==0 && restaurant_name.size()==0)
            type_mode=true;
        cur_client.show_info(restaurant_name,reserve_id,type_mode);
        
    }

    void delete_server(App& app)
    {
        DELETE del;
        vector<string> keys={"restaurant_name","reserve_id"};
        string restaurant_name=analysis.search_words(line,keys[0],keys);
        string reserve_id=analysis.search_words(line,keys[1],keys);
        for(int i=0;i<cur_client.reserves.size();i++)
        {
            if(cur_client.reserves[i].get_restaurant_name()==restaurant_name)
            {
                if(to_string(cur_client.reserves[i].get_reserve_id())==reserve_id)
                {
                    int x;
                    cur_client.reserves[i].delete_reserve();
                    x=del.del_func(restaurant_name,stoi(reserve_id),app);
                    // cout<<"salam man injam   "<<x<<endl;
                    cur_client.decrease_budget(-1 * x* 0.6);
                    err.OK();
                    return;
                }else
                {
                    err.Not_Found();
                    return;
                }
            }
        }
        err.Permission_Denied();
        return;
    }


    void Add_budget_server(App& app)
    {
        vector<string>keys={"amount"};
        string amount=analysis.search_words(line,keys[0],keys);
        int x;
        try
        {
            x=stoi(amount);
            cur_client.Add_budget(x);
            err.OK();
            return;
        }
        catch(...)
        {
            err.Bad_Request();
            return;
        }
        
    }

    void show_budget_server(App& app)
    {
        cout<<cur_client.get_budget()<<endl;
    }

public:
    Serverr(){}

    void set_Server(int t_cmd, string line_input)
    {
        type_cmd=t_cmd;
        line=line_input;
    }

    void check(App& app, int &login_status)
    {
        if(login_status==DE_ACTIVE)
        {

            if(type_cmd==CMD_SIGNUP)
            {
                if(signup_server(app))
                    login_status=ACTIVE;
                return;
            }

            if(type_cmd==CMD_LOGIN)
            {
                login_server(app,login_status);
                return;
            }

            if(type_cmd==CMD_LOGOUT)
            {
                err.Permission_Denied();
                return;
            }
            
            err.Permission_Denied();
        }else
        {

            if(type_cmd==CMD_SIGNUP)
                err.Permission_Denied();

            if(type_cmd==CMD_LOGIN)
                err.Permission_Denied();
            
            if(type_cmd==CMD_LOGOUT)
            {
                login_status=DE_ACTIVE;
                err.OK();
            }

            if(type_cmd==CMD_DISTRICTS)
                district_server(app);
            
            if(type_cmd==CMD_FULL_DISTRICTS)
                district_server(app);
            
            if(type_cmd==CMD_PUT_DISTRICT)
                my_district_server(app);
            
            if(type_cmd==CMD_RESTAURANTS_WITHOUT_FOODNAME)
                restaurants_server(app);
            
            if(type_cmd==CMD_RESTAURANTS_WITH_FOODNAME)
                restaurants_server(app);

            if(type_cmd==CMD_RESERVE_WITH_FOOD)
                reserve_server(app);
            
            if(type_cmd==CMD_RESERVE_WITHOUT_FOOD)
                reserve_server(app);
            
            if(type_cmd==CMD_RESTAURANT_DETAIL)
                show_restaurant_detail_server(app);

            if(type_cmd==CMD_INFO_CLIENT)
                show_client_info(app);

            if(type_cmd==CMD_DELETE_M)
                delete_server(app);
            
            if(type_cmd==CMD_INCREASE_BUDGET)
                Add_budget_server(app);

            if(type_cmd==CMD_SHOW_BUDGET)
                show_budget_server(app);



        }
        
    }



};
