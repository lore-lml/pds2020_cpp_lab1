#pragma once
#include <optional>
#include "Message.h"

class MessageStore {
    Message *messages;
    int dim; // dimensione corrente array
    int n; // incremento memoria
    int next;

    void reallocMessages();
public:
    MessageStore(int n);
    ~MessageStore();

    // inserisce un nuovo messaggio o sovrascrive quello precedent se ce n’è uno presente con lo stesso id
    void add(Message& m);

    // restituisce un messaggio se presente
    std::optional<Message> get(long id);

    // cancella un messaggio se presente
    bool remove(long id);

    // restituisce il numero di messaggi validi e di elementi vuoti ancora disponibili
    std::tuple<int, int> stats();

    // compatta l’array (elimina le celle vuole e riporta l’array alla dimensione multiplo di n minima
    // in grado di contenere tutte le celle)
    void compact();

    Message *getMessages() const;
};

