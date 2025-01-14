#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <list>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>
#include "Constants.hpp"
#include "Outputmsg.hpp"
#include "split_func.hpp"
using namespace std;


class Analysis_input
{
private:
    int status;
    Output_msg err;
public:
    Analysis_input(){status=1;}

    int CMD_CONTROLLER(string &line)
    {
        vector<string> input_sections;
        input_sections=split_by_space(line,DELIMITER_SPACE);
        string output_type;


        // lev set 0
        if(input_sections[0]==CMD_POST)
            output_type+="1";
        if(input_sections[0]==CMD_GET)
            output_type+="2";
        if(input_sections[0]==CMD_PUT)
            output_type+="3";
        if(input_sections[0]==CMD_DELETE)
        {
            output_type+="4";
            return stoi(output_type);
        }

        // lev set 0 is ok?
        if(output_type.size()==0)
        {
            err.Not_Found();
            return -1;
        }


        // lev set 1
        if(input_sections[1]=="signup")
            output_type+="1";
        if(input_sections[1]=="login")
            output_type+="2";
        if(input_sections[1]=="logout")
            output_type+="3";
        if(input_sections[1]=="districts")
        {
            output_type+="1";
            auto it=find(input_sections.begin(), input_sections.end(),"district");
            if(it!=input_sections.end())
                output_type+="1";
        }
        if(input_sections[1]=="my_district")
            output_type+="1";
        if(input_sections[1]=="restaurants")
        {
            output_type+="2";
            auto it=find(input_sections.begin(), input_sections.end(),"food_name");
            if(it==input_sections.end())
                output_type+="1";
        }

        if(input_sections[1]=="reserve")
        {
            output_type+="4"; 
            auto it =find(input_sections.begin() , input_sections.end() , "foods");
            if(it==input_sections.end())
                output_type+="1";
        }
        if(input_sections[1]=="restaurant_detail")
            output_type+="3";
        
        if(input_sections[1]=="reserves")
            output_type+="6";
        
        if(input_sections[1]=="increase_budget")
            output_type+="15";

        if(input_sections[1]=="show_budget")
            output_type+="111";
        






        return stoi(output_type);
    }



    vector<string> Analysis_username_password(string& line)
    {
        vector<string> output;
        vector<string> line_token= split_by_space(line,DELIMITER_SPACE);

        auto it=find(line_token.begin() , line_token.end(),"username");
        it++;
        output.push_back((*it));
        it=find(line_token.begin(),line_token.end(),"password");
        it++;
        output.push_back((*it));
        return output;
    }

    string get_district_name(vector<string>& line_token)
    {
        string output;
        for(int i=0;i<line_token.size();i++)
        {
            if(line_token[i]=="district")
            {
                for(int j=(i+1) ; j<line_token.size();j++)
                {
                    output+=line_token[j];
                    if((j+1)!=line_token.size())
                        output+=" ";
                }
            }
        }
        return output;
    }

    string get_food_name(vector<string>& line_token)
    {
        string output;
        for(int i=0;i<line_token.size();i++)
        {
            if(line_token[i]=="food_name")
            {
                for(int j=(i+1) ; j<line_token.size();j++)
                {
                    output+=line_token[j];
                    if((j+1)!=line_token.size())
                        output+=" ";
                }
            }
        }
        return output;
    }


    // in 3 ta baraye tahlil reserve hast
    bool check_type(vector<string> name_list,string next_name)
    {
        for(int i=0;i<name_list.size();i++)
        {
            if(next_name==name_list[i])
                return 0;
        }
        return 1;
    }

    vector<string> Analysis_on_food(string foods)
    {
        vector<string> output=split_by_space(foods,DELIMITER_COMMA);
        return output;
    }

    vector<string> Analysis_reserve(string& line)
    {
        vector<string>output;
        vector<string> token;
        token=split_by_space(line,DELIMITER_SPACE);
        string extra;
        vector<string> list_name={"reserve","restaurant_name","table_id","start_time","end_time","foods"};
        auto it=find(token.begin(), token.end(),"restaurant_name");
        it++;
        while (check_type(list_name,(*it)))
        {
            extra+=(*it);
            it++;
            if(it==token.end())
                break;
            if(check_type(list_name,(*it)))
                extra+=" ";
        }
        output.push_back(extra);
        extra="";

        
        it=find(token.begin(), token.end(),"table_id");
        it++;
        while (check_type(list_name,(*it)))
        {
            extra+=(*it);
            it++;
            if(it==token.end())
                break;
        }
        output.push_back(extra);
        extra="";


        it=find(token.begin(), token.end(),"start_time");
        it++;
        while (check_type(list_name,(*it)))
        {
            extra+=(*it);
            it++;
            if(it==token.end())
                break;
        }
        output.push_back(extra);
        extra="";



        it=find(token.begin(), token.end(),"end_time");
        it++;
        while (check_type(list_name,(*it)))
        {
            extra+=(*it);
            it++;
            if(it==token.end())
                break;
        }
        output.push_back(extra);
        extra="";

        it=find(token.begin(), token.end(),"foods");
        if(it==token.end())
            return output;
        it++;

        while (check_type(list_name,(*it)))
        {
            extra+=(*it);
            it++;
            if(it==token.end())
                break;
            if(check_type(list_name,(*it)))
                extra+=" ";
        }


        vector<string> foods_list=Analysis_on_food(extra);
        for(int i=0;i<foods_list.size();i++)
        {
            output.push_back(foods_list[i]);
        }
        return output;

    }

    vector<string> separate_food(vector<string> words)
    {
        vector<string> output;
        for(int i=4;i<words.size();i++)
            output.push_back(words[i]);
        return output;
    }

    string restaurant_name(vector<string> words)
    {
        string output;
        for(int i=0;i<words.size();i++)
        {
            if(words[i]=="restaurant_name")
            {
                for(int j=(i+1); j<words.size();j++)
                {
                    output+=words[j];
                }
            }
        }
        return output;
    }

    string search_words(string& line, string& key , vector<string>& keys)
    {
        vector<string> tokens=split_by_space(line,DELIMITER_SPACE);
        string output="";
        for(int i=0;i<tokens.size();i++)
        {
            if(tokens[i]==key)
            {
                for(int j=(i+1);j<tokens.size();j++)
                {
                    if(find(keys.begin(),keys.end(),tokens[j]) == keys.end())
                    {
                        output+=tokens[j];
                        output+=" ";
                    }else
                        break;;
                }
                break;
            }
        }
        if(output.size()!=0)
            output.pop_back();
        return output;
    }



};
