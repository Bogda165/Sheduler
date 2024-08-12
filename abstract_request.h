//
// Created by User on 12/08/2024.
//

#ifndef SHEDULER_ABSTRACT_REQUEST_H
#define SHEDULER_ABSTRACT_REQUEST_H

//using abstract class to allow the despather to handle different types of request!!!
class AbstractReuquest {
public:
    virtual void setValue(int val) = 0; // adapted
    virtual void process() = 0;
    virtual void finish() = 0;
};


#endif //SHEDULER_ABSTRACT_REQUEST_H
