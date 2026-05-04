#include "Simulation.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <string>

Simulation::Simulation(long long total_pop, long long initial_sick, Virus v)
    : healthy(total_pop - initial_sick), virus(v){
        sick_days.resize(v.incubation_period, 0);
        sick_days[0] = initial_sick;
}

void Simulation::nextDay(){ 
    long long total_sick = std::accumulate(sick_days.begin(), sick_days.end(), 0LL);
    long long new_infected = total_sick * virus.infection_rate;
    if (new_infected > healthy) new_infected = healthy; // Ограничиваем возможное число больных
    healthy -= new_infected;

    // Сдвигаем больных, добавляем новых
    long long finishing_illness = sick_days.back();
    for (int i = sick_days.size() - 1; i > 0; --i){
        sick_days[i] = sick_days[i-1];
    }
    sick_days[0] = new_infected;
        
    // Исход болезни
    long long deaths = finishing_illness * virus.mortality_rate;
    dead += deaths;
    recovered += (finishing_illness - deaths);

    current_day += 1; // Обновляем количетсво дней
}

void Simulation::printStats(){
    long long total_sick = std::accumulate(sick_days.begin(), sick_days.end(), 0LL);
    std::cout << "Day " << current_day << " | Healthy: " << healthy
                << " | Sick: " << total_sick
                << " | Dead: " << dead
                << " | Recovered: " << recovered << std::endl;
}