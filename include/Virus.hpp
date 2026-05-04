#ifndef VIRUS_HPP
#define VIRUS_HPP

#include <string>

struct Virus {
    std::string name;
    double infection_rate;
    int incubation_period;
    double mortality_rate;
};

#endif