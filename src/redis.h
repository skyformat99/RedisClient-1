#ifndef REDIS_REDIS_H
#define REDIS_REDIS_H

#include "connection.h"

class Redis{
public:
    Redis(const std::string &addr,int port);
    ~Redis();

    std::vector<std::string> keys(const std::string& pattern);

    int del(const std::vector<std::string> &keys);
    int del(const std::string &key);
    int exists(const std::string &key);
    int expire(const std::string &key,unsigned seconds);
    int expireat(const std::string &key,unsigned timestamp);
private:
    Connection con;
};
#endif //REDIS_REDIS_H