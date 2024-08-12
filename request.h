//
// Created by User on 12/08/2024.
//

#ifndef SHEDULER_REQUEST_H
#define SHEDULER_REQUEST_H
#include "abstract_request.h"

#include <string>

using std::string;

typedef void(*logFunction)(string text);

class Request: public AbstractReuquest {
    int value;
    logFunction outFunc;

public:

    void setOutput(logFunction func) {
        this->outFunc = func;
    }

    void setValue(int val) override;
    void process() override;
    void finish() override;
};


#endif //SHEDULER_REQUEST_H
