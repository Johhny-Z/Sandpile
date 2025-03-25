#ifndef SANDPILE_CELL_HPP
#define SANDPILE_CELL_HPP

#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "SandpileState.hpp"
#include <algorithm>  // For std::min

using namespace cadmium::celldevs;

class Sandpile : public GridCell<SandpileState, double> {
public:
    Sandpile(const std::vector<int>& id, const std::shared_ptr<const GridCellConfig<SandpileState, double>>& config)
        : GridCell<SandpileState, double>(id, config) {}

    [[nodiscard]] SandpileState localComputation(
        SandpileState state,
        const std::unordered_map<std::vector<int>, NeighborData<SandpileState, double>>& neighborhood
    ) const override {
        const int threshold = 4;
        SandpileState newState = state;

        // Case 1: Current cell is unstable (height > threshold)
        if (state.height > threshold) {
            // Count stable neighbors
            int stableNeighbors = 0;
            for (const auto& [neighborId, neighborData] : neighborhood) {
                if (neighborData.state->height <= threshold) {
                    stableNeighbors++;
                }
            }

            // Release grains only if there are stable neighbors to receive them
            int grainsToRelease = std::min(4, stableNeighbors);
            newState.height -= grainsToRelease;
            return newState;  // Unstable cells don't receive grains
        }

        // Case 2: Current cell is stable (height ≤ threshold)
        // Count how many unstable neighbors are sending grains to this cell
        int grainsToReceive = 0;
        for (const auto& [neighborId, neighborData] : neighborhood) {
            if (neighborData.state->height > threshold) {
                // Each unstable neighbor can send at most 1 grain
                grainsToReceive++;
            }
        }

        newState.height += grainsToReceive;
        return newState;
    }

    [[nodiscard]] double outputDelay(const SandpileState& state) const override {
        return 1.0;
    }
};

#endif // SANDPILE_CELL_HPP

