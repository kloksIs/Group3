#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Virus.hpp"
#include "Simulation.hpp"

using json = nlohmann::json;

int main(){
    std::string configPath = std::string(PROJECT_SOURCE_DIR) + "/data/config.json";
    std::ifstream file(configPath);
    if (!file.is_open()){
        std::cerr << "Error: could not open config.json" << configPath << std::endl;
        return 1;
    }

    // Парсинг JSON
    json config;
    file >> config;

    Simulation Sim(1000000);
    for (const auto& item : config["viruses"]){
        Sim.addVirus(Virus(item),10);
    }
    for (int i = 0; i < 15; i++){
        Sim.nextDay();
        Sim.printStats();
    }
    

    return 0;
}