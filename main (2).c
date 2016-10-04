/* ------------------------------------------------
 * Project 3: IKEA Project
 *
 * Class: Fall 2016, UIC CS141,  Tuesday 1PM lab.
 * System: Windows 10, DevC++ and Code Blocks
 * Author: Julio Castaneda Jose Galeano
 * UIC NET ID: Jcasta24 and jgalea5.
 *
 * Discription: The purpose of this program is to open
 * multiple text files(IKEA, Input, and dictionary) and depending on
 * task being asked to do and function being called it will compare the
 * certain word with a specific txt file.
 *
 * Sample code provided by Professor Dale Reed of University of Illinois at Chicago.
 *-------------------------------------------------*/

/* Have to include these so the program works correctly.
   Standard libraries in C, helpful with strings. */

#include <stdio.h>    // Input and output.
#include <string.h>   // for string length.
#include <stdlib.h>   // for std library.
#include <ctype.h>   // Need this for certain string functions.
#define TRUE 1       // Defining True as 1.
#define FALSE 0     // Defining False as 0.

const int NumberOfWordsInDictionary = 40445;       // Number of words in the dictionary.
const int NumberOfWordsInIKEAFile = 1765;          // Number of words in IKEA file.
const char DictionaryFileName[] = "dictionary.txt";// File name for where dictionary words are found.
const char IKEAFileName[] = "IKEAwords.txt";       // File name for where IKEA words are found.
const char InputFileName[] = "inputfile.txt";      // File name for where Input words are found.
const int MaxWordSize = 21 + 1; // Maximum size of any word in the dictionary, + 1 for null.

// Function Prototypes
void readWordsInFromDictionaryFile(FILE *pDictionaryFile, char dictionary[ ][ MaxWordSize]);
void readWordsInFromIKEAFile(FILE *pIKEAFile, char IKEAwords[ ][MaxWordSize]);
void readWordsInFromInputFile(FILE *pInputFile, char Inputwords[ ][ MaxWordSize]);
void CountWordsInInputFile(FILE *pInputFile, int *NumberOfWordsInInputFile);
void removeLeadingAndTrailingPunctuation(char theWord[]);
void OrganizeWords(char wordList[][MaxWordSize], int wordListSize);
void MakeWordLowerCase(char aWord[]);
void MakeWordUpperCase(char aWord[]);
int MatchSubstring(char aWord[], char IKEAwords[][MaxWordSize]);
int CompareWords(char aWord[], char IKEAwords[][MaxWordSize]);
void CompareIKEAToDictionary(char dictionary[][ MaxWordSize], char IKEAwords[][ MaxWordSize]);
void CompareInputToIKEA(char IKEAwords[][ MaxWordSize], char InputWords[][ MaxWordSize], int NumberOfWordsInInputFile);
int DeleteCharacter(char aInputWord[], char IKEAwords[][MaxWordSize]);
int EditOneCharacter(char IKEAwords[][ MaxWordSize], char InputWords[]);
int EditThreeCharacters(char IKEAwords[][ MaxWordSize], char InputWords[]);
int DeleteThreeCharacters(char aInputWord[], char IKEAwords[][MaxWordSize]);
int SubstituteCharacter(char aInputWord[], char IKEAwords[][MaxWordSize]);
int SubstituteThreeCharacters(char aInputWord[], char IKEAwords[][MaxWordSize]);



/* Thiw will count the number of words in the input file becauses the program
   doesn't know how many words are in the file. Have to count them to get an index.
   Passing the file and number of words as parameters. */

void CountWordsInInputFile(FILE *pInputFile, int *NumberOfWordsInInputFile)
{
    int index = 0;                      // Index of InputFile word being read.
    int tempIndex;                      // Index of temporary word.
    char tempnInputWord[MaxWordSize];   // Temporary array for each word.

    // Associate the actual file name with file pointer and try to open it.
    pInputFile = fopen(InputFileName, "r");
    // verify that file opens, or it will give the user an error message.
    if (pInputFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", InputFileName);
        exit(-1);
    }

    // Keep reading words until it reaches the end.
    while(fscanf(pInputFile, "%s", tempnInputWord) != EOF) {
    	// Increment the index.
        index++;
        // Increment the number of words in the file.
        *NumberOfWordsInInputFile+=1;
        // Reset the temporary array by making each element the null.
        for(tempIndex=0;tempIndex<strlen(tempnInputWord);tempIndex++){
            tempnInputWord[tempIndex] = '\0';
        }//end for loop*/
    }
    fclose(pInputFile);   // close the dictionary file

}// End CountWordsInInputFile()

/* The purpose of this function is to organized the words because the words are not in order
   in the input file. Can not use binary algorithm if the words are not in order. */

void OrganizeWords(char wordList[][MaxWordSize], int wordListSize)
{
    int wordIndex;  // Index of current words
    int nextWord;   // Index of word being compared
    char tempWord[MaxWordSize]; // Temporary words

    /* The nested for loops and if statements will go through all the words from the input file
       organized them in order because they're not in order. Using strcmp to compare the word with
	   the next word. If the word should come before the current word then they will swap places until the
	   order is current. Similar to a buble search. */
    for (wordIndex = 0; wordIndex <wordListSize - 1 ; wordIndex++) {
        for (nextWord = wordIndex+1; nextWord <wordListSize; nextWord++) {
            if (strcmp(wordList[wordIndex], wordList[nextWord]) > 0) {
                strcpy(tempWord, wordList[wordIndex]);
                strcpy(wordList[wordIndex], wordList[nextWord]);
                strcpy(wordList[nextWord], tempWord);
            }// End of if statement.
        }// End of inner for loop.
    }// End swapping for loop

}// End OrganizeWords()


/* This function will make a word lower case because the dictionary is lower case and the ikea
   file is upper case. The input file can also have upper and lower case letters. Need to make
   everything the same so strcmp can be used. */

void MakeWordLowerCase(char aWord[])
{
    int charIndex;  // Index for characters

    // For loop to go through every char in the file and make it lower case.
    for(charIndex=0; charIndex<strlen(aWord); charIndex++){
        aWord[ charIndex] = tolower( aWord[ charIndex]);
    } // End of for loop.

}// End MakeWordLowerCase()


/* This function will make a word upper case because the IKEA file is upper case and the input
   file is upper case and lower case.. The input file can also have upper and lower case letters. Need to make
   everything the same so strcmp can be used. */

void MakeWordUpperCase( char aWord[])
{
    int charIndex;  // Index for characters

    // For loop to go through every char in the file and make it lower case.
    for(charIndex=0; charIndex<strlen(aWord); charIndex++){
        aWord[ charIndex] = toupper( aWord[ charIndex]);
    }// End of for loop.

}// End MakeWordUpperCase()

/* This function will compare the IKEA file to the dictionary. It will print out the words and how many words match
	and are found in both files. */

void CompareIKEAToDictionary(char dictionary[][ MaxWordSize], char IKEAwords[][ MaxWordSize])
{
    int wordIndex;         // Index for word to be used.
    int low, mid, high;    // Array indices for binary search.
    int searchResult = -1; // Stores index of word if search succeeded, else -1.
    int j=1;              // Counter to be incremented and printed out based on the results.

	// For loop that will go through all the words in the IKEA file.
    for (wordIndex=0; wordIndex< NumberOfWordsInIKEAFile; wordIndex++){
        // Setting the lowest value to 0.
        low = 0;
        // Setting the highest value to the lenght of the array without the NULL.
        high = NumberOfWordsInDictionary - 1;
        // While loop to search the dictionary. If it's less or equal to the highest number then it will run.
        while (low <= high)  {
        	// The middle is the average of the low and high values.
            mid = (low + high) / 2;
            // Calling function to make lower case.
            MakeWordLowerCase(IKEAwords[wordIndex]);
            // Return the value for the strcmp.
            searchResult = strcmp( IKEAwords[ wordIndex], dictionary[ mid]);
            // If there is a match then it will print it out.
            if (searchResult == 0)  {
                printf("%d: ", j);
                j++;
                printf("%s\n",( IKEAwords[ wordIndex]));
                break;
            }
            // Else if and else statements to set the new high and low if the value of the strcmp is less than 0.
            else if (searchResult < 0)  {
                high = mid - 1; // Word should be located prior to mid location.
                continue;
            }
            else{
                low = mid + 1; // Word should be located after mid location.
                continue;
            }// End of else.
        }// End of while loop.
    }//End binary search for-loop

}// End CompareIKEAToDictionary()


/* This function will compare the IKEA file to the input file. It will print out the words, how many words match
	and are found in both files. */

void CompareInputToIKEA(char IKEAwords[][ MaxWordSize], char InputWords[][ MaxWordSize],
                          int NumberOfWordsInInputFile)
{
    int wordIndex;         // Index for word to be used
    int low, mid, high;    // Array indices for binary search
    int searchResult = -1; // Stores index of word if search succeeded, else -1

	// For loop to go through all the words in the Input file.
    for (wordIndex=0; wordIndex<NumberOfWordsInInputFile;wordIndex++){
        int printed = 0;
        // Make the word lower case.
        MakeWordLowerCase( InputWords[ wordIndex]);
        // Setting the low to 0.
        low = 0;
        // Setting high the total number of words - 1.
        high = NumberOfWordsInIKEAFile - 1;
        // While loop to keep searching until the condition is no longer true.
        while (low <= high)  {
            // Set the mid to the average of high and low.
            mid = (low + high) / 2;
            // SearcResult is equal to the value of strcmp.
            searchResult = strcmp(InputWords[wordIndex], IKEAwords[ mid]);
            // If statement if the searchResult is 0. Print out the number and increase j.
            if (searchResult == 0)  {
                // Make the word uppercase.
                MakeWordUpperCase(InputWords[wordIndex]);
                // Print the word in upper case.
                printf("%s ",(InputWords[wordIndex]));
                // Break out of the loop.
                printed = 1;
                break;
            }// End of while loop.
            // Else if and else statements to set the new high and low if the value of the strcmp is less than 0.
            else if (searchResult < 0)  {
                high = mid - 1; // Word should be located prior to mid location.
                continue;
            }
            else  {
                low = mid + 1; // Word should be located after mid location.
                continue;
            }// End of else statement.
        }
        if(printed){
            continue;
        }
        printed = EditOneCharacter(IKEAwords, InputWords[wordIndex]);
        if(printed){
            continue;
        }
        printed = EditThreeCharacters(IKEAwords, InputWords[wordIndex]);
        if(printed){
            continue;
        }
        printf("%s ", InputWords[ wordIndex]);

    }//End binary search for-loop

}// End CompareInputToIKEA()


/* This function will print after going through all the functions and checking to see which one matches. If the word matches after editing
   then it will print out. */

int EditOneCharacter(char IKEAwords[][ MaxWordSize], char InputWord[])
{
    int index;      // Index of words being used
    int printed = 0;// Bool int type to verify if a word was printed

    // If the word was printed, it will skip and go to the next word
    // Printed is equal to the return of DeletedCharacter function.
    printed = DeleteCharacter(InputWord, IKEAwords);
    if(printed){
        return 1;
    }
    // Printed is equal to the return of SubstituteCharacter.
    printed = SubstituteCharacter(InputWord, IKEAwords);
    if(printed){
        return 1;
    }
    /*printed = InsertCharacter( InputWords[ index], IKEAwords);
    if(printed){
``      return 1;
    }*/
    // Printed is equal to the return of MatchSubstring.
    printed = MatchSubstring(InputWord, IKEAwords);
    if(printed){
        return 1;
    }// End of if statment.
    return 0;

}// End EditWords()


/* Similar the editOneCharacter function. It will check the functions and if then print out the word if the function
   being called return a value back to this function. */

int EditThreeCharacters(char IKEAwords[][ MaxWordSize], char InputWord[])
{
    int index;      // Index of words being used
    int printed = 0;// Bool int type to verify if a word was printed

    // If the word was printed, it will skip and go to the next word.
    // printed is equal to the value return by the function being called.
    printed = DeleteThreeCharacters(InputWord, IKEAwords);
    if(printed){
        return 1;
    }
    printed = SubstituteThreeCharacters(InputWord, IKEAwords);
    if( printed){
        return 1;;
    }
    /*printed = InsertCharacter(InputWords[index], IKEAwords);
        if(printed){
    continue;
    }*/
    return 0;
}// End EditWords()


/* This function will delete one character at a time from the word. Passing the input word and IKEA word as parameters.
   Will be returning a value of int. */

int DeleteCharacter(char aInputWord[], char IKEAwords[][MaxWordSize]){

	// Declaring the loop counters.
    int i;
    int j;
    int k;
    int resetIndex; // Index for reseting a word
    int printed; // To return back to another function to be printed based on the results.
    char tempWord[ MaxWordSize];     // Array for temp word.
    char compareWord[MaxWordSize];   // Array for the compare word.

    // for loop to reset the index of the compareWord.
    for(resetIndex=0; resetIndex<MaxWordSize; resetIndex++){
            compareWord[ resetIndex] = '\0';}

	// Make the word lower case.
    MakeWordLowerCase(aInputWord);

    // For loop to copy the input word to the temp word.
    for(i=0; i< strlen(aInputWord); i++){
        strcpy(tempWord, aInputWord);
        tempWord[ i] = ' ';                  // Add space to every element of array

        for (j=0; k<strlen(tempWord); j++){ // Create new string without space
            if(tempWord[j] != ' ' ){
                compareWord[k] = tempWord[j];
                k++;
            }//end if statement
        }
        //printf("%s\n", compareWord);
        // Calling compareWords to compare the words.
        printed = CompareWords(compareWord, IKEAwords);
        if(printed){
            // Return 1.
            return 1;
        }
		// Similar to the for loop above to reset the index and add the NULL.
        for(resetIndex=0; resetIndex<MaxWordSize; resetIndex++){
                compareWord[resetIndex] = '\0';
        }//end for loop
        k = 0;
    }//end for loop
	// Return 0.
    return 0;

}// End DeleteCharacter()

// This function will delete 3 characters into the word and will be return an int value.

int DeleteThreeCharacters(char aInputWord[], char IKEAwords[][MaxWordSize]){

	// Three blank spaces.
    int blank1;
    int blank2;
    int blank3;
    // Int to reset the index.
    int resetIndex;
    // Int to return if printed.
    int printed;
    // Char array for temp word.
    char tempWord[MaxWordSize];
    // Char array for compare word.
    char compareWord[ MaxWordSize];

    int i;
    int k=0;
    for(resetIndex=0; resetIndex< MaxWordSize; resetIndex++){
            compareWord[ resetIndex] = '\0';
    }

    for(blank1 = 0; blank1<strlen(aInputWord)-2; blank1++){
        for(blank2 = blank1 + 1; blank2<strlen(aInputWord)-1; blank2++){
            for(blank3 = blank2 + 1; blank3<strlen(aInputWord); blank3++){
                strcpy( tempWord, aInputWord);
                tempWord[blank1]= ' ';
                tempWord[blank2]= ' ';
                tempWord[blank3]= ' ';
                for(i=0; i< strlen(tempWord); i++){
                    if( tempWord[ i] != ' ' ){
                        compareWord[ k] = tempWord[ i];
                        k++;
                    }//end if statement
                }
                printed = CompareWords( compareWord, IKEAwords);
                if( printed){
                    return 1;
                }
                for(resetIndex=0; resetIndex< MaxWordSize; resetIndex++){
                    compareWord[ resetIndex] = '\0';
                }
                k=0;
            }// End blank3 for loop
        }// End blank2 for loop
    }// End blank1 for loop

    return 0;
}

//----------------------------------------------------------------------------
//
int SubstituteCharacter(char aInputWord[], char IKEAwords[][MaxWordSize])
{
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char tempWord[MaxWordSize];
    int lengthOfWord = strlen( aInputWord);
    int lengthOfAlphabet= strlen( alphabet);
    int counter=0;
    int printed=0;

    int i,j;

    for ( i=0; i< lengthOfWord; i++){
        for( j=0; j< lengthOfAlphabet; j++){
            strcpy( tempWord, aInputWord);
            MakeWordLowerCase( tempWord);
            if(tempWord[ i] != alphabet[ j]){
                tempWord[ i] = alphabet[ j];
                counter++;
                printed = CompareWords( tempWord, IKEAwords);
                if(printed){
                    return 1;
                }
            }
        }
    }// End for loop

    // No comparison was found.
    return 0;

}// End SubstituteCharacter()



// This function will substitute 3 characters into the word and will be return an int value.
int SubstituteThreeCharacters(char aInputWord[], char IKEAwords[][MaxWordSize])
{
	//Array of letters.
    char alphabet[] = "abcdefghijklmnopqrstuvwxyz";
    // Temp word arrays to be used for the changes made.
    char tempWord[MaxWordSize];
    char tempWord2[MaxWordSize];
    char tempWord3[MaxWordSize];
    // lengthOfWord is equal to the strlen of (aInputWord).
    int lengthOfWord = strlen(aInputWord);
    // lengthOfAlphabet is equal to the strlen of (alphabet).
    int lengthOfAlphabet = strlen(alphabet);
    // Printed intialize to 0.
    int printed=0;
    // Variables for counter.
    int i,j,k;
    int a,b,c;

   // Make the word lower case.
    MakeWordLowerCase(aInputWord);
    //Nested for loop to change one letter.
    for (i=0; i< lengthOfWord-2; i++){
        for( a=0; a< lengthOfAlphabet; a++){
        	// Copy the word to the tempWord.
            strcpy(tempWord, aInputWord);
            // If statement to that will set tempWord[i] to te alphabet[loop counter]
            if(tempWord[i] != alphabet[a]){
                tempWord[i] = alphabet[a];
            }
            // The same loop for the next letter to be changed and it will create a new word.
            for (j=i+1; j< lengthOfWord-1; j++){
                for(b=0; b< lengthOfAlphabet; b++){
                	// Copy the word to the tempWord.
                    strcpy( tempWord2, tempWord);
                    // If statement to that will set tempWord[i] to te alphabet[loop counter]
                    if( tempWord2[j] != alphabet[ b]){
                        tempWord2[j] = alphabet[ b];
                    }
            // The same loop for the next letter to be changed and it will create a new word.
                    for (k=j+1; k< lengthOfWord; k++){
                        for(c=0; c< lengthOfAlphabet; c++){
                        	// Copy the word to the tempWord.
                            strcpy( tempWord3, tempWord2);
                            // If statement to that will set tempWord[i] to te alphabet[loop counter]
                            if( tempWord3[k] != alphabet[c]){
                                tempWord3[k] = alphabet[c];
                                printed = CompareWords(tempWord3, IKEAwords);
                                if(printed){
                                    // Return 1;
                                    return 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }// End of first for loop.

	// No comparison was found.
    return 0;

}//  End of SubstituteThreeCharacters.

/* This function will return an int and it will compare a word with the IKEA words from the txt. This
   function is using a binary search and the code is provided by Professor Reed. */

int CompareWords(char aWord[], char IKEAwords[][MaxWordSize])
{
    int wordIndex;         // Index for word to be used
    int low, mid, high;    // array indices for binary search
    int searchResult = -1; // Stores index of word if search succeeded, else -1
    char tempWord[ MaxWordSize]; // Copy of original word

    strcpy( tempWord, aWord);
    MakeWordLowerCase( tempWord);
    // Binary search for word
    // Sets low to 0;
    low = 0;
    // Sets high to the total number of words in the IKEA file - 1.
    high = NumberOfWordsInIKEAFile - 1;
    // While loop that will check the condition and keep checking if the condition is true.
    while (low <= high)  {
        // Mid is the average of the low and high values.
        mid = (low + high) / 2;
        // Calling the function to make the word lower case.
        MakeWordLowerCase(IKEAwords[mid]);
        // Compare the ikea words with the word. Search result is the value of the result of strcmp.
        searchResult = strcmp(tempWord, IKEAwords[ mid]);
        // If statement to make the word upper case and print it.
        if (searchResult == 0)  {
            MakeWordUpperCase( IKEAwords[ mid]);
            printf("%s ",( IKEAwords[ mid]));
            return 1;
        }
        // Else if and else statements if the result is lower than 0.
        else if (searchResult < 0)  {
            high = mid - 1; // word should be located prior to mid location
            continue;
        }
        else  {
            low = mid + 1; // word should be located after mid location
            continue;
        }
    }
    // Return 0 is no word is found.
    return 0;

}// End CompareWords()


/* Function to find if the word is a substring of another word from the input file.
   Passing the word, Ikeawords and the size as parameters. */

int MatchSubstring(char aWord[], char IKEAwords[][MaxWordSize])
{
	// Declaring variables index, pointer PTempWord, and int printed.
    int index;
    char pTempWord;

	// For loop to go through all the number of words in the ikea file and then use if statement for word and ikea word.
 	for(index = 0; index <NumberOfWordsInIKEAFile; index++){
        if(strcmp(aWord, IKEAwords[index])==0){
            return 0;}
        // pTempWord is the substring between the ikea word and aword.
        pTempWord = strstr(IKEAwords[index], aWord);
        // If statement if the pTempWord does not equal the NULL then print it out.
        if(pTempWord!= NULL){
        	// Call the function to make the word upcase and print it out. Return int 1.
            MakeWordUpperCase(IKEAwords[index]);
            printf("%s ", IKEAwords[index]);
            return 1;
        }// End of if statement.
    }// End of for loop.

	// Returns 0.
    return 0;
} // End of MatchingSubstring function.


// Main function.

int main()
{
	// The students information required for this program.
	printf("\n");
    printf("Authors: Julio Casteneda and Jose Galeano       \n");
    printf("UIC NET IDs: Jcasta24 and jgalea5      \n");
    printf("Program #3: IKEA project with input txt files. Printing out the words depending on the task and function. \n");
    printf("TA: Guixiang Ma, Tu 1PM. \n");
    printf("Date: October 1, 2016           \n");
    printf("\n");

    // Array of array for all dictionary and IKEA words
    char dictionary[ NumberOfWordsInDictionary][ MaxWordSize];
    char IKEAwords[ NumberOfWordsInIKEAFile][MaxWordSize];

    FILE *pDictionaryFile;  // File pointer to dictionary.
    FILE *pIKEAFile;        // File pointer to IKEA file.
    FILE *pInputFile;       // File pointer to inputfile.

    // Create arrays of words for both dictionary and IKEA files
    readWordsInFromDictionaryFile( pDictionaryFile, dictionary);
    // Calling the function to read the words from the IKEA file.
    readWordsInFromIKEAFile( pIKEAFile, IKEAwords);

    // Organize IKEA words.
    OrganizeWords(IKEAwords, NumberOfWordsInIKEAFile);

    // Function to count number of words in input file.
    int NumberOfWordsInInputFile = 0;
    // Calling the function to count the number of words in the file.
    CountWordsInInputFile(pInputFile, &NumberOfWordsInInputFile);

    // Create and fix array of words in Input file.
    char InputWords[NumberOfWordsInInputFile+1][ MaxWordSize];
    // Calling the function to read the words using the file and total number of input words are parameters.
    readWordsInFromInputFile(pInputFile, InputWords);
	int index;
    for(index=0; index<NumberOfWordsInInputFile; index++){
        removeLeadingAndTrailingPunctuation(InputWords[index]);
    }
	// The start of stage 1 output.
    printf("----------------------Stage 1 -------------------------------\n");
    printf("***IKEA words found in the dictionary.txt file:***\n");
    // Calling the function that compares the ikea file to dictionary.
    CompareIKEAToDictionary(dictionary, IKEAwords);
    printf("---------------------End Stage 1 ----------------------------\n");
    // End of the stage 1 output.

	// The start of stage 2 output.
    printf("----------------------Stage 2 -------------------------------\n");
    printf("***IKEA words found in the inputfile.txt file:***\n");
    // Calling the function to compare the IKEA words and the input file.
    CompareInputToIKEA(IKEAwords, InputWords, NumberOfWordsInInputFile);
    printf("\n----------------------End Stage 2 ---------------------------\n");
    // End of stage 2.


}//end main()


/* This function is provided by Professor Reed. The function will pass the word from the input file and remove
   leading or trailing puntuation from the word. Credit to Dale Reed */

void removeLeadingAndTrailingPunctuation(char theWord[])
{
    // Make a copy of the word
    char wordCopy[MaxWordSize];
    // Counter for the for loop.
    int i;
    // for loop to make a copy of the array.
    for(i=0; i<strlen(theWord); i++) {
        wordCopy[ i] = theWord[ i];
    }

    // Find first non punctuation character
    i=0;
    while(ispunct( wordCopy[ i])) {
        i++;}

    // Copy over the rest of the word
    int j=0;  // Set the destination index to start at the beginning of the word
    for( ; i<strlen( theWord); i++) {
        theWord[ j] = wordCopy[ i];
        j++;
    }
    // null terminate the word
    theWord[ j] = '\0';

    // Repeatedly overwrite trailing punctuation characters with nulls
    // Cast into (int) to avoid warning of "implicit loss of precision"
    i = (int)strlen( theWord) - 1;   // Set index to the last character in the word
    while( i>=0 && ispunct(theWord[ i])) {
        theWord[ i] = '\0';
        i--;
    }// End of while loop.
}// End of function.

/* The purpose of this function is to read the words from the dictionary and
   passing the dictionary and 2D array for the dictionary as parameters. It
   will check to see if the file can be open, read the words, and close the file. */

void readWordsInFromDictionaryFile(FILE *pDictionaryFile, char dictionary[ ][ MaxWordSize])
{
    // Index of dictionary word being read.
	int index = 0;

    // Associate the actual file name with file pointer and try to open it.
    pDictionaryFile = fopen(DictionaryFileName, "r");
    // Verify that file open if not then it gives user an error message.
    if (pDictionaryFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", DictionaryFileName);
        exit(-1);
    }

    // Keep reading words while until it reaches the end.
    while(fscanf(pDictionaryFile, "%s", dictionary[index]) != EOF) {
    	// Increment for the index.
        index++;
    }

	// Close the dictionary file.
    fclose(pDictionaryFile);

}// End readWordsInFromDictionaryFile()


/* The purpose of this function is to read the words from the IKEA File and
   passing the IKEA File and 2D array for the IKEA File as parameters. It
   will check to see if the file can be open, read the words, and close the file. */

void readWordsInFromIKEAFile(FILE *pIKEAFile, char IKEAwords[ ][MaxWordSize])
{
    // Index of IKEA word being read
	int index = 0;

    // Associate the actual file name with file pointer and try to open it.
    pIKEAFile = fopen(IKEAFileName, "r");
     // Verify that file open if not then it gives user an error message.
    if (pIKEAFile == NULL) {
        printf("Can't open %s. Verify it is in correct location\n", IKEAFileName);
        exit(-1);
    }

    // Keep reading words until it reaches the end.
    while(fscanf(pIKEAFile, "%s", IKEAwords[index]) != EOF) {
    	//Increment for the index of the words.
        index++;
    }
    // Closes file.
    fclose(pIKEAFile);

}// End readWordsInFromIKEAFile()


/* The purpose of this function is to read the words from the Input File and
   passing the Input File and 2D array for the Input File as parameters. It
   will check to see if the file can be open, read the words, and close the file. */

void readWordsInFromInputFile(FILE *pInputFile, char Inputwords[ ][ MaxWordSize])
{
	// Index of dictionary word being read
    int index = 0;

    // Associate the actual file name
    pInputFile = fopen(InputFileName, "r");

    // Keep reading words until it reaches the end.
    while( fscanf(pInputFile, "%s", Inputwords[ index]) != EOF) {
    	// Increments the index.
        index++;
    }
    // Closes the file when done.
    fclose(pInputFile);

}//End readWordsInFromInputFile()



