#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <stdbool.h>
void turn();

//roundRobin(Int);
//SJF();
struct process{
  int arrival;
  int burst;
  int start;
  int finish;
  int waiting;
  bool running;
};

int arrivalCount;
FILE * fp;


int main( int argc, char ** argv){
  int timeSlice = 5; //given time slice
  int arrival[30] = {};//array of the input arival times, max 30
  int burst[30] = {}; //array of the input bursts, max 30
  arrivalCount = 0;//number of lines read from file
  int lines = 0;//number of lines needed to finish the simulation to output
  if( argc != 3 && argc !=2) {
     printf("Uasge: fine name, scheduling algorithm, time-slice");
     exit(-1);}
     
  fp = fopen ("config.txt", "r");
  
  //read in all of the arrivals and burst times into arrays
  int i = 0;
  while (fscanf(fp, "%d %d", &arrival[i], &burst[i]) > 0){i++;arrivalCount++;}
  //clsoe the input file
  fclose(fp);
  
  //count how many lines are needed for the simulation
  for (i=0; i<arrivalCount; i++)
   {
	 lines = lines + burst[i];
   }
  
  //create the structure array
  struct process procs[arrivalCount];
  int a;
  for(a = 0; a < arrivalCount; a++){
    procs[a].arrival = arrival[a];
    procs[a].burst = burst[a];
  } 
  //open output file
  fp = fopen ("output.txt", "w");
  
  //print out top row
  fprintf(fp, "%-10s", "Time");
  for(i = 0;i<arrivalCount;i++){
    fprintf(fp,"P%-9d",i);
  }
  fprintf(fp, "\n------------------------------\n");
  int j;
  //this will print out each line
  for(i = 0;i<=lines;i++){
    turn(procs, i);
  }

  
  //print out end of simulation line
  fprintf(fp, "\n------------------------------");
  
  for(i = 0;i<arrivalCount;i++){
    fprintf(fp,"\nP%-5d waited %-5.3f sec.", i, (float)i);
  }
  
  /*
  if(argc == 3){
  roundRobin((atoi( argv[1])));}
  else{SJF();} */
 fclose(fp);
  return 0;
} 

void turn(struct process procs[arrivalCount], int round){
  fprintf(fp,"%-9d",round);
  int index = 0;
  int smallestBurstindex = round;
  int amounttoburst;
  int currentlowestburst = 99;
  
 
  for(index = 0;index <arrivalCount;index++){
    if(procs[index].arrival <= round){ //if arival time is before this round
      
      
      
      
      
      if((procs[index].burst < currentlowestburst) && (procs[index].burst > 0)){
	currentlowestburst = procs[index].burst;
	smallestBurstindex = index;
	amounttoburst = procs[index].burst;
	}
      }
  }
  
  
  
  
  
  
  
  procs[smallestBurstindex].burst--;
  for(index = 0;index <arrivalCount;index++){
    if (round < (procs[index].arrival-1)){
       fprintf(fp,"%-10s", "");}
    
    else if(index == smallestBurstindex){
      fprintf(fp,"%-10s", "*");
      }
    else{
      fprintf(fp,"%-10s", "-");
      }

   }
   
   fprintf(fp, "\n");
}






