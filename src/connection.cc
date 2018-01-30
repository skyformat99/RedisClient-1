#include "connection.h"

Connection::Connection(const std::string& addr, int port) {
    redis_addr = addr;
    redis_port = port;
    client_fd = connect_to_redis();
}

Connection::~Connection(){
    if(client_fd>0){
        close(client_fd);
    }
}

int Connection::connect_to_redis() {
    int sockfd;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        return -1;
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(redis_port);

    if (inet_pton(AF_INET, redis_addr.c_str(), &servaddr.sin_addr) < 0) {
        return -1;
    }

    if (connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        return -1;
    }
    return sockfd;
}

int Connection::get_line(char* buf, int size) {
    char c = '\0';
    int read_size = 0;
    while (read_size < size - 1 && c != '\n') {
        ssize_t num = recv(client_fd, &c, 1, 0);
        if (num > 0) {
            if (c == '\r') {
                num = recv(client_fd, &c, 1, MSG_PEEK);
                if (num > 0 && c == '\n')
                    recv(client_fd, &c, 1, 0);
                else
                    c = '\n';
            }
            if (c != '\n') {
                buf[read_size] = c;
                read_size++;
            }
        } else {
            c = '\n';
        }
    }
    buf[read_size] = '\0';
    return read_size;
}

std::string Connection::get_string_from_reply(char* buffer) {
    std::string result = "";
    char* p = buffer;
    p++;
    while (*p != '\0') {
        result += *p;
        p++;
    }
    return result;
}

std::string Connection::parser_status_reply(char* buffer) {
    std::string result = get_string_from_reply(buffer);
    return result;
}

std::string Connection::parser_error_reply(char* buffer) {
    std::string result = get_string_from_reply(buffer);
    return result;
}

int Connection::get_int_from_reply(char* buffer) {
    std::string str = "";
    char* p = buffer;
    p++;
    while (*p != '\0') {
        str += *p;
        p++;
    }
    int result = atoi(str.c_str());
    return result;
}

int Connection::parser_integer_reply(char* buffer) {
    int result = get_int_from_reply(buffer);
    return result;
}

Response Connection::parser_buik_reply(char* buffer) {
    Response res;
    int reply_len = get_int_from_reply(buffer);
    if (reply_len == -1) {
        res.is_null = true;
    } else {
        res.is_null = false;
        int recv_size = 0;
        int num = 0;
        while (recv_size < reply_len) {
            num = get_line(buffer, MAXLINE);
            if (num == 0) {
                break;
            }
            recv_size += num;
            res.string_res += buffer;
        }
    }
    return res;
}

Response Connection::parser_multi_reply(char* buffer) {
    int reply_num = get_int_from_reply(buffer);
    Response res;
    if (reply_num == -1) {
        res.is_null = true;
        return res;
    }
    while (reply_num) {
        reply_num--;
        Response item = Connection::recv_reply();
        res.multi_res.push_back(item);
    }
    return res;
}

Response Connection::recv_reply() {
    char buffer[MAXLINE + 1];
    int recv_size = 0;

    recv_size = get_line(buffer, MAXLINE);

    Response res;

    switch (buffer[0]) {
        case '+':
            res.res_type = RESPONSE_TYPE::STATUS_REPLY;
            res.string_res = parser_status_reply(buffer);
            break;
        case '-':
            res.res_type = RESPONSE_TYPE::ERROR_REPLY;
            res.string_res = parser_error_reply(buffer);
            break;
        case ':':
            res.res_type = RESPONSE_TYPE::INTEGER_REPLY;
            res.integer_res = parser_integer_reply(buffer);
            break;
        case '$':
            res = parser_buik_reply(buffer);
            break;
        case '*':
            res = parser_multi_reply(buffer);
            break;
    }
    return res;
}

Response Connection::send_commands(std::vector<std::string>& commands) {
    unsigned command_num = commands.size();
    std::string command = "*" + std::to_string(command_num) + "\r\n";
    for (auto str : commands) {
        command += "$" + std::to_string(str.size()) + "\r\n" + str + "\r\n";
    }
    send(client_fd, command.c_str(), command.size(), 0);
    Response res = recv_reply();
    return res;
}