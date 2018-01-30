#include "redis.h"

Redis::Redis(const std::string& addr, int port) : con(addr, port) {}

Redis::~Redis() {}

std::vector<std::string> Redis::keys(const std::string& pattern) {
    std::vector<std::string> commands = {"KEYS", pattern};

    Response res = con.send_commands(commands);
    std::vector<std::string> result;
    if (res.is_null) {
        return result;
    }
    for (auto item : res.multi_res) {
        result.push_back(item.string_res);
    }
    return result;
}

int Redis::del(const std::vector<std::string>& keys) {
    std::vector<std::string> commands;
    commands.push_back("DEL");
    for (auto key : keys) {
        commands.push_back(key);
    }
    Response res = con.send_commands(commands);
    return res.integer_res;
}

int Redis::del(const std::string& key) {
    std::vector<std::string> commands = {"DEL", key};

    Response res = con.send_commands(commands);

    return res.integer_res;
}

int Redis::exists(const std::string& key) {
    std::vector<std::string> commands = {"EXISTS", key};

    Response res = con.send_commands(commands);

    return res.integer_res;
}

int Redis::expire(const std::string& key, unsigned seconds) {
    std::vector<std::string> commands = {"EXPIRE", key,
                                         std::to_string(seconds)};

    Response res = con.send_commands(commands);

    return res.integer_res;
}

int Redis::expireat(const std::string& key, unsigned timestamp) {
    std::vector<std::string> commands = {"EXPIREAT", key,
                                         std::to_string(timestamp)};
    Response res = con.send_commands(commands);
    return res.integer_res;
}