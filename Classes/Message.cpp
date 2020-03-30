#include "Message.h"
#include <string>
#define debug 0

long Message::next =  0;
long Message::alloc =  0;

char *Message::mkMessage(int n) {
    std::string vowels = "aeiou";
    std::string consonants = "bcdfghlmnpqrstvz";
    char * m = new char [n+1];
    for ( int i= 0 ; i<n; i++){
        m[i]= i% 2 ? vowels[rand()%vowels.size()] :
              consonants[rand()%consonants.size()];
    }
    m[n] = 0 ;
    return m;
}

Message::Message() {
    if constexpr (debug) std::cout<<"Message()"<<std::endl;
    this->size = 0;
    this->id = -1;
    this->buffer = new char[1];
    this->buffer[0] = '\0';

    alloc++;
}

Message::Message(int size) : size(size) {
    if constexpr (debug) std::cout<<"Message(size)"<<std::endl;
    this->id = next++;
    this->size = size;
    this->buffer = this->mkMessage(size);

    alloc++;
}

Message::Message(const Message& source) {
    if constexpr (debug) std::cout<<"copy Message(source)"<<std::endl;
    this->size = source.size;
    this->id = source.id;
    this->buffer = new char[source.size + 1];
    memcpy(this->buffer, source.buffer, source.size+1);

    alloc++;
}

Message::Message(Message&& source) {
    if constexpr (debug) std::cout<<"movement Message(source)"<<std::endl;
    this->size = source.size;
    source.size = -1;
    this->id = source.id;
    source.id = -1;
    this->buffer = source.buffer;
    source.buffer = nullptr;

    alloc++;
}


Message::~Message() {
    if constexpr (debug) std::cout<<"~Message()"<<std::endl;
    delete[] this->buffer;
    this->size = -1;
    this->id = -1;

    alloc --;
}

Message& Message::operator=(const Message &that) {
    if constexpr (debug) std::cout<<"operator= copy"<<std::endl;
    if(this != &that){
        delete[] this->buffer;
        this->size = that.size;
        this->id = that.id;
        this->buffer = new char[that.size+1];
        memcpy(this->buffer, that.buffer, that.size+1);
    }
    return *this;
}

Message& Message::operator=(Message &&that) {
    if constexpr (debug) std::cout<<"operator= movement"<<std::endl;
    if(this != &that){
        delete[] this->buffer;
        this->size = that.size;
        this->id = that.id;
        this->buffer = that.buffer;
        that.buffer = nullptr;
        that.size = -1;
        that.id = -1;
    }
    return *this;
}

long Message::getId() const {
    return id;
}

const char *Message::getMessage() const {
    return buffer;
}

int Message::getSize() const {
    return size;
}

long Message::getAlloc() {
    return alloc;
}


std::ostream & operator <<(std::ostream & out, const Message& m){
// accedere alle parti contenute nell’oggetto Message e
// stamparle utilizzando out << … ;
// Questa funzione DEVE restituire l’oggetto out
    out << "[id:" << std::to_string(m.getId()) << "] [size:" + std::to_string(m.getSize()) << "] [data:" << m.getMessage() << "]";
    return out;
}
