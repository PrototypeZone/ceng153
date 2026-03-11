# TECH 153 Lab 01
- [ ] Demonstrate the execution of the program in vscode to your professor. ___/1
- [ ] Submit the rtf file on blackboard. ___/1

## Task 1 - Setting up your environment
1. In your `~/ceng153/labs` directory `mkdir queue`
2. `cd queue` and `mkdir .vscode`
3. In WinSCP and set Options->Preferences->Panels->Show hidden files
4. Download and use WinSCP to transfer the following files into your `queue` directory:
   - https://github.com/PrototypeZone/ceng153/blob/main/old/led2472g.h
   - https://github.com/PrototypeZone/ceng153/blob/main/old/led2472g.c
   - https://github.com/PrototypeZone/ceng153/blob/main/old/font.h 
4. Download and use WinSCP to transfer the following file into your `.vscode` directory:
   - https://github.com/PrototypeZone/ceng153/blob/main/old/.vscode/launch.json 

## Task 2 - Creating a makefile
1. In your `~/ceng153/labs/queue/` directory create the following makefile
```
#makefile
queue: queue.o led2472g.o
	gcc -g -o queue queue.o led2472g.o
queue.o: queue.c queue.h
	gcc -g -c queue.c
led2472g.o: led2472g.c led2472g.h
	gcc -g -c led2472g.c
.PHONY: clean
clean:
	rm -f *.o
	touch *

```

## Task 3 - Creating a header file
1. In your `~/ceng153/labs/queue/` directory create the following `queue.h`
```
/** @brief Header file for a mock up of the lab assistance queue usually on the whiteboard.
 *  @file queue.h
 *  @since 2026-03-11
 *  @version ceng153, Serial: 1a2b3c4d  
 */

// Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include "led2472g.h"

// Constants

// Structures
typedef struct student
{
    int studentNum;
    double grade;
    struct student * next;
}student_t;

// Function Prototypes
///@cond INTERNAL
///@endcond

```

## Task 4 - Creating a main function 
1. In your `~/ceng153/labs/queue/` directory create the following queue.c
```
/** @brief A mock up of the lab assistance queue usually on the whiteboard.
 *  @file queue.c
 *  @since 2026-03-11
 *  @version ceng153, Serial: 1a2b3c4d  
 */
#include "queue.h"

/** @brief Defines the entry point for a mock up of the lab assistance queue usually on the whiteboard.  
 *  @author Your Name
 *  @since 2026-03-11
 *  @param void
 *  @return exit status
 */
int main(void)  
{  
    fprintf(stdout,"Unit: %LX\n",ShGetSerial()); // Prints serial ID
    
    struct student classlist[3];
    classlist[0].studentNum=12345;
    classlist[0].grade=70.0;
    classlist[1].studentNum=23456;
    classlist[1].grade=80.0;
    classlist[2].studentNum=34567;
    classlist[2].grade=95.0;

    printf("Printing from the Array of Structures\n");
    for(int i=0;i<3;i++)
    {
        printf("Student %d's grade is %f\n", classlist[i].studentNum, classlist[i].grade);
    }
    
    return EXIT_SUCCESS;
}

```

## Task 5 - Showing your work and experimenting with the debugger
A visual interface is available with Vs Code for the gdb debugger.
1.	From the main menu on the pi go to Programming and select Visual Studio Code.
2.	From the File menu select open folder and select then Open the queue folder you created.
3.	Trust the authors (you and I).
4.	From the Terminal menu select New Terminal, or if you already have one open at the bottom of the screen click on it, type `make clean`, then `make` in the terminal to build the code.
5.	The code should run by using the command `./queue`
6.	Demonstrate to your professor.
7. From the file window open the queue.c file and then from the Run menu select Start Debugging.
8. When prompted for the debugger select the first item for the Microsoft Intellisense extension.
9. Open queue.c and use F9 to set a breakpoint on the printf statement;
10. From the Run menu select Start Debugging. The debugger windows should open up and the program should execute and stop at the breakpoint.
11. Explore the Step Over (F10) and Step Into (F11) VS Code visual environment calls to gdb's next and step
![image](https://github.com/PrototypeZone/ceng153/blob/main/old/ghcvscode.png)

## Task 6 - Submitting your work
doxygen

