/* COMP211: Challenge Problem 1p: Mastermind
 * Lance Gartrell
 * Professor Danner
 * March 30, 2023
 * 
 * Information on pointers, enum, and arrays came from class resources: IC, C for COMP 211, and Modern C
 */

#include <stdlib.h>
#include <time.h>
#include <stdio.h>


/* generates a random sequence of non-duplicated colors from the color enumeration */
void getcode(int *ncode){
    int duplicate, cplace = 0;
    srand48(time(NULL));
    enum color {RED=1, BLUE=2, GREEN=3, YELLOW=4, WHITE=5, ORANGE=6};
    enum color col;
    while(cplace < 4) {

        /* uses tplace as a placeholder in the code array, going through each element of ncode and comparing it to the selected colors */
        col = lrand48() % 6 + 1;
        for(int tplace=0; tplace<=cplace; tplace++) {
            if(ncode[tplace] != col){
                duplicate = 0;
            }
            /* if duplicate, break from for loop and get new number*/
            else if(ncode[tplace] == col) {
                duplicate = 1;
                break;
            }
        }
        /* if color is not a duplicate, adds that color to the cplace element of ncode array, which is then incremented */
        if(duplicate==0) {
            ncode[cplace]=col;
            cplace++;
        }
    }
    /* for (int i = 0; i < 4; i++){
        printf("code is %d \n", ncode[i]);
    } */
    
}

/* translates the integer value of the colors to a char array */
void translatecode(int *ncode, char *c){
    for (int i=0;i<4;i++) {
        if (ncode[i]==1) {
            c[i]='R';
        }
        if (ncode[i]==2) {
            c[i]='B';
        }
        if (ncode[i]==3) {
            c[i]='G';
        }
        if (ncode[i]==4) {
            c[i]='Y';
        }
        if (ncode[i]==5) {
            c[i]='W';
        }
        if (ncode[i]==6) {
            c[i]='O';
        }
       
    }
    

}

/* checks if color is correct by comparing the guess to the code, incrementing a color if it is there. */
void color_correct(int cnp, char *guess, char *code){
    int coloronly = 0, cc = 0;
    int R=0,B=0,G=0,Y=0,W=0,O=0;

    /* imporatant note: if color is repeated i.e GOOW, O gets value of 2. Thus, if any color = 2, then decremented by 1.*/
    for (int i=0;i<4;i++) {
        if (guess[i]=='R') {
            for (int x=0;x<4;x++){
                if (code[x]=='R') {
                    R++;
                }
                if (R == 2){
                    R--;
                }
            }
        }
        if (guess[i]=='B') {
            for (int x=0;x<4;x++){
                if (code[x]=='B') {
                    B++;
                }
                if (B == 2){
                    B--;
                }
            }    
        }
        if (guess[i]=='G') {
            for (int x=0;x<4;x++){
                if (code[x]=='G') {
                    G++;
                }
                if (G == 2){
                    G--;
                }
            }
        
        }
        if (guess[i]=='Y') {
            for (int x=0;x<4;x++){
                if (code[x]=='Y') {
                    Y++;
                }
                if (Y == 2){
                    Y--;
                }
            }
        }
        if (guess[i]=='W') {
            for (int x=0;x<4;x++){
                if (code[x]=='W') {
                    W++;
                }
                if (W == 2){
                    W--;
                }
            }
        }
        if (guess[i]=='O') {
            for (int x=0;x<4;x++){
                if (code[x]=='O') {
                    O++;
                }
                if (O == 2){
                    O--;
                }
            }
        }
    }

    /* sum all correct colors and substract the colors in the correct postions from the total */
    cc = R+B+G+Y+W+O;
    coloronly = cc-cnp;
    printf(" %d colors in the wrong position. \n", coloronly);  
}

/* function that ask the user to input the remaining characters of their guess */
void add_to_over(char *ng, char *guess, int *amt_over, int *wo, char *c){
    char input[3];
    int ov = *amt_over; 
    printf("the secret code is %s \n", c);
    printf("colors to add: %s+", ng);
    scanf("%s", input);

    /* loops which first add the charcters from nextguess[] to guess[], then adds the input to guess[]*/
    for (int i = 0; i < *amt_over; i++){
        guess[i]=ng[i];
    }
    for (int i = 0; i < 4; i++){
        guess[i+ov]=input[i];
    }
    printf("You guessed: %s \n", guess);
    *wo = 0;
    
}

/* function that checks if the user guess went over the 4 charcter limit */
void went_over(char *guess, int *wo, char *nextguess, int *amt_over){
    int len = 0, over = 0, o = 0;

    /* calculates the length of the guess */
    for(int i = 0; guess[i] != '\0'; i++) {
        len += 1;
    }

    /* if len is above 4 char, then will add the chars over the limit to the nextguess[] */
    if (len > 4){
        over = (len - 4);
        printf("length is too long. the characters over the limit will be used in the next guess \n");
        for (int i = 0; i < over; i++) {
                nextguess[i] = guess[4+i] ;
            }
        o = 1;    
        *wo = o;
        *amt_over = over;
    } 
}

/* plays the mastermind game*/
void playgame(void){
    
    /* loop to continue playing the game until user types 'n' */
    char answer = 'y';
    while (answer == 'y') {

        /* variable declarions */
        int ncode[4];
        char code[4], guess[7], nextguess[4], ng[4], response[0];
        int quit = 0, cnp = 0, wins = 0, lost = 0, tot = 0, attempt = 1, over = 0, wo = 0; 

        /* function calls*/
        getcode(ncode);
        translatecode(ncode, code);
        
        /* array reassignment due to miscellaneous 'y' at the end for some odd reason... */
        char c[4];
        for (int i = 0; i<4;i++){
            c[i] = code[i];
        }

        /* loop that will play a round of the game. Stops when user wins or runs out of attempts */
        while (quit == 0) {
            
            if (attempt == 4){
                quit = 1;
            }

            /* function call */
            went_over(guess, &wo, nextguess, &over);

            /* if statement to see if the users guess was over char limit */
            if (wo == 1){

                /* same deal as line 207 */
                for (int i = 0; i < over; i++){
                    ng[i] = nextguess[i];
                }

                /* function call */
                add_to_over(ng, guess, &over, &wo, c);

            }
            else {
                printf("the 'secret code' is %s \n", c);
                printf("Please enter your guess as a string of exactly 4 characters: ");
                scanf("%s", guess);
            }
            
            /* checks if all the colors guessed are in the correct position. */
            int incguess = 0;
            for (int i=0;i<4;i++) {
                if (guess[i]!= c[i]) {
                    incguess=1;
                }
            } 
            /* if all in correct postion, display victory message. */
            if (incguess==0) {
                printf("Congratulations! You have won the game after %d tries\n", attempt);
                wins++;
                printf("Would you like to play again? (y/n) ");
                scanf("%c", response);
                answer = response[0];
                break;
            }
            /* checks which colors are in the correct postion and sums that number to cnp */
            for (int i=0;i<4;i++) {
                if (guess[i]==c[i]) {
                    cnp++;
                }    
            }
            printf("You got %d colors in the right position and", cnp);

            /* function call for correct color but worng postion. */
            color_correct(cnp, guess, c);

            /* resets variables and incremetns attempt */
            cnp = 0;
            attempt++;

            /* Display message for if the user runs out of attempts */
            if (quit == 1){
                printf("Too bad, you lost. The code was %s \n", c);
                lost++;
                printf("Would you like to play again (y/n)? ");
                scanf("%c", response);
                answer = response[0];
                break;
            }
        }
                
        tot = wins + lost;

        /* displays games won if user decides to quit */
        if (answer == 'n'){
            printf("you won %d/%d", wins, tot);
            break;
        }
    }    
}

int main (void) {
    printf("Welcome to Mastermind! \n") ;
    printf("Enter a guess as a string of 4 characters, where they must be \n");
    printf("G - Green \n");
    printf("B - Blue \n") ;
    printf("R - Red \n") ;
    printf("Y - Yellow \n"); 
    printf("W - White \n") ;
    printf("O - Orange \n") ;
    printf("Warning: if you enter too many colors for your guess, colors after the fourth will be used as part of your next guess. \n");
    playgame();
    return 0;
    
}

