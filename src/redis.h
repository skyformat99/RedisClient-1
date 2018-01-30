#ifndef REDIS_REDIS_H
#define REDIS_REDIS_H

#include "connection.h"

class Redis {
public:
    Redis(const std::string &addr, unsigned port);

    Redis(const std::string &addr, unsigned port, unsigned db);

    ~Redis();

    //待实现：migrate,object,restore,dump

    std::vector<std::string> keys(const std::string &pattern);

    int del(const std::vector<std::string> &keys);

    int del(const std::string &key);

    int exists(const std::string &key);

    int expire(const std::string &key, unsigned seconds);

    int expireat(const std::string &key, unsigned timestamp);

    int move(const std::string &key, unsigned db);

    int persist(const std::string &key);

    int pexpire(const std::string &key, unsigned milliseconds);

    int pexpireat(const std::string &key, unsigned long long milliseconds_timestamp);

    int pttl(const std::string &key);

    std::string randomkey();

    std::string rename(const std::string &key, const std::string &newkey);

    int renamenx(const std::string &key, const std::string &newkey);

    std::vector<std::string>
    sort(const std::string &key, int offset = 0, int count = 0, bool desc = false, bool alpha = false,
         const std::string &by = "",
         const std::vector<std::string> &get = {});

    int ttl(const std::string &key);

    std::string type(const std::string &key);

    std::vector<std::string> scan(const std::string &cursor, int count = 0, const std::string &pattern = "");

    int append(const std::string &key, const std::string &value);

private:
    Connection con;
};

#endif  // REDIS_REDIS_H