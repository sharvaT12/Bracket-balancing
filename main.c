//
//  CS-211 Project 2
//  Sharva Thakur
//  Uin: 654135206
//

//  This project takes input and compares all the brackets and finds if the brackets is balanced or not. If they are not balanced this points towards the error and what is expected there.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TRUE  1
#define FALSE 0

int DebugMode;

typedef struct stack{
 char*   item;  /* pointer to dynamic array  */
 int     current_size;  /* amount of space allocated */
 int     top; /* top of stack indicator 
		   - counts how many values are on the stack   */
} stack;

//  This function initalizes a stack with size 2 and top pointing towards -1
void init(stack* s){
    s->current_size = 2;
    s->item = (char*)malloc(sizeof (char) * s->current_size );
    s->top  = -1;
}

//  This function checks if the stack is empty or not
int is_empty(stack* s){
    if ( s->top == -1)
        return TRUE;
    else
        return FALSE;
}

//  This function increases the size of the dynamically allocated array stack->items
static void increase_size(stack* s){
    char* temp; 
    temp = malloc(s->current_size*2*sizeof(char));
    int copied =0;
    for(int i = 0; i < s->current_size; i++){
        temp[i] = s->item[i]; // copying the elements to new array
        copied ++;
    }
    if(DebugMode == TRUE){  // debug command
        printf("The size of the array is being increased from old size %d to new size %d, total elements copied are %d\n",s->current_size,s->current_size*2,copied);
    }

    s->current_size = s->current_size * 2; // increase size
    free(s->item); // frees the temporary array
    s->item = temp;
}

//  This function pushes each element into stack and increases the top by one. if the array is full this calls resize and doubles the size.
void push(stack* s, char c){
    if(DebugMode == TRUE){
        printf("The element being pushed is %c \n",c);
    }

    if(s->top >= s->current_size -1){
         increase_size(s);
    }
    s->top = s->top + 1;
    s->item[s->top] = c;
}

//  This function removes the top element from the array and reduces the top by 1.
void pop(stack* s){
    if(s->top == -1){ //  if the array is empty
        abort();
    }
    if(DebugMode == TRUE){  //  debug command
        printf("The element being popped is %c \n",s->item[s->top]);
    }
    s->top = s->top - 1;
}


// This function returns the top elemnt
char top(stack* s){
    return(s->item[s->top]);
}


// This functions frees the dynamically allocated array and clears the stack.
void clear(stack* s){
    free(s->item);
    init(s);

}

// This functiom checks if the input is opening braces
int is_opening(char a){
    switch(a){
    case '{': return 1;
    case '[': return 1;
    case '<': return 1;
    case '(': return 1;
  }
    return -1;
}

// This functiom checks if the input is closing braces
int is_closing(char a){
    switch(a){
    case '}': return 1;
    case ']': return 1;
    case '>': return 1;
    case ')': return 1;
  }
    return -1;
}


// This functiom returns the opening braces to the corresponding closing braces
char curr_brac_opening(char a){
    switch(a){
    case '}': return'{';
    case ']': return '[';
    case '>': return '<';
    case ')': return '(';
  }
  return 'n';
}

// This functiom returns the closing braces to the corresponding opening braces
char curr_brac_closing(char a){
    switch(a){
    case '{': return'}';
    case '[': return ']';
    case '<': return '>';
    case '(': return ')';
  }
  return 'n';
}

// This function process the data
void process(stack* s, char* input,int i){

    char comp; 
    int count = 0;
    int tracker = 0;

    while (count < i){ // to the end of input
        if (is_opening(input[count]) == 1){ // checks if char is opening braces
            push(s,input[count]);  // pushes the element
        }
        else if (is_closing(input[count]) == 1){ // checks if char is closing braces    
            char st = curr_brac_opening(input[count]); 
            
            if(s->top == -1){ // if closing bracker appears before oepning bracket
                printf("Unbalanced expression, Error 1: Missing opening symbol\n");
                printf ("%s\n", input);
                comp = curr_brac_opening(input[count]);
                for(int i = 0; i < tracker; i++){
                    printf(" ");
                }
                printf("^ missing %c\n",comp);
                return;
            }


            if(st == s->item[s->top]){ // if opening and closing brackets are correct
                pop(s);
            }
            else{
                printf("Unbalanced expression, Error 2: Expecting different closing symbol\n");
                printf ("%s\n", input);
                comp = curr_brac_closing(s->item[s->top]);
                for(int i = 0; i < tracker; i++){
                    printf(" ");
                }
                printf("^ expecting %c\n",comp);
                return;
            }
        }
        tracker++;
        count ++;
    }

    if(is_empty(s)){ // checks if the equation is balanced
        printf ("%s\n", input);
        printf("Expression is balanced\n");
        return;
    }
    else{ // if not balanced
        printf("Unbalanced expression. Error 3: missing closing symbol\n");
        printf ("%s\n", input);
        for(int i = 0; i < tracker; i++){
            printf(" ");
        }
        comp = curr_brac_closing(s->item[s->top]);
        printf("^ missing %c\n",comp);
        return;
    }
}

//main
int main (int argc, char** argv)
{
 char input[301];
 stack s; 
 init(&s);


 /* check for command line argument of -d */
 DebugMode = FALSE;
 int i;
 for ( i = 0; i < argc; i++)
    if ( strcmp (argv[i], "-d") == 0)
       DebugMode = TRUE;

 /* set up an infinite loop */
 while (1)
 {

   /* get line of input from standard input */
   printf ("\nEnter input to check or q to quit\n");
   fgets(input, 300, stdin);

   /* remove the newline character from the input */
   int i = 0;
   while (input[i] != '\n' && input[i] != '\0')
   {
      i++;

   }
   input[i] = '\0';

   /* check if user enter q or Q to quit program */
   if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
     break;
 
   
    
    process(&s, input,i);  
    
   /* run the algorithm to determine is input is balanced */
    
    clear(&s);
 }
  
 printf ("\nGoodbye\n");
 return 0;
}
