# Syntax Analyzer

## Introduction
This is a syntax analyzer for a custom defined language that supports integer, real, boolean, 2D jagged array and 2D rectangular arrays as data types. The language description can be found in `Language_description.pdf` file. If the syntax is correct, it will also generate the type expression table for the program. This project was done as a part of our course : - Principles of programming languages. 

## How to run
After downloading the repository, write the below code in the root directory: -

`$ make`

`$ ./run “testcases/t4.txt”`

## Functionalities
After you run the above commands, you will get few options to execute. 

Option 1: Create parse tree

Option 2: Traverse the parse tree to construct Type Expression Table. Also print the type errors while traversing the parse tree and accessing the typeExpressionTable.

Option 3: Print parse tree.

Option 4: Print Type Expression Table. 

## Authors
1. [Shrey Shah](https://github.com/imshreyshah)
2. [Abhimanyu Sethi](https://github.com/gollum-98)
3. [Pranali Sancheti]()
4. [Rushikesh Zawar](https://github.com/RBZ-99)
