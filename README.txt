NOTE:class account available for testing is in cssc2103@edoras.sdsu.edu
Jose Toscano(822990578)
cssc2103@edoras.sdsu.edu
CS 570, Summer 2020
Professor Leonard
Assignment #2, MicroShell
README.txt
6/29/20

File manifest:
msh.cpp 
Pipes.cpp 
Pipes.h
FileCheck.cpp 
FileCheck.h
ProcessString.cpp
ProcessString.h
README.txt
Makefile

Job distribution/ Development Process:
Unfortunately I wasn't able to obtain a partner for this one so everything was written by me. I tried using Agile to break down the program into chunks(formatting user input, file checking, piping/running programs) and would work on those chunks every few days and keep 
track of any issues I had to go back into and fix.

Compile Instructions:
g++ -std=c++11 -o msh msh.cpp Pipes.cpp FileCheck.cpp ProcessString.cpp

Operating instructions:
To run type in:
msh

Novel/Significant Design Decisions:
Initially I was planning to use a array of double
pointers to store each command with its respective arguments
to then run but I couldn't get it to work. I still don't fully
understand pointers so instead I settled in keeping the tokens
which are commands, pipes, arguments in a vector and used an index
to keep track where I am and another vector that would let me know
how many arguments the command uses and passed that instead to a
function that would then run the programs.

Extra features/Algorithms/Functionality:
No extra features included.

Known Bugs:
There is one bug I am aware of. Assuming I need to deal with
commands that provide more than one flag, when doing so it 
does not print a useful message to console. For example,
if I try to run fakeProgram -e -t, the program will continue to
run fine but it won't print a message to console saying the file
doesn't exist. However with just one flag it works as it should.
So if I do fakeProgram -e it will print a message saying the file
doesn't exist.

Lessons Learned:
One big lesson that took me quite a while to learn was how to
use pipes and file descriptors and making sure all the pipes
are closed up or else my program would hang and never finish.
It was alot easier to figure out once I drew it on paper to see
what parts need to be opened and closed and which pipes needed to
be redirected so it wouldn't print to console but instead pass
it's information to the next child with it's program.

