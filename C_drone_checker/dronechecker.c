// 6522056 zy22056 Xiangjun Peng

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>


#define MAX_LINE_NUM 1024
// As for the visualization, we take 1024 as the greatest number 
// of the characters in one line. But actually it's unlimited.
// Of course, u can change it for more complex tests.

struct list_point{
  int x,y;
  struct list_point *next;
};

struct list_circle{
  int a,b,r;
  struct list_circle *next;
};

typedef struct list_point LPoint;
typedef struct list_circle LCircle;

LPoint *start_point,*next_point;
LCircle *start_circle,*next_circle;

// A procedure call for prompt when the program is
// unable to reallocate memory

void Unable_To_Reallocate(){

  printf("Unable to allocate memory.\n");
  exit(5);

}

// A procedure call for global variables' initialization

void Global_Variable_Initialization(){
  
  start_point = malloc(sizeof(LPoint));
  if (start_point == NULL) Unable_To_Reallocate();
 
  next_point = start_point;
     
  start_circle = malloc(sizeof(LCircle));
  if (start_circle == NULL) Unable_To_Reallocate();
 
  next_circle = start_circle;

  return;  

}

// A function to return a number which is from the string target

int Str_To_Int(char* target){

  int result = 0, i, factor = 1, len = (int) strlen(target);
  for (i = len-1; i >= 0; i--)

    if ((target[i]<=57) && (target[i]>=48)){  

      result += factor * (target[i] - 48);
      factor *= 10; 

    } 

  return result; 
 
}

// A function to return the counter that this string target contains
// how many numbers. if there is one number greater than 9999, return -1

int Valid_Number_Counter(char* target){

  int counter = 0, len = strlen(target), position = 0,i = 0;

  for (i = 0; i< len; i++){

    if ((target[i] <= 57) && (target[i]>=48)){
 
      counter++;
      position = i;

      while ((target[i] <= 57) && (target[i]>=48)) i++;

      if ((i-position) > 4) return -1;

    }

  }

  return counter;

}

// A procedure call to combine all continuous spaces into one space
// in string target.

void Trim(char *target, char *result){

  int j = 0, len = strlen(target);
  for (int i = 0; i < len; i++){

    if (target[i] != ' ') {

      result[j] = target[i];   
      j++;

    } else {

      result[j] = ' ';
      j++;
      while ((target[i] == ' ')&&(i<len)) i++;
      i--;

    }
  }

  return;

}

// A procedure call to append the data into the corresponding list

int List_appends(char* line_trim, int num){

    char x[4],y[4],ra[4];
    int point_x, point_y, r;

    sscanf(line_trim, "%s %s %s", x, y, ra);

    point_x = Str_To_Int(x);
    point_y = Str_To_Int(y);
    if (num == 2) {

      next_point->x = point_x;
      next_point->y = point_y;
      next_point-> next = malloc(sizeof(LPoint));
      if (next_point->next == NULL) Unable_To_Reallocate();
      next_point = next_point -> next; 

    } else {
    
      r = Str_To_Int(ra);
      if (r == 0) return 1;

      next_circle->a = point_x;
      next_circle->b = point_y;
      next_circle->r = r;
      next_circle-> next = malloc(sizeof(LCircle));
      if (next_circle->next == NULL) Unable_To_Reallocate();
      next_circle = next_circle -> next; 
            
    }
  
  return 0;

}

// A procedure call for list destroy

void List_Destroy(){

  next_point = start_point;
  start_point = NULL;

  LPoint *next;

  while (next_point != NULL){
  
    next = next_point->next;
    free(next_point);
    next_point = next;

  }
  
  free(next_point);
  next_point = NULL;

  next_circle = start_circle;
  start_circle = NULL; 
 
  LCircle *nextC;

  while (next_circle != NULL){

    nextC = next_circle->next;  
    free(next_circle);
    next_circle = nextC;

  }

  free(next_circle);
  next_circle = NULL;

  return ;

}

/* In order to decrease the possibility of faults, I tried to
   use the one-time file processing, which means I need to do 
   the valid file checking and data structing meanwhile        */

// A procedure call which checks the file line by line, if it's valid so append
// the data into the corresponding list. Once there is any invalid line,
// empty the dynamic memory and exit with appropriate numbers

void File_ValidCheck_DataStructing(int num, char* argv[]){

    FILE *valid_check;
    int comparison, valid=0, determine = 0;
    char prompt[25]; 

    if (num == 1) {
 
       comparison = 3; 
       strcpy(prompt,"No-fly zone file invalid.");

    } else {

       comparison = 2;    
       strcpy(prompt, "Flight plan file invalid.");

    }   

    char *line = (char *) malloc(sizeof(char) * MAX_LINE_NUM);
    if (line == NULL) Unable_To_Reallocate();

    char *line_trim_previous = (char *) malloc(sizeof(char) * MAX_LINE_NUM);
    if (line_trim_previous == NULL) { 
       free(line); 
       line=NULL;
       Unable_To_Reallocate();
    }

    strcpy(line_trim_previous,"");

    valid_check = fopen(argv[num],"r");
    // Having checked in advance, so we ignore this checking process

    while (!feof(valid_check)){

      fgets(line, MAX_LINE_NUM, valid_check);

      if (feof(valid_check)) break;
        
      if ((line[0] !='#')&&(line[0]!='\n')) {

        // Check the non-comment line's elements. If one of them is not a number, space or '\n',
        // this line must be invalid. 

        for (int i = 0; i < strlen(line)-1; i++){

          if (!(((line[i]<=57)&&(line[i]>=48))||(line[i]==' ')||(line[i]=='\n'))) {
 
	     free(line);
	     line = NULL;
             free(line_trim_previous);
             line_trim_previous = NULL;
             List_Destroy();
             fclose(valid_check);

             printf("%s\n",prompt); 
             exit(num + 1);
            
          }
        } 

        // Once passed last check process, there are just spaces, numbers and '\n', which can guarantee
        // no negative number here. So we don't need a double-check in the StrToInt function call.

        char *line_trim = (char *) malloc(sizeof(char) * sizeof(line));
        if (line_trim == NULL) {

          free(line);
          line = NULL;
          free(line_trim_previous);
          line_trim_previous = NULL;
          List_Destroy();
          Unable_To_Reallocate();

        }

        strcpy(line_trim,""); 
        Trim(line, line_trim);

        // After trim procedure, compare the previous line and the line now to make sure there is not two consecutive
        // points in flight plan file. Then check if there is any space before the data and if there are appropriate 
        // valid number in corresponding file. If not, exit with appropriate number.

        if (((strcmp(line_trim_previous,line_trim) == 0)&&(num == 2))||
            ((line_trim[0] == ' ')||
            (Valid_Number_Counter(line_trim) != comparison))|| 
            (line_trim[strlen(line_trim)-2] == ' ')){

           free(line);
           line = NULL;
           free(line_trim_previous);
           line_trim_previous = NULL;
           free(line_trim);
           line_trim = NULL;
           List_Destroy();
           fclose(valid_check);
           printf("%s\n",prompt); 
           exit(num + 1);

        }

        strcpy(line_trim_previous, line_trim);

        // After checking, this line is valid so far, so append it into the list

        valid++; 
        determine += List_appends(line_trim, num);

        free(line_trim); 
        line_trim = NULL;

      }
  }

  // In addition, flight plan needs to have at least two valid point pairs. So
  // I check this here.

  if (((num == 2)&&(valid < 2)) || (determine > 0)) {
 
    free(line);
    line = NULL;
    free(line_trim_previous);
    line_trim_previous = NULL;
    List_Destroy();
    fclose(valid_check);   

    printf("%s\n",prompt);
    exit(num + 1);      
  
  }

  free(line_trim_previous);
  line_trim_previous = NULL;
  free(line);
  line = NULL;
  fclose(valid_check);

  return;

}

// A procedure call to check the command line arguments and if the file can be opened

void File_Check(int argc, char *argv[]){

  if (argc != 3) {

    printf("Invalid command line arguments. Usage: <noflyzones> <flightplan>\n");

    exit(1);

  } else {

    for (int i = 1; i <= 2; i++){

      FILE *fp;
      fp = fopen(argv[i],"r");
      if (fp == NULL) {

        char *prompt;
        prompt = (char *) malloc(sizeof(char) * MAX_LINE_NUM);
        if (prompt == NULL) Unable_To_Reallocate();

        strcpy(prompt, "Cannot open ");
        strcat(prompt, argv[i]);
        strcat(prompt, " file. ");

        perror(prompt);
        free(prompt);
        prompt = NULL;

        exit(1);

      }

      fclose(fp);
    }  
  }

  return ;  

}

// A function call to calculate and return the value of the distance between two points (x,y) and (a,b)

float Distance_Cal(int x, int y, int a, int b){
  
  return sqrt(pow(x-a,2)+pow(y-b,2));

}

// A function call to determine if point x or point y is in this circle r.
// If either of them or both of them be, return 1. Otherwise, return 0.

int inCircle(LPoint *x, LPoint *y, LCircle *r){

  if ((Distance_Cal(x->x,x->y,r->a,r->b) <= r->r) || (Distance_Cal(y->x,y->y,r->a,r->b) <= r->r)) 

    return 1;

  else

    return 0;

}

// A function call to use the formula to determine if the segment line from point x
// to point y intersects the circle r. If it does, return 1. Otherwise, return 0.

/* Particularly, it's neccesary to satisfy that this segment line is not in the circle r.
   The program has to check it in advance.                                               */

int Det_By_Discrim(LPoint *x, LPoint *y, LCircle *r){

  long int X = 0, Y = 0, Z = 0;

  X = (x->x)*(x->x) - (2*(x->x)*(y->x)) + (y->x)*(y->x) + (x->y)*(x->y) - (2*(x->y)*(y->y)) + (y->y)*(y->y);
 
  Y = (2*(r->a)*(y->x)) - (2*(r->a)*(x->x)) - (2*(r->b)*(x->y)) + (2*(r->b)*(y->y)) + (2*(x->x)*(y->x)) + (2*(x->y)*(y->y)) - (2*(y->x)*(y->x)) - (2*(y->y)*(y->y));

  Z = (r->a)*(r->a) - (2*(r->a)*(y->x)) + (r->b)*(r->b) - (2*(r->b)*(y->y)) - (r->r)*(r->r) + (y->x)*(y->x) + (y->y)*(y->y);
  
  long int Discrim = 0;

  Discrim = Y*Y - (4*X*Z);

  if (Discrim < 0) { 

    return 0;

  }  else {

    float t_greater = 0, t_less = 0;

     t_greater = (float) ( (-Y)+sqrt(Discrim) ) / (2*X);
     t_less = (float) ( (-Y)-sqrt(Discrim) ) / (2*X);

     if (((t_greater >= 0)&&(t_greater <= 1)) || ((t_less >= 0)&&(t_less <= 1))) {
       
       return 1;
     
     } else {
  
       return 0;

     }
  }

}

//A procedure call to have a sort for the circle list. Which use the distance of 
//the start point minus the radius and have a sort. to make sure that the circles
//are listed from the closest to the farest according to the start point.

void List_Sort(LPoint *start){

  LCircle *close_next, *min_next;
  close_next = start_circle;

  while (close_next->next != NULL){

    min_next = close_next->next;   
    
    while (min_next-> next != NULL){  
 
      if ((Distance_Cal(start->x, start->y, min_next->a, min_next->b)-min_next->r) <=
          (Distance_Cal(start->x, start->y, close_next->a, close_next->b)-close_next->r)){

        int a = 0, b = 0, r = 0;

        a = close_next->a; close_next->a = min_next->a; min_next->a = a;
        b = close_next->b; close_next->b = min_next->b; min_next->b = b;
        r = close_next->r; close_next->r = min_next->r; min_next->r = r;

      }

      min_next = min_next->next;

    }

    close_next = close_next->next; 
  

  }

  close_next = NULL;
  min_next = NULL;

  return;

}

// A procedure call to check if this flight plan is valid.

void If_FlightPlan_Valid(){

  next_point = start_point;

  while (next_point->next != NULL){

    List_Sort(next_point);
    // Sorted based on the distance due to the start point, 
    // details are in the function

    next_circle = start_circle;

    while (next_circle->next != NULL){

      if (( ((inCircle(next_point, next_point->next, next_circle)==0))&&
           (Det_By_Discrim(next_point, next_point->next, next_circle)==1) )
	  ||(inCircle(next_point, next_point->next, next_circle)==1)) {

	  printf("Invalid flight plan.\n");
          printf("Enters restricted area around %d,%d.\n", next_circle->a, next_circle->b);

          List_Destroy();

          exit(4);

      }
  
      next_circle = next_circle->next;

    }  

    next_point = next_point->next;

  }  

  printf("Valid flight plan.\n");

  return ;

}

int main(int argc, char *argv[]){

  File_Check(argc,argv);

  Global_Variable_Initialization();

  File_ValidCheck_DataStructing(1,argv);
  
  File_ValidCheck_DataStructing(2,argv);

  If_FlightPlan_Valid(); 

  List_Destroy();

  return 0;

}
