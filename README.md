## How to use 
For building and simulating the project, run the following command from the root directory:
```sh
source build_sim.sh
```
## How to modify scenarios
For modify scenarios,change the data from sandpil_config.json and sandpileVisualization_config.json
```
       "initial": {
            "state": {"height":()}, 
            "cell_map": [ [(),()] ]
        }
```
## How to run simulation
For running the simulation,use
```
./bin/SandpileModel config/sandpile_config.json <simulation_steps>
```
Replace<simulation_steps> with the number you want to simulate.
For example,simulate with 20 step:
```
./bin/SandpileModel config/sandpile_config.json 20
```
