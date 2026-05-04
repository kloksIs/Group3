#ifndef VIRUS_HPP
#define VIRUS_HPP

#include <string>

struct Virus {
    std::string name;
    double infection_rate; // Заразность чел/день от одного больного
    int incubation_period; // Инкубация в днях
    double mortality_rate; // Смертность от 0.0 (0%) до 1.0 (100%)
};

#endif