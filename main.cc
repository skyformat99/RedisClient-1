#include "src/redis.h"
#include <string>
#include <iostream>
#include <vector>

void test_keys(Redis &redis) {
    std::string pattern = "*";
    std::vector<std::string> result = redis.keys(pattern);
    for (auto str : result) {
        std::cout << str << std::endl;
    }
}

void test_del(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.del(key);
    std::cout << "Del Count:" << result << std::endl;
}

void test_del_keys(Redis &redis) {
    std::vector<std::string> keys;
    keys.push_back("del_test");
    keys.push_back("del_test_1");
    keys.push_back("del_test_2");
    int result = redis.del(keys);
    std::cout << "Del Count:" << result << std::endl;
}

void test_exists(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.exists(key);
    std::cout << "Exists:" << result << std::endl;
}

void test_expire(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int seconds = 0;
    std::cout << "Input Seconds:";
    std::cin >> seconds;

    int result = redis.expire(key, seconds);
    std::cout << "Expire:" << result << std::endl;
}

void test_expireat(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int timestamp = 0;
    std::cout << "Input Timestamp:";
    std::cin >> timestamp;

    int result = redis.expireat(key, timestamp);
    std::cout << "Expire:" << result << std::endl;
}

void test_move(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.move(key, 0);
    std::cout << "Move:" << result << std::endl;
}

void test_persist(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.expire(key, 40);
    std::cout << "Expire:" << result << std::endl;
    result = redis.persist(key);
    std::cout << "Persist:" << result << std::endl;
}

void test_pexpire(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.pexpire(key, 40000);
    std::cout << "Pexpire:" << result << std::endl;
}

void test_pexpireat(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.pexpireat(key, 1555555555005);
    std::cout << "Pexpire:" << result << std::endl;
}

void test_pttl(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.pttl(key);
    std::cout << "Pttl:" << result << std::endl;
}

void test_randomkey(Redis &redis) {
    std::string result = redis.randomkey();
    std::cout << "RandomKey:" << result << std::endl;
}

void test_rename(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    std::string newkey;
    std::cout << "Input NewKey:";
    std::cin >> newkey;
    std::string result = redis.rename(key, newkey);
    std::cout << "rename:" << result << std::endl;
}

void test_renamenx(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    std::string newkey;
    std::cout << "Input NewKey:";
    std::cin >> newkey;
    int result = redis.renamenx(key, newkey);
    std::cout << "rename:" << result << std::endl;
}

void test_sort(Redis &redis) {
    std::vector<std::string> get;
    get.emplace_back("test_key_*");
    std::vector<std::string> result = redis.sort("list_test_key", 0, 5, false, true, "", get);
    for (auto &str:result) {
        std::cout << str << std::endl;
    }
}

void test_ttl(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.ttl(key);
    std::cout << "TTL:" << result << std::endl;
}

void test_type(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    std::string result = redis.type(key);
    std::cout << "TYPE:" << result << std::endl;
}

void test_scan(Redis &redis) {
    std::vector<std::string> result = redis.scan("0", 10, "*");
    for (auto &str:result) {
        std::cout << str << std::endl;
    }
}

void test_append(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.append(key, "te   st");
    std::cout << "Append Count:" << result << std::endl;
}

void test_bitcount(Redis &redis) {
    std::string key;
    std::cout << "Input Key:";
    std::cin >> key;
    int result = redis.bitcount(key,0,1);
    std::cout << "bitount:" << result << std::endl;
}

int main() {
    std::string addr = "127.0.0.1";
    int port = 6379;
    Redis redis(addr, port);
    test_keys(redis);
    test_bitcount(redis);
    return 0;
}