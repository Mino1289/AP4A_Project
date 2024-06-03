#include <ctime>
#include <sys/stat.h>


#include "server.hpp"
#include "sensor.hpp"
#include "scheduler.hpp"

int main() {
    srand(time(NULL));

    cout << "Combien voulez-vous de capteurs à valeurs flottantes ?" << endl;
    unsigned nb;
    cin >> nb;
    vector<Sensor<float>> sensorsF = vector<Sensor<float>>();
    for (unsigned i = 0; i < nb; i++) {
        string name;
        cout << "Nom du capteur " << i << " : ";
        cin >> name;
        sensorsF.push_back(Sensor<float>(0, name));
    }

    cout << "Combien voulez-vous de capteurs à valeurs entières ?" << endl;
    cin >> nb;
    vector<Sensor<int>> sensorsI = vector<Sensor<int>>();
    for (unsigned i = 0; i < nb; i++) {
        string name;
        cout << "Nom du capteur " << i << " : ";
        cin >> name;
        sensorsI.push_back(Sensor<int>(0, name));
    }

    cout << "Combien voulez-vous de capteurs à valeurs booléennes ?" << endl;
    cin >> nb;
    vector<Sensor<bool>> sensorsB = vector<Sensor<bool>>();
    for (unsigned i = 0; i < nb; i++) {
        string name;
        cout << "Nom du capteur " << i << " : ";
        cin >> name;
        sensorsB.push_back(Sensor<bool>(0, name));
    }

    unsigned interval = 1;
    cout << "Interval de temps entre chaque mesure (en secondes) : ";
    cin >> interval;

    Scheduler sched = Scheduler(interval, sensorsF, sensorsI, sensorsB);

    bool console = false;
    cout << "Voulez-vous afficher les valeurs sur la console ? (0/1)" << endl;
    cin >> console;
    
    bool logs = false;
    cout << "Voulez-vous enregistrer les valeurs dans un fichier ? (0/1)" << endl;
    cin >> logs;

    bool filePerSensor = false;
    if (logs) {
        cout << "Voulez-vous un fichier par capteur ? (0/1)" << endl;
        cin >> filePerSensor;
    }

    std::string filename;

    if (filePerSensor) {
        cout << "Les fichiers auront le nom du capteur suivi de \"_log.txt\"." << endl;
        cout << "Donnez le nom du dossier dans lequel les fichiers seront créés : (sans le /) " << endl;
        cin >> filename;
#ifdef _WIN32
        mkdir(filename.c_str());
#else
        mkdir(filename.c_str(), 0777);
#endif
    }

    bool header = false;
    if (logs && !filePerSensor) {
        cout << "Nom du fichier : ";
        cin >> filename;
        cout << "Voulez-vous écraser le fichier et ajouter les noms des capteurs en en-tête ? (0/1)" << endl;
        cin >> header;
    }


    Server serv = Server(console, logs, filePerSensor, filename.c_str(), sched);
    if (console) {
        cout << "Time, ";
        for(auto name : sched.getNames()) {
            cout << name << ", ";
        }
    }
    if (header) {
        ofstream file;
        file.open(filename.c_str());
        file << "Time, ";
        for(auto name : sched.getNames()) {
            file << name << ", ";
        }
        file << endl;
        file.close();
    }
    cout << endl;
    serv.run();

    return 0;
}