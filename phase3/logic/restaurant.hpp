#pragma once
#include "district.hpp"
#include "Discount_structure.hpp"
class Restaurant : public Reserve
{
private:
    int status;
    string name;
    string district;
    vector<Reserve> reserves;
    int open_time,close_time, num_of_table;
    map<string,int>menu_item; 
    friend class App;
    friend class Check;
    friend class GET;
    friend class POST;
    friend class Serverr;
    friend class DELETE;
    friend class Client;
    Output_msg err;

    vector<discount> discounts;
    total_discount total_price_discount;
    first_discount first_order_discount;





    bool conflict_time(int s1,int e1,int s2 , int e2)
    {
        if(s1<1 || e1>24)
            return false;
        if(e1>s2 && e1<e2)
            return false;
        if(s1>s2 && s1<e2)
            return false;
        if(e2>s1 && e2<e1)
            return false;
        if(s2>s1 && s2<e1)
            return false;
        return true;
    }



    bool Add_reserve(int table_id, int s_time ,int e_time, vector<string> foods,int budget=0)
    {
        Reserve reserve(name,table_id,s_time,e_time,foods);
        vector<int> prices;
        
        if(table_id>num_of_table)
        {
            err.Not_Found();
            return false;
        }

        for(int i=0;i<reserves.size();i++)
        {
            if(reserves[i].get_table_id()==table_id)
            {
                if(!conflict_time(s_time,e_time,reserves[i].get_start_time(),reserves[i].get_end_time()))
                {
                    
                    err.Permission_Denied();
                    return false;
                }
            }
        }
        

        for(int i=0;i<foods.size();i++)
        {
            if(menu_item[foods[i]]==0)
            {
                err.Not_Found();
                return false;
            }
            prices.push_back(menu_item[foods[i]]);
        }
        int sum_all=0;
        for(int i=0;i<prices.size();i++)
            sum_all+=prices[i];


        int takhfif=0;
        for(int i=0;i<foods.size();i++)
        {

            for(int j=0;j<foods.size();j++)
            {
                if(discounts[i].name_food==foods[j])
                {
                    if(discounts[i].type=="amount")
                    {
                        takhfif+=stoi(discounts[i].value);
                    }
                
                    if(discounts[i].type=="percent")
                    {
                        takhfif+= stoi(discounts[i].value)*prices[i];
                    }
                }
            }
        }
        if(first_order_discount.type=="amount")
        {
            takhfif+=stoi(first_order_discount.value);
        }
        if(first_order_discount.type=="percent")
        {
            takhfif+=stoi(first_order_discount.value) * (sum_all-takhfif)/100;
        }


        if((sum_all-takhfif)>stoi(total_price_discount.floor_price))
        {
            if(total_price_discount.type=="amount")
            {
                takhfif+=stoi(total_price_discount.value);
            }
            if(total_price_discount.type=="percent")
            {
                takhfif+=stof(total_price_discount.value) * (sum_all-takhfif)/100;
            }
        }
         
        
        if(budget<(sum_all-takhfif))
        {
            err.Bad_Request();
            return false;
        }

        reserve.set_final_price(sum_all-takhfif);
        reserve.set_price(prices);
        reserve.set_reserve_id(reserves.size()+1);
        reserves.push_back(reserve);
        return true;
    }


public:

    Restaurant(vector <string> data)
    {
        int size=data.size();
        name=data[0];
        district=data[1];
        for(int i=2; i<(size - 3) ; i=i+2)
            menu_item[data[i]]=stoi(data[i+1]);
        open_time=stoi(data[size-3]);
        close_time=stoi(data[size-2]);
        num_of_table=stoi(data[size-1]);
    }


    void show_restaurant_info()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"District: "<<district<<endl;
        cout<<"Time: "<<open_time<<"-"<<close_time<<endl;
        cout<<"Menu:";
        string foods_name_price;
        for(auto it=menu_item.begin();it!=menu_item.end();it++)
        {
            if((*it).second!=0)
            {
                foods_name_price+=" ";
                foods_name_price+=(*it).first;
                foods_name_price+="(";
                foods_name_price+=to_string(((*it).second));
                foods_name_price+="),"; 
            }
            
        }
        cout<<foods_name_price.substr(0,foods_name_price.size()-1)<<endl;


        map<int , string > output;
        vector<int> num_of_table_id;


        for(int i=0;i<num_of_table;i++)
        {
            num_of_table_id.push_back(i+1);
        }







        string itt;
        string xx;

        for(int i=0;i<num_of_table_id.size();i++)
        {
            xx="";
            itt="";
            vector<string> irrr;
            for(int j=0;j<reserves.size();j++)
            {
                if(reserves[j].get_table_id()== num_of_table_id[i] && reserves[j].get_status()==1)
                {
                    itt+=" ";
                    itt+="(";
                    itt+=to_string(reserves[j].get_start_time());
                    itt+="-";
                    itt+=to_string(reserves[j].get_end_time());
                    itt+=")";
                    itt+=",";
                }
                irrr.push_back(itt);
                itt="";
            }
            sort(irrr.begin(),irrr.end());
            for(int k=0;k<irrr.size();k++)
            {
                xx+=irrr[k];
            }
            if(xx.size()!=0)
                xx.pop_back();
            output[num_of_table_id[i]]=xx;
        }
        
        for(auto it=output.begin(); it!=output.end() ; it++)
        {
            cout<<(*it).first<<":";
            cout<<(*it).second<<endl;
        }


    }


    void Add_total_price(string words)
    {
        vector<string> data=split_by_space(words,DELIMITER_SIMIC);

        if(data[0]=="none")
        {
            total_price_discount.floor_price="none";
            total_price_discount.type="none";
            total_price_discount.value="none";
            return;
        }

        total_price_discount.type=data[0];
        total_price_discount.floor_price=data[1];
        total_price_discount.value=data[2];
        return;
    }

    void Add_first_order(string words)
    {
        vector<string>data=split_by_space(words,DELIMITER_SIMIC);

        if(data[0]=="none")
        {
            first_order_discount.type="none";
            first_order_discount.value="none";
            return;
        }

        first_order_discount.type=data[0];
        first_order_discount.value=data[1];
        return;
    }

    void Add_foods_discounts(string words)
    {
        vector<string> section_food=split_by_space(words,DELIMITER_YA);

        if(section_food[0]=="none")
        {
            discount dis;
            dis.name_food="none";
            dis.type="none";
            dis.value="none";
            discounts.push_back(dis);
            return;
        }

        for(int i=0;i<section_food.size();i++)
        {
            vector<string> data_discount=split_by_space(section_food[i],DELIMITER_SIMIC);
            discount dis;
            dis.type=data_discount[0];
            vector<string>x=split_by_space(data_discount[1],DELIMITER_2_DOT);
            dis.name_food=x[0];
            dis.value=x[1];
            discounts.push_back(dis);
        }

    }

    void show_order_amount_discount()
    {
        if(total_price_discount.type=="none")
            return;
        cout<<"Order Amount Discount: "<<total_price_discount.type<<", ";
        cout<<total_price_discount.floor_price<<", "<<total_price_discount.value<<endl;  
    }

    void show_food_discount()
    {
        if(discounts.size()==0)
            return;

        cout<<"Item Specific Discount:";
        string x;
        for(int i=0;i<discounts.size();i++)
        {
            x+=" ";
            x+=discounts[i].name_food;
            x+="(";
            x+=discounts[i].type;
            x+=": ";
            x+=discounts[i].value;
            x+="),";
        }
        if(x.size()!=0)
            x.pop_back();
        cout<<x<<endl;
    }

    void show_first_discount()
    {
        if(first_order_discount.value=="none")
            return;
        cout<<"First Order Discount: ";
        cout<<first_order_discount.type<<", ";
        cout<<first_order_discount.value<<endl;
    }


    void show_discount()
    {
        show_order_amount_discount();
        show_food_discount();
        show_first_discount();
    }

};
