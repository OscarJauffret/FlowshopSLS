library(irace)

# === Instances
instances <- list.files("../../instances/Benchmarks", pattern = "^ta0[56]", full.names = TRUE)
cat(instances)

# === Scenario
scenario <- readScenario(filename="./scenario.txt")

# === run
irace(scenario = scenario)
