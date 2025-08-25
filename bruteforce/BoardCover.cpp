
#include <iostream>
#include <vector>
using namespace std;
//h 과 w  높이와 , 넓이를 입력 받고
// 보드판의 모형이 주어질때 
// 해당 모드판에서  3칸짜리 l 로  흰칸을 채울수 있는 방법을 구하라.

// 깊게 고민하지 않고 생각해보면 , 일단 .(흰칸) 의 갯수는 3 의 배수여야함
// 입력은 배열을  받을테니 , 각 하나의 칸들을 true  = 검은색, white 는 하얀색으로 놓고 , 
// 음 일단 고정적인 자리가 있다. < 내생각 , 그리고 하나 씩 채우면 된다 ,
// l 자의 모형은 크게  4가지로 밖에 나올수가 없다 ., 각 점마다  해당 모양이 들어올수 있는지 테스트 해본다?,  근데 이러면 같은 모양으로 밖에 칠할수가 없지 않나 ?
// 필요 함수,  점 기준  4가지 체크 함수, 2 , 경계값 체크 하는 함수 , 3 재귀?


const int L_shapes[4][2][2] = {
    { {0,1}, {1,0} }, // └ 모양
    { {0,1}, {-1,0} }, // ┌ 모양
    { {0,-1}, {1,0} }, // ┘ 모양
    { {0,-1}, {-1,0} } // ┐ 모양
};
vector<vector<bool>> board;

void setL(vector<vector<bool>>& board, int y, int x, int shapeIdx, bool fill) {
    int dy1 = L_shapes[shapeIdx][0][0];
    int dx1 = L_shapes[shapeIdx][0][1];
    int dy2 = L_shapes[shapeIdx][1][0];
    int dx2 = L_shapes[shapeIdx][1][1];

    int coords[3][2] = {{y,x}, {y+dy1, x+dx1}, {y+dy2, x+dx2}};
    for (auto &c : coords) board[c[0]][c[1]] = fill;
}

bool findFirstWhite (vector<vector<bool>>& board , int & y, int& x) {
	for(y=0; y<board.size(); y++) {
		for(x=0; x<board[0].size(); x++) {
			if(!board[y][x]) return true;
		}
	}
	return false;
}
int countWhite (const vector<vector<bool>>& board) {
	int cnt= 0; 
	for (auto &row: board) {
		for(bool cell: row) {
			if(!cell) cnt++;
		}
	}
	return cnt;	
}
bool canPlace(const vector<vector<bool>>& board, int y, int x, int shapeIdx) {
    int dy1 = L_shapes[shapeIdx][0][0];
    int dx1 = L_shapes[shapeIdx][0][1];
    int dy2 = L_shapes[shapeIdx][1][0];
    int dx2 = L_shapes[shapeIdx][1][1];

    int h = board.size(), w = board[0].size();
    int coords[3][2] = {{y,x}, {y+dy1, x+dx1}, {y+dy2, x+dx2}};

    for (auto &c : coords) {
        int ny = c[0], nx = c[1];
        if (ny < 0 || ny >= h || nx < 0 || nx >= w) return false;
        if (board[ny][nx]) return false; // 검은칸
    }
    return true;
}

int cover(vector<vector<bool>>& board) {
    int y, x;
    if (!findFirstWhite(board, y, x)) return 1; // 더 이상 흰칸 없음

    int total = 0;
    for (int shape = 0; shape < 4; shape++) {
        if (canPlace(board, y, x, shape)) {
            setL(board, y, x, shape, true);
            total += cover(board);
            setL(board, y, x, shape, false);
        }
    }
    return total;
}

int main() {
vector<vector<bool>> board = {
    {true,  false, false, false, false, false, true},
    {true,  false, false, false, false, false, true},
    {true,  true,  false, false, true,  true,  true}
};

    if (countWhite(board) % 3 != 0) {
        cout << 0 << endl;
    } else {
        cout << cover(board) << endl;
    }
    return 0;
}