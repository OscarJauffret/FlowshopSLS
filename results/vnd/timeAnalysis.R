setwd("A:/C Projects/FlowshopSLS/results")
library(dplyr)
# Load the file
results <- read.csv("resultsVND.csv")
comparison_results <- data.frame()

print_results <- function(cmp1, cmp2, n_jobs, w_test, t_test, mean1, mean2, significant_w_test, significant_t_test) {
  cat("\n----------------------------------------------\n")
  cat("Comparing:", cmp1, "vs", cmp2, "\n")
  cat("Number of jobs: ", n_jobs, "\n")
  cat("Average execution time:", cmp1, "=", round(mean1, 3), "ms |", cmp2, "=", round(mean2, 3), "ms\n")
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
  # The null hypothesis in the Wilcoxon signed-rank test is that the median difference between the paired observations is zero, 
  # i.e., there is no systematic difference in central tendency between the two groups
  alpha <- 0.05   # The maximum allowable probability of incorrectly rejecting the null hypothesis
  # The null hypothesis is rejected if and only if the p-value is smaller than the significance level (alpha)
  
  # The p-value represents the probability of observing the data (or more extreme results) 
  # under the assumption that the null hypothesis is true.
  # If this probability is low (i.e., p < alpha), we reject the null hypothesis, 
  # because such an observation would be very unlikely under the null hypothesis.
  
  w_test <- wilcox.test(merged$time_ms_1, merged$time_ms_2, paired=TRUE)$p.value # Paired means that the test will look if the configuration A beats the config B on multiple instances
  
  # For the t-test, the null hypothesis is that the mean difference between the two configurations is equal to zero 
  # (H0 = no systematic difference between the two groups). 
  # But here, we are assuming normal distribution
  
  t_test <- t.test(merged$time_ms_1, merged$time_ms_2, paired=TRUE)$p.value
  
  # Test the significance
  significant_w_test <- w_test < alpha # If true, we reject the null hypothesis -> one configuration is better than the other
  significant_t_test <- t_test < alpha
  
  mean1 <- mean(merged$time_ms_1)
  mean2 <- mean(merged$time_ms_2)
  
  return(list(
    w_test = w_test,
    t_test = t_test,
    significant_w_test = significant_w_test,
    significant_t_test = significant_t_test,
    mean1 = mean1,
    mean2 = mean2
  ))
}


compare_strategies <- function(strategy1, strategy2, jobs) {
  a1 <- results %>% filter(neighborhood_order==strategy1, n_jobs==jobs)  # Selects only the lines that respect the conditions
  a2 <- results %>% filter(neighborhood_order==strategy2, n_jobs==jobs)
  
  merged <- merge(a1, a2, by = "instance", suffixes = c("_1", "_2"))  # Merge the two tables, and puts _1 as a suffix for the columns of a1, and _2 for a2
  
  test_results <- perform_tests(merged)
  print_results(strategy1, strategy2, jobs, test_results$w_test, test_results$t_test, test_results$mean1, 
                test_results$mean2, test_results$significant_w_test, test_results$significant_t_test)
}

n_jobs_arr <- c(50, 100, 200)
for (n_jobs in n_jobs_arr) {
  compare_strategies("tei", "tie", n_jobs)  
}
write.csv(comparison_results, "./vnd/time_comparison.csv", row.names = FALSE)