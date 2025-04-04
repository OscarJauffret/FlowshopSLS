library(dplyr)
setwd("A:/C Projects/FlowshopSLS/results")
results_vnd <- read.csv("resultsVND.csv")

summary_vnd <- results_vnd %>%
  group_by(neighborhood_order, n_jobs) %>%
  summarise(
    avg_dev = mean(pct_dev),
    avg_time = mean(time_ms),
    .groups = "drop"
  )


results_single <- read.csv("resultsII.csv") %>%
  filter(neighborhood %in% c("exchange", "insert")) %>%
  group_by(neighborhood, n_jobs) %>%
  summarise(
    avg_dev = mean(pct_dev),
    avg_time = mean(time_ms),
    .groups = "drop"
  )

comparison <- summary_vnd %>%
  left_join(results_single, by = "n_jobs", suffix = c("_vnd", "_single")) %>%
  mutate(
    method_compared = neighborhood,
    improvement_pct_dev = 100 * (avg_dev_single - avg_dev_vnd) / avg_dev_single,
    improvement_time = 100 * (avg_time_single - avg_time_vnd) / avg_time_single
  ) %>%
  select(neighborhood_order, n_jobs, method_compared, improvement_pct_dev, improvement_time)

print(summary_vnd)
print(comparison)

write.csv(summary_vnd, "./vnd/summary.csv", row.names = FALSE)
write.csv(comparison, "./vnd/improvement_comparison.csv", row.names = FALSE)
