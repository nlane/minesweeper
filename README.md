
     As the second in a series of three major projects for a Secure Software course, this project is a c++ implementation of 
     the classic game of Minesweeper. 
     
     With a commandline interface you can play through a game of minesweeper. You can set flags for a unique width (-w) and 
     height (-h) of the game (between 1 and 19 for each) as well as a mine flag (-m) for specifying the number of mines 
     desired in the board. The board is printed for each move with "*" representing a mine, a number representing the number 
     of mines immediately surrounding the cell, or a "-" representing an unopened cell.
     
     In programming this game, I worked with one other person. We had to pay attention as to how we were checking our inputs 
     and flags. With security in mind, you must check that the user is inputting valid text. Also we had to handle creating 
     our own "Cell" class for this implementation. We decided that having a 2D array of Cell objects was the cleanest way to 
     handle storing the gameboard. Writing out the rest of the game's logic was a further test of my c++ skills. 
     
     Specifically in this project I feel that I gained a lot of knowledge in debugging c++ code. When we were getting constant
     seg faults, I couldn't find the error in my code until I ran Valgrind and got a better error message for the code. Similarly
     I gathered a deeper knowledge of creating classes and header files in c++.
