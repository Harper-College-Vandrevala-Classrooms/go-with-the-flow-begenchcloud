#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

using namespace std;

class HeatFlow {
private:
    vector<float> temperatures;
    float K;
    map<int, float> sources_and_sinks;

public:

    HeatFlow(float initial_temperature, int num_sections, float K, const map<int, float>& sources_and_sinks): K(K), sources_and_sinks(sources_and_sinks) {
        temperatures.resize(num_sections, initial_temperature);

        for (const auto& [index, value] : sources_and_sinks) {
            if (index >= 0 && index < num_sections) {
                temperatures[index] = value;
            }
        }
    }

    void tick() {
        vector<float> new_temperatures = temperatures;

        for (size_t i = 1; i < temperatures.size() - 1; ++i) {
            if (sources_and_sinks.find(i) == sources_and_sinks.end()) {
                new_temperatures[i] = temperatures[i] + K * (temperatures[i + 1] - 2 * temperatures[i] + temperatures[i - 1]);
            }
        }

        temperatures = new_temperatures;
    }


    void print() const {
        cout << "+";
        for (size_t i = 0; i < temperatures.size(); ++i) {
            cout << "------";
        }
        cout << "+" << endl;

        cout << "|";
        for (float temp : temperatures) {
            cout << setw(5) << fixed << setprecision(1) << temp << " |";
        }
        cout << endl;

        cout << "+";
        for (size_t i = 0; i < temperatures.size(); ++i) {
            cout << "------";
        }
        cout << "+" << endl;
    }
};


int main() {
    map<int, float> sources_and_sinks;
    sources_and_sinks[0] = 100.0;

    float initial_temperature = 10.0;
    int num_sections = 5;
    float K = 0.1;

    HeatFlow h(initial_temperature, num_sections, K, sources_and_sinks);

    h.print();

    h.tick();
    h.print();

    h.tick();
    h.print();

    h.tick();
    h.print();

    h.tick();
    h.print();

    h.tick();
    h.print();

    return 0;
}
