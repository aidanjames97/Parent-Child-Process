#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

// main program (parent)
int main(int argc, char *argv[]) {
    printf("\n  Main function starting \n\n");
    // checking for correct number of parameters
    if(argc != 4) {
        // not correct input
        printf("incorrect input, need path and 3 parameters (N, M, S)\n");
    } else {
        // correct input
        printf("\n parent stared in here 2 \n\n");
        // starting program execution
        printf("parent(PID %d): process started\n\n", getppid());
        pid_t child_1, child_1_1, child_1_2, child_2; // initiate creation of child process'

        printf("parent(PID %d): forking child_1\n", getppid());
        child_1 = fork(); // create child process

        if(child_1 > 0) {
            printf("\n child creation successful (returned child pid (>0)) 3 \n\n");
            // child creation successful
            printf("parent (PID %d): fork successful for child_1 (PID %d)\n", getppid(), getpid());
            printf("parent (PID %d): waiting for child_1 (PID %d) to complete\n", getppid(), getpid());
            wait(NULL); // wait for child_1 to complete

            printf("\n child1 is fully done, returned to child after wait, going to fork child2 12 \n\n");

            // child1 execution completed
            printf("parent (PID %d): forking child_2\n", getpid());
            child_2 = fork(); // forking child2

            if(child_2 > 0) {

                printf("\n child2 has been forked, inside with value > 0 13 \n\n");

                // child2 creation successful
                printf("parent (PID %d): fork successful for child_2 (PID %d)\n", getppid(), getpid());
                wait(NULL); // waiting for child2 to execute

                printf("\n execution is completed back to parent \n\n");

                // execution done
                printf("parent (PID %d): completed parent\n", getpid());
            } else if (child_2 == 0) {

                printf("\n now in child2's child value is 0, 14 \n\n");

                // in child2
                printf("child_2 (PID %d): process started from parent (PID %d)\n", getpid(), getppid());
                printf("child_2 (PID %d): calling an external program [./external_program2.out]\n\n", getpid());

                printf("\n child2 now going to call execl (extrnal program2.out) 15 \n\n");

                execl("./external_program2.out", argv[3], NULL);
            } else {
                // child2 creation failed
                printf("child2 failed\n\n");
            }

        } else if (child_1 == 0) {
            printf("\n first child entred, fork value is now 4 \n\n");
            // in child
            printf("child_1 (PID %d): process started from parent (PID %d)\n\n", getpid(), getppid());
            printf("child_1 (PID %d): forking child_1.1\n", getpid());
            child_1_1 = fork(); // forking child1.1

            if(child_1_1 > 0) {
                printf("\n child1 created a child 1.1, child1 returned value greater than 0, 5\n\n");
                // child1.1 creation successful
                wait(NULL); // waiting for child1.1

                printf("\n back to child1 after execl call, forking child 1.2 8 \n\n");

                printf("child_1 (PID %d): completed child_1.1\n\n", getpid());
                printf("child_1 (PID %d): forking child_1.2\n", getpid());
                child_1_2 = fork(); // creating child1.2 here

                if(child_1_2 > 0) {
                    
                    printf("\n child1 created child1.2, returned >0 (child1.2's pid) 9 \n\n");

                    // child1.2 creation successful
                    wait(NULL); // waiting for child1.2
                    printf("child_1 (PID %d): completed child_1.2\n\n", getpid());
                } else if (child_1_2 == 0) {

                    printf("\n inside of child1.2 10 \n\n");

                    // in child1.2
                    printf("child_1.2 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
                    printf("child_1.2 (PID %d): calling an external program [./external_program1.out]\n", getpid());

                    printf("\n child1.2 is calling execl (external program1.out) 11 \n\n");

                    // calling external program and passing M
                    execl("./external_program1.out", argv[2], NULL);
                } else {
                    // child1.2 creation failed
                    printf("child1.2 failed\n\n");
                }
            } else if (child_1_1 == 0) {
                printf("\n entre child 1.1, value retured is now 0, 6 \n\n");
                // in child1.1
                printf("child_1.1 (PID %d): process started from child_1 (PID %d)\n", getpid(), getppid());
                printf("child_1.1 (PID %d): calling an external program [./external_program1.out]\n", getpid());

                printf("\n child1.1 is calling execl (external program1.out) 7 \n\n");
                // calling external program and passing it N
                execl("./external_program1.out", argv[1], NULL);
            } else {
                // child1.1 creation failed
                printf("child1.1 failed\n\n");
            }
        } else {
            // child creation fail
            printf("child creation failed\n\n");
        }
    }
    return 0; // default return statement
}