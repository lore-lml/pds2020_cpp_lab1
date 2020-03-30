#include "DurationLogger.h"
#include <utility>
#include <iostream>

DurationLogger::DurationLogger(std::string name): name(std::move(name)), start(clock()) {
    std::cout <<">>>>>>>>>>>>>> starting ["<<this->name<<"]" << std::endl;
}

DurationLogger::~DurationLogger() {
    std::cout <<"ending ["<<this->name<<"]: ["<<clock() - start<<"] ticks"<< " <<<<<<<<<<<<<<<"<<std::endl;
}
