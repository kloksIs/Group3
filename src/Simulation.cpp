#include "Simulation.hpp"
#include "Virus.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <string>

VirusState::VirusState(Virus v, long long initial_sick) : virus(v) {
        sick_days.resize(v.getIncubationPeriod(), 0);
        if (!sick_days.empty()) sick_days[0] = initial_sick;
    }

Simulation::Simulation(long long total_pop): healthy(total_pop){}

void Simulation::addVirus(const Virus& v, long long initial_sick){
    active_viruses.push_back(VirusState(v, initial_sick));
}

void Simulation::nextDay(){
    // Пробегаемся по всем вирусам поочереди
    for (auto& state : active_viruses) {
        long long total_sick = std::accumulate(state.sick_days.begin(), state.sick_days.end(), 0LL);
        long long new_infected = static_cast<long long>(total_sick * state.virus.getInfectionRate());
        if (new_infected > healthy) new_infected = healthy; // Ограничиваем возможное число больных
        healthy -= new_infected;

        // Сдвигаем больных, добавляем новых
        long long finishing_illness = state.sick_days.back();
        for (int i = state.sick_days.size() - 1; i > 0; --i){
            state.sick_days[i] = state.sick_days[i-1];
        }
        state.sick_days[0] = new_infected;
            
        // Исход болезни
        long long deaths = finishing_illness * state.virus.getMortalityRate();
        state.dead += deaths;
        state.recovered += (finishing_illness - deaths);
    }
    current_day += 1; // Обновляем количетсво дней
}

void Simulation::printStats() {
    std::cout << "\n--- Day " << current_day << " ---" << std::endl;
    std::cout << "Healthy people: " << healthy << std::endl;

    for (const auto& state : active_viruses) {
        long long total_sick = std::accumulate(state.sick_days.begin(), state.sick_days.end(), 0LL);
        
        std::cout << "  > Virus: " << state.virus.getName()
                  << " | Sick: " << total_sick
                  << " | Dead: " << state.dead
                  << " | Recovered: " << state.recovered << std::endl;
    }
    std::cout << "--------------------" << std::endl;
}

double Simulation::getTotalSick(){
    double global_sick = 0;
    for (const auto& state : active_viruses){
        global_sick += std::accumulate(state.sick_days.begin(), state.sick_days.end(), 0LL);
    }
    return global_sick;
}