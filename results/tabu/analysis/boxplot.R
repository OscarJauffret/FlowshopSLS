library(ggplot2)
setwd("/Users/oscar/code/c/FlowshopSLS/results/tabu/analysis/")

tabu <- read.csv("../../resultsTabu.csv")
memetic <- read.csv("../../resultsMemetic.csv")
vnd <- read.csv("../../resultsVND.csv")
tabu <- tabu[, c("n_jobs", "pct_dev")]
memetic <- memetic[, c("n_jobs", "pct_dev")]
vnd  <- vnd[, c("n_jobs", "pct_dev")]
tabu$Algorithm <- "TS"
vnd$Algorithm <- "VND"
memetic$Algorithm <- "Memetic"



data <- rbind(tabu, vnd, memetic)

ggplot(data, aes(x = interaction(Algorithm, n_jobs), y = pct_dev, fill = Algorithm)) +
  geom_boxplot() +
  labs(
    title = "Boxplot of % deviation by algorithm and instance size",
    x = "Algorithm - Instance Size",
    y = "% Deviation from Best Known Solution"
  ) +
  theme_minimal() +
  theme(
    axis.text.x = element_text(angle = 45, hjust = 1),
    plot.title = element_text(hjust = 0.5)
  ) +
  scale_fill_manual(values = c("TS" = "lightblue", "VND" = "lightpink", "Memetic" = "lightgreen"))
