/* Lance Gartrell
 * 
 * loan code
 * 2/26/2023
 */

#include <stdio.h>

int main (void) {

    /* declarion of variables that will be scanned from user input */
    double loan, rp, apr;

    /* user prompts */
    printf("Enter loan amount:");
    scanf("%lf", &loan);
    
    printf("Enter the repayment period in years (must be integer): ");
    scanf("%lf", &rp);

    printf("Enter the APR (e.g., for 5 percent, enter .05): ");
    scanf("%lf", &apr);

    /* declarion of variables that will be used as placeholders in the monthly payemnt equation */
    double num_of_months, pow, tot;

    /* minor calcualtions to ease monthly payment calcualtion */
    tot = 1;
    num_of_months = rp * 12;
    pow = 1 + (apr/12);
    int month = 0;

    /* obtains the total number of months to calculate */
    while (month++ < num_of_months) {
        tot *= pow;
    }
    
    /* declarion of variables that will be used in calcualtions */
    double principle, monthly_payment, interest, total_int;
    
    /* monthly payment equation */
    monthly_payment = ((loan * tot * apr) / (12*(tot-1)));

    printf("Month | Principle    | \tInterest    | \tRemaining \n");
    printf("---------------------------------------------------- \n");
    month = 0;

    /* calculates the interest, principle, and remaining amount on the loan and prints the values */
    while (month++ < num_of_months){
        interest = (loan * (apr/12));
        total_int = total_int + interest;
        principle = monthly_payment - interest;
        loan = loan - principle;
        printf("%d\t %lf\t %lf\t %lf\t \n", month, principle,interest,loan);
    }

    /* prints the monnthly payment and total interest */
    printf("Monthly payment: %lf total interest: %lf ", monthly_payment, total_int);
    return 0;
}