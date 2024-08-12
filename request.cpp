//
// Created by User on 12/08/2024.
//

#include "request.h"

void Request::setValue(int val){
    this->value = val;
}

void Request::process() {
    outFunc("Processing request" + std::to_string(value) + "...");
    //buisnes logic
}

void Request::finish() {
    outFunc("Finishing request" + std::to_string(value));
    //finishing logic
}