#include "redis.h"

Redis::Redis(const std::string &addr, unsigned port) : con(addr, port) {}

Redis::Redis(const std::string &addr, unsigned port, unsigned db)
        : con(addr, port, db) {}

Redis::~Redis() {};

std::vector<std::string> Redis::keys(const std::string &pattern) {
    std::vector<std::string> command = {"KEYS", pattern};

    Response res = con.execute_command(command);
    std::vector<std::string> result;
    if (res.is_null) {
        return result;
    }
    for (auto item : res.multi_res) {
        result.push_back(item.string_res);
    }
    return result;
}

int Redis::del(const std::vector<std::string> &keys) {
    std::vector<std::string> command;
    command.emplace_back("DEL");
    for (auto &key : keys) {
        command.push_back(key);
    }
    Response res = con.execute_command(command);
    return res.integer_res;
}

int Redis::del(const std::string &key) {
    std::vector<std::string> command = {"DEL", key};

    Response res = con.execute_command(command);

    return res.integer_res;
}

int Redis::exists(const std::string &key) {
    std::vector<std::string> command = {"EXISTS", key};

    Response res = con.execute_command(command);

    return res.integer_res;
}

int Redis::expire(const std::string &key, unsigned seconds) {
    std::vector<std::string> command = {"EXPIRE", key,
                                        std::to_string(seconds)};

    Response res = con.execute_command(command);

    return res.integer_res;
}

int Redis::expireat(const std::string &key, unsigned timestamp) {
    std::vector<std::string> command = {"EXPIREAT", key,
                                        std::to_string(timestamp)};
    Response res = con.execute_command(command);
    return res.integer_res;
}

int Redis::move(const std::string &key, unsigned db) {
    std::vector<std::string> command = {"MOVE", key, std::to_string(db)};
    Response res = con.execute_command(command);
    return res.integer_res;
}

int Redis::persist(const std::string &key) {
    std::vector<std::string> command = {"PERSIST", key};
    Response res = con.execute_command(command);
    return res.integer_res;
}

int Redis::pexpire(const std::string &key, unsigned milliseconds) {
    std::vector<std::string> command = {"PEXPIRE", key,
                                        std::to_string(milliseconds)};
    Response res = con.execute_command(command);

    return res.integer_res;
}

int Redis::pexpireat(const std::string &key,
                     unsigned long long milliseconds_timestamp) {
    std::vector<std::string> command = {
            "PEXPIREAT", key, std::to_string(milliseconds_timestamp)};
    Response res = con.execute_command(command);
    return res.integer_res;
}

int Redis::pttl(const std::string &key) {
    std::vector<std::string> command = {"PTTL", key};
    Response res = con.execute_command(command);
    return res.integer_res;
}

std::string Redis::randomkey() {
    std::vector<std::string> command = {"RANDOMKEY"};
    Response res = con.execute_command(command);
    return res.string_res;
}

std::string Redis::rename(const std::string &key, const std::string &newkey) {
    std::vector<std::string> command = {"RENAME", key, newkey};
    Response res = con.execute_command(command);
    return res.string_res;
}

int Redis::renamenx(const std::string &key, const std::string &newkey) {
    std::vector<std::string> command = {"RENAMENX", key, newkey};
    Response res = con.execute_command(command);
    return res.integer_res;
}

std::vector<std::string> Redis::sort(const std::string &key,
                                     int offset,
                                     int count,
                                     bool desc,
                                     bool alpha,
                                     const std::string &by,
                                     const std::vector<std::string> &get) {
    std::vector<std::string> command = {"SORT", key};
    if (!by.empty()) {
        command.emplace_back("BY");
        command.emplace_back(by);
    }
    if (offset != 0 || count != 0) {
        command.emplace_back("LIMIT");
        command.emplace_back(std::to_string(offset));
        command.emplace_back(std::to_string(count));
    }
    if (!get.empty()) {
        command.emplace_back("GET");
        for (auto &pattern:get) {
            command.emplace_back(pattern);
        }
    }

    if (desc) {
        command.emplace_back("DESC");
    }

    if (alpha) {
        command.emplace_back("ALPHA");
    }
    Response res = con.execute_command(command);

    std::vector<std::string> result;
    for (auto &item:res.multi_res) {
        result.emplace_back(item.string_res);
    }
    return result;
}

int Redis::ttl(const std::string &key) {
    std::vector<std::string> command = {"TTL", key};
    Response res = con.execute_command(command);
    return res.integer_res;
}

std::string Redis::type(const std::string &key) {
    std::vector<std::string> command = {"TYPE", key};
    Response res = con.execute_command(command);
    return res.string_res;
}

std::vector<std::string> Redis::scan(const std::string &cursor, int count, const std::string &pattern) {
    std::vector<std::string> command = {"SCAN", cursor};

    if (!pattern.empty()) {
        command.emplace_back("MATCH");
        command.emplace_back(pattern);
    }

    if (count != 0) {
        command.emplace_back("COUNT");
        command.emplace_back(std::to_string(count));
    }

    Response res = con.execute_command(command);
    std::vector<std::string> result;
    for (auto &item:res.multi_res) {
        if (item.res_type == RESPONSE_TYPE::MULTI_BULK_REPLY) {
            for (auto &reply:item.multi_res) {
                result.emplace_back(reply.string_res);
            }
        } else {
            result.emplace_back(item.string_res);
        }

    }
    return result;
}

int Redis::append(const std::string &key, const std::string &value) {
    std::vector<std::string> command = {"APPEND", key, value};
    Response res = con.execute_command(command);
    return res.integer_res;
}

int Redis::bitcount(const std::string &key, int start, int end) {
    std::vector<std::string> command = {"BITCOUNT", key};
    if (start != 0 || end != 0) {
        command.emplace_back(std::to_string(start));
        command.emplace_back(std::to_string(end));
    }
    Response res = con.execute_command(command);
    return res.integer_res;
}