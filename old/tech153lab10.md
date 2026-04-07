# TECH 153 Lab 10 Memory Dumps
- [ ] Demonstrate the execution in vscode to your professor. ___/1
- [ ] Submit the screen capture on blackboard. ___/1

## Task 1 - DEBUG CONSOLE   
1. Open your `~/ceng153/labs/queue` folder in Visual Studio Code.
2. In order to use the DEBUG CONSOLE there needs to be a session running which can be achieved by setting a breakpoint and then Run->Start Debugging F5.
3. For us we want to dump memory that has data in it so we decide to **put the breakpoint on the return statement** in main so that the program has put everything in memory but has yet to potentially clear it and terminate.
4. The command to use the dump a particular variable from memory is `x`. In the DEBUG CONSOLE try:
```
-exec x classlist
```
This provides the first hexadecimal byte.   

5. To see additional bytes, specify the number:
```
-exec x/16 classlist
```
6. To see the integer value, specify the data type the same way as you would in a print statement:
```
-exec x/16d classlist
```
now we can see the student numbers in the array of structures.

7. Dump the memory to a binary file specifying the file name, start address, and end address:
```
-exec dump memory file.dat classlist classlist+3
```
## Task 2 - Terminal
1. At the terminal you can terminate the program with Ctrl-c and then use the `hexdump` command to display the data in hexidecimal:
```
hexdump file.dat
```
2. To show the integers:
```
hexdump -d file.dat
```
3. To see text including strings it is typical to use the Canonical side by side form of hexadecimal and characters:
```
hexdump -C file.dat
```
4. Show this to your professor.
5. In fact, now that you are at the terminal you can also do memory dumps from gdb as well:
```
gdb queue
```
6. We then choose to set a breakpoint towards the end of main by choosing a line number ## and then run to that point by writing:
```
break queue.c:##
run
```
7. Now we can execute the same gdb commands:
```
x classlist
x/16 classlist
x/16d classlist
```
## Task 4 - Submitting your work
1. Submit a screen capture of the terminal to blackboard.
