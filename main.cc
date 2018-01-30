#include "src/redis.h"
#include <string>
#include <iostream>
#include <vector>

void test_keys(Redis &redis){
    std::string pattern="*";
    std::vector<std::string> result = redis.keys(pattern);
    for (auto str : result) {
        std::cout << str << std::endl;
    }
}

void test_del(Redis &redis){
    std::string key="";
    std::cout<<"Input Key:";
    std::cin>>key;
    int result=redis.del(key);
    std::cout<<"Del Count:"<<result<<std::endl;
}

void test_del_keys(Redis &redis){
    std::vector<std::string> keys;
    keys.push_back("del_test");
    keys.push_back("del_test_1");
    keys.push_back("del_test_2");
    int result=redis.del(keys);
    std::cout<<"Del Count:"<<result<<std::endl;
}

void test_exists(Redis &redis){
    std::string key="";
    std::cout<<"Input Key:";
    std::cin>>key;
    int result=redis.exists(key);
    std::cout<<"Exists:"<<result<<std::endl;
}

void test_expire(Redis &redis){
    std::string key="";
    std::cout<<"Input Key:";
    std::cin>>key;
    int seconds=0;
    std::cout<<"Input Seconds:";
    std::cin>>seconds;

    int result=redis.expire(key,seconds);
    std::cout<<"Expire:"<<result<<std::endl;
}

void test_expireat(Redis &redis){
    std::string key="";
    std::cout<<"Input Key:";
    std::cin>>key;
    int timestamp=0;
    std::cout<<"Input Timestamp:";
    std::cin>>timestamp;

    int result=redis.expireat(key,timestamp);
    std::cout<<"Expire:"<<result<<std::endl;
}

int main() {
    std::string addr = "127.0.0.1";
    int port = 6379;
    Redis redis(addr,port);
    test_keys(redis);
    test_expireat(redis);
    return 0;
}