

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>


#define MAX_LINE_NUM 10000

int valid_number_counter(char *target){

  int counter = 0, len = strlen(target);

  for (int i = 0; i< len; i++){

    if ((target[i] <= 57) && (target[i]>=48)){
       
      counter++;

      while ((target[i] <= 57) && (target[i]>=48)) i++;
    }

  }

  return counter;

}

void trim(char *target,char *result){

  int j = 0, len = strlen(target);

  for (int i = 0; i < len; i++){

    if (target[i] != ' ') {

      result[j] = target[i];
      
      j++;

    } else {

      result[j] = ' ';

      j++;

      while (target[i] == ' ') i++;

      i--;

    }
  }

  if (result[0] == ' ') { 

     for (int i = 1; i < j; i++) 

       result[i-1]=result[i];  }

   result[j] = '\0';

  

  return;
}

void FileValidCheck(int num, char* argv[]){

    FILE *valid_check;

    int comparison;

    char prompt[25]; 

    if (num == 1) {
 
       comparison = 3; 

       strcpy(prompt,"No-fly zone file invalid.");

    } else {

       comparison = 2;

       strcpy(prompt, "Flight plan file invalid.");

    } 

    char *line = (char *) malloc(sizeof(char) * MAX_LINE_NUM);

    valid_check = fopen(argv[num],"r");

    while (!feof(valid_check)){

        fgets(line, MAX_LINE_NUM, valid_check);
        
        if ((line[0] !='#')&&(strlen(line)!=0)) {

          for (int i = 0; i < strlen(line)-1; i++){

	    if (!(((line[i]<=57)&&(line[i]>=48))||(line[i]==' ')||(line[i]=='\n'))) { 

	       printf("%s\n",prompt); 

               exit(3);
            
            }
	  } 

          char *line_trim = (char *) malloc(sizeof(char) * sizeof(line));

          trim(line, line_trim);

          if ((valid_number_counter(line_trim) != comparison)&&(valid_number_counter(line_trim) != 0)&&(strlen(line_trim)!=0)) {

	      printf("%s\n",prompt);

	      exit(3);

          }

          free(line_trim);

        }
    }
 
    free(line);

    fclose(valid_check);

    return;

}

void FileCheck(int argc, char *argv[]){

  if (argc != 3) {

    printf("Invalid command line arguments. Usage: <noflyzones> <flightplan>\n"); 

    exit(1);

  } else {

    for (int i = 1; i <= 2; i++){
 
      if ( access(argv[i], F_OK) == -1 ){
  
        printf("File %s doesn't exist!\n",argv[i]);

        exit(1);

      } else if (access(argv[i], R_OK) == -1 ){

        printf("File %s doesn't have read permission!\n",argv[i]);
  
        exit(1);

      }
    }
 
    FileValidCheck(1,argv);

    FileValidCheck(2,argv);

    return ;
  
  }

  return;  

}

int StrToInt(char target[], int len){

  int result = 0, i, factor = 1;

  for (i = len-1; i >= 0; i--){

    if ((target[i]<=57)&&(target[i]>=48)){  
   
     result += factor * (target[i] - 48);

     factor *= 10;
   
    } else 

      return -1;
  
  }

  return result;  

}

float DistanceCal(int x, int y, int a, int b){

  return sqrt(pow(x-a,2)+pow(y-b,2));

}

int inCircle(int x,int y, int n, int m, int a, int b, int r){

  if ((DistanceCal(x,y,a,b) <= r) && (DistanceCal(x,y,n,m) <= r)) 

    return 1;

  else

    return 0;

}

int DetByDiscrim(int x_A, int y_A, int x_B, int y_B, int x_C, int y_C, int r){

  long int X, Y, Z;

  X = x_A * x_A - (2 * x_A * x_B) + x_B * x_B + y_A * y_A - (2 * y_A * y_B) + y_B * y_B;
 
  Y = (2 * x_C *x_B) - (2 * x_C * x_A) - (2 * y_C * y_A) + (2 * y_C * y_B ) + (2 * x_A * x_B ) - (2 * y_A * y_B) - (2 * x_B * x_B ) - (2 * y_B * y_B );

  Z = x_C * x_C - (2 * x_C * x_B) + y_C * y_C - (2 * y_C * y_B) - r * r + x_B * x_B + y_B * y_B;   
  

  long int Discrim;

  Discrim = Y * Y - ( 4 * X * Z );

  if ( Discrim < 0 ) { 

    return 0;

  }  else {

     float t_greater, t_less;

     t_greater = (( - Y ) + sqrt(Discrim)) / ( 2 * X );

     t_less = (( - Y ) - sqrt(Discrim)) / ( 2 * X );

     if ( ( ( t_greater >= 0 ) && ( t_greater <= 1) ) && ( ( t_less >= 0 ) && ( t_less <= 1) ) ) {

       return 1;
     
     }
  
     return 0;

  }


}

int main(int argc, char *argv[]){

  FileCheck(argc,argv);

  FILE  *fp_flightplan;

  int A_X, A_Y, B_X, B_Y;

  fp_flightplan = fopen(argv[2], "r");

  int valid_input_counter = 0;

  while ( !feof(fp_flightplan) ) {

    char x[4],y[4];

    fscanf(fp_flightplan, "%s %s", x,y);

    char *next_line;

    next_line = (char *) malloc(sizeof(char) * MAX_LINE_NUM);

    fgets(next_line, MAX_LINE_NUM, fp_flightplan);

    free(next_line);

      if ( (x[0] >= 48) && (y[0] <= 57) ) {          

       valid_input_counter++; 

       if (valid_input_counter == 1) { 

         B_X = StrToInt(x,strlen(x));

         B_Y = StrToInt(y,strlen(y));
   
       } else {

	 // printf("%d %d %d %d\n", A_X, A_Y, B_X, B_Y);

         A_X = B_X;

         A_Y = B_Y;

         B_X = StrToInt(x,strlen(x));

         B_Y = StrToInt(y,strlen(y));

         if ((A_X == B_X) && (A_Y == B_Y)) break;
         
         FILE *fp_nofly;

         fp_nofly = fopen(argv[1], "r");

         while ( !feof(fp_nofly) ) {

           char R_x[4], R_y[4], R[4];

           int r_x, r_y, r;

           fscanf(fp_nofly, "%s %s %s", R_x, R_y, R);

           next_line = (char *) malloc(sizeof(char) * MAX_LINE_NUM);

           fgets(next_line, MAX_LINE_NUM, fp_nofly);

           free(next_line);

	     if ( (R_x[0] >= 48) && (R_x[0] <= 57) ) {

             r_x = StrToInt(R_x, strlen(R_x));

             r_y = StrToInt(R_y, strlen(R_y));

             r = StrToInt(R, strlen(R));

             if ((inCircle(A_X,A_Y,B_X,B_Y,r_x,r_y,r) == 1)) {

	       fclose(fp_nofly);

               fclose(fp_flightplan);

                printf("Invalid flight plan.\n");

                printf("Enter restricted area around %d,%d.\n",r_x,r_y);

                exit(4);

             } else{

               if (DetByDiscrim(A_X,A_Y,B_X,B_Y,r_x,r_y,r) == 1) {

		fclose(fp_nofly);

                fclose(fp_flightplan);

                printf("Invalid flight plan.\n");

                printf("Enter restricted area around %d,%d.\n",r_x,r_y);

                exit(4);

               }
               
             }
	    } 

         }

     fclose(fp_nofly);    

     }          

   }
  
  }
  

  fclose(fp_flightplan);

  printf("Valid flight plan.\n");


  return 0;

}
