#include <iostream>
#include "Classes/Message.h"
#include "Classes/DurationLogger.h"
#include "Classes/MessageStore.h"
#include <cmath>
#include <tuple>

int main() {
    // PARTE 1
    DurationLogger dm("Main");
    {
        Message buff1[10];
        auto *buff2 = new Message[10];

        {
            DurationLogger d("Buff1 copy");
            for (auto &i : buff1)
                i = Message((int) pow(2, 20));
        }
        {
            DurationLogger d("Buff2 copy");
            for (int i = 0; i < 10; i++)
                buff2[i] = buff1[i];
        }
        delete[] buff2;



        //PARTE 2
        DurationLogger dl("Parte 2");

        MessageStore ms(10);
        auto *m = new Message[100];
        for (int i = 0; i < 100; i++) {
            m[i] = Message((int) pow(2, 20));
            ms.add(m[i]);
        }


        auto stats = ms.stats();
        std::cout << "Before removing" << std::endl;
        std::cout << "valid: " << std::to_string(std::get<0>(stats)) << " empty: " << std::to_string(std::get<1>(stats))
                  << std::endl << std::endl;

        for (int i = 0; i < 100; i += 2)
            ms.remove(m[i].getId());

        stats = ms.stats();
        std::cout << "After removing" << std::endl;
        std::cout << "valid: " << std::to_string(std::get<0>(stats)) << " empty: " << std::to_string(std::get<1>(stats))
                  << std::endl << std::endl;

        ms.compact();

        stats = ms.stats();
        std::cout << "After compact" << std::endl;
        std::cout << "valid: " << std::to_string(std::get<0>(stats)) << " empty: " << std::to_string(std::get<1>(stats))
                  << std::endl << std::endl;
        delete[] m;
    }
    std::cout<<"Number of memory leakage= "<<Message::getAlloc()<<std::endl;

    return 0;
}
