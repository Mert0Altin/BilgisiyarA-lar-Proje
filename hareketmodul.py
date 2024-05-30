import sumolib
import traci

sumoBinary = sumolib.checkBinary('sumo')
traci.start([sumoBinary, "-c", "your_sumo_config_file.sumocfg"])

step = 0
while step < 1000:
    traci.simulationStep()
    step += 1

traci.close()
