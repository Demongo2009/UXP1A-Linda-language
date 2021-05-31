#include "../include/client/linda.h"
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sstream>

void lindaReadOrInput(std::stringstream &ss, std::vector<std::string> &vecWord, bool isRead);
void lindaOutput(std::stringstream &ss, std::vector<std::string> &vecWord);


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
//    Tuple t1 = Tuple({1, 2, 3});
//    linda_output(t1);
//
//    TuplePattern p1 = TuplePattern("integer:*, string:*, integer:*");
//    time_t time1 = 1000;
//    std::optional<Tuple> t2 = linda_input(p1, time1);
//    if(t2){
//        t2.value().print();
//    }else{
//        std::cout<<"timeout"<<std::endl;
//    }

    std::stringstream ss;
    std::string line;
    std::getline(std::cin, line);
    std::vector<std::string> vecWord;

    while(line != "q"){
        ss << line;
        for(std::string s; ss >>s;){
            vecWord.push_back(s);
        }


        if(vecWord[0] == "read") {
            lindaReadOrInput(ss, vecWord, true);

        } else if(vecWord[0] == "input"){
            lindaReadOrInput(ss, vecWord, false);

        } else if(vecWord[0] == "output"){
            lindaOutput(ss, vecWord);

        } else{
            std::cout << "Unrecognised command!\n";
        }
        ss.clear();
        vecWord.clear();
        std::getline(std::cin, line);
    }

}

void lindaOutput(std::stringstream &ss, std::vector<std::string> &vecWord) {

    std::string tuple;
    if(vecWord.size() > 1){
        tuple = std::string (vecWord[1].begin(), vecWord[1].end());
        auto it = tuple.begin();

        while(it != tuple.end()){
            if(*it == ';'){
                *it = ',';
                it++;
            }
            it++;
        }
    }else{
        std::cout << "No tuple pattern!\n";
        return;
    }

    for(int i=0; i<tuple.size() ;i++){
        if(tuple[i] == ','){
            i++;
            tuple.insert(i, " ");
        }
    }


    Tuple p = Tuple(false, tuple);

    linda_output(p);

    std::cout << "User passed: ";
    p.print();
    std::cout << "\n";

}

void lindaReadOrInput(std::stringstream &ss, std::vector<std::string> &vecWord, bool isRead) {

    std::string tupleTemplate= "";
    if(vecWord.size() > 1){
        tupleTemplate = std::string (vecWord[1].begin(), vecWord[1].end());
        auto it = tupleTemplate.begin();
        while(*it != '\000'){
            if(*it == ';'){
                *it = ',';
                it++;
            }
            it++;
        }
    }else{
        std::cout << "No tuple pattern!\n";
        return;
    }
    long int timeout;

    for(int i=0; i<tupleTemplate.size() ;i++){
        if(tupleTemplate[i] == ','){
            i++;
            tupleTemplate.insert(i, " ");
        }
    }


    if(vecWord.size() > 2){
        timeout = atol(vecWord[2].c_str());
    }else{
        std::cout << "Needs timeout!\n";
        return;
    }

    TuplePattern p = TuplePattern(tupleTemplate);
    time_t time = timeout;
    std::optional<Tuple> readTuple;
    if(isRead){
        readTuple = linda_read(p,time);
    }else{
        readTuple = linda_input(p,time);
    }
    if(readTuple.has_value()){
        readTuple.value().print();
    } else{
        std::cout << time << "ms have passed!\n";
    }
}