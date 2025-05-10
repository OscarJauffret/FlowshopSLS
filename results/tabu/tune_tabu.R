library(irace)

# === Scenario
scenario <- readScenario(filename="./scenario.txt")

# === run
irace(scenario = scenario)
