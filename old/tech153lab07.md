# TECH 153 Lab 07
- [ ] Demonstrate the execution of the program in vscode to your professor. ___/1
- [ ] Submit the rtf file on blackboard. ___/1

## Task 1 - Setting up your environment and annotating source code   
1. Open your `~/ceng153/labs/queue` folder in VS Code, complete lab06 if you haven't.   
2. Annotate your source code and add the function prototypes in `queue.h`; then add the display function after your main function in `queue.c`:   
This process adds comments to the code that are embedded with special symbols and key words used by doxygen to automate documentation generation. We will use the JavaDocs style for our function annotations:   
    
brief description   
@author – programmer name   
@version – course code and serial   
@since - date of last modification   
@param – one or more descriptions of function parameters   
@return – return type description   
### File
At the top of each file is some basic identification with a brief description similar to that for functions followed by an @file tag followed by the name of the current file:   
```
/**  @brief Constants, structures, function prototypes
 *   @file queue.h
 */
```
### Function Prototypes
So Doxygen does not repeat the source code details of functions enclose all the function prototypes e.g.:   
```
//Prototypes
///@cond INTERNAL 
student_t * AddOneStudent(int studentNum, double grade,student_t * head);  
void DisplayStudents(student_t * head);
//…other function prototypes…
///@endcond
```
### Functions
```
/** Prints out data in a linked list
 *  @version ceng153, Serial: 1a2b3c4d
 *  @author Your Name
 *  @since 2026-03-18
 *  @param head a student_t *
 *  @return void
*/
void DisplayStudents(student_t * head) 
{ 
	student_t * cur=head;  
	for(;cur!=NULL;cur=cur->next) 
	{
		printf("Student %d's grade is %f\n", cur->studentNum, cur->grade);
	}

} 

```
Your task is to add header annotations for all files and add in the header information for all non-stub functions (ie./in other words: add header information for all functions that have code that does something).
## Task 2 - Creating a linked list
While our current system keeps the information in an array, arrays can become quite complex, requiring more types, prioritization, and other factors.  As such, we will transition to using a list data structure that can dynamically grow or shrink, rather than use a fixed sized construct such as an array.  The linked list will dynamically allocate/deallocate memory, and track the various alarm records using pointers.   

With linked lists, each collection of data is defined with a structure and additionally these structures have pointers that reference where other similar data records can be found.  This next field is termed ‘self-referential’ as it holds a memory address to an object that is its own type.   

While all pointers use the same amount of memory, when you specify the structure, the compiler finds members of the same type of structure using the -> structure dereferencing operator. The linked list joins a series of dynamically allocated memory locations that store information in structures.  Note, we need both the structure tag and the typedef tag, to allow for the self-referential declaration used for the next field.   

While the address of the ‘head’ record normally does not change, we can link any number of records to the end of the list, by finding the address of the last record, allocating some memory, and storing the pointers in the last record.  Records are removed from the list, by changing the pointers of the previous record’s next field.  You do not have to maintain a count of the number of list members, as you just keep searching the ‘next’ memory locations until you hit the last one, which is a null pointer.  While sorting is a bit more complicated, it relies on changing the next pointers to reflect the desired sort key.   

Add this function after your main function in `queue.c` and complete the annotations: 
```
/** Beginning with adding to the bottom of the list
 * @since
 * @author
 * @param
 * @return
 */
student_t * AddOneStudent(int studentNum, double grade,student_t * head) 
{ 
	student_t * cur=head;  
	student_t * arecord;  

    // First we start with a pointer and allocate some memory to it:
	arecord = (student_t *) calloc(1,sizeof(student_t));  
 
	if(arecord == NULL)  
	{  
		fprintf(stderr,"\nCannot allocate memory\n");  
		return NULL; //EXIT_FAILURE;  
	} 
    // We then can assign values to the various parts:
	arecord->studentNum = studentNum;  
	arecord->grade = grade;  
	arecord->next=NULL; 
	if(head == NULL)  
	{ 
		return arecord; 
	} 
	else if (head->next == NULL) 
	{ 
		head->next=arecord; 
		return head; 
	} 
 
	while (cur->next!=NULL)
	{
		cur = cur->next;
	} 
cur->next=arecord;
	return head;
} 
```
## Task 3 - Displaying the contents of a linked list 
1. In your main, declare a pointer and call the functions:
```
	student_t * head=NULL;
	head=AddOneStudent(classlist[0].studentNum,classlist[0].grade,head);  
	DisplayStudents(head); 
```
2.	Show the output of your queue program to your professor.
## Task 4 - Submitting your work
1. Type `doxygen ceng153`
2. Use WinSCP to obtain your makefile and `~/ceng153/labs/queue/rtf/refman.rtf` which you should rename to `LastName153L07.rtf`.
3. In Word, Edit the second page of the .rtf to include the text contents of your makefile and a sample output screen capture including the output of program execution from within VS Code.
4. Please use Notepad++->Plugins->NppExport->Copy RTF to clipboard then paste the makefile text.
5. Use Ctrl A to select all and F9 to update fields to generate the table of contents and the index. If you are using LibreOffice Writer, right click on the gray Table of contents and select Update index also right click on the gray INDEX at the end of the file and select Update index.
6. Submit the .rtf on blackboard.


