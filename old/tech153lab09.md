# TECH 153 Lab 09
- [ ] Demonstrate the execution of the program in vscode to your professor. ___/1
- [ ] Submit the rtf file on blackboard. ___/1

## Task 1 - Declaration and initialization   
1. Open your `~/ceng153/labs/queue` folder in VS Code, complete lab06, lab07, and lab08 if you haven't.   
2. To be able to write to a file, add early in your main function in `queue.c`:   
```
    FILE *fp;
    char fname[10]="log.txt";
    fp = fopen(fname,"a");
    if(fp == NULL)
    {
        fprintf(stderr,"\nCan't open file, data not retrieved!\n");
        return 0;
    }
```
3. Also initialize and clear the frame buffer in your main:
```
    struct fb_t *fb;
    fb=ShInit(fb);
    memset(fb, 0, 128);
    usleep (300000);
```
## Task 2 - Wrap up actions
Add to the end of the main function in `queue.c`, but prior to the return:
```
    int spot=0;
    student_t * cur=head;
	for(;cur!=NULL;cur=cur->next) 
	{
        fprintf(fp,"Student %d's grade is %f\n", cur->studentNum, cur->grade);
		if(spot<8)
		{
            fb->pixel[spot][1]=GREEN;
            fb->pixel[spot][2]=GREEN;
            fb->pixel[spot][3]=GREEN;
		}
		else if(spot<16)
		{
            fb->pixel[spot-8][5]=GREEN;
            fb->pixel[spot-8][6]=GREEN;
            fb->pixel[spot-8][7]=GREEN;
        }
        spot++;		
        usleep (300000);
    }
```
## Task 3 - Compile and demonstrate 
1. Show the output of your queue program to your professor.
## Task 4 - Submitting your work
1. Type `doxygen ceng153`
2. Use WinSCP to obtain your makefile and `~/ceng153/labs/queue/rtf/refman.rtf` which you should rename to `LastName153L09.rtf`.
3. Open the rtf in Word then use Ctrl A to select all and F9 to update fields to generate the table of contents and the index. If you are using LibreOffice Writer, right click on the gray Table of contents and select Update index also right click on the gray INDEX at the end of the file and select Update index.
4. Edit the second page of the .rtf to include the text contents of your makefile and a sample output screen capture including the output of program execution from within VS Code.
5. Please use Notepad++->Plugins->NppExport->Copy RTF to clipboard then paste the makefile text.
6. Submit the .rtf on blackboard.


