/*
Name: Manan Patel
UIN: 658283328
description abot the project: The project is creating a program that, with the help of a dictionary, determines the shortest word ladder between two specified words. A word ladder is a list of words where each word is a different dictionary word and differs from the preceding word by one letter. The application utilizes linked lists to investigate ladder pathways, reads the dictionary, and maintains word data. Offering an entertaining and informative wordplay and programming experience, it engages the user by asking them to enter two words. An algorithm is then used to determine the shortest word ladder that connects the two words.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct WordNode_struct {
    char* myWord;
    struct WordNode_struct* next; 
} WordNode;

typedef struct LadderNode_struct {
    WordNode* topWord;
    struct LadderNode_struct* next; 
} LadderNode;

int countWordsOfLength(char* filename, int wordSize) { 
    //---------------------------------------------------------
    // TODO - write countWordsOfLength()    
    //      open a file with name <filename> and count the 
    //      number of words in the file that are exactly 
    //      <wordSize> letters long, where a "word" is ANY set
    //      of characters that falls between two whitespaces 
    //      (or tabs, or newlines, etc.). 
    //          return the count, if filename is valid
    //          return -1 if the file cannot be opened
    //---------------------------------------------------------
    
    FILE* file=fopen(filename,"r");  //opens the file
    if (file==NULL) //checking if the file is NULL or not
    {
        return -1;
    } 

    int count=0;
    char word[100];

    while(fscanf(file,"%s",word)!=EOF)  //Read words from the file until the end of the file (EOF) is reached
    {
        if(strlen(word)==wordSize)  // Check the length of the current word
        {
            count++;  //increments the count
        }
    }

    fclose(file);  //closes the file
    return count; //returns count 
}

bool buildWordArray(char* filename, char** words, int numWords, int wordSize) { 
    //---------------------------------------------------------
    // TODO - write buildWordArray()    
    //      open a file with name <filename> and fill the 
    //      pre-allocated word array <words> with only words
    //      that are exactly <wordSize> letters long;
    //      the file should contain exactly <numWords> words 
    //      that are the correct number of letters; thus, 
    //      <words> is pre-allocated as <numWords> char* ptrs, 
    //      each pointing to a C-string of legnth <wordSize>+1;
    //          return true iff the file is opened successfully
    //                      AND the file contains exactly 
    //                      <numWords> words of exactly 
    //                      <wordSize> letters, and those words
    //                      are stored in the <words> array
    //          return false otherwise
    //---------------------------------------------------------
    
    FILE* file=fopen(filename,"r");  //opens the file
    if(file==NULL)  //checks if the file is null or not
    {
        return false; // Failed to open the file
    }
    int wordsFound=0;
    char word[100];  //reads words from the file

    while(!feof(file))
    {
        fscanf(file,"%s",word);
        if(strlen(word)==wordSize)
        {
            if(wordsFound>=numWords)
            {
                fclose(file);
                return false;
            }
            strcpy(words[wordsFound],word);
            wordsFound++;
        }
    }
    fclose(file);
    if(wordsFound==numWords)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int findWord(char** words, char* aWord, int loInd, int hiInd) { 
    //---------------------------------------------------------
    // TODO - write findWord()
    //          binary search for string <aWord> in an 
    //          alphabetically sorted array of strings <words>, 
    //          only between <loInd> & <hiInd>
    //              return index of <aWord> if found
    //              return -1 if not found b/w loInd & hiInd
    //---------------------------------------------------------
    while(loInd<=hiInd) 
    {
        int mid=loInd+(hiInd-loInd)/2;
        int compareResult=strcmp(words[mid],aWord);

        if(compareResult==0) 
        {
            return mid;  // Word found at index 'mid'
        } 
        else if(compareResult<0) 
        {
            loInd=mid+1;  // Word may be in the right half
        } 
        else 
        {
            hiInd=mid-1;  // Word may be in the left half
        }
    }
    return -1;  // Word not found
}

void freeWords(char** words, int numWords) {
    //---------------------------------------------------------
    // TODO - write freeWords()
    //          free up all heap-allocated space for <words>,
    //          which is an array of <numWords> C-strings
    //           - free the space allocated for each C-string 
    //           - then, free the space allocated for the array
    //                  of pointers, <words>, itself
    //---------------------------------------------------------
    for(int i=0;i<numWords;i++)  //loop through numWords
    {
        free(words[i]);  //frees the array words
    }
    free(words);  //free words
}

void insertWordAtFront(WordNode** ladder, char* newWord) {
    //---------------------------------------------------------
    // TODO - write insertWordAtFront()
    //          allocate space for a new [WordNode], set its 
    //          [myWord] subitem using <newWord> and insert
    //          it to the front of <ladder>, which is a 
    //          pointer-passed-by-pointer as the head node of 
    //          ladder changes inside this function; 
    //          <newWord> is a pointer to a C-string from the 
    //          full word array, already heap-allocated
    //---------------------------------------------------------
    WordNode* newNode=(WordNode*)malloc(sizeof(WordNode));  //assigns a new memory block 
    newNode->myWord=newWord;
    newNode->next=*ladder;
    *ladder=newNode; // Update the ladder to point to the new node
}

int getLadderHeight(WordNode* ladder) {
    //---------------------------------------------------------
    // TODO - write getLadderHeight()
    //          find & return number of words in <ladder> list
    //---------------------------------------------------------
    int height=0;
    WordNode* current=ladder;  // Start at the beginning of the ladder

    while(current!=NULL)  //loop check through current gets null 
    {
        height++;  //increment height in the ladder
        current=current->next;  //Move to the next word in the ladder
    }
    return height;
}

WordNode* copyLadder(WordNode* ladder) {
    //---------------------------------------------------------
    // TODO - write copyLadder()
    //          make a complete copy of <ladder> and return it;
    //          the copy ladder must have new space allocated
    //          for each [WordNode] in <ladder>, BUT the
    //          C-string pointers to elements of the full word  
    //          array can be reused; i.e. the actual words do 
    //          NOT need another allocation here
    //---------------------------------------------------------
    WordNode* copiedLadder=NULL; // Initialize the copied ladder
    WordNode* tail=NULL;

    while(ladder!=NULL)
    {
        WordNode* newNode=(WordNode*)malloc(sizeof(WordNode));
        newNode->myWord=ladder->myWord;
        newNode->next=NULL;

        if(copiedLadder==NULL)  //checks if copied ladder is null or not
        {
            copiedLadder=newNode;  //Set the copied ladder to the first node
            tail=newNode;  //Set the tail to the first node
        }
        else
        {
            tail->next=newNode;  // Append the new node to the tail of the copied ladder
            tail=newNode;  // Update the tail to the new node
        }
        ladder=ladder->next;  // Move to the next node in the original ladder
    }
    return copiedLadder; // Return the copied ladder
}

void freeLadder(WordNode* ladder) {
    //---------------------------------------------------------
    // TODO - write freeLadder()
    //          free up all heap-allocated space for <ladder>;
    //          this does NOT include the actual words, 
    //          instead just free up the space that was 
    //          allocated for each [WordNode]
    //---------------------------------------------------------
    while(ladder!=NULL)
    {
        WordNode* current=ladder;  //store the current node
        ladder=ladder->next;  //move to the next node
        free(current);  //free the current node
    }
}

void insertLadderAtBack(LadderNode** list, WordNode* newLadder) {
    //---------------------------------------------------------
    // TODO - write insertLadderAtBack()
    //          allocate space for a new [LadderNode], set its 
    //          [topWord] subitem using <newLadder>; then, find
    //          the back of <list> and append the newly created
    //          [LadderNode] to the back; Note that <list> is a 
    //          pointer-passed-by-pointer, since this function 
    //          must handle the edge case where <list> is empty
    //          and the new [LadderNode] becomes the head node
    //---------------------------------------------------------
    LadderNode* newNode=(LadderNode*)malloc(sizeof(LadderNode));
    newNode->topWord=newLadder;
    newNode->next=NULL;

    if(*list==NULL) 
    {
        *list=newNode;  // If the list is empty, set the new node as the head
    } 
    else 
    {
        LadderNode* current=*list;  // Traverse the list to find the last node
        while(current->next != NULL)   //ckecks if node is null or not
        {
            current=current->next;
        }
        current->next=newNode;  // Append the new node to the end
    }
}

WordNode* popLadderFromFront(LadderNode** list) {
    //---------------------------------------------------------
    // TODO - write popLadderFromFront()
    //          pop the first Ladder from the front of the list
    //          by returning the pointer to the head node 
    //          of <list> AND updating the head node of <list>
    //          to the next [LadderNode]; Note that <list> is a 
    //          pointer-passed-by-pointer, since this function 
    //          updates the head node to be one down the list;
    //          the [LadderNode] popped off the front must have
    //          its memory freed in this function, since it 
    //          will go out of scope, but the ladder itself, 
    //          i.e. the head [WordNode], should NOT be freed. 
    //---------------------------------------------------------
    if(*list==NULL)
    {
        return NULL;
    }
    LadderNode* poppedLadder=*list;  // Store the head of the list
    *list=poppedLadder->next;  // Update the head to the next ladder
    WordNode* ladder=poppedLadder->topWord;  // Get the top word of the ladder
    free(poppedLadder);  //frees poppedLadder
    return ladder;
}

void freeLadderList(LadderNode* myList) {
    //---------------------------------------------------------
    // TODO - write freeLadderList()
    //          free up all heap-allocated space for <myList>;
    //          for each ladder in <myList>:
    //           - free the space allocated for each [WordNode] 
    //                  in the ladder using freeLadder()
    //           - then, free the space allocated for the 
    //                  [LadderNode] itself 
    //---------------------------------------------------------
    while(myList!=NULL)
    {
        LadderNode* current=myList;
        myList=myList->next;
        free(current->topWord); // Free the WordNode list
        free(current); // Free the LadderNode
    }
}

bool isNeighbor(const char* word1, const char* word2, int wordSize)  //made this extra function because it checks if two words are neighbors, which means they have exactly one differing character at the same position in the word.
{
    int diffCount=0;
    for(int i=0;i<wordSize;i++) 
    {
        if(word1[i]!=word2[i])   //If characters at the same position are different
        {
            diffCount++;  //Increment the difference count
            if(diffCount>1)   
            {
                return false;  // If more than one difference is found, return false
            }
        }
    }
    return diffCount==1;
}

WordNode* findShortestWordLadder(   char** words, 
                                    bool* usedWord, 
                                    int numWords, 
                                    int wordSize, 
                                    char* startWord, 
                                    char* finalWord ) {
    //---------------------------------------------------------
    // TODO - write findShortestWordLadder()
    //          run algorithm to find the shortest word ladder
    //          from <startWord> to <finalWord> in the <words>
    //          word array, where each word is <wordSize> long 
    //          and there are <numWords> total words;
    //          <usedWord> also has size <numWords>, such that
    //          usedWord[i] is only true if words[i] has 
    //          previously be entered into a ladder, and should
    //          therefore not be added to any other ladders; 
    //          the algorithm creates partial word ladders, 
    //          which are [WordNode] linked lists, and stores 
    //          them in a [LadderNode] linked list. 
    //              return a pointer to the shortest ladder;
    //              return NULL if no ladder is possible;
    //                  before return, free all heap-allocated 
    //                  memory that is created here that is not 
    //                  the returned ladder
    //---------------------------------------------------------
    LadderNode** ladders=(LadderNode**)malloc(numWords * sizeof(LadderNode*));   // Create an array of LadderNodes to store partial ladders
    for(int i=0;i<numWords;i++) 
    {
        ladders[i]=(LadderNode*)malloc(sizeof(LadderNode));  // Allocate memory for the current ladder node
        ladders[i]->topWord=(WordNode*)malloc(sizeof(WordNode));
        ladders[i]->topWord->myWord=startWord;
        ladders[i]->topWord->next=NULL;
        ladders[i]->next=NULL;
    }

    int startInd=0;  // Index of the ladder with the start word
    int rear=0;      // Index of the last ladder in the ladders array
    
    while(startInd<=rear)  // Loop to find the shortest ladder
    {
        LadderNode* currentLadder=ladders[startInd];
        WordNode* currentWord=currentLadder->topWord;

        if(strcmp(currentWord->myWord,finalWord)==0)
        {
            return currentLadder->topWord;   // If the current ladder reaches the final word, return it
        }

        for(int i=0;i<numWords;i++) 
        {
            if(!usedWord[i] && isNeighbor(currentWord->myWord, words[i],wordSize)) 
            {
                ladders[++rear]=(LadderNode*)malloc(sizeof(LadderNode));  // Create a copy of the current ladder and append the new word
                ladders[rear]->topWord=(WordNode*)malloc(sizeof(WordNode));
                ladders[rear]->topWord->myWord=words[i];
                ladders[rear]->topWord->next=copyLadder(currentLadder->topWord);
                ladders[rear]->next=currentLadder;
                usedWord[i]=true;
            }
        }
        startInd++;
    }
    
    return NULL;
}

// interactive user-input to set a word; 
//  ensures sure the word is in the dictionary word array
void setWord(char** words, int numWords, int wordSize, char* aWord) {
    bool valid = false;
    printf("  Enter a %d-letter word: ", wordSize);
    int count = 0;
    while (!valid) {
        scanf("%s",aWord);
        count++;
        valid = (strlen(aWord) == wordSize);
        if (valid) {
            int wordInd = findWord(words, aWord, 0, numWords-1);
            if (wordInd < 0) {
                valid = false;
                printf("    Entered word %s is not in the dictionary.\n",aWord);
                printf("  Enter a %d-letter word: ", wordSize); 
            }
        } else {
            printf("    Entered word %s is not a valid %d-letter word.\n",aWord,wordSize);
            printf("  Enter a %d-letter word: ", wordSize);
        }
        if (!valid && count >= 5) { //too many tries, picking random word
            printf("\n");
            printf("  Picking a random word for you...\n");
            strcpy(aWord,words[rand()%numWords]);
            printf("  Your word is: %s\n",aWord);
            valid = true;
        }
    }
}

// helpful debugging function to print a single Ladder
void printLadder(WordNode* ladder) {
    WordNode* currNode = ladder;
    while (currNode != NULL) {
        printf("\t\t\t%s\n",currNode->myWord);
        currNode = currNode->next;
    }
}

// helpful debugging function to print the entire list of Ladders
void printList(LadderNode* list) {
    printf("\n");
    printf("Printing the full list of ladders:\n");
    LadderNode* currList = list;
    while (currList != NULL) {
        printf("  Printing a ladder:\n");
        printLadder(currList->topWord);
        currList = currList->next;
    }
    printf("\n");
}


//-----------------------------------------------------
// The primary application is fully provided in main(); 
//  no changes should be made to main()
//-----------------------------------------------------
int main() {
    srand((int)time(0));
    
    printf("\nWelcome to the CS 211 Word Ladder Generator!\n\n");

    // set word length using interactive user-input
    int wordSize;
    printf("Enter the word size for the ladder: ");
    scanf("%d",&wordSize);
    printf("\n");

    printf("This program will make the shortest possible\n"); 
    printf("word ladder between two %d-letter words.\n\n",wordSize);
    
    // interactive user-input sets the dictionary file;
    //  check that file exists; if not, user enters another file
    //  if file exists, count #words of desired length [wordSize]
    char dict[100];
    printf("Enter filename for dictionary: ");
    scanf("%s", dict);
    printf("\n");
    int numWords = countWordsOfLength(dict,wordSize);
    while (numWords < 0) {
        printf("  Dictionary %s not found...\n",dict);
        printf("Enter filename for dictionary: ");
        scanf("%s", dict);
        printf("\n");
        numWords = countWordsOfLength(dict,wordSize);
    }
    
    // allocate heap memory for the word array; only words with desired length
    char** words = (char**)malloc(numWords*sizeof(char*));
    for (int i = 0; i < numWords; ++i) {
        words[i] = (char*)malloc((wordSize+1)*sizeof(char));
    }

    // end program if file does not have at least two words of desired length
    if (numWords < 2) {
        printf("  Dictionary %s contains insufficient %d-letter words...\n",dict,wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    
    // [usedWord] bool array has same size as word array [words];
    //  all elements initialized to [false];
    //  later, usedWord[i] will be set to [true] whenever 
    //      words[i] is added to ANY partial word ladder;
    //      before adding words[i] to another word ladder,
    //      check for previous usage with usedWord[i] 
    bool* usedWord = (bool*)malloc(numWords*sizeof(bool));
    for (int i = 0; i < numWords; ++i) {
        usedWord[i] = false;
    }
    
    // build word array (only words with desired length) from dictionary file
    printf("Building array of %d-letter words... ", wordSize); 
    bool status = buildWordArray(dict,words,numWords,wordSize);
    if (!status) {
        printf("  ERROR in building word array.\n");
        printf("  File not found or incorrect number of %d-letter words.\n",wordSize);
        printf("Terminating program...\n");
        return -1;
    }
    printf("Done!\n"); 

    // set the two ends of the word ladder using interactive user-input
    //  make sure start and final words are in the word array, 
    //  have the correct length (implicit by checking word array), AND
    //  that the two words are not the same
    char startWord[30];
    char finalWord[30];
    printf("Setting the start %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, startWord);
    printf("\n");
    printf("Setting the final %d-letter word... \n", wordSize);
    setWord(words, numWords, wordSize, finalWord);
    while (strcmp(finalWord,startWord) == 0) {
        printf("  The final word cannot be the same as the start word (%s).\n",startWord);
        printf("Setting the final %d-letter word... \n", wordSize);
        setWord(words, numWords, wordSize, finalWord);
    }
    printf("\n");

    // run the algorithm to find the shortest word ladder
    WordNode* myLadder = findShortestWordLadder(words, usedWord, numWords, wordSize, startWord, finalWord);

    // display word ladder and its height if one was found
    if (myLadder == NULL) {
        printf("There is no possible word ladder from %s to %s\n",startWord,finalWord);    
    } else {
        printf("Shortest Word Ladder found!\n");
        printLadder(myLadder);
    }
    printf("Word Ladder height = %d\n",getLadderHeight(myLadder));
    
    // free the heap-allocated memory for the shortest ladder
    freeLadder(myLadder);
    // free the heap-allocated memory for the words array
    freeWords(words,numWords);
    free(usedWord);
    
    return 0;
}
