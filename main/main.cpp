#include "nlohmann/json.hpp"
#include <cadmium/modeling/celldevs/grid/coupled.hpp>
#include <cadmium/simulation/logger/csv.hpp>
#include <cadmium/simulation/root_coordinator.hpp>
#include <fstream>
#include <string>
#include "include/SandpileCell.hpp"

using namespace cadmium::celldevs;
using namespace cadmium;

// 工厂函数：根据配置创建细胞实例
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
    if (argc < 2) { // 检查命令行参数
        std::cout << "Usage: " << argv[0] << " SCENARIO_CONFIG.json [MAX_SIMULATION_TIME (default: 500)]" << std::endl;
        return -1;
    }

    std::string configFilePath = argv[1]; // 配置文件路径
    double simTime = (argc > 2)? std::stod(argv[2]) : 500.0; // 模拟时间

    // 初始化模型
    auto model = std::make_shared<GridCellDEVSCoupled<SandpileState, double>>("sandpile", addGridCell, configFilePath);
    model->buildModel();

    // 初始化根协调器
    auto rootCoordinator = RootCoordinator(model);
    rootCoordinator.setLogger<CSVLogger>("sandpile_log.csv", ";"); // 使用 CSV 日志记录器

    // 运行模拟
    rootCoordinator.start();
    rootCoordinator.simulate(500.0);
    rootCoordinator.stop();

    return 0;
}