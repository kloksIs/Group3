/**
 * @file Simulation.hpp
 * @brief Классы VirusState и Simulation для симуляции эпидемии
 * @author Артем Петров, Эльвира Бочкарева, Елизавета Цепелева, Вадим Горшков
 * @version 1.0
 */

#ifndef SIMULATION_HPP
#define SIMULATION_HPP

#include "Virus.hpp"
#include <vector>

/**
 * @brief Состояние активного вируса в симуляции
 * @details Хранит очередь больных по дням и статистику
 */
struct VirusState {
    Virus virus;                      ///< Сам вирус
    std::vector<long long> sick_days; ///< Очередь больных по дням
    long long recovered = 0;          ///< Выздоровевшие
    long long dead = 0;               ///< Умершие

    /**
     * @brief Конструктор состояния вируса
     * @param v Вирус
     * @param initial_sick Начальное количество заражённых
     */
    VirusState(Virus v, long long initial_sick);
};

/**
 * @brief Главный класс симуляции эпидемии
 * @details Управляет популяцией и распространением вирусов
 */
class Simulation {
private:
    long long healthy;                    ///< Здоровые люди
    int current_day = 0;                  ///< Текущий день
    std::vector<VirusState> active_viruses; ///< Активные вирусы

public:
    /**
     * @brief Конструктор симуляции
     * @param total_pop Общая численность населения
     */
    Simulation(long long total_pop);

    /**
     * @brief Добавляет вирус в симуляцию
     * @param v Вирус
     * @param initial_sick Начальное количество заражённых
     */
    void addVirus(const Virus& v, long long initial_sick);
    
    /**
     * @brief Удаляет вирус по индексу
     * @param index Индекс вируса в списке
     */
    void removeVirus(int index);
    
    /// @brief Симулирует один день
    void nextDay();
    
    /// @brief Выводит текущую статистику в консоль
    void printStats();
    
    /// @brief Возвращает общее количество заражённых
    double getTotalSick();
    
    /// @brief Возвращает количество активных вирусов
    int getVirusCount() const { return active_viruses.size(); }
};

#endif
