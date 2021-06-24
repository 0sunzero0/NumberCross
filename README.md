# Number Cross

## 1. Introduction to NumberCross
- Number Cross consists of a M×N grid where every square, every row, and every column and is labeled with a positive integer
- The goal of the game is to determine the color of each square as either Black or White, such that 
    - the label (number) of each column is the same as the sum of the numbers in the Black squares of the column 
    - the label of each row is the same as the sum of the numbers in the White squares of the column 
    - the number of a square label is greater than or equal to 1, and not greater than 9 
    - initially, no information on the coloring is given 
    ![Alt text](https://github.com/0sunzero0/NumberCross/blob/master/img.png)
    

## 2. Input
-  input is given via the standard input 
-  the first line consists of N tokens which are a sequence of the column labels 
-  each of the following M lines has N + 1 tokens; first N tokens are a sequence of the square labels in the row, and the last label for the row label
-  M is not greater than 50, and so is N. 
```
20 23 30 29 34 6 9 21 19
8 2 1 8 1 3 5 7 6 18
9 1 4 2 5 6 3 1 7 28
3 5 1 4 9 1 3 9 1 8
8 6 6 3 5 1 1 4 1 4
8 6 6 2 6 8 3 3 9 31
8 7 8 8 4 5 2 1 1 18
4 8 3 5 5 2 1 2 8 24
1 2 8 8 8 3 7 2 7 22
8 3 9 5 9 2 1 4 9 35
```

## 3. Output
- print the coloring of the grid to the standard output 
  - 1 : Black 
  - 0 : White
```
  1 0 1 0 0 1 0 0 
  1 1 0 1 0 0 0 0 
  1 1 0 1 0 0 1 1 
  1 1 1 1 1 1 0 1 
  0 0 1 1 0 0 1 1 
  1 1 1 0 0 1 1 0 
  0 1 0 0 0 1 1 1 
  1 1 1 0 1 0 1 0 
  0 0 0 1 1 0 1 0 
```
- print “No solution” if there’s no solution 
```
No solution
```

## 4. Logical Formula
![Alt text](https://github.com/0sunzero0/NumberCross/blob/master/formula.png)

## 4. Guideline
```
   NumberCrossSource
    -- homework1.c
    -- input
    -- Makefile
```
- There are files in NumberCrossSource directory.
    - __homework1.c:__ Source code to solve NumberCross
    - __input:__ Input file named input
    - __Makefile:__ Makefile to build and run homework1.c
    
- You can make input file named "input". And If you run homework1.c then, the computer will input the input file named input and print the output without having to type the name of the input file.
- If you want input another contents of input, then you modify contents of input file named "input".

## 5. How to build
Make Makefile and type below command.
```
exe:
	gcc -o hw1.out homework1.c
	./hw1.out

clean:
	rm hw1.out formula
```

## 6. How to run
Command this instruction
```
gcc -o hw1.out homework1.c
./hw1.out
```
or
```
make exe
```
