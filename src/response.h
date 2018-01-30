#ifndef REDIS_REPONSE_H
#define REDIS_REPONSE_H

#include <string>
#include <vector>

enum class RESPONSE_TYPE {
    STATUS_REPLY,
    ERROR_REPLY,
    INTEGER_REPLY,
    BUIK_REPLY,
    MULTI_BULK_REPLY
};

class Response {
   public:
    Response() { is_null = false; }
    Response(RESPONSE_TYPE type) {
        res_type = type;
        is_null = false;
    }
    Response(const Response& res) {
        res_type = res.res_type;
        is_null = res.is_null;
        string_res = res.string_res;
        integer_res = res.integer_res;
        multi_res = res.multi_res;
    }

    ~Response() {}

    RESPONSE_TYPE res_type;
    std::string string_res;
    int integer_res;
    std::vector<Response> multi_res;
    bool is_null;
};

#endif
