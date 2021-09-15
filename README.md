# ATOMIC TEDDY INVESTORS

**ATOMIC TEDDY INVESTORS** is a programming project designed by Mr. David RENAULT, conducted by all first year informatics engineering students of ENSEIRB-MATMECA in the 2019/2020 scholar year.

Briefly, students should carry out multiple achievements through out this project. But, the goal isn't to finish all of them, in fact no body has never done so since the very beginning of this evaluation. The goal is to have us think outside the box and write a highly robust code using all of the knowledge and assets we learned through out this semester. 

## Team members

- Elomari Alaoui Ismail

- Bernard--Hême Hugo

## 1	 Compilation:
Once you are locally in a version of this project, compile using the "Makefile". It has different functionnalities:
     You can write "make" in order to compile the source code, and delete all the .o files after compilation
     You can write "make test" to compile the tests, delete the .o files and execute the executable "test". This will give you the number of tests, related to many structures, that have passed correctly. Of course, if an error occurs, you will be informed exaclty which test in which structure did the test fail. 
     You can also write "make clean" in order to delete all the executables 'project' , 'test' and the linkers ( .o files) if they aren't already deleted.

## 2   	 Locally:
You'll see in addition to the different versions of the project, many files:
       authors.txt : A file containing the authors of this project
       README.md: This file describes our project
       rapport.tex: This file is the source code of our report, written in LaTeX. Unfortunately, some parts we have in the final report, parts such as the grantt diagrm describing our time management, could not be compiled locally. So we deleted them from this file. In order to compile this file, you should use the command "pdflatex" like so: "pdflatex rapport.tex" . After that, you can easily see our report using "evince rapport.pdf" . 
       

## 3   	  Usage:
Each version of this project has a main file "project-?.c" with contains the main function of every version. Once you've compiled the source code, you can execute it using "./project" which launchs a 1000-turns game between two teddies. As the random generator is not initialized 'seed = 0', the teddies use time if they are asked to choose randomly.
In order to control the game, you can also use options such as:
   	   -n :in order to control the number of players
	   -m :in order to control number of turns
	   -s :in order to control the so called 'seed', also known as the random generator
Thus, executing a certain version of this project using ./project -n 5 -s 156 -m 100 , launchs a 100-turns game with 5 teddies who can choose randomly using the seed 156.

## 4    	License
	ENSEIRB-MATMECA  
