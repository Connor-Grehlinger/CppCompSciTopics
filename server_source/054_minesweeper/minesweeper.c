#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#define CLICK_KNOWN_MINE -2
#define CLICK_INVALID -1
#define CLICK_CONTINUE 0
#define CLICK_LOSE 1

#define KNOWN_MINE -3
#define HAS_MINE -2
#define UNKNOWN -1

#define IS_MINE(x) ((x) == HAS_MINE || (x) == KNOWN_MINE)


struct _board_t {
  int ** board;
  int width;
  int height;
  int totalMines;
};

typedef struct _board_t board_t;

void addRandomMine(board_t * b) {
  int x;
  int y;
  //we could have a board too small for the number
  //of mines taht we request. try w*h*10 times before
  //we give up
  int limit = b->width * b->height * 10;
  do {
    x = random() % b->width;
    y = random() % b->height;
    assert(limit > 0);
    limit--;
  } while(b->board[y][x] == HAS_MINE);
  b->board[y][x] = HAS_MINE;
}

board_t * makeBoard(int w, int h, int numMines) {
  //WRITE ME!
  // The board struct must be initialized before calling addRandomMine
  // which will be called numMines times

  // malloc the fields of board struct first, also board[y][x], y--> 0 to h, x--> 0 to w
  // start with int ** board (2D integer array)
  
  int ** board = malloc(h * sizeof(*board));
  // now you have an array of pointers to an array of ints, there are h pointers
  for (int i = 0; i < h; i++){
    // board[i] is the index of the ith pointer to an int array (boardRow)
    board[i] = malloc(w * sizeof(**board));
    // this allocates memory for w ints (a board row) which is pointed at by board[i]
  }
  // now board field of struct is allocated
  board_t * newBoardPtr = malloc(sizeof(*newBoardPtr));

  // now fill in all squares of the board with UNKNOWN
  for (int j = 0; j < h; j++){
    for (int i = 0; i < w; i++){
      board[j][i] = UNKNOWN;
    }
  }
  
  newBoardPtr->board = board;
  newBoardPtr->width = w;
  newBoardPtr->height = h;
  newBoardPtr->totalMines = numMines;

  for (int i = 0; i < numMines; i++){
    addRandomMine(newBoardPtr);
  }  
  return newBoardPtr;
}

void printBoard(board_t * b) {    
  int found = 0;
  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x/10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x%10);
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");
  for (int y = 0; y < b->height; y++) {
    printf("%2d: ", y %100);
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == KNOWN_MINE) {
	printf("*");
	found++;
      }
      else if (b->board[y][x] < 0) {
	printf("?");
      }
      else if (b->board[y][x] == 0) {
	printf(" ");
      }
      else {
	printf("%d", b->board[y][x]);
      }
    }
    printf("\n");
  }
  printf("\n----");
  for (int x = 0; x < b->width; x++) {
    printf("-");
  }
  printf("\n");

  printf("    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x/10);
  }
  printf("\n    ");
  for (int x = 0; x < b->width; x++) {
    printf("%d",x%10);
  }
  printf("\nFound %d of %d mines\n", found, b->totalMines);
}

int countMines(board_t * b, int x, int y) {
  //WRITE ME!
  // count the mines in the 8 squares arroud the x,y coordinate
  // make sure you don't go out of bounds
  // use IS_MINE(b->board[y][x]) for checking
  int rightBound = b->width - 1; // -1 because its an index
  int bottomBound = b->height - 1;
  // do check assuming you're in bounds first, then handle corner cases
  int mineCount = 0;
  if ((x < rightBound) && (y < bottomBound) && (x > 0) && (y > 0)){
    //printf("No constraint.\n");
    for (int i = y - 1; i < y + 2; i++){ // row
      for (int j = x - 1; j < x + 2; j++){ // column
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  // x == 0 or y in range
  else if ((x == 0) && (0 < y) && (y < bottomBound)){  // constrain the columns
    //printf("x == 0, y is gucci\n");
    for (int i = y - 1; i < y + 2; i++){ //row
      for (int j = x; j < x + 2; j++){ //column
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  else if ((x == 0) && (y == bottomBound)){  // constrain both
    //printf("x == 0, y == bottomBound\n");
    for (int i = y - 1; i < y + 1; i++){ //row
      for (int j = x; j < x + 2; j++){ //column
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  else if ((y == 0) && (0 < x) && (x < rightBound)){  // constrain the rows
    //printf("y == 0, x is gucci\n");
    for (int i = y; i < y + 2; i++){ // row
      for (int j = x - 1; j < x + 2; j++){ // column
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  else if ((y == 0) && (x == rightBound)){  // constrain both
    //printf("y == 0, x == rightBound\n");
    for (int i = y; i < y + 2; i++){ //row
      for (int j = x - 1; j < x + 1; j++){ //column
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  else if((y == 0) && (x == 0)){
    // both x and y == 0, constrain both
    //printf("x && y == 0 conditional\n");
    for (int i = y; i < y + 2; i++){  // rows
      for (int j = x; j < x + 2; j++){ // columns
	//printf("IS_MINE: %d\n",IS_MINE(b->board[i][j]));
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  } 
  else if ((x == rightBound) && (0 < y) && (y < bottomBound)){ // constrain columns
    //printf("x == rightBound, y is gucci\n");
    for (int i = y - 1; i < y + 2; i++){  // rows
      for (int j = x - 1; j < x + 1; j++){ // columns
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  else if ((y == bottomBound) && (0 < x) && (x < rightBound)){ // constrain rows
    //printf("y == bottomBound, x is gucci\n");
    for (int i = y - 1; i < y + 1; i++){ // rows
      for (int j = x - 1; j < x + 2; j++){ // columns
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  else{
    // both x == rightBound and y == bottomBound
    //printf("x == rightBound, y == bottomBound\n");
    for (int i = y - 1; i < y + 1; i++){ // constrain both
      for (int j = x - 1; j < x + 1; j++){
	if (i == y && j == x){
	  continue;
	}
	else if (IS_MINE(b->board[i][j])){
	  mineCount++;
	}
      }
    }
  }
  
  return mineCount;
}

int click (board_t * b, int x, int y) {
  if (x < 0 || x >= b->width ||
      y < 0 || y >= b->height) {
    return CLICK_INVALID;
  }
  if (b->board[y][x] == KNOWN_MINE) {
    return CLICK_KNOWN_MINE;
  }
  if (b->board[y][x] == HAS_MINE) {
    return CLICK_LOSE;
  }
  if (b->board[y][x] != UNKNOWN) {
    return CLICK_CONTINUE;
  }

  b->board[y][x] = countMines(b,x,y);
  return CLICK_CONTINUE;
}

int checkWin(board_t * b) {
  //WRITE ME!
  for (int j = 0; j < b->height; j++){
    for(int i = 0; i < b->width; i++){
      if (b->board[j][i] == UNKNOWN){
	return 0;
      }
    }
  }
  return 1;
}

void freeBoard(board_t * b) {
  //WRITE ME!
  // free all of the int ** board first
  // then free the actual board struct
  for (int j = 0; j < b->height; j++){
    free(b->board[j]);
  }
  free(b->board);
  free(b);
}

int readInt(char ** linep, size_t * lineszp) {
  if (getline (linep, lineszp, stdin) == -1) {
    fprintf (stderr,"End of file from keyboard reading a number.  Quitting\n");
    exit(EXIT_FAILURE);
  }
  char * endptr = NULL;
  long int x = strtol (*linep, &endptr, 10);
  if (endptr == *linep) {
    fprintf (stderr,"You did not enter any valid number\n");
    printf ("Please try again\n");
    return readInt (linep, lineszp);
  }
  if (*endptr != '\n') {
    fprintf( stderr, 
	     "Input was not entirely a number (junk at end)\n");
    printf ("Please try again\n");
    return readInt (linep, lineszp);
  }
  if (x > INT_MAX) {
    fprintf(stderr,"%ld is too big for an int!\n", x);
    printf("Please try again\n");
    return readInt(linep, lineszp);
  }
  return x;
}

void doReveal(board_t * b, int x, int y, int revealMines){
  for (int dy = -1; dy <=1 ; dy++) {
    for (int dx = -1; dx <=1 ; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width &&
	  ny >= 0 && ny < b->height) {
	if (revealMines) {
	  assert(b->board[ny][nx] != UNKNOWN);
	  if (b->board[ny][nx] == HAS_MINE){
	    b->board[ny][nx] = KNOWN_MINE; 
	  }
	}
	else  {
	  assert(b->board[ny][nx] != HAS_MINE);
	  if (b->board[ny][nx] == UNKNOWN) {
	    b->board[ny][nx] = countMines(b,nx,ny);
	  }
	}
      }
    }
  }
}

int maybeReveal(board_t * b, int x, int y) {
  int unknownSquares = 0;
  int knownMines = 0;
  for (int dy = -1; dy <=1 ; dy++) {
    for (int dx = -1; dx <=1 ; dx++) {
      int nx = x + dx;
      int ny = y + dy;
      if (nx >= 0 && nx < b->width &&
	  ny >= 0 && ny < b->height) {
	if (b->board[ny][nx] == UNKNOWN || 
	    b->board[ny][nx] == HAS_MINE) {
	  unknownSquares++;
	}
	else if(b->board[ny][nx] == KNOWN_MINE) {
	  knownMines++;
	}
      }
    }
  }
  assert(knownMines + unknownSquares >= b->board[y][x]);
  assert(knownMines <= b->board[y][x]);
  if (unknownSquares > 0) {
    int revealMines = (knownMines + unknownSquares == 
		       b->board[y][x]);
    int allKnown = knownMines == b->board[y][x];
    if(revealMines || allKnown) {
      assert(!revealMines || !allKnown);
      doReveal(b,x,y, revealMines);
      return 1;
    }
  }
  return 0;
}
void determineKnownMines(board_t * b) {
  int foundMore = 0;
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] >= 0) {
	foundMore = maybeReveal(b,x,y) || foundMore;
      }
    }
  }
  if (foundMore) {
    determineKnownMines(b);
  }
}

void revealMines(board_t * b) {
  for (int y = 0; y < b->height; y++) {
    for (int x = 0; x < b->width; x++) {
      if (b->board[y][x] == HAS_MINE) {
	b->board[y][x] = KNOWN_MINE;
      }
    }
  }
}
int playTurn(board_t * b, char ** linep, size_t *lineszp) {
  printf("Current board:\n");
  printBoard(b);
  printf("x coordinate:\n");
  int x = readInt(linep, lineszp);
  printf("y coordinate:\n");
  int y = readInt(linep, lineszp);
  int result = click(b,x,y);
  determineKnownMines(b);
  if (result == CLICK_LOSE) {
    printf("Oh no! That square had a mine. You lose!\n");
    revealMines(b);
    printBoard(b);
    return 1;
  }
  else if (result == CLICK_INVALID) {
    printf("That is not a valid square, please try again\n");
  }
  else if (result == CLICK_KNOWN_MINE) {
    printf("You already know there is a mine there!\n");
  }
  else if(checkWin(b)) {
    printBoard(b);
    printf("You win!\n");
    return 1;
  }
  return 0;
}


int main(int argc, char ** argv) {
  if (argc != 4) {
    fprintf(stderr,"Usage: minesweeper width height numMines\n");
    return EXIT_FAILURE;
  }
  int width = atoi(argv[1]);
  int height = atoi(argv[2]);
  int numMines = atoi(argv[3]);
  if (width <= 0 || height <= 0 || numMines <= 0) {
    fprintf(stderr,
	    "Width, height, and numMines must all be positive ints\n");
    return EXIT_FAILURE;
  }
  char * line = NULL;
  size_t linesz = 0;

  do {
    board_t * b = makeBoard (width, height, numMines);
    int gameOver = 0;
    while (!gameOver) {
      gameOver = playTurn(b, &line, &linesz);
    }
    freeBoard(b);
    do {
      printf("Do you want to play again?\n");
    } while(getline(&line, &linesz, stdin) == -1);
  } while(line[0] == 'Y' || line[0] == 'y');
  free(line);
  return EXIT_SUCCESS;
}
