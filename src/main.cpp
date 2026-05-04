#include "Simulation.hpp"
#include "Virus.hpp"
#include <iostream>

int main(){
    std::cout << "Simulation Started" << std::endl;
    Virus covid = {"COVID-Lite", 1.5, 7, 0.05}; // Заразность 1.5 , болезнь 7 дней, смертность 5%
    Simulation sim(1000000, 10, covid); // 1 млн. население, изначально 10 заражённых

    for ( int i = 1; i <= 30; ++i){ // Симуляция 30 дней
        sim.nextDay();
        sim.printStats();
    }

    return 0;
}