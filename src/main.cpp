#include <iostream>
#include <vector>
#include <numeric>

struct Virus {
    std::string name;
    double infection_rate; // Заразность чел/день от одного больного
    int incubation_period; // Инкубация в днях
    double mortality_rate; // Смертность от 0.0 (0%) до 1.0 (100%)
};

class Simulation {
private:
    long long healthy;
    std::vector<long long> sick_days; // Запоминаем больных по дням заражения, через период инкубации - определяем исход
    long long recovered = 0;
    long long dead = 0;
    Virus virus;

public:
    // Определяются изначальные параметры симуляции 
    Simulation(long long total_pop, long long initial_sick, Virus v)
        : healthy(total_pop - initial_sick), virus(v){
        sick_days.resize(v.incubation_period, 0);
        sick_days[0] = initial_sick;
    }

    // Обновление показателей после одного дня симуляции 
    void nextDay(){ 
        long long total_sick = std::accumulate(sick_days.begin(), sick_days.end(), 0LL);
        long long new_infected = total_sick * virus.infection_rate;
        if (new_infected > healthy) new_infected = healthy; // ограничиваем возможное число больных
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
    }

    // Вывод последней (актуальной) информации по вирусу
    void printStats(int day){
        long long total_sick = std::accumulate(sick_days.begin(), sick_days.end(), 0LL);
        std::cout << "Day " << day << " | Healthy: " << healthy
                    << " | Sick: " << total_sick
                    << " | Dead: " << dead
                    << " | Recovered: " << recovered << std::endl;
    }    
};

int main(){
    std::cout << "Simulation Started" << std::endl;
    Virus covid = {"COVID-Lite", 1.5, 7, 0.05}; // Заразность 1.5 , болезнь 7 дней, смертность 5%
    Simulation sim(1000000, 10, covid); // 1 млн. население, изначально 10 заражённых

    for ( int i = 1; i <= 30; ++i){ // Симуляция 30 дней
        sim.nextDay();
        sim.printStats(i);
    }

    return 0;
}