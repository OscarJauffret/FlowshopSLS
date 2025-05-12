library(dplyr)
library(ggplot2)
library(tidyr)

setwd("/Users/oscar/code/c/FlowshopSLS/results/tabu/analysis/")

tabu <- read.csv("../../resultsTabu.csv")
memetic <- read.csv("../../resultsMemetic.csv")

tabu$algo <- "Tabu"
memetic$algo <- "Memetic"

all_data <- bind_rows(tabu, memetic)

# Average deviation per algorithm and instance
avg_dev <- all_data %>%
  group_by(instance, algo, n_jobs) %>%
  summarise(avg_pct_dev = mean(pct_dev), .groups = 'drop')

# To have a single line per instance: <instance, n_jobs, Tabu, Memetic>
wide_dev <- avg_dev %>%
  pivot_wider(names_from = algo, values_from = avg_pct_dev)

ggplot(wide_dev, aes(x = Tabu, y = Memetic, color = factor(n_jobs))) +
  geom_point(size = 3) +
  geom_abline(slope = 1, intercept = 0, linetype = "dashed") +
  labs(
    title = "Correlation plot: Tabu vs Memetic",
    x = "Average % Deviation (Tabu)",
    y = "Average % Deviation (Memetic)",
    color = "Instance Size"
  ) +
  theme_minimal() + 
  coord_fixed() + xlim(0, NA) + ylim(0, NA) + 
  theme(plot.title = element_text(hjust = 0.5))


