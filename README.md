## How to use 
For building and simulating the project, run the following command from the root directory:
```sh
make sim
./bin/SandpileModel config/sandpile_config.json
## How to modify scenarios
For modify scenarios,change the data from sandpil_config.json and sandpileVisualization_config.json
"initial": {
            "state": {"height":()}, 
            "cell_map": [ [(),()] ]
        }
