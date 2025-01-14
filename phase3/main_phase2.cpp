#include "./logic/serverr.hpp"

void control_structure(char* argv[])
{
    App app;
    string line;
    app.handle_input_data(argv,app);
    Analysis_input analysis;
    Serverr serverrr;
    int cmd_type;
    int login_status=0;
    while (getline(cin,line))
    {
        cmd_type=analysis.CMD_CONTROLLER(line);
        // cout<<cmd_type<<endl;
        if(cmd_type==WRONG_CMD)
            break;
        serverrr.set_Server(cmd_type,line);
        serverrr.check(app,login_status);
    }   
}

int main(int argc , char* argv[])
{
    control_structure(argv);
}
