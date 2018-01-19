#include <stdlib.h>
#include <stdio.h>


struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double update_account_balance(double current_account_balance, double months_rate_of_return,
				  double months_contribution)
{
  
  return ((current_account_balance * months_rate_of_return) + current_account_balance) + months_contribution;
}

void retirement(int startAge,   //in months
		double initial, //inital savings in dollars
		retire_info working, // info about working
		retire_info retired) // info about being retired
{

  // variable for holding user's retirement account balance
  double retirement_account_balance = initial;  
  // initialize to the initial savings value

  // accumulate account value while working each month
  for (int i = startAge; i < startAge + working.months; i++)
    {
      // print out the current balance at the start of each month
      printf("Age %3d month %2d you have $%.2lf\n", (i/12), (i % 12), retirement_account_balance);
      
      retirement_account_balance = update_account_balance(retirement_account_balance, working.rate_of_return, working.contribution);
      // now retirement_account_balance is updated for the month
    }

  for (int j = startAge + working.months; j < startAge +  working.months + retired.months; j++)
    {
      printf("Age %3d month %2d you have $%.2lf\n", (j/12), (j % 12), retirement_account_balance);

      // now update for retirement
      retirement_account_balance = update_account_balance(retirement_account_balance, retired.rate_of_return, retired.contribution);
    }


}


int main(void)
{
  // Working info
  double workingRateOfReturn = 0.045/12;

  retire_info working = {489, 1000, workingRateOfReturn};
  
  // Retired info
  double retiredRateOfReturn = 0.01/12;
  
  retire_info retired = {384, -4000, retiredRateOfReturn};  

  retirement(327, 21345, working, retired);

  return EXIT_SUCCESS;
}
		
