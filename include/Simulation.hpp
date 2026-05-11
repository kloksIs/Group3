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
 * @details Хранит очередь больных по дням и статистику конкретного вируса
 */
struct VirusState {
    Virus virus;                      ///< Сам вирус
    std::vector<long long> sick_days; ///< Очередь больных по дням заражения
    long long recovered = 0;          ///< Выздоровевшие от этого вируса
    long long dead = 0;               ///< Умершие от этого вируса

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
    long long global_sick = 0;            ///< Общее число больных (все вирусы)
    long long global_recovered = 0;       ///< Общее число выздоровевших
    long long global_dead = 0;            ///< Общее число умерших
    int current_day = 0;                  ///< Текущий день
    std::vector<VirusState> active_viruses; ///< Список активных вирусов

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
    
    /**
     * @brief Симулирует один день
     * @details Обновляет показатели распространения и исходы болезней
     */
    void nextDay();
    
    /**
     * @brief Выводит текущую статистику в консоль
     * @details Отображает актуальную информацию по всем вирусам и популяции
     */
    void printStats();
    
    /// @brief Возвращает текущее количество здоровых людей
    long long getHealthy() const { return healthy; }

    /// @brief Возвращает общее количество больных по всем вирусам
    long long getGlobalSick() const { return global_sick; }

    /// @brief Возвращает общее количество выздоровевших за всё время
    long long getGlobalRecovered() const { return global_recovered; }

    /// @brief Возвращает общее количество умерших за всё время
    long long getGlobalDead() const { return global_dead; }

    /// @brief Возвращает количество активных вирусов
    int getVirusCount() const { return active_viruses.size(); }
};

#endif
