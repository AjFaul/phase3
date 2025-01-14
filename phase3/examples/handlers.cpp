#include "handlers.hpp"

#include <cstdlib>
#include <iostream>

Response* signup_handler::callback(Request* req) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    if (username == "root") {
        throw Server::Exception("Remote root access has been disabled.");
    }
    std::cout << "username: " << username << ",\tpassword: " << password << std::endl;
    Response* res = Response::redirect("/signup");
    res->setSessionId("SID");
    return res;
}

Response* LoginHandler::callback(Request* req) {
    std::string username = req->getBodyParam("username");
    std::string password = req->getBodyParam("password");
    if (username == "root") {
        throw Server::Exception("Remote root access has been disabled.");
    }
    std::cout << "username: " << username << ",\tpassword: " << password << std::endl;
    Response* res = Response::redirect("/login");
    res->setSessionId("SID");
    return res;
}