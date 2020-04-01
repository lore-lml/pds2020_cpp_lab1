#include "DurationLogger.h"
#include <utility>
#include <iostream>
#include <iomanip>

DurationLogger::DurationLogger(std::string name): name(std::move(name)), start(clock()) {
    std::cout <<">>>>>>>>>>>>>> starting ["<<this->name<<"]" << std::endl;
}

DurationLogger::~DurationLogger() {
    std::cout<<std::setprecision(3)<< "<<<<<<<<<<<<<< " <<"ending ["<<this->name<<"]: ["<<(double)(clock() - start) / 1000<<"] sec"<<std::endl;
}
