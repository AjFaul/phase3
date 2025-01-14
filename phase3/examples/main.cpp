#include <iostream>
#include <string>
#include "../server/server.hpp"
#include "handlers.hpp"
using namespace std;

void mapServerPaths(Server& server) {
    server.setNotFoundErrPage("static/404.html");

    server.get("/", new ShowPage("static/home.html"));
    server.get("/home.png", new ShowImage("static/home.png"));

    server.get("/signupform", new ShowPage("static/signup.html"));
    server.post("/signup", new signup_handler());

    server.get("/loginform", new ShowPage("static/logincss.html"));
    server.post("/login", new LoginHandler());



}

int main(int argc, char** argv) {
    try {
        int port = argc > 1 ? std::stoi(argv[1]) : 5000;
        Server server(port);
        mapServerPaths(server);
        std::cout << "Server running on port: " << port << std::endl;
        server.run();

    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
    catch (const Server::Exception& e) {
        std::cerr << e.getMessage() << std::endl;
    }
    return 0;
}
