#include "Virus.hpp"

Virus::Virus(const nlohmann::json& data) {
    name = data.at("name").get<std::string>();
    infection_rate = data.at("infection_rate").get<double>();
    incubation_period = data.at("incubation_period").get<int>();
    mortality_rate = data.at("mortality_rate").get<double>();
}
