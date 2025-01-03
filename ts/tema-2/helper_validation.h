#include <numeric>
#include <cmath>

namespace Helper {
    // Functie pentru generarea unei variabile aleatoare Gamma(a, 1)
    double generateGamma(double a, std::mt19937 &gen) {
        std::gamma_distribution<> gammaDist(a, 1.0);
        return gammaDist(gen);
    }

    // Functie pentru calculul mediei unei selectii de valori
    double mean(const std::vector<double> &data) {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return sum / data.size();
    }

    // Functie pentru calculul dispersiei unei selectii de valori
    double variance(const std::vector<double> &data) {
        double meanValue = mean(data);
        double sum = 0.0;
        for (const auto &value: data) {
            sum += std::pow(value - meanValue, 2);
        }
        return sum / data.size();
    }

}
