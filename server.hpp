#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#include "scheduler.hpp"


using namespace std;

class Server {
    private:
        bool console, logs, filePerSensor;
        const char* filename;
        Scheduler sched;
        vector<float> valsF;
        vector<int> valsI;
        vector<bool> valsB;

        void consoleWrite();
        void fileWrite();

        void log();
        void update();
        
    public:
        Server();
        Server(const bool&, const bool&, const bool&, const char*, const Scheduler&);
        Server(const Server&);
        
        ~Server();
        Server& operator=(const Server&);
        
        friend ostream& operator<<(ostream&, Server&);

        void run();
};

constexpr char base_filename[] = "logs.txt";



#endif // __SERVER_HPP__