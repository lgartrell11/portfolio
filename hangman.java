import java.util.Scanner;

// Lance Gartrell
// 12/10/2020
// Hangman game project
// Added hint system and ASCII hangman
public class historyHangman {

    public static void main(String[] args) {
        int[] previousGuess = new int[65];
        int holder = 0;
        checkSpace();
        instructions();
        Scanner x = new Scanner(System.in);
        while (asteriskWord.contains("*")) {
            askGuess();
            String userGuess = x.next();
            System.out.print("\n");
            checkQuit(userGuess);
            if (isValid(userGuess)) {
                wantsHint(userGuess);
                checkCorrectGuess(userGuess, previousGuess, holder);
            } else {
                printInvalidMessage(userGuess);
            }
        }
        winMessage();
    }

    public static void checkCorrectGuess(String x, int[] previousGuess, int holder) { // checks the users guess
        String guess = x.toUpperCase();
        if (isPreviousGuess(x, previousGuess)) {
            System.out.println("You Bonehead... you already guessed " + x + ".");
            return;
        }
        String newAsteriskWord = "";
        checkGuess(newAsteriskWord, guess);
    }


    public static void checkGuess(String newAsteriskWord, String guess) { // github-makes a new asterisk word, showing guessed letters that appear in the word
        for (int selectedLetter = 0; selectedLetter < secretWord.length(); selectedLetter++) { // goes through each char of the word, seeing the guess matches while creating its own word.
            if (secretWord.charAt(selectedLetter) == guess.charAt(0)) {
                newAsteriskWord += guess.charAt(0);
            } else if (secretWord.charAt(selectedLetter) == ' ') {
                newAsteriskWord += '_';
            } else if (asteriskWord.charAt(selectedLetter) != '*') { // if its not an '*' then it replaces it with the letter
                newAsteriskWord += secretWord.charAt(selectedLetter);
            } else {
                newAsteriskWord += '*';
            }
        }
        displayResult(newAsteriskWord, guess);

    }

    public static void displayResult(String newAsteriskWord, String userGuess) { // compares the newly generated asterisk word to the previous and the secret word
        if (asteriskWord.equals(newAsteriskWord)) {
            System.out.println("Sorry, there are no " + userGuess + "'s " + "in the secret word.");
            asciiHang++;
            hangmanImage(asciiHang);
            if ((asciiHang > 2 && asciiHang < 10) && !usedHint) { // ask the user if they want a hint. if they do, doesn't ask again
                Scanner y = new Scanner(System.in);
                askHint();
                String answer = y.next();
                if (wantsHint(answer)){
                    System.out.println();
                    System.out.println(hint);
                    usedHint = true;
                }
            }
        } else {
            System.out.println("Correct! " + userGuess + " is in the word.");
            asteriskWord = newAsteriskWord;
        }

        if (asteriskWord.equals(secretWord)) {
            System.out.println("Nice job! the word was " + newAsteriskWord + ".");
        }
    }

    public static void checkSpace() { // checks if word has a space. If it does, then it replaces it with an "_"
        String spaceAsteriskWord = "";
        for (int i = 0; i < secretWord.length(); i++) {
            if (secretWord.charAt(i) == ' ') {
                spaceAsteriskWord += "_";
            } else {
                spaceAsteriskWord += '*';
            }
        }
        asteriskWord = spaceAsteriskWord;
    }

    public static boolean isValid(String userGuess) { // checks if the user input is a only 1 letter
        char charCheck = userGuess.charAt(0);
        for (char i : userGuess.toCharArray()) {
            if (Character.isDigit(i))
                return false;
        }
        if (!Character.isLetter(charCheck)) {
            return false;
        } else return userGuess.length() <= 1;
    }

    public static boolean isPreviousGuess(String userGuess, int[] previousGuess) { // checks if the user guess is already inputted
        char charCheck = userGuess.charAt(0);
        int counter = charCheck - 65;
        previousGuess[counter]++;
        for (int i : previousGuess) { // Henry Bedel helped me with the for loop
            int place = previousGuess[counter];
            if (place > 1) {
                return true;
            }
        }
        return false;
    }

    public static void checkQuit(String userGuess) { // checks if the user wants to quit
        if (userGuess.equals("$$$")) {
            System.err.println("END GAME: Thanks for playing!");
            System.exit(0);
        }
    }

    public static void askGuess() { // ask the ser for its guess
            System.out.println();
            System.out.println("Your secret letter: " + asteriskWord);
            System.out.println();
            System.out.print("A letter in the word?:  ");
    }

    public static void hangmanImage(int count) { // Displays image based off incorrect guesses
        switch (count) {
            case 1 -> {
                System.out.println();
                System.out.println("  ");
                System.out.println("  ");
                System.out.println("  ");
                System.out.println("  ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 2 -> {
                System.out.println();
                System.out.println("  / ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 3 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  / ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 4 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  /         |");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 5 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  /         |");
                System.out.println(" |        (^_^)");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 6 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  /         |");
                System.out.println(" |        (^_^)");
                System.out.println(" |          |");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 7 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  /         |");
                System.out.println(" |        (^_^)");
                System.out.println(" |       ~--|");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 8 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  /         |");
                System.out.println(" |        (^_^)");
                System.out.println(" |       ~--|--~");
                System.out.println(" | ");
                System.out.println(" | ");
                System.out.println("_|_ ");
            }
            case 9 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  /         |");
                System.out.println(" |        (^_^)" + "  NO!!! Stop guessing wrong !!!");
                System.out.println(" |       ~--|--~");
                System.out.println(" |          |");
                System.out.println("_|_        /");
            }
            case 10 -> {
                System.out.println();
                System.out.println("   __________");
                System.out.println("  /         |");
                System.out.println(" |        (X_X)");
                System.out.println(" |       ~--|--~");
                System.out.println(" |          |");
                System.out.println(" |         / \\");
                System.out.println("_|_ ");
                System.err.println("GAME OVER. You couldn't save him... :(");
                System.out.println("The word was " + secretWord + ".");
                System.exit(0);
            }
        }
    }

    public static void instructions() { // opening instructions on how to play the game
        System.out.println("Welcome to HistoryHangman! ");
        System.out.println("In this game, if you're not already familiar, you will be asked to guess a random word 1 letter at a time.");
        System.out.println("You have 10 lives. Entering a non-letter guess will result in a invalid guess, but you wont lose your lives. ;)");
        System.out.println("If you to wish to quit, entering in '$$$' will fulfil your wishes.");
        System.out.println();
        System.out.println(" (^_^)  " + "-'Please don't let me die' ");
        System.out.println("~--|--~ ");
        System.out.println("   |    " + "  This is Misovi. His fate resides in your guessing ability. He has a very bright future ahead...So be careful.");
        System.out.println("  / \\");
        System.out.println();
        System.out.println("The theme of this game is WW1 and WW2 battles, with the exception of one definition you should DEFINITELY know.");
        System.out.println("Since not everyone is a history buff, ill provide an option for 1 hint with the date and details of the secret word after 3 incorrect guesses." + "\n" + "After the hint is used, the prompt will disappear.");
        System.out.println("If you don't enter in 'yes' or 'no' when prompted, your answer will not be taken and the game will proceed.");
        System.out.println();
        System.out.println("Ready? Cool, lets begin!");
    }

    public static void askHint() { // ask if the user wants a hint
            System.out.println();
            System.out.print("Would you like a hint? enter in 'yes' or 'no' here: ");
    }
    public static boolean wantsHint(String answer){ // shows hint if user wants it. Doesn't show if user doesn't want it
        if (answer.equals("yes")) {
            return true;
        }
        if (answer.equals("no")){
            System.out.println();
            System.out.println("Good! I like your perseverance.");
        }
    return false;
    }
    public static void printInvalidMessage(String userGuess){ // prints invalid message if guess is invalid
        System.out.println(userGuess + " is an Invalid guess. Please enter a valid guess.");
    }
    public static void winMessage(){
        System.out.println();
        System.out.println("Congrats!! You solved the word! the word was " + secretWord + ".");
        System.exit(0);
    }
    public static String[] secretWords = new String[]{   // random set of words that can be chosen
            "SECOND BATTLE OF YPRES", "SIEGE OF LENINGRAD", "BATTLE OF STALINGRAD", "BATTLE OF VERDUN", "BRUSILOV OFFENSIVE",
            "BATTLE OF IWO JIMA", "STUDY OF PATTERNS", "GALLIPOLI CAMPAIGN", "BATTLE OF THE NEK", "BATTLE OF THE SOMME",
            "THE KAISERSCHLACHT", "BATTLE OF PASSCHENDAELE", "PEARL HARBOUR", "UNRESTRICTED SUBMARINE WARFARE", "SCHLIEFFEN PLAN",
            "BATTLE OF ATTRITION", "TRENCH WARFARE", "BATTLE OF MIDWAY", "OPERATION BARBAROSSA", "BLITZKRIEG"
    };
    public static String[] wordHint = new String[]{ // random set of hints that correspond with the words
            "1915: Deployed by the germans, this is the first ever usage of poison gas in war.", "1941-44: Known as the '900 day siege'. over 1 million civilian deaths from starvation", "1943-44: German disaster marked the end of eastern advancements and the total destruction of the German 6th army.",
            "1916: General von Falkenhayn wanted to 'bleed France white'.", "1916: this 'june advance' led to the greatest Russian advances in WW1.", "1945: Knowledge from this bloody japanese engagement influenced the bombings of Hiroshima and Nagasaki.",
            "Simply put, what is mathematics??", "1915-16: Failure of British plans to take Constantinople led to a casualty free evacuation(known as most successful part of operation).", "1915: poor co-ordination of artillery with ANZAC troops let to no territorial gain and many casualties, making it the final assault of the operation.",
            "1916: British assault to relieve fighting in Verdun. Known as bloodiest day in British history.", "1918: German name for the final German offensive of WW1.", "1917: Formally known as the 'Third Battle of Ypres'.", "1941: This unprecedented bombing of US ships brought USA into WW2.",
            "1915 and 1917: resumption of this warfare was one of the main causes of US involvement into WW1.", "1914: Failure of this German plan brought Britain into WW1.", "Base strategy of WW1-- focused on depleting your enemies resources before your own.", "The type of warfare fought in WW1.",
            "1942: Decisive US naval victory that deterred all hopes of japanese destruction of US navy.", "1941: Code name for the German invasion of Russia.", "German attack strategy in WW2. 'Lightning Warfare'. "
    };


    public static int a = (int) (Math.random() * 20);
    public static String secretWord = secretWords[a]; // from github: allows variables to be used in all methods w/o declaring them in parameter
    public static String hint = wordHint[a];
    public static String asteriskWord = new String(new char[secretWord.length()]).replace("\0", "*"); // stackoverflow- replaces the 0 with _
    public static int asciiHang = 0;
    public static boolean usedHint = false;
    public static int pick = 0;