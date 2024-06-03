#include "server.hpp"


Server::Server() {
    this->console = this->logs = this->filePerSensor = false;
    this->filename = nullptr;
    this->sched = Scheduler();
}

Server::Server(const bool& console, const bool& logs, const bool& filePerSensor, const char* filename, const Scheduler& sched) {
    this->console = console;
    this->logs = logs;
    this->filePerSensor = filePerSensor;
    this->filename = filename;
    this->sched = sched;
}

Server::~Server() {

}

Server::Server(const Server& serv) {
    this->console = serv.console;
    this->logs = serv.logs;
    this->filePerSensor = serv.filePerSensor;
    this->filename = serv.filename;
    this->sched = serv.sched;
}

Server& Server::operator=(const Server& serv) {
    this->console = serv.console;
    this->logs = serv.logs;
    this->filePerSensor = serv.filePerSensor;
    this->filename = serv.filename;
    this->sched = serv.sched;

    return *this;
}

/**
 * @brief Surcharge de l'opérateur << pour l'affichage des valeurs du serveur
 * 
 * @param os 
 * @param serv 
 * @return ostream& 
 */
ostream& operator<<(ostream& os, Server& serv) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    // format : YYYY-MM-DD HH:MM:SS
    os << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << ", ";
    os << setw(4) << setprecision(3) << fixed;
    for (const auto& val : serv.valsF) {
        os << val << ", ";
    }

    os << setw(2) << setprecision(0);
    for (const auto& val : serv.valsI) {
        os << val << ", ";
    }

    for (const auto& val : serv.valsB) {
        os << val << ", ";
    }

    return os;
}

/**
 * @brief Ecriture des valeurs du serveur dans la console
 * 
 */
void Server::consoleWrite() {
    cout << *this << endl;
}


/**
 * @brief Ecriture des valeurs du serveur dans un fichier ou dans plusieurs fichiers
 * 
 */
void Server::fileWrite() {
    if (!filePerSensor) {
        ofstream file;

        file.open(this->filename, ios::app);

        file << *this << endl;
        file.close();
    } else {
        vector<std::string> names = this->sched.getNames();
        int idx = 0;
        time_t now = time(0);
        tm* ltm = localtime(&now);
        for (std::size_t i = 0; i < names.size(); ++i) {
            string path = std::string(this->filename) + "/" + names[i] + "_log.txt"; // nom du fichier
            ofstream file;
            file.open(path.c_str(), ios::app);
            // récupération de la date et de l'heure
            // format : YYYY-MM-DD HH:MM:SS
            file << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << " " << ltm->tm_hour << ":" << ltm->tm_min << ":" << ltm->tm_sec << ", ";
            
            // récupération des valeurs des capteurs de chaque type
            if (i < this->valsF.size()) {
                // access valsF values
                idx = i;
                file << this->valsF.at(idx) << endl;
            } else if (i < this->valsF.size() + this->valsI.size()) {
                // access valsI values
                idx = i - this->valsF.size();
                file << this->valsI.at(idx) << endl;
            } else {
                // access valsB values
                idx = i - this->valsF.size() - this->valsI.size();
                file << this->valsB.at(idx) << endl;
            }
            file.close();
        }
    }
}

/**
 * @brief Interface pour gérer l'écriture des valeurs du serveur
 * 
 */
void Server::log() {
    if (this->console || this->logs) {
        this->update();
    }
    if (this->console) {
        this->consoleWrite();
    }
    if (this->logs) {
        this->fileWrite();
    }
}

/**
 * @brief Récupère les valeurs des capteurs pour les mettre dans les attributs du serveur
 * 
 */
void Server::update() {
    this->valsF = this->sched.getFloatVals();
    this->valsI = this->sched.getIntVals();
    this->valsB = this->sched.getBoolVals();
}

/**
 * @brief Fonction principale du serveur
 * 
 */
void Server::run() {
    while (true) {
        this->log();
        sleep(this->sched.getInterval());
    }
}


