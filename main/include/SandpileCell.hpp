#ifndef SANDPILE_CELL_HPP
#define SANDPILE_CELL_HPP

#include <nlohmann/json.hpp>
#include <cadmium/modeling/celldevs/grid/cell.hpp>
#include <cadmium/modeling/celldevs/grid/config.hpp>
#include "SandpileState.hpp"

using namespace cadmium::celldevs;

class Sandpile : public GridCell<SandpileState, double> {
public:
    Sandpile(const std::vector<int>& id, const std::shared_ptr<const GridCellConfig<SandpileState, double>>& config)
        : GridCell<SandpileState, double>(id, config) {}

    // Local computation function: defines the sandpile collapse rule
    [[nodiscard]] SandpileState localComputation(
        SandpileState state,
        const std::unordered_map<std::vector<int>, NeighborData<SandpileState, double>>& neighborhood
    ) const override {
        int unstableNeighbors = 0; // Count the number of neighbors exceeding the threshold
        
        // Step 1: Count the number of neighbors with height > 4
    
        for (const auto& [neighborId, neighborData] : neighborhood) {
            if (neighborData.state->height > 4) {
                unstableNeighbors+=1;
            }
        }
        
        // Step 2: If the current cell exceeds the threshold, process its sand grains first
        if (state.height > 4) {
            state.height -= 4; // Reduce by 4 sand grains
            
            
        }
        // Step 3: Increase its own sand grains based on the number of unstable neighbors
        state.height += unstableNeighbors;
        // Each unstable neighbor adds 1 grain
        
        return state;
    }

    // Output delay function: defines the state update delay time
    [[nodiscard]] double outputDelay(const SandpileState& state) const override {
        return 1.0; // Fixed delay time of 1.0
    }
};

#endif // SANDPILE_CELL_HPP


