#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct proc{
  int id;
  int priority;
  int quantity;
  float score;
  float meter;
};

void scheduleProcess(struct proc *p){
  printf("%d\n", p->id);
  p->score += p->meter;
  p->quantity --;
}

int main(int argc, char **argv) {
  //quick check to make sure i have a valid number of arguments - avoid a seg fault 
  if(argc%2 == 0){
    printf("invalid number of arguments\n");
    return 0;
  }

  //array of proc structs 
  struct proc procs[argc/2];
  int total = 0;
  
  //variable used to keep track of higest meter
  int highestMeter = 0;

  //for every 2 items starting at one - should get every instance of the input pairs
  for(int i=1; i<argc; i+=2){
    //intializing the struct
    procs[i/2].id = (i/2)+1;
    procs[i/2].priority = atoi(argv[i]);
    procs[i/2].quantity = atoi(argv[i+1]);
    procs[i/2].score = 0;
    procs[i/2].meter = 1.0/procs[i/2].priority;
    //updating total
    total += procs[i/2].quantity;
  }

  //for the total number times things have to be scheduled
  for(int i=0; i<total; i++){
    //pointer to a proc struct - will be the lowest item (thing to be shceduled)
    struct proc *lowScore;
 
    //finding the first item with a quantity bigger than zero
    for(int i=0; i<argc/2; i++){
      if(procs[i].quantity != 0){
        lowScore = &procs[i];
        break;
      }
    }
    
    //for every process in the procs array
    for(int i=0; i<argc/2; i++){
      //making sure that each process has ran its specified number of times
      if(procs[i].quantity > 0){
        //checking their score, setting lowScore to the lowest scored item (least scheduled) 
        //checking if the score is the same - if so check priority
        if(procs[i].score == lowScore->score){
          //check priority
          //if they're equal have to go by lower id
          if(procs[i].priority == lowScore->priority){
            //check if id is lower - should never be the same
            if(procs[i].id < lowScore->id){
              lowScore = &procs[i];
            }
          }
          //checking priority
          else if(procs[i].priority > lowScore->priority){
            lowScore = &procs[i];
          }
        }
        //if it is lower set lowScore to that
        else if(procs[i].score < lowScore->score){
          lowScore = &procs[i];
        }
      } 
    }
    //at this point lowScore should be pointing to the prcess that needs to be scheduled
    scheduleProcess(lowScore);
  }
  return 0;
}
