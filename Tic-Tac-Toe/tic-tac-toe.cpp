#include <iostream>
using namespace std;

char game[3][3];

// a function to draw the board
void draw_board() {
  cout << endl;
  cout << game[0][0] << " | " << game[0][1] << " | " << game[0][2] << endl;
  cout << "__  _   __ " << endl;
  cout << endl;
  cout << game[1][0] << " | " << game[1][1] << " | " << game[1][2] << endl;
  cout << "__  _   __ " << endl;
  cout << endl;
  cout << game[2][0] << " | " << game[2][1] << " | " << game[2][2] << endl;
}

// a funtion to check if the player has won
bool check_win_player() {

  for (int i = 0; i < 3; i++) {
    if (game[i][0] == game[i][1] && game[i][1] == game[i][2] &&
        game[i][0] == 'O') {
      return true;
    }
  }

  for (int i = 0; i < 3; i++) {
    if (game[0][i] == game[1][i] && game[1][i] == game[2][i] &&
        game[0][i] == 'O') {
      return true;
    }
  }

  if (game[0][0] == game[1][1] && game[1][1] == game[2][2] &&
      game[0][0] == 'O') {
    return true;
  }

  if (game[0][2] == game[1][1] && game[1][1] == game[2][0] &&
      game[1][1] == 'O') {
    return true;
  }

  return false;
}

// a funtion to check if the computer has won
bool check_win_computer() {
  for (int i = 0; i < 3; i++) {
    if (game[i][0] == game[i][1] && game[i][1] == game[i][2] &&
        game[i][0] == 'X') {
      return true;
    }
  }

  for (int i = 0; i < 3; i++) {
    if (game[0][i] == game[1][i] && game[1][i] == game[2][i] &&
        game[0][i] == 'X') {
      return true;
    }
  }

  if (game[0][0] == game[1][1] && game[1][1] == game[2][2] &&
      game[0][0] == 'X') {
    return true;
  }

  if (game[0][2] == game[1][1] && game[1][1] == game[2][0] &&
      game[1][1] == 'X') {
    return true;
  }

  return false;
}

// a funtion to check if game results in a draw
bool check_draw() {

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (game[i][j] != 'X' && game[i][j] != 'O')
        return false;
    }
  }

  return true;
}

// implemantation of minimax algorithm
int minimax(bool Max, int depth) {

  if (check_win_computer() == true)
    return 10;

  else if (check_win_player() == true)
    return -10;

  else if (check_draw() == true)
    return 0;
  if (Max == true) {
    int optimum = INT16_MIN;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (game[i][j] == '*') {
          game[i][j] = 'X';
          optimum = max(optimum, minimax(!Max, depth + 1));
          game[i][j] = '*';
        }
      }
    }
    return optimum;
  } else {
    int optimum = INT16_MAX;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (game[i][j] == '*') {
          game[i][j] = 'O';
          optimum = min(optimum, minimax(!Max, depth + 1));
          game[i][j] = '*';
        }
      }
    }
    return optimum;
  }
}

// A function to find optimum move that can be made
void Find_Best_Move() {
  int best_value = INT16_MIN;
  int best_x = -1, best_y = -1;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      if (game[i][j] == '*') {
        game[i][j] = 'X';
        int move_value = minimax(false, 0);
        game[i][j] = '*';
        if (move_value > best_value) {
          best_x = i;
          best_y = j;
          best_value = move_value;
        }
      }
    }
  }
  game[best_x][best_y] = 'X';
}
int main() {
  int player_score = 0;
  int computer_score = 0;
  char play_again;
  do {
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        game[i][j] = '*';
      }
    }
    cout << "TIC - TAC - TOE" << endl;
    cout << endl;
    cout << "user -> 'O' computer -> 'X' " << endl;
    cout << endl;
    draw_board();
    int x, y;
    while (1) {
    label1:
      cout << "Enter Your Move(x,y): ";
      cin >> x >> y;
      if (game[x - 1][y - 1] == '*' && x < 4 && y < 4) {
        game[x - 1][y - 1] = 'O';
        draw_board();
        cout << endl;
      } else {
        cout << "Invalid Move" << endl;
        goto label1;
      }
      if (check_win_player() == true) {
        cout << "You won " << endl;
        player_score++;
        break;
      }
      cout << "CPU Move :" << endl;
      Find_Best_Move();
      draw_board();
      cout << endl;
      if (check_win_computer() == true) {
        cout << "You lose " << endl;
        computer_score++;
        break;
      }
      if (check_draw() == true) {
        cout << "Game Drawn: " << endl;
        break;
      }
    }

    cout << "Your Score: " << player_score
         << " Computer Score: " << computer_score << endl;
    cout << "Do you want to play again?(Y/N): ";
    cin >> play_again;

  } while (play_again == 'Y');

  cout << "Your Score: " << player_score << endl;
  cout << "Computer Score: " << computer_score << endl;
  return 0;
}
