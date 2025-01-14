#pragma once
#include "app.hpp"
class Check
{
private:
    int status;
    Output_msg err;
public:
    Check(){status=1;}


    bool name_is_repeatly(string name, App& app)
    {
        vector<string> usernames;
        for(int i=0;i<app.clients.size();i++)
            usernames.push_back(app.clients[i].username);
        for(int i=0; i<usernames.size();i++)
        {
            if(usernames[i]==name)
                return true;
        }
        return false;
    }

    bool check_user_pass(vector<string> user_pass , App &app)
    {
        for(int i=0;i<app.clients.size();i++)
        {
            if(app.clients[i].username==user_pass[0] && app.clients[i].password!=user_pass[1])
            {
                err.Permission_Denied();
                return false;
            }
            if(app.clients[i].username==user_pass[0] && app.clients[i].password==user_pass[1])
                return true;
        }
        err.Not_Found();
        return false;
    }

    bool check_district_name(vector<District> districts ,string name)
    {
        for(int i=0;i<districts.size();i++)
        {
            if(name==districts[i].name)
            {
                err.OK();
                return true;
            }
        }
        err.Not_Found();
        return false;
    }

    bool check_visited(string name, vector<string>& visited)
    {
        for(int i=0;i<visited.size();i++)
        {
            if(name==visited[i])
                return true;
        }
        return false;
    }

    District find_district(string name, App& app)
    {
        for(int i=0;i<app.distritcs.size();i++)
        {
            if(app.distritcs[i].get_name()==name)
                return app.distritcs[i];
        }
        vector<string> data_dummy={name};
        District dummy(data_dummy);
        return dummy;
    }

    vector<string> bfs_function(vector<string>& neighbors , vector<string>&visited , App &app)
    {
        int number_of_new_visited=0;
        vector<string> new_neighbors;
        for(int i=0;i<neighbors.size();i++)
        {
            District cur_district=find_district(neighbors[i],app);
            // show_vector(cur_district.neighbors);
            for(int j=0;j<cur_district.neighbors.size();j++)
            {
                if(!check_visited(cur_district.neighbors[j],visited))
                {
                    new_neighbors.push_back(cur_district.neighbors[j]);
                    visited.push_back(cur_district.neighbors[j]);
                    number_of_new_visited++;
                }
            }
        }
        if(number_of_new_visited==0)
            return visited;
        return bfs_function(new_neighbors,visited,app);
    }



};
