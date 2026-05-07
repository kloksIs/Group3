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

    Simulation sim(1000000);
    for (const auto& item : config["viruses"]){
        sim.addVirus(Virus(item),10);
    }
    
    int daysToRun;
    while (sim.getTotalSick() > 0) {
        std::cout << "Enter days to simulate (or 0 to stop): ";
        std::cin >> daysToRun;
        if (daysToRun <= 0) break;

        for (int i = 0; i < daysToRun; ++i) {
            sim.nextDay();
            sim.printStats();
        }
    }

    

    return 0;
}