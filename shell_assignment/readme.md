Introduction
Through the use of commands, users can communicate with their operating system via the Simple Shell command-line interpreter. 
It offers a quick and easy method for managing files, running programs, and navigating directories.

Getting started

All you have to do is open a terminal window on your UNIX system to begin utilizing the Simple Shell. 
Use the supplied "make" command to compile the shell software if you haven't already.

Internal commands
-cd : change directory. Use cd <directory> to navigate to a specific directory
-dir: list directory contents
-pwd: print the working directory
-echo: display a line of text. Use echo <message> to print a message to the terminal.
-clr: clear the terminal screen. 
-environ: print the system's environment variables
-help: display the user manual
-pause - pause operation of the shell until 'Enter' is pressed
quit - quit the shell

Input/Output redirection
The shell allows you to specify the source of command input and the destination of command output by supporting input/output redirection. 
Here are a few typical operators for redirection:

-'<' : redirect input from a file.To specify a file as an input for a command, use '< file'.
-'>' : redirect ouput to a file. To overwrite the contents of a file with command input, use '> file'.
-'>>' : append ouput to file. To append command output to the end of a file, use '>> file'.
For exmaple:
ls > files.txt

Backgroud execution
allows for program background execution, so you can run commands without having to wait for them to finish. 
Add an ampersand & at the end of the command line to execute it in the background.
For example:
sleep 10 & (runs the sleep command in the background for 10 seconds)

Processes and background vs foreground
A process is a running instance of a program in the Unix operating system. 
There are memory spaces, program codes, data, and system resources that are unique to each process. 
The shell launches a new process to carry out a command when you run one.

Foreground execution: The terminal is accessible to a process running in the foreground (standard input and output).
Background execution: Usually, background processes interact with the system instead of the user during their operation.

