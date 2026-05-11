/**
 * @file Virus.hpp
 * @brief Класс Virus - параметры вируса
 * @author Артем Петров, Эльвира Бочкарева, Елизавета Цепелева, Вадим Горшков
 * @version 1.0
 */

#ifndef VIRUS_HPP
#define VIRUS_HPP

#include <string>
#include <nlohmann/json.hpp>

/**
 * @brief Класс, представляющий вирус
 * @details Содержит название, скорость заражения,
 *          инкубационный период и уровень летальности
 */
class Virus {
private:
    std::string name;           ///< Название вируса
    double infection_rate;      ///< Скорость заражения (чел/день)
    int incubation_period;      ///< Инкубационный период (дни)
    double mortality_rate;      ///< Уровень летальности (0.0-1.0)

public:
    /**
     * @brief Конструктор из JSON
     * @param data JSON-объект с полями: name, infection_rate, 
     *             incubation_period, mortality_rate
     */
    Virus(const nlohmann::json& data);

    /// @brief Возвращает название вируса
    std::string getName() const { return name; }
    
    /// @brief Возвращает скорость заражения
    double getInfectionRate() const { return infection_rate; }
    
    /// @brief Возвращает инкубационный период
    int getIncubationPeriod() const { return incubation_period; }
    
    /// @brief Возвращает уровень летальности
    double getMortalityRate() const { return mortality_rate; }
};

#endif
