setwd("A:/C Projects/FlowshopSLS/results")
library(dplyr)
# Load the file
results <- read.csv("resultsII.csv")

summary_stats <- results %>%
  group_by(initialization_method, n_jobs) %>%
  summarise(
    avg_pct_dev = round(mean(pct_dev), 3),
    total_time_ms = round(sum(time_ms), 1),
    .groups = 'drop'
  )

write.csv(summary_stats, "./ii/summary.csv", row.names = FALSE)
