#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Virus.hpp"
#include <vector>

// Описываем состояние конкретного вируса
struct VirusState {
    Virus virus;
    // Запоминаем больных, делаем очередь по дням заражения, чтобы через период инкубации - определить исход
    std::vector<long long> sick_days; 
    long long recovered = 0;
    long long dead = 0;

    VirusState(Virus v, long long initial_sick);
};

class Simulation {
private:
    long long healthy;
    int current_day = 0;
    std::vector<VirusState> active_viruses; // Список активных вирусов

public:
    // Определяются изначальные параметры симуляции 
    Simulation(long long total_pop);

    // Добавление нового вируса в симуляцию
    void addVirus(const Virus& v, long long initial_sick);

    // Обновление показателей после одного дня симуляции 
    void nextDay();

    // Вывод последней (актуальной) информации по вирусу
    void printStats();
};

#endif