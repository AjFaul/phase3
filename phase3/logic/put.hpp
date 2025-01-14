#pragma once
#include "get.hpp"
#include "Outputmsg.hpp"
class PUT
{
private:
    Output_msg err;
    void my_district(string name,Client& client)
    {
        client.set_district(name);
    }

    friend class Serverr;
public:
    PUT(){}

};
