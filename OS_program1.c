/* This program creates multiple children processes and each child starts a new program
 * from the set of possible 5 execcutables and also the program discerns which child 
 * completes and prints an appropriate message*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<string.h>

//function returning the index of the exiting child based on its pid
int matching_index( int child_pid_array[],int length, int wpid)
{
	int i;
	int index;
	for(i=0;i<=length;i++)
	{
		if(child_pid_array[i] == wpid)
		{
			index = i;
			break;
		}
	}

	return index;
}

int main(int argc, char* argv[])
{
	pid_t  childpid;  //pid of the child process
	pid_t cpid; //pid of the child process
	pid_t parentid = -1; //pid of the parent process
	pid_t temp_id = -1; // a temproray id to check if it is the original parent process


       	if(argc<2) //if it has less than 2 arguments print error
	{
		printf("Please enter the number of child processes\n");
		//the count of child processes is passes as command line argument
		printf("Error in receiving the arguments\n");
		return 1;
	}
	else
	{

	
			int count = (atoi)(argv[1]);//convert the count argument to integer form

      			 int *child_pid_array = (int*) malloc(sizeof(int)*count);
			//allocate an array to store child pids

			int i=0;
			char command[10][10] = {"./test1","./test2","./test3","./test4","./test5"}; //path of the executables
       

			parentid = getpid ();  //get the pid of the parent process
			printf("Parent pid is %ld\n",parentid);

			int k =0; 
        		for(int j = 0;j < count;j++) //create the child processes in a loop
			{
				temp_id = getpid (); //get the pid of the current process
				if (temp_id != parentid) 
					continue;
				//if it is the original parent process then only fork
				childpid = fork();
			       
				if(childpid < 0)
				{
					printf("fork failed\n");
					exit(1);
				}
				else if(childpid == 0)
				{
					

					cpid = getpid();
				
     					printf("Started child %d with pid %ld\n", i+1,cpid);
					execlp(command[k],NULL);
					
					sleep(3);
					exit(0);
		
				}
				else
				{
				
					
			
					child_pid_array[i] = childpid; //store the children pids
					
					
					

				}
						
				i++;
				
				k++;
				//because we have 5 executables
				//child1 executes test1, child2 executes test2, child3 executes test3
				//...child6 executes again test1...so on.
				if(k==5) //after the k reaches 5 it is rounded back to 0

				{
					k =0;
				}

		 	}

		
	
		int child_count = i;
		int status;
		pid_t wpid;
		int child_no;
		while(i>0)  //wait for all the child processes to finish
		{
			wpid = wait(&status);
			//find the index of the exiting child
			child_no = matching_index(child_pid_array,child_count,wpid);	
			printf("Child %d (PID %d) finished\n",child_no+1,wpid);
			i--;
			
		}
	
			
	}
	return 0;
	
}
