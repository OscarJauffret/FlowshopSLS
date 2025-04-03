setwd("A:/C Projects/FlowshopSLS/results")
library(dplyr)
# Load the file
results <- read.csv("resultsII.csv")
comparison_results <- data.frame()

print_results <- function(cmp1, cmp2, param1, param2, w_quality_test, t_quality_test, mean_quality_1, mean_quality_2,
                          significant_w_quality_test, significant_t_quality_test, w_time_test, t_time_test, mean_time_1, mean_time_2,
                          significant_w_time_test, significant_t_time_test) {
  cat("\n----------------------------------------------\n")
  cat("Comparing:", cmp1, "vs", cmp2, "\n")
  cat("Other parameters: ", param1, "|", param2, "\n")
  cat("Average dev from optimal:", cmp1, "=", round(mean_quality_1, 3), "% |", cmp2, "=", round(mean_quality_2, 3), "%\n")
  cat("Average time taken: ", cmp1, "=", round(mean_time_1, 3), "ms |", cmp2, "=", round(mean_time_2, 3), "ms\n")
  cat("Wilcoxon quality p-value: ", w_quality_test, "| Significant difference: ", significant_w_quality_test, "\n")
  cat("T-test quality p-value: ", t_quality_test, "| Significant difference: ", significant_t_quality_test, "\n")
  cat("Wilcoxon time p-value: ", w_time_test, "| Significant difference: ", significant_w_time_test, "\n")
  cat("T-test time p-value: ", t_time_test, "| Significant difference: ", significant_t_time_test, "\n")
  
  if (significant_w_quality_test) {
    if (mean_quality_1 < mean_quality_2) {
      cat("Wilcoxon quality test >>>", cmp1, "is better on average.\n")
    } else if (mean_quality_2 < mean_quality_1) {
      cat("Wilcoxon quality test >>>", cmp2, "is better on average.\n")
    } else {
      cat("Wilcoxon quality test >>> Both are identical.\n")
    }
  }
  
  
  if (significant_t_quality_test) {
    if (mean_quality_1 < mean_quality_2) {
      cat("T-test quality >>>", cmp1, "is better on average.\n")
    } else if (mean_quality_2 < mean_quality_1) {
      cat("T-test quality >>>", cmp2, "is better on average.\n")
    } else {
      cat("T-test quality >>> Both are identical.\n")
    }
  }
  
  if (significant_w_time_test) {
    if (mean_time_1 < mean_time_2) {
      cat("Wilcoxon time test >>>", cmp1, "is faster on average.\n")
    } else if (mean_time_2 < mean_time_1) {
      cat("Wilcoxon time test >>>", cmp2, "is faster on average.\n")
    } else {
      cat("Wilcoxon time test >>> Both are identical.\n")
    }
  }
  
  if (significant_t_time_test) {
    if (mean_time_1 < mean_time_2) {
      cat("T-test time >>>", cmp1, "is faster on average.\n")
    } else if (mean_time_2 < mean_time_1) {
      cat("T-test time >>>", cmp2, "is faster on average.\n")
    } else {
      cat("T-test time >>> Both are identical.\n")
    }
  }
  
  comparison_results <<- rbind(comparison_results, data.frame(
    cmp1 = cmp1,
    cmp2 = cmp2,
    param1 = param1,
    param2 = param2,
    mean_quality_1 = round(mean_quality_1, 3),
    mean_quality_2 = round(mean_quality_2, 3),
    p_wilcoxon_quality = w_quality_test,
    p_ttest_quality = t_quality_test,
    significant_wilcoxon_quality = significant_w_quality_test,
    significant_ttest_quality = significant_t_quality_test,
    better_quality = if (mean_quality_1 < mean_quality_2) cmp1 else if (mean_quality_2 < mean_quality_1) cmp2 else "equal",
    agreement_quality = significant_w_quality_test == significant_t_quality_test, # If both tests agree
    mean_time_1 = round(mean_time_1, 3),
    mean_time_2 = round(mean_time_2, 3),
    p_wilcoxon_time = w_time_test,
    p_ttest_time = t_time_test,
    significant_wilcoxon_time = significant_w_time_test,
    significant_ttest_time = significant_t_time_test,
    better_time = if (mean_time_1 < mean_time_2) cmp1 else if (mean_time_2 < mean_time_1) cmp2 else "equal",
    agreement_time = significant_w_time_test == significant_t_time_test # If both tests agree
  ))
}

perform_quality_tests <- function(merged) {
  # The null hypothesis in the Wilcoxon signed-rank test is that the median difference between the paired observations is zero, 
  # i.e., there is no systematic difference in central tendency between the two groups
  alpha <- 0.05   # The maximum allowable probability of incorrectly rejecting the null hypothesis
  # The null hypothesis is rejected if and only if the p-value is smaller than the significance level (alpha)
  
  # The p-value represents the probability of observing the data (or more extreme results) 
  # under the assumption that the null hypothesis is true.
  # If this probability is low (i.e., p < alpha), we reject the null hypothesis, 
  # because such an observation would be very unlikely under the null hypothesis.
  
  w_test <- wilcox.test(merged$pct_dev_1, merged$pct_dev_2, paired=TRUE)$p.value # Paired means that the test will look if the configuration A beats the config B on multiple instances
  
  # For the t-test, the null hypothesis is that the mean difference between the two configurations is equal to zero 
  # (H0 = no systematic difference between the two groups). 
  # But here, we are assuming normal distribution
  
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

perform_time_tests <- function(merged) {
  alpha <- 0.05
  
  w_test <- wilcox.test(merged$time_ms_1, merged$time_ms_2, paired=TRUE)$p.value
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

compare_init <- function(init1, init2, pivot, neigh) {
  a1 <- results %>% filter(initialization_method  == init1, pivot_rule  == pivot, neighborhood == neigh)  # Selects only the lines that respect the conditions
  a2 <- results %>% filter(initialization_method  == init2, pivot_rule  == pivot, neighborhood == neigh)
  
  merged <- merge(a1, a2, by = "instance", suffixes = c("_1", "_2"))  # Merge the two tables, and puts _1 as a suffix for the columns of a1, and _2 for a2

  quality_test_results <- perform_quality_tests(merged)
  time_test_results <- perform_time_tests(merged)
  
  print_results(init1, init2, pivot, neigh, quality_test_results$w_test, quality_test_results$t_test, quality_test_results$mean1, 
                quality_test_results$mean2, quality_test_results$significant_w_test, quality_test_results$significant_t_test,
                time_test_results$w_test, time_test_results$t_test, time_test_results$mean1, time_test_results$mean2,
                time_test_results$significant_w_test, time_test_results$significant_t_test)
}

compare_pivots <- function(pivot1, pivot2, init, neigh) {
  a1 <- results %>% filter(initialization_method  == init, pivot_rule  == pivot1, neighborhood == neigh)  # Selects only the lines that respect the conditions
  a2 <- results %>% filter(initialization_method  == init, pivot_rule  == pivot2, neighborhood == neigh)
  
  merged <- merge(a1, a2, by = "instance", suffixes = c("_1", "_2"))  # Merge the two tables, and puts _1 as a suffix for the columns of a1, and _2 for a2
  
  quality_test_results <- perform_quality_tests(merged)
  time_test_results <- perform_time_tests(merged)
  
  print_results(pivot1, pivot2, init, neigh, quality_test_results$w_test, quality_test_results$t_test, quality_test_results$mean1, 
                quality_test_results$mean2, quality_test_results$significant_w_test, quality_test_results$significant_t_test,
                time_test_results$w_test, time_test_results$t_test, time_test_results$mean1, time_test_results$mean2,
                time_test_results$significant_w_test, time_test_results$significant_t_test)
}

compare_neighs <- function(neigh1, neigh2, init, pivot) {
  a1 <- results %>% filter(initialization_method  == init, pivot_rule  == pivot, neighborhood == neigh1)  # Selects only the lines that respect the conditions
  a2 <- results %>% filter(initialization_method  == init, pivot_rule  == pivot, neighborhood == neigh2)
  
  merged <- merge(a1, a2, by = "instance", suffixes = c("_1", "_2"))  # Merge the two tables, and puts _1 as a suffix for the columns of a1, and _2 for a2
  
  quality_test_results <- perform_quality_tests(merged)
  time_test_results <- perform_time_tests(merged)
  
  print_results(neigh1, neigh2, init, pivot, quality_test_results$w_test, quality_test_results$t_test, quality_test_results$mean1, 
                quality_test_results$mean2, quality_test_results$significant_w_test, quality_test_results$significant_t_test,
                time_test_results$w_test, time_test_results$t_test, time_test_results$mean1, time_test_results$mean2,
                time_test_results$significant_w_test, time_test_results$significant_t_test)
}

inits <- c("random", "srz")
pivots <- c("first", "best")
neighborhoods <- c("transpose", "exchange", "insert")

for (pivot in pivots) {
  for (neigh in neighborhoods) {
    compare_init(inits[1], inits[2], pivot, neigh)
  }
}

for (init in inits) {
  for (neigh in neighborhoods) {
    compare_pivots(pivots[1], pivots[2], init, neigh)
  }
}

neigh_pairs <- list(
  c("transpose", "exchange"),
  c("transpose", "insert"),
  c("exchange", "insert")
)

for (pair in neigh_pairs) {
  for (init in inits) {
    for (pivot in pivots) {
       compare_neighs(pair[1], pair[2], init, pivot)
    }
  }
}


write.csv(comparison_results, "ii_comparison_summary.csv", row.names = FALSE)
