#ifndef SANDPILE_STATE_HPP
#define SANDPILE_STATE_HPP
#include <iostream>
#include <nlohmann/json.hpp>

struct SandpileState {
    int height; // Height of the sand grains

    explicit SandpileState(): height(0) {} // Default constructor, initializes height to 0
};

 // Overload the output stream operator
std::ostream& operator<<(std::ostream& os, const SandpileState& x) {
    os <<"<" << x.height <<">"; // Output the height of the sand grains
    return os;
}

// Overload the inequality operator
bool operator!=(const SandpileState& x, const SandpileState& y) {
    return x.height != y.height;
}

// Read the initial state from a JSON file
void from_json(const nlohmann::json& j, SandpileState& s) {
    j.at("height").get_to(s.height);
}

#endif // SANDPILE_STATE_HPP