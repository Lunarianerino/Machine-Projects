# Define the revised tax table for 2022
tax_table_2022 <- data.frame(
  lower_limit = c(0, 20834, 33333, 66667, 166667, 666667),
  upper_limit = c(20833, 33332, 66666, 166666, 666666, Inf),
  base_tax = c(0, 0, 2500, 10833.33, 40833.33, 200833.33),
  tax_rate = c(0, 0.20, 0.25, 0.30, 0.32, 0.35)
)

# Define the SSS, PhilHealth, and Pag-IBIG contribution calculation functions
calculate_sss_contribution <- function(income) {
  sss_rate <- 0.045
  sss_contribution <- min(income * sss_rate, 1350)
  return(sss_contribution)
}

calculate_philhealth_contribution <- function(income) {
  # 4.5%
  philhealth_rate <- 0.04
  philhealth_contribution <- income * philhealth_rate
  return(philhealth_contribution / 2)
}

calculate_pagibig_contribution <- function(income) {
  if (income > 15000){
    pagibig_rate <- 0.02  
  } else {
    pagibig_rate <- 0.01
  }
  pagibig_contribution <- min(income * pagibig_rate, 100)
  return(pagibig_contribution)
}

# Create a function that calculates the total contributions, taxable income, and income tax based on income, the tax table, and the SSS, PhilHealth, and Pag-IBIG contribution calculation functions
calculate_tax <- function(income, tax_table, sss_function, philhealth_function, pagibig_function) {
  # Calculate total contributions
  sss_contribution <- sss_function(income)
  philhealth_contribution <- philhealth_function(income)
  pagibig_contribution <- pagibig_function(income)
  total_contributions <- sss_contribution + philhealth_contribution + pagibig_contribution

  # Calculate tax
  taxable_income <- income
  cat(paste("taxable income", taxable_income, "\n"))
  tax = 0
  for (i in 1:nrow(tax_table)) {
    if (taxable_income <= tax_table$upper_limit[i]) {
      taxable_income_this_level <- taxable_income - tax_table$lower_limit[i]
      #cat(paste("taxable_this_level:", taxable_income_this_level, "\n"))
      tax = taxable_income_this_level * tax_table$tax_rate[i] + tax_table$base_tax[i]
      cat(paste("tax:", taxable_income_this_level, "with rate:", tax_table$tax_rate[i], "and base tax of", tax_table$base_tax[i], "\n"))
      cat(paste("final_tax:", tax, "\n"))
      break
    }
  }
  
  # Return results as a list
  return(list(total_contributions = total_contributions, taxable_income = taxable_income, income_tax = tax))
}

income <- 25000
tax_info <- calculate_tax(income, tax_table_2022, calculate_sss_contribution, calculate_philhealth_contribution, calculate_pagibig_contribution)
cat(paste("Your income is:", income, "\n"))
cat(paste("Your SSS contribution is:", calculate_sss_contribution(income), "\n"))
cat(paste("Your PhilHealth contribution is:", calculate_philhealth_contribution(income), "\n"))
cat(paste("Your Pag-IBIG contribution is:", calculate_pagibig_contribution(income), "\n"))
cat(paste("Your total contributions are:", calculate_sss_contribution(income) + calculate_philhealth_contribution(income) + calculate_pagibig_contribution(income), "\n"))
cat(paste("Your taxable income is:", tax_info$taxable_income, "\n"))
cat(paste("Your income tax for 2022 is:", tax_info$income_tax, "\n"))
cat(paste("Your Total Deduction:", tax_info$total_contributions + tax_info$income_tax, "\n"))
cat(paste("Your Net Pay:", income - tax_info$total_contributions - tax_info$income_tax))