#include "Simulation.hpp"
#include "Virus.hpp"

#include <iostream>
#include <vector>
#include <numeric>
#include <string>

VirusState::VirusState(Virus v, long long initial_sick) : virus(v) {
        sick_days.resize(v.getIncubationPeriod(), 0);
        sick_days[0] = initial_sick;
    }

Simulation::Simulation(long long total_pop): healthy(total_pop){}

void Simulation::addVirus(const Virus& v, long long initial_sick){
    if (v.getIncubationPeriod() <= 0) {
        throw std::invalid_argument("Error: Virus '" + v.getName() + "' must have duration > 0");
    }
    if (initial_sick > healthy) {
        throw std::runtime_error("Error: Not enough healthy people for initial infection of " + v.getName());
    }
    
    active_viruses.push_back(VirusState(v, initial_sick));
    healthy -= initial_sick;
    global_sick += initial_sick;
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
        global_dead += deaths;
        
        long long new_recovered = finishing_illness - deaths;
        state.recovered += new_recovered;
        global_recovered += new_recovered;

        // Добовляем настоящее количество заражённых по вирусам в глобальное значение
        global_sick += (new_infected - finishing_illness);
    }
    current_day += 1; // Обновляем количетсво дней
}

void Simulation::printStats() {
    std::cout « "\n─── Day " « current_day « " ───" « std::endl;

    // Общае статистистические данные
    std::cout « "  Population Details:" « std::endl;
    std::cout « "    • Healthy   : " « healthy « std::endl;
    std::cout « "    • Total Sick: " « global_sick « std::endl;
    std::cout « "    • Deaths    : " « global_dead « std::endl;
    std::cout « "    • Recovered : " « global_recovered « std::endl;

    // Детализация по вирусам
    if (!active_viruses.empty()) {
        std::cout « "\n  Active Viruses:" « std::endl;
        
        for (const auto& state : active_viruses) {
            long long total_sick = std::accumulate(state.sick_days.begin(), state.sick_days.end(), 0LL);
            
            std::cout « "    ▶️ " « state.virus.getName() « std::endl;
            std::cout « "      └──> Infected: " « total_sick 
                      « "  |  Dead: " « state.dead 
                      « "  |  Recovered: " « state.recovered « "\n" « std::endl;
        }
    }
    std::cout « "───────────────────────────────────" « std::endl;
}
