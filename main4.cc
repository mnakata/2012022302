#include <iostream>
#include <string>
#include <queue>

#include <cstring>


class EllysCheckers {
public:
  std::string getWinner(std::string board);
};

std::string EllysCheckers::getWinner(std::string board)
{
  int size = board.size();

  unsigned int b = 0;

  for (int i = 0; i < size; i ++) {
    b <<= 1;
    
    if (board[size - i - 1] == 'o')
      b |= 1;
  }

  b &= (1 << size - 1) - 1;

  char dp[2][2 << 20];

  memset((void*)dp, -1, sizeof(dp));

  dp[0][b] = dp[1][b] = 0;

  char* cur  = dp[0];
  char* next = dp[1];

  for (int i = 0; cur[0] == -1; i ++, std::swap(cur, next)) {
    for (int j = 0; j < (1 << size); j ++) {
      if (cur[j] == i) {
	int mask = 15, pat = 7, excl = 9;

	for (int k = 0; k < size - 4 + 1; k ++, mask <<= 1, excl <<= 1, pat <<= 1)
	  if ((j & mask) == pat) {
	    int c = j ^ excl & ((1 << size - 1) - 1);
	    
	    if (cur[c] == -1)
	      cur[c] = next[c] = i + 1;
	  }

	mask = 3, pat = 1, excl = 3;

	for (int k = 0; k < size - 1; k ++, mask <<= 1, excl <<= 1, pat <<= 1)
	  if ((j & mask) == pat) {
	    int c = j ^ excl & ((1 << size - 1) - 1);
	    
	    if (cur[c] == -1)
	      cur[c] = next[c] = i + 1;
	  }
      }
    }
  }

  if (cur[0] % 2) {
    return "YES";
  }
  else {
    return "NO";
  }
}

int main(int argc, char** argv)
{
  std::string board;

  std::cin >> board;

  std::cout << EllysCheckers().getWinner(board) << std::endl;
}
