#include<stdio.h>
int addToBoard(char c , int index, int five ,char board[6][7],int posI[42], int posJ[42], int pointer);
void printBoard(char board[6][7]);
int checkWin(char board[6][7], char c);
int ver(int i, int j, char board[6][7], char c);
int hor(int i, int j, char board[6][7], char c);
int diaL(int i, int j, char board[6][7], char c);
int diaR(int i, int j, char board[6][7], char c);

int main(int argc, char const *argv[]) {
  char board[6][7] = {{ ' ', ' ', ' ', ' ' ,' ', ' ', ' '}
                     ,{ ' ', ' ', ' ', ' ' ,' ', ' ', ' '}
                     ,{ ' ', ' ', ' ', ' ' ,' ', ' ', ' '}
                     ,{ ' ', ' ', ' ', ' ' ,' ', ' ', ' '}
                     ,{ ' ', ' ', ' ', ' ' ,' ', ' ', ' '}
                     ,{ ' ', ' ', ' ', ' ' ,' ', ' ', ' '}};
  int posI[42];
  int posJ[42];
  int pointer = -1;
  printf("Welcome!\n\n");
  printBoard(board);
  int oTurn = 0;
  int xTurn = 1;
  int winner = 0;
  while (!winner) {
    while (!oTurn) {
      int index;
      printf("Player X, please enter a column number: (or 0 to Undo) \n");
      char enter;
      if(scanf("%d%c", &index, &enter) != 2 || enter != '\n'){
        printf("Invalid input, bye-bye!\n");
        return 0;
      }
      if (index<0||index>7) {
        printBoard(board);
        printf("Invalid input, the number must be between 1 to 7: \n");
      }
      else if(index==0){
        if (pointer==-1) {
          printBoard(board);
          printf("Board is empty - can't undo!\n");
        }
        else{
          board[posI[pointer-1]][posJ[pointer-1]]=' ';
          printBoard(board);
          pointer--;
          oTurn = 1;
          xTurn = 0;
        }
      }
      else{
        if ((addToBoard('X', index, 5, board, posI, posJ, pointer)+1)>0) {
          printBoard(board);
          pointer++;
          if(checkWin(board, 'X')){
            printf("Player X Wins!\n");
            return winner=1;
          }
          else if(winner==0&&pointer==41){
            printf("It's a tie!\n");
            return 0;
          }
          else{
            oTurn = 1;
            xTurn = 0;
          }
        }
      }
    }
    while (!xTurn) {
      int index;
      printf("Player O, please enter a column number: (or 0 to Undo) \n");
      char enter;
      if(scanf("%d%c", &index, &enter) != 2 || enter != '\n'){
        printf("Invalid input, bye-bye!\n");
        return 0;
      }
      if (index<0||index>7) {
        printBoard(board);
        printf("Invalid input, the number must be between 1 to 7: \n");
      }
      else if(index==0){
        if (pointer==-1) {
          printBoard(board);
          printf("Board is empty - can't undo!\n");
        }
        else{
          board[posI[pointer-1]][posJ[pointer-1]]=' ';
          printBoard(board);
          pointer--;
          oTurn = 0;
          xTurn = 1;
        }
      }
      else{
        if ((addToBoard('O', index, 5, board, posI, posJ, pointer)+1)>0) {
          printBoard(board);
          pointer++;
          if(checkWin(board, 'O')){
            printf("Player O Wins!\n");
            return winner=1;
          }
          else if(winner==0&&pointer==41){
            printf("It's a tie!\n");
            return 0;
          }
          else{
            oTurn = 0;
            xTurn = 1;
          }
        }
      }
    }
  }
  return 0;
}

int addToBoard(char c , int index, int five ,char board[6][7],int posI[42], int posJ[42], int pointer) {
  if (five<0){
    printBoard(board);
    printf("\nInvalid input, this column is full. Please choose another one: \n");
    return -1;
  }
  else if(board[five][index-1]=='X'||board[five][index-1]=='O'){
    five--;
    addToBoard(c,index,five,board,posI,posJ,pointer);
  }
  else{
        board[five][index-1]=c;
        posI[pointer]=five;
        posJ[pointer]=index-1;
        return five;
  }
}
void printBoard(char board[6][7]){
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 7; j++) {
      printf(" | %c | ",board[i][j]);
    }
    printf("\n");
  }
  char line[]= {'1','2','3','4','5','6','7'};
  for (size_t i = 0; i < 7; i++) {
  printf("   %c   ",line[i]);
  }
  printf("\n");
}

int checkWin(char board[6][7], char c){
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 7; j++) {
      if (ver(i ,j ,board,c)||hor(i ,j ,board, c)||diaL(i ,j ,board, c)||diaR(i ,j ,board, c)) {
        return 1;
      }
    }
  }
  return 0;
}
int ver(int i, int j, char board[6][7], char c){
  if(i>2){
    if((board[i][j]==c)&&(board[i-1][j]==c)&&(board[i-2][j]==c)&&(board[i-3][j]==c)){
        return 1;
      }
      else{
        return 0;
      }
  }
  else{
    return 0;
  }
}
int hor(int i, int j, char board[6][7], char c){
  if(j<3){
      if((board[i][j]==c)&&(board[i][j+1]==c)&&(board[i][j+2]==c)&&(board[i][j+3]==c)){
        return 1;
      }
      else{
        return 0;
      }
  }
  else{
    return 0;
  }
}
int diaL(int i, int j, char board[6][7], char c){
  if(j>=3||i>=3){
      if((board[i][j]==c)&&(board[i-1][j-1]==c)&&(board[i-2][j-2]==c)&&(board[i-3][j-3]==c)){
        return 1;
      }
      else{
        return 0;
      }
  }
  else{
    return 0;
  }
}
int diaR(int i, int j, char board[6][7], char c){
  if(j<=3||i>=3){
      if((board[i][j]==c)&&(board[i-1][j+1]==c)&&(board[i-2][j+2]==c)&&(board[i-3][j+3]==c)){
        return 1;
      }
      else{
        return 0;
      }
    }
  else{
    return 0;
  }
}
