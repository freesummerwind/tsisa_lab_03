#include <cmath>
#include <ctime>
#include <iomanip>
#include <iostream>

using std::cout;

double randomInRange(const double lower, const double upper) {
    return lower + rand() * 1./RAND_MAX * (upper - lower);
}

void printTableHead() {
    cout << std::left << std::string(47, '-') << '\n'
         << "| " << std::setw(4) << "N"
         << "| " << std::setw(10) << "T"
         << "| " << std::setw(11) << "x"
         << "| " << std::setw(13) << "f(x)" << "|\n"
         << std::string(47, '-') << '\n';
}

void printLine(const int iteration, const double T,
               const double value, const double functionValue) {
    cout << "| " << std::setw(4) << iteration
         << "| " << std::setw(10) << T
         << "| " << std::setw(11) << value
         << "| " << std::setw(13) << functionValue << "|\n";
}

template<class Function>
auto simulatedAnnealingMethod(const double lower, const double upper,
                              Function func) {
    printTableHead();

    const double T_min = .01;
    double T_i = 10000.;
    double x_i = randomInRange(lower, upper);
    int i = 0;
    while (T_i > T_min) {
        ++i;
        double x_new = randomInRange(lower, upper);
        double delta_f = func(x_new) - func(x_i);
        if (delta_f <= 0) {
            x_i = x_new;
        } else {
            double randomProb = randomInRange(0, 1);
            double probability = exp(-delta_f/T_i);
            if (randomProb < probability) {
                x_i = x_new;
            }
        }
        printLine(i, T_i, x_i, func(x_i));
        T_i *= .95;
    }

    cout << std::string(47, '-') << '\n';
    return std::pair{x_i, func(x_i)};
}

double function_variant_4(const double x) {
    return cos(x) * tanh(x);
}

double function_variant_4_with_sin(const double x) {
    return function_variant_4(x) * sin(5*x);
}

const double LOWER = -2.;
const double UPPER = 0.;

int main() {
    cout << "Variant 4.\nFunction 1: cos(x)*th(x), interval: ["
         << LOWER << " " << UPPER << "]\n";
    srand(time(nullptr));
    auto result_1 = simulatedAnnealingMethod(LOWER, UPPER, function_variant_4);
    cout << "Result: Xmin = " << result_1.first
         << ", Fmin = " << result_1.second << '\n';

    cout << "\nFunction 2: cos(x)*th(x)*sin(5*x), interval: ["
         << LOWER << " " << UPPER << "]\n";
    auto result_2 = simulatedAnnealingMethod(LOWER, UPPER, function_variant_4_with_sin);
    cout << "Result: Xmin = " << result_2.first
         << ", Fmin = " << result_2.second << '\n';

    return 0;
}
