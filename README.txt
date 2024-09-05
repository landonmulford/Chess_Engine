Chess Engine:

  How to use: insert a position by its FEN, a list of characters easily found on any chess website that  
    describes the position. The engine will display its best move by displaying the board after the move 
    is made.

  Details: The engine uses a recursive Depth First Search, where it continues searching down until it 
    hits the desired depth, where it will then return the value of the evaluation of that position,
    using material, space, and other criteria. As the tree moves back up, it will chose the best position
    below it, and use that positions eval as its eval. This will continue until it reaches the best possible moves.

  Challenges: Due to computational restricitions and potential inefficiencies, the engine cannot reach depths
    comprable to real chess engines in a reasonable amount of time. This results in some inaccuracies.
