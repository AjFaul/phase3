#pragma once
#include "client.hpp"
class App
{
private:
    int status;
    vector<Restaurant> restaurants;
    vector<Client> clients;
    vector<District> distritcs;
    void Add_district(District district){distritcs.push_back(district);}
    void Add_restaurant(Restaurant restaurant){restaurants.push_back(restaurant);}


    void handle_restaurants(App& app,ifstream& file_restaurants)
    {
        string line;
        int num_line=0;
        vector<string>data_line;
        while (getline(file_restaurants,line))
        {
            if(num_line==0)
            {
                num_line++;
                continue;
            }
            data_line=split(line,DELIMITER);
            Restaurant restaurant(data_line);
            app.Add_restaurant(restaurant);

        }
        file_restaurants.close();
    }

    void handle_districts(App& app,ifstream& file_district){
        string line;
        int num_line=0;
        vector<string> data_line;
        while (getline(file_district,line))
        {
            if(num_line==0)
            {
                num_line++;
                continue;
            }
            data_line=split(line,DELIMITER);
            District dirstrict(data_line);
            app.Add_district(dirstrict);
        }
        file_district.close();  
    }

    void update_district()
    {
        vector<string> names_district;
        for(int i=0;i<distritcs.size();i++)
            names_district.push_back(distritcs[i].get_name());
        sort(names_district.begin(),names_district.end());

        vector<District> cpy_district;
        for(int i=0;i<names_district.size();i++)
        {
            for(int j=0;j<distritcs.size();j++)
            {
                if(distritcs[j].get_name()==names_district[i])
                    cpy_district.push_back(distritcs[j]);
            }
        }
        distritcs=cpy_district;
    }


    void handle_discounts(App& app ,ifstream& file_discounts)
    {
        string line;
        int num_line=0;
        vector<string>data_line;
        while (getline(file_discounts,line))
        {
            if(num_line==0)
            {
                num_line++;
                continue;
            }
            data_line=split_by_space(line,DELIMITER_COMMA);

            for(int i=0;i<app.restaurants.size();i++)
            {
                if(app.restaurants[i].name==data_line[0])
                {
                    app.restaurants[i].Add_total_price(data_line[1]);
                    app.restaurants[i].Add_first_order(data_line[2]);
                    app.restaurants[i].Add_foods_discounts(data_line[3]);
                }
            }
        }
        file_discounts.close();
    }



    friend class Check;
    friend class GET;
    friend class Serverr;
    friend class POST;
    friend class DELETE;
    friend class Client;

public:
    App(){status=1;}
    
    void handle_input_data(char* argv[],App& app)
    {
        string name_file_restaurants=argv[2];
        string name_file_districts=argv[3];
        string name_file_discounts=argv[4];

        ifstream file_restaurants(name_file_restaurants);
        if(!file_restaurants.is_open())
            cout<<"file is not open"<<endl;
        
        ifstream file_districts(name_file_districts);
        if(!file_districts.is_open())
            cout<<"file is not open"<<endl;
        
        ifstream file_discount(name_file_discounts);
        if(!file_discount.is_open())
            cout<<"file is not open"<<endl;
        
        
        handle_restaurants(app,file_restaurants);
        handle_districts(app,file_districts);
        update_district();
        handle_discounts(app,file_discount);
    }

    void Add_client(Client client)
    {
        clients.push_back(client);
    }

};
