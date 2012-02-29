#include <iostream>
#include <string>
#include <queue>

#include <cstring>


class move_t {
public:
  static int digest(const std::string& board);

public:
  move_t(std::string board) : board_(board), index_(0) {};

  inline std::string board() const { return board_; };
  inline int         index() const { return index_; };

  move_t next(std::string board);

private:
  std::string board_;
  int         index_;
};

move_t move_t::next(std::string board)
{
  move_t move(board);

  move.index_ = index_ + 1;

  return move;
}

int move_t::digest(const std::string& board)
{
  int digest = 0;

  for (int i = 0; i < board.size(); i ++) {
    digest = digest << 1;

    if (board[i] == 'o')
      digest |= 1;
  }

  return digest;
}


class EllysCheckers {
public:
  std::string getWinner(std::string board);
};

std::string EllysCheckers::getWinner(std::string board)
{
  int size = board.size();

  std::queue<move_t> queue;

  queue.push(move_t(board));

  char memo[1 << 20];

  memset((void*)memo, -1, sizeof(memo));

  for ( ; 1; queue.pop()) {
    move_t move = queue.front();

    std::string board = move.board();

    if (board[size - 1] == 'o')
      board[size - 1] = '.';

    //    std::cerr << move.index() << ' ' << board << std::endl;

    if (board.find('o') == std::string::npos)
      if (move.index() % 2) {
	return "YES";
      }
      else {
	return "NO";
      }

    for (int i = 0; i < size; i ++)
      if (board[i + 0] == 'o' &&
	  board[i + 1] == 'o' &&
	  board[i + 2] == 'o' &&
	  board[i + 3] == '.') {

	std::string b(board);

	b[i + 0] = '.';
	b[i + 3] = 'o';

	int digest = move_t::digest(b);

	if (memo[digest] == -1) {
	  queue.push(move.next(b));
	  
	  memo[digest] = move.index() + 1;
	}
      }

    // std::cerr << "--" << std::endl;

    for (int i = 0; i < size - 1; i ++)
      if (board[i + 0] == 'o' &&
	  board[i + 1] == '.') {
	
	std::string b(board);
	
	b[i + 0] = '.';
	b[i + 1] = 'o';

	int digest = move_t::digest(b);

	if (memo[digest] == -1) {
	  queue.push(move.next(b));
	  
	  memo[digest] = move.index() + 1;
	}
      }
  }
}

int main(int argc, char** argv)
{
  std::string board;

  std::cin >> board;

  std::cout << EllysCheckers().getWinner(board) << std::endl;
}
