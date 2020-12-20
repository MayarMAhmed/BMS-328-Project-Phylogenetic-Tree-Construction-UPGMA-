# BMS-328-Project
This program was done by Mayar Mansour Mohamed Ahmed

It allows the used to construct their own phyogenetic tree using the lower half of a percent identity matrix.
There is a step before the coding which is getting the FASTA file from NCBI then use it in to get the percentage identity matrix. After preparing the file:

The first step in the code is declaring a new class called UPGMA that include all the function needed to do the clusters exist. When declaring the class 3 arguments are given: the name of the file containing the lower half matrix as it is symmetrical, and the number of rows and columns which are equivalent to the number of species you are investigating +1. The UPGMA class automatically calls for creatematrix() and loadmatrix() functions

The second step is including 5 functions within the UPGMA class for clustering the species: creatematrix(), loadmatrix(), printmatrix(), minimum_value() and finally Build_Cluster().

The creatematrix() function creates a zero matrix with the dimensions given when declaring a UPGMA class.
The function loadmatrix() read the file containing the identity matrix and put it in the zero matrix created by creatmatrix() and making sure that m[i,x]= m[x,i]
Printmatrix() function prints the matrix resulted after each cluster
Minimum_value(): finds the value with the highest percentage identity (i.e. the value where 2 species are closest to each other) and print this value , its position and the 2 taxa it was found between
Build_Cluster():uses the positions extracted from minimum_value function to build the cluster by taking the average between them and other pints in the matrix then call the printing function to print the new matrix. it keeps redoing that until the all elements are clustered and the last matrix is size 2x2. Moreover, every cluster and the distance between them are saved in a file called tree.txt

The third Step is using the tree.txt file to build the tree which includes building a class named node and a print function called printTree() to show the resulted tree. This step is done using the PhylogeneticTreeConstruction.cpp 

you will find a file called mydata.txt which contains the perecentage identity matrix, you can run to see the output yourself, u will also find a txt file called tree.txt with the clusters if you want ot compare the results after running the program yourself. there is also the FASTA file I used to get the percentage matrix called sequences.fasta. you can use it redo the step of the creation fo the matrix then enter the matrix to the program to see the results.

there is also a report attached containing all the information regarding this program and screenshots from the results.


Thank you

