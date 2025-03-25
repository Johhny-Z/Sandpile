#include "nlohmann/json.hpp"
#include <cadmium/modeling/celldevs/grid/coupled.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <fstream>
#include <string>
#include "include/SandpileCell.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;

// Factory function: creates cell instances based on configuration
std::shared_ptr<GridCell<SandpileState, double>> addGridCell(
    const coordinates & cellId,
    const std::shared_ptr<const GridCellConfig<SandpileState, double>>& cellConfig
) {
    auto cellModel = cellConfig->cellModel;
    if (cellModel == "sandpile") {
        return std::make_shared<Sandpile>(cellId, cellConfig);
    } else {
        throw std::bad_typeid();
    }
}

int main(int argc, char ** argv) {
    // Check command line arguments
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 500)]" << std::endl;
        return -1;
    }

    std::string configFilePath = argv[1]; // Path to configuration file
    double simTime = (argc > 2)? std::stod(argv[2]) : 500.0; // Simulation time

    // Initialize the model
    auto model = std::make_shared<GridCellDEVSCoupled<SandpileState, double>>("sandpile", addGridCell, configFilePath);
    model->buildModel();

    // Initialize root coordinator
    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>("sandpile_log.csv", ";"); // Use CSV logger

    // Run the simulation
    rootCoordinator.start();
    rootCoordinator.simulate(simTime);
    rootCoordinator.stop();

    return 0;
}
