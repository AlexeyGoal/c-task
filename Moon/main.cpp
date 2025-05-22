#include "Moon.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

struct MoonEventTimes {
    std::string rise;
    std::string culmination;
    std::string set;
};

MoonEventTimes calculateMoonEvents(const std::vector<MoonObservation>& observations) {
    MoonEventTimes events;
    bool riseFound = false, setFound = false;
    double prevElevation = observations[0].elevation;
    int maxIndex = 0;

    // Первичный анализ данных
    for (size_t i = 0; i < observations.size(); i++) {
        const auto& obs = observations[i];

        // Поиск максимальной высоты (кульминация)
        if (obs.elevation > observations[maxIndex].elevation) {
            maxIndex = i;
        }

        // Поиск восхода (переход от отрицательной к положительной высоте)
        if (!riseFound && prevElevation < 0 && obs.elevation >= 0) {
            events.rise = obs.time;
            riseFound = true;
        }

        // Поиск захода (переход от положительной к отрицательной высоте)
        if (!setFound && prevElevation >= 0 && obs.elevation < 0) {
            events.set = obs.time;
            setFound = true;
        }

        prevElevation = obs.elevation;
    }

    // Уточнение времени кульминации с помощью параболической аппроксимации
    if (observations.size() >= 3 && maxIndex > 0 && maxIndex < observations.size() - 1) {
        const auto& prev = observations[maxIndex - 1];
        const auto& curr = observations[maxIndex];
        const auto& next = observations[maxIndex + 1];

        double A[3][3] = {
            {prev.hours * prev.hours, prev.hours, 1.0},
            {curr.hours * curr.hours, curr.hours, 1.0},
            {next.hours * next.hours, next.hours, 1.0}
        };
        double B[3] = { prev.elevation, curr.elevation, next.elevation };
        double invA[3][3];

        if (MoonUtils::invert3x3Matrix(A, invA)) {
            double coeffs[3];
            MoonUtils::multiplyMatrixByVector(invA, B, coeffs);
            double t_culm = -coeffs[1] / (2 * coeffs[0]);
            events.culmination = MoonUtils::hoursToHMS(t_culm);
            return events;
        }
    }

    // Если аппроксимация не удалась, используем ближайшее измерение
    events.culmination = observations[maxIndex].time;
    return events;
}

int main() {
    try {
        std::string inputYear, inputDate;
        std::cout << "Enter year (YYYY): ";
        std::cin >> inputYear;
        std::cout << "Enter date (DD.MM.YYYY): ";
        std::cin >> inputDate;

        std::string targetDate = MoonUtils::convertDateFormat(inputDate);
        std::string filename = "../input/moon" + inputYear + ".dat";

        std::ifstream file(filename);
        if (!file) {
            throw std::runtime_error("Cannot open file: " + filename);
        }

        // Пропуск заголовка
        std::string header;
        std::getline(file, header);

        // Чтение данных
        std::vector<MoonObservation> observations;
        std::string fileDate, fileTime;
        double t, r, elevation, az, fi, lg;

        while (file >> fileDate >> fileTime >> t >> r >> elevation >> az >> fi >> lg) {
            if (MoonUtils::compareStrings(fileDate, targetDate)) {
                observations.emplace_back(MoonObservation{
                    fileDate,
                    fileTime,
                    MoonUtils::timeToDecimalHours(fileTime),
                    elevation
                    });
            }
        }

        if (observations.empty()) {
            throw std::runtime_error("No data for selected date");
        }

        MoonEventTimes events = calculateMoonEvents(observations);

        // Вывод результатов
        std::cout << "\nDate: " << inputDate << "\n";
        std::cout << "Moonrise: " << (events.rise.empty() ? "not found" : events.rise) << "\n";
        std::cout << "Moon culmination: " << events.culmination << "\n";
        std::cout << "Moonset: " << (events.set.empty() ? "not found" : events.set) << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
