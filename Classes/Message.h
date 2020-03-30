#pragma once
#include <iostream>

class Message {
    static long next, alloc;
    long id;
    char *buffer;
    int size;

    char* mkMessage(int n);

public:
    Message();
    Message(int size);
    Message(const Message& source);
    Message(Message&& source);
    Message& operator=(const Message& that);
    Message& operator=(Message&& that);
    ~Message();
    long getId() const;
    const char* getMessage() const;
    int getSize() const;

    static long getAlloc();
};

std::ostream & operator <<(std::ostream & out, const Message & m);