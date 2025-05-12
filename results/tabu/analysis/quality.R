library(dplyr)
setwd("/Users/oscar/code/c/FlowshopSLS/results/tabu/analysis/")

tabu <- read.csv("../../resultsTabu.csv")
memetic <- read.csv("../../resultsMemetic.csv")
vnd <- read.csv("../../resultsVND.csv")
vnd <- vnd %>% filter(neighborhood_order == "tei")
comparison_results <- data.frame()


print_results <- function(cmp1, cmp2, n_jobs, w_test, t_test, mean1, mean2, significant_w_test, significant_t_test) {
  cat("\n----------------------------------------------\n")
  cat("Comparing:", cmp1, "vs", cmp2, "\n")
  cat("Jobs: ", n_jobs, "\n")
  cat("Average dev from optimal:", cmp1, "=", round(mean1, 3), "% |", cmp2, "=", round(mean2, 3), "%\n")
  cat("Wilcoxon p-value: ", w_test, "| Significant difference: ", significant_w_test, "\n")
  cat("T-test p-value: ", t_test, "| Significant difference: ", significant_t_test, "\n")
  
  if (significant_w_test) {
    if (mean1 < mean2) {
      cat("Wilcoxon test >>>", cmp1, "is better on average.\n")
    } else if (mean2 < mean1) {
      cat("Wilcoxon test >>>", cmp2, "is better on average.\n")
    } else {
      cat("Wilcoxon test >>> Both are identical.\n")
    }
  }
  
  
  if (significant_t_test) {
    if (mean1 < mean2) {
      cat("T-test >>>", cmp1, "is better on average.\n")
    } else if (mean2 < mean1) {
      cat("T-test >>>", cmp2, "is better on average.\n")
    } else {
      cat("T-test >>> Both are identical.\n")
    }
  }
  
  comparison_results <<- rbind(comparison_results, data.frame(
    cmp1 = cmp1,
    cmp2 = cmp2,
    n_jobs = n_jobs,
    mean1 = round(mean1, 3),
    mean2 = round(mean2, 3),
    p_wilcoxon = w_test,
    p_ttest = t_test,
    significant_wilcoxon = significant_w_test,
    significant_ttest = significant_t_test,
    better = if (mean1 < mean2) cmp1 else if (mean2 < mean1) cmp2 else "equal",
    agreement = significant_w_test == significant_t_test # If both tests agree
  ))
}
perform_tests <- function(merged) {
  alpha <- 0.05
  
  w_test <- wilcox.test(merged$pct_dev_1, merged$pct_dev_2, paired=TRUE)$p.value # Paired means that the test will look if the configuration A beats the config B on multiple instances
  t_test <- t.test(merged$pct_dev_1, merged$pct_dev_2, paired=TRUE)$p.value
  
  # Test the significance
  significant_w_test <- w_test < alpha # If true, we reject the null hypothesis -> one configuration is better than the other
  significant_t_test <- t_test < alpha
  
  mean1 <- mean(merged$pct_dev_1)
  mean2 <- mean(merged$pct_dev_2)
  
  return(list(
    w_test = w_test,
    t_test = t_test,
    significant_w_test = significant_w_test,
    significant_t_test = significant_t_test,
    mean1 = mean1,
    mean2 = mean2
  ))
}

merged <- merge(tabu, vnd, by = "instance", suffixes = c("_1", "_2"))
merged$n_jobs <- merged$n_jobs_1

for (nj in unique(merged$n_jobs)) {
  subset_data <- merged %>% filter(n_jobs == nj)
  test_results <- perform_tests(subset_data)
  
  print_results("tabu", "vnd", nj, 
                test_results$w_test, test_results$t_test, 
                test_results$mean1, test_results$mean2, 
                test_results$significant_w_test, test_results$significant_t_test)
}

write.csv(comparison_results, "tabu_vs_vnd.csv", row.names = FALSE)


merged <- merge(tabu, memetic, by = "instance", suffixes = c("_1", "_2"))
merged$n_jobs <- merged$n_jobs_1

for (nj in unique(merged$n_jobs)) {
  subset_data <- merged %>% filter(n_jobs == nj)
  test_results <- perform_tests(subset_data)
  
  print_results("tabu", "memetic", nj, 
                test_results$w_test, test_results$t_test, 
                test_results$mean1, test_results$mean2, 
                test_results$significant_w_test, test_results$significant_t_test)
}

write.csv(comparison_results, "tabu_vs_memetic.csv", row.names = FALSE)


merged <- merge(memetic, vnd, by = "instance", suffixes = c("_1", "_2"))
merged$n_jobs <- merged$n_jobs_1

for (nj in unique(merged$n_jobs)) {
  subset_data <- merged %>% filter(n_jobs == nj)
  test_results <- perform_tests(subset_data)
  
  print_results("memetic", "vnd", nj, 
                test_results$w_test, test_results$t_test, 
                test_results$mean1, test_results$mean2, 
                test_results$significant_w_test, test_results$significant_t_test)
}

write.csv(comparison_results, "memetic_vs_vnd.csv", row.names = FALSE)