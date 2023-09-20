#ifndef __CODES_HPP
#define __CODES_HPP

class Codes {
public:
    static const int SystemError = 50010;

    static const int SaveOk = 20011;
    static const int DeleteOk = 20021;
    static const int UpdateOk = 20031;
    static const int GetOk = 20041;
    
    static const int SaveError = 20010;
    static const int DeleteError = 20020;
    static const int UpdateError = 20030;
    static const int GetError = 20040;

    static const int LoginOk = 20051;
    static const int LoginParaNull = 20052;
    static const int LoginParaError = 20053;

    static const int RegisterOk = 20061;
    static const int RegisterParaNull = 20062;
    static const int RegisterParaExisted = 20063;

    static const int Message = 20071;
    static const int TokenError = 20072;

    static const int OK = 200;
    static const int Created = 201;
    static const int Accepted = 202;
    static const int MovedPermanently = 301;
    static const int Found = 302;
    static const int BadRequests = 400;
    static const int Unauthorized = 401;
    static const int Forbidden = 403;
    static const int InternalServerError = 500;
    static const int ServiceUnavailable = 503;
};

#endif //__CODES_HPP
