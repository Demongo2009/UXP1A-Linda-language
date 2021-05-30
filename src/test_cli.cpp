#include "../include/client/linda.h"
#include <iostream>
#include <ctime>
#include <unistd.h>
int main(){
    /**
     * TODO:
     *  1. trzeba jakieś mozliwie proste cli, zeby mozna bylo odpalic dwie/trzy konsole i zaprezentować realtime
     *  2. i ten najprostszy mozliwy interpreter, ja sobie to tak wyobrazalem:
     *      a. proces bierze na wejściu nazwe pliku w ktorym ma komendy
     *      b. komendy sa napisane tak:
     *          |<nazwa_komendy> <wzorzec_krotki/krotka> <timeout(dla input/read)>|
     *              np.: read "string:==abc, integer:>=12, float:*" 1000
     *      c. proces czyta po jednej linijcie i wykonuje sekwencyjnie te komendy jednocześnie wypisując co się dzieje żeby można było weryfikowac
     *  3. przedmiot maksowany essa profit
     */
     /**
      * Teraz można tworzyć krotki za pomocą stringa
      * ALE UWAGA!!!
      * jako pierwszy argument musi być dowolny boolean, bo jak go nie ma to mamy `unambigious declaration`
      * czyli żeby zrobić krotkę (1, "nanana", 12.12) za pomocą stringa to musimy to zrobić tak:
      * Tuple tuple = Tuple(false(!!!), "integer:1, string:nanana, float:12.12");
      *
      * jakie to ma konsekwencje? kompletnie żadne
      * jedyne to musimy pamiętać podczas tworzenia CLI żeby wywoływać konstruktor z pierwszym booleanem
      * */
    Tuple t1 = Tuple({1, 2, 3});
    linda_output(t1);

    TuplePattern p1 = TuplePattern("integer:*, string:*, integer:*");
    time_t time1 = 1000;
    std::optional<Tuple> t2 = linda_input(p1, time1);
    if(t2){
        t2.value().print();
    }else{
        std::cout<<"timeout"<<std::endl;
    }

}