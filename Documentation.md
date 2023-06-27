# Documentation

## Table of Contents

- [Board](##Board)
- [Movement](##Movement)
- [Piece](##Piece)
    - [Pawn](##Pawn)
    - [Rook](##Rook)
    - [Knight](##Knight)
    - [Bishop](##Bishop)
    - [Queen](##Queen)
    - [King](##King)
- [Pieces](##Pieces)
    - [WhitePieces](##WhitePieces)
    - [BlackPieces](##Blackieces)
- [Notation](##Notation)
- [Move](##Move)
- [Coords](##Coords)
- [BoardUtils](##BoardUtils)
    

## Board

The `Board` class represents a chess board and provides methods for manipulating and analyzing the board state.

### Properties

- `moveFor`: Indicates the color of the player to move next.
- `board`: Represents the chess board as a 2D character array.

### Methods

- `isThreeFoldRepetition()`: Checks if the current board position has occurred three times.
- `isDrawDueToInsufficientMaterial()`: Checks if the current board position leads to a draw due to insufficient material.
- `isFiftyMoveRule()`: Checks if the current board position satisfies the fifty-move rule.
- `resetMovesSinceCapture()`: Resets the count of moves since the last capture or pawn move.
- `getPieces(color)`: Returns the pointer to the `Pieces` object for the specified color.
- `setOutcome(outcome)`: Sets the outcome of the game.
- `getOutcome()`: Returns the outcome of the game.
- `setKingsCastlingRights(king)`: Sets the castling rights for the specified king.
- `increaseMovesSinceCapture()`: Increments the count of moves since the last capture or pawn move.
- `setMove1Before(move)`: Sets the move made in the previous turn.
- `getMove1Before()`: Returns the move made in the previous turn.
- `setPGN(pgn)`: Sets the PGN representation of the game.
- `getPGNMoves()`: Returns the individual moves in PGN format.
- `importFEN(fen)`: Imports the board state from the specified FEN string.
- `importPGN(pgn)`: Imports the game moves from the specified PGN string.
- `exportFEN()`: Exports the current board state as a FEN string.
- `exportFEN(board)`: Exports the specified board state as a FEN string.
- `exportPGN()`: Exports the game moves as a PGN string.
- `printBoard()`: Prints the current board state.
- `printBigBoard()`: Prints the current board state in a larger format.
- `scanBoard(whitePieces, blackPieces)`: Scans the board and updates the piece positions for white and black.
- `findPiece(type, color)`: Finds the first occurrence of a piece with the specified type and color.
- `findPiece(piece)`: Finds the first occurrence of the specified piece.
- `findPiece(coords)`: Finds the piece at the specified coordinates.
- `findPiece(square)`: Finds the piece on the specified square.
- `pushBoardState(fen)`: Pushes the current board state into the past board states.
- `pushMove(move)`: Adds the move to the list of PGN moves.
- `quantityOfPiece(type, color)`: Returns the quantity of pieces with the specified type and color.
- `copyBoard(src, dest)`: Copies the contents of the source board to the destination board.
- `copyMove(src, dest)`: Copies the contents of the source move to the destination move.

### Constructors

- `Board()`: Default constructor.
- `Board(fen)`: Constructs a `Board` object using the specified FEN string.
- `Board(board)`: Constructs a `Board` object using the specified 2D character array representing the board.

### Destructor

- `~Board()`: Destructor.

---

## Movement

The `Movement` namespace provides functions related to movement and rules in chess.

### Functions

- `isInCheckmate(King *king, Board *board)`: Checks if the given king is in checkmate on the board.
- `isInStalemate(King *king, Board *board)`: Checks if the given king is in stalemate on the board.
- `isProtected(Piece *piece, Board *board)`: Checks if the given piece is protected by any other piece on the board.
- `isProtected(string square, string color, Board *board)`: Checks if the given square with the specified color is protected on the board.
- `isPinned(string to, Piece *piece, Board *board)`: Checks if the given piece is pinned to the king on the board.
- `kingTouchesKing(string to, string color, Board *board)`: Checks if the move to the given square would result in the two kings touching on the board.
- `canMove(Move move, Board *board)`: Checks if the given move is valid on the board.
- `canAttack(Move move, Board *board)`: Checks if the given move is a valid attack on the board.
- `canMove(string color, string square, Board *board)`: Checks if any piece of the given color can move to the specified square on the board.
- `canAttack(string color, string square, Board *board)`: Checks if any piece of the given color can attack the specified square on the board.
- `canKingCapturePiece(King *king, Move move, Board *board)`: Checks if the given move allows the king to capture a piece on the board.
- `getValidMoves(Piece *piece, Board *board)`: Retrieves a list of valid moves for the given piece on the board.
- `getValidMoves(string square, Board *board)`: Retrieves a list of valid moves for the piece on the specified square on the board.
- `movePiece(Move move, Board *board)`: Moves the piece according to the given move on the board.
- `moveFreely(Move move, Board *board)`: Moves the piece freely without checking for rules on the board.
- `removePiece(string square, Board *board)`: Removes the piece from the specified square on the board.
- `removePieceFreely(string square, Board *board)`: Removes the piece from the specified square freely without checking for rules on the board.
- `promoteTo()`: Prompts for the type of piece to promote a pawn to.
- `promotePawn(Move move, Pawn *pawn, Board *board)`: Promotes the pawn according to the given move on the board.
- `enpassantPawn(string square, Pawn *pawn, Board *board)`: Handles en passant capture of a pawn on the board.
- `castleKing(string square, King *king, Board *board)`: Castles the king according to the given move on the board.
- `kingWantsToCastle(Move move)`: Checks if the king wants to castle based on the given move.

---

## Piece

The `Piece` class represents a chess piece.

### Public Members

- `printPiece()`: Prints the details of the piece.
- `toString()`: Returns a string representation of the piece.
- `isValidMove(string to, char board[][8])`: Checks if the move to the specified square is a valid move for the piece.
- `getPseudoValidMoves(char board[][8])`: Returns a vector of pseudo-valid moves for the piece.
- `capturesOwnPiece(Coords toCoords, char board[][8])`: Checks if the move to the specified coordinates results in capturing own piece.
- `currentSquare`: The current square where the piece is located.
- `color`: The color of the piece.
- `boardChar`: The character representing the piece on the chess board.
- `value`: The value of the piece.
- `type`: The type of the piece.
- `hasMoved`: Flag indicating if the piece has moved.

### Constants

- `WHITE`: The string representation of the white color.
- `BLACK`: The string representation of the black color.
- `KING`: The string representation of the king piece.
- `QUEEN`: The string representation of the queen piece.
- `ROOK`: The string representation of the rook piece.
- `BISHOP`: The string representation of the bishop piece.
- `KNIGHT`: The string representation of the knight piece.
- `PAWN`: The string representation of the pawn piece.

---

## Pawn

The `Pawn` class represents a pawn piece, which is a derived class of `Piece`.

### Public Members

- `isValidMove(string to, char board[][8])`: Checks if the move to the specified square is a valid move for the pawn.
- `getPseudoValidMoves(char board[][8])`: Returns a vector of pseudo-valid moves for the pawn.
- `isValidCapture(string to, char board[][8])`: Checks if the capture to the specified square is a valid move for the pawn.
- `canPromote(string to, char board[][8])`: Checks if the pawn can be promoted on reaching the specified square.
- `attacksSquare(string square, char board[][8])`: Checks if the pawn attacks the specified square.
- `canEnpassant(string to, Move move_1_before)`: Checks if the move to the specified square is a valid en passant capture.

---

## Rook

The `Rook` class represents a rook piece, which is a derived class of `Piece`.

### Public Members

- `isValidMove(string to, char board[][8])`: Checks if the move to the specified square is a valid move for the rook.
- `getPseudoValidMoves(char board[][8])`: Returns a vector of pseudo-valid moves for the rook.

---

## Knight

The `Knight` class represents a knight piece, which is a derived class of `Piece`.

### Public Members

- `isValidMove(string to, char board[][8])`: Checks if the move to the specified square is a valid move for the knight.
- `getPseudoValidMoves(char board[][8])`: Returns a vector of pseudo-valid moves for the knight.

---

## Bishop

The `Bishop` class represents a bishop piece, which is a derived class of `Piece`.

### Public Members

- `isValidMove(string to, char board[][8])`: Checks if the move to the specified square is a valid move for the bishop.
- `getPseudoValidMoves(char board[][8])`: Returns a vector of pseudo-valid moves for the bishop.

---

## Queen

The `Queen` class represents a queen piece, which is a derived class of `Piece`.

### Public Members

- `isValidMove(string to, char board[][8])`: Checks if the move to the specified square is a valid move for the queen.
- `getPseudoValidMoves(char board[][8])`: Returns a vector of pseudo-valid moves for the queen.

---

## King

The `King` class represents a king piece, which is a derived class of `Piece`.

### Public Members

- `a_rook_moved`: Flag indicating if the rook on the a-file has moved.
- `h_rook_moved`: Flag indicating if the rook on the h-file has moved.
- `isValidMove(string to, char board[][8])`: Checks if the move to the specified square is a valid move for the king.
- `getPseudoValidMoves(char board[][8])`: Returns a vector of pseudo-valid moves for the king.
- `canCastle(string to, char board[][8])`: Checks if the move to the specified square is a valid castle move for the king.
- `isInCheck(char board[][8])`: Checks if the king is in check on the board.
- `isInCheck(string to, char board[][8])`: Checks if the move to the specified square would result in the king being in check.

---

## Pieces

The `Pieces` class represents a collection of chess pieces.

### Public Members

- `pieces`: Vector of `Piece*` representing the pieces.
- `material`: The total material value of the pieces.
- `color`: The color of the pieces.
- `starting_material`: The starting material value for the pieces.

### Public Functions

- `printPieces()`: Prints the details of all the pieces.
- `pieceInSquare(string square, char board[][8])`: Returns the piece located on the specified square.
- `isValidMove(string square, char board[][8])`: Returns a vector of pieces that can move to the specified square.
- `calculateMaterial()`: Calculates and returns the total material value of the pieces.
- `loadPieces(char board[][8])`: Abstract function to load the pieces onto the board.

---

## WhitePieces

The `WhitePieces` class represents a collection of white pieces, which is a derived class of `Pieces`.

### Public Members

- Inherits all the public members from the `Pieces` class.

### Public Functions

- `loadPieces(char board[][8])`: Loads the white pieces onto the board.

---

## BlackPieces

The `BlackPieces` class represents a collection of black pieces, which is a derived class of `Pieces`.

### Public Members

- Inherits all the public members from the `Pieces` class.

### Public Functions

- `loadPieces(char board[][8])`: Loads the black pieces onto the board.

---

## Notation

The `Notation` namespace provides functions for handling chess notations.

### PGN Functions

- `parsePGN(string pgn)`: Parses the PGN (Portable Game Notation) and returns a vector of moves in algebraic notation.
- `moveToPGNMove(Move m, Board *board)`: Converts the given `Move` object to a PGN move notation string.
- `algebraicNotationToMove(string algebraicNotation, int index, Board board)`: Converts the algebraic notation string to a `Move` object, given the index and the `Board` object.
- `pgnToMoves(string pgn, Board *board)`: Converts the PGN string to a vector of `Move` objects, using the given `Board` object.

### FEN Functions

- `isValidFEN(string fen)`: Checks if the given FEN (Forsyth–Edwards Notation) is valid.

---

## Move

The `Move` struct represents a chess move.

### Members

- `from`: The starting square of the move in algebraic notation (e.g., "e2").
- `to`: The destination square of the move in algebraic notation (e.g., "e4").
- `promotion`: Optional. Specifies the piece to which a pawn is promoted (e.g., "Q" for queen, "N" for knight, etc.).

---

## Coords

The `Coords` struct represents the coordinates of a point in a 2-dimensional space.

### Members

- `x`: The x-coordinate of the point.
- `y`: The y-coordinate of the point.

---

## BoardUtils

> The following methods are helpers and they are probably not necessary to the programmer when using the library

The `BoardUtils` namespace provides utility functions for working with chess boards.

### Functions

- `contains(vector<string> moves, string move)`: Checks if a given move is present in a vector of moves.
- `makeMove(string from, string to, char board[][8])`: Makes a move on the chess board, updating the board state.
- `calcDirection(King *king, string square)`: Calculates the direction from a king's position to a target square.
- `printCoords(Coords coords)`: Prints the coordinates of a point in the 2-dimensional space.
- `printCoords(string square)`: Prints the coordinates of a square on the chess board.
- `emptyBoard(char board[][8])`: Empties the chess board, setting all squares to empty.
- `pieceToMove(Coords coords, char board[][8])`: Retrieves the piece on a specified coordinate on the chess board.
- `pieceToMove(string square, char board[][8])`: Retrieves the piece on a specified square on the chess board.
- `translateSquare(string square)`: Translates a square coordinate to its corresponding `Coords` object.
- `translateSquare(Coords coords)`: Translates `Coords` object to its corresponding square coordinate.
- `squareIsAttacked(string square, Pieces *p, char board[][8])`: Determines if a square is attacked by any pieces of a specific color.
- `getRookToCastle(int direction, string color, Board *board)`: Retrieves the rook piece to perform castling in a given direction.
- `offsetSquare(string square, int offset_v, int offset_h)`: Offsets a square coordinate by the specified vertical and horizontal offsets.
- `addSpaces(int row, int starting, int numberOfSpaces, char board[][8])`: [Not used] Adds spaces to a row of the chess board.
- `addSpaces(int index, int num, string fen)`: Adds spaces to a Fen string at the specified index.
- `replaceSpaces(string fen)`: Replaces spaces in a Fen string with slashes.
- `splitString(const std::string& input, char delimiter)`: Splits a string into a vector of substrings based on a delimiter.
- `findMove(Move move, vector<Move> moves)`: Finds the index of a move within a vector of moves.
- `isValidSquare(string square)`: Checks if a given string represents a valid chess square.
- `characterQuantity(char c, string str)`: Counts the quantity of a specific character in a string.

