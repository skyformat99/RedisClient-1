#ifndef REDIS_CONNECTION_H
#define REDIS_CONNECTION_H

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <vector>

#include "response.h"

#define MAXLINE 512

class Connection {
public:
    Connection(const std::string &addr,int port);
    ~Connection();
    Response send_commands(std::vector<std::string>& commands);

private:
    int connect_to_redis();
    int get_line(char* buf, int size);

    std::string get_string_from_reply(char* buffer);
    std::string parser_status_reply(char* buffer);
    std::string parser_error_reply(char* buffer);
    int get_int_from_reply(char* buffer);
    int parser_integer_reply(char* buffer);
    Response parser_buik_reply(char* buffer);
    Response parser_multi_reply(char* buffer);
    Response recv_reply();

    int client_fd;
    std::string redis_addr;
    int redis_port;
};

#endif