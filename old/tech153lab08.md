# TECH 153 Lab 08
- [ ] Demonstrate the execution of the program in vscode to your professor. ___/1
- [ ] Submit the rtf file on blackboard. ___/1

## Task 1 - Header and other updates   
1. Open your `~/ceng153/labs/queue` folder in VS Code, complete lab06 and lab07 if you haven't.   
2. Add the function prototype in `queue.h`:   
```
student_t * RemoveOneStudent(int studentNum,student_t * head); 
```
## Task 2 - Additional function
Add a function to the end of `queue.c`, completing the annotations, to remove a record:
Removing students is more complicated than adding them, as there are three unique conditions in a linked list (aside from an empty list).  You might have:
•	a match for the student, and only one item in the list.
•	a match for the student for the first item in a multi-item list.
•	a match for the student for items other than the first item in a multi-item list.
To do this:
1.	Declare two student_t pointers cur and prev.
2.	Assign the head pointer argument to both cur and prev.
3.	If the list is empty, print to stderr and return head.
4.	If the cur studentNum field matches the studentNum argument, and the cur next field is NULL, you only have one item in the list.  
5.	free the memory pointed to by cur, and return NULL.
6.	If the cur studentNum field matches the studentNum argument, and the cur next field is not equal to NULL, you want to delete the first record in a multi-record list.  Assign the cur next field to head, free the memory pointed to by cur, and return head.
7.	Otherwise use a while loop to move through the list.  If the cur studentNum field matches the studentNum argument, set the prev next field to the cur next field, free cur, and return head.
8.	Otherwise continue moving through the list by first setting the prev pointer to the cur pointer, and then assigning the cur next pointer to the cur pointer.
9.	If no match is found, print the stderr and return the head pointer.
For example:
```
/** Removes one student
 * @since 2025-03-25
 * @author 
 * @param int studentNum to be removed
 * @param student_t pointer to the head of a list
 * @return student_t pointer to the head of a list
 */
student_t * RemoveOneStudent(int studentNum,student_t * head) 
{ 
	student_t * cur=head;  
	student_t * prev=head;  
	//empty list
	if(cur==NULL)
	{
		fprintf(stderr,"Trying to remove from empty list.\n");
		return head;
	}
	//a match for the student, and only one item in the list.
	else if(cur->next==NULL && cur->studentNum==studentNum)
	{
		head=cur->next;
		free(cur);
		return head;
	}
	//a match for the student for the first item in a multi-item list.
	else if(cur->next!=NULL && cur->studentNum==studentNum)
	{
		head=cur->next;
		free(cur);
		return head;
	}
	//a match for the student for items other than the first item in a multi-item list.
	while (cur!=NULL)
	{
		if(cur->studentNum==studentNum)
		{
			prev->next=cur->next;
			free(cur);
			return head;
		}
		else
		{
			prev=cur;
			cur = cur->next;
		}
	}
	fprintf(stderr,"Student not found.\n");
	return head;
}
```
## Task 3 - Updating main 
1. If you have yet to in your main, make sure your main adds all 3 entries from the array into the linked list. Then delete the middle entry prior to displaying the linked list.
```
head=RemoveOneStudent(classlist[1].studentNum,head);
```
3. Show the output of your queue program to your professor.
## Task 4 - Submitting your work
1. Type `doxygen ceng153`
2. Use WinSCP to obtain your makefile and `~/ceng153/labs/queue/rtf/refman.rtf` which you should rename to `LastName153L08.rtf`.
3. Open the rtf in Word then use Ctrl A to select all and F9 to update fields to generate the table of contents and the index. If you are using LibreOffice Writer, right click on the gray Table of contents and select Update index also right click on the gray INDEX at the end of the file and select Update index.
4. Edit the second page of the .rtf to include the text contents of your makefile and a sample output screen capture including the output of program execution from within VS Code.
5. Please use Notepad++->Plugins->NppExport->Copy RTF to clipboard then paste the makefile text.
6. Submit the .rtf on blackboard.


