#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Virus.hpp"
#include <vector>

class Simulation {
private:
    long long healthy;
    // Запоминаем больных по дням заражения и через период инкубации - определяем исход
    std::vector<long long> sick_days; 
    long long recovered = 0;
    long long dead = 0;
    int current_day = 0;
    Virus virus;

public:
    // Определяются изначальные параметры симуляции 
    Simulation(long long total_pop, long long initial_sick, Virus v);

    // Обновление показателей после одного дня симуляции 
    void nextDay();

    // Вывод последней (актуальной) информации по вирусу
    void printStats();
};

#endif