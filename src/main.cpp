#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include "Virus.hpp"

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

    // Вывод данных для проверки
    std::cout << "--- Viruses found in config ---" << std::endl;
    for (const auto& item : config["viruses"]){
        std::string name = item["name"];
        double rate = item["infection_rate"];

        std::cout << "Name: " << name << " | Rate: " << rate << std:: endl;

    }
    return 0;
}