#ifndef VIRUS_HPP
#define VIRUS_HPP

#include <string>
#include <nlohmann/json.hpp>

class Virus {
private:
    std::string name;
    double infection_rate; // Заразность чел/день от одного больного
    int incubation_period; // Инкубация в днях
    double mortality_rate; // Смертность от 0.0 (0%) до 1.0 (100%)

public:
    // Конструктор, принимающий блок данных из JSON
    Virus(const nlohmann::json& data);

    // Геттеры (чтобы Simulation могла брать данные)
    std::string getName() const { return name; }
    double getInfectionRate() const { return infection_rate; }
    int getIncubationPeriod() const { return incubation_period; }
    double getMortalityRate() const { return mortality_rate; }
};

#endif