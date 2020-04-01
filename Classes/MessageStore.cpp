#include <cmath>
#include <tuple>
#include "MessageStore.h"
#include "DurationLogger.h"
#define copy 1
#define allocation_optimized 0

MessageStore::MessageStore(int n) : n(n), dim(n), next(0) {
   messages = new Message[n];
}

MessageStore::~MessageStore() {
    delete[] messages;
    n = -1;
    dim = -1;
    next = -1;
}

void MessageStore::reallocMessages() {
    if constexpr (copy) {
        //DurationLogger dl("Realloc tramite copia");
        if constexpr (!allocation_optimized)
            this->dim += n;
        else
            this->dim *= 2;

        auto *m = new Message[dim];
        for (int i = 0; i < next; i++)
            if (this->messages[i].getId() != -1)
                m[i] = this->messages[i];
        delete[] this->messages;
        this->messages = m;
    }else{
        //DurationLogger dl("Realloc tramite movimento");
        if constexpr (!allocation_optimized)
            this->dim += n;
        else
            this->dim *= 2;

        auto *m = new Message[dim];
        for (int i = 0; i < next; i++)
            if (this->messages[i].getId() != -1)
                m[i] = std::move(this->messages[i]);
        delete[] this->messages;
        this->messages = m;
    }
}

void MessageStore::add(Message &m) {
    if(m.getId() == -1) return;

    for(int i = 0; i<next; i++){
        if(this->messages[i].getId() == m.getId())
            return;
    }

    if(this->next >= this->dim)
        reallocMessages();

    this->messages[next++] = m;
}

std::optional<Message> MessageStore::get(long id) {
    if(id == -1) return std::nullopt;

    for(int i = 0; i<next; i++)
        if(this->messages[i].getId() == id)
            return this->messages[i];

    return std::nullopt;
}

bool MessageStore::remove(long id) {
    if(id == -1) return false;

    for(int i = 0; i<next; i++)
        if(this->messages[i].getId() == id) {
            this->messages[i] = Message();
            return true;
        }

    return false;
}

std::tuple<int, int> MessageStore::stats() {
    int valid=0;

    for(int i = 0; i<next; i++){
        if(this->messages[i].getId() != -1)
            valid++;
    }

    return std::make_tuple(valid, dim-valid);
}

void MessageStore::compact() {
    std::tuple<int,int> stats = MessageStore::stats();
    int valid = std::get<0>(stats);
    Message *m;
    if(valid == 0){
        m = new Message[this->n];
        this->dim = n;
        this->next = 0;
        delete[] this->messages;
        this->messages = m;
        return;
    }

    int new_size = (int)std::round((double)valid / n) * n;
    m = new Message[new_size];
    for(int i = 0, j = 0; i<next; i++)
        if(this->messages[i].getId() != -1) {
            m[j++] = copy == 1 ? messages[i] : std::move(messages[i]);
        }
    delete[] this->messages;

    this->messages = m;
    this->dim = new_size;
    this->next = valid;
}

Message *MessageStore::getMessages() const {
    return messages;
}

