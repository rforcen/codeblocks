#pragma once

#include <vector>
#include <string>

#include "Thread.h"
#include <boost/multiprecision/cpp_int.hpp>

using uint1024_t = boost::multiprecision::number<boost::multiprecision::cpp_int_backend<1024, 1024, boost::multiprecision::unsigned_magnitude,boost::multiprecision::unchecked, void>, boost::multiprecision::et_off>;
using namespace std;


// Board

class Board {
  public:
    Board() {}
    Board(int n) : n(n), n1(n-1), board(vector<int>(n)), ld(vector<bool>(n*2)), rd(vector<bool>(n*2)), cl(vector<bool>(n*2)) {}
    Board(const Board&b) {
        this->n=b.n;
        this->n1=b.n1;
        this->board=b.board;
        this->ld=b.ld;
        this->rd=b.rd;
        this->cl=b.cl;
    }
    inline void set(int col, int val) {
        board[col] = val;

        ld[val - col + n1] = true;
        rd[val + col] = true;
        cl[val] = true;
    }

    inline int get(int col) {
        return board[col];
    }

    inline void reset(int col, int val) {
        board[col] = 0;

        ld[val - col + n1] = false;
        rd[val + col] = false;
        cl[val] = false;
    }

    inline bool isValidPosition(int col, int i) {
        return ! (ld[i - col + n1] || rd[i + col] || cl[i]);
    }

    inline bool isNotValidPosition(int col, int i) {
        return ! isValidPosition(col, i);
    }

    int cmp(const Board &b0, const Board&b1) {
        for (int i=0; i<b0.n; i++)
            if (b0[i] != b1[i]) return b0[i] - b1[i];
        return 0;
    }
    bool operator==(const Board&b) {
        return cmp(*this, b)==0;
    }
    bool operator<(const Board&b) {
        return cmp(*this, b)<0;
    }

    inline int& operator [](int i) {
        return board[i];    // mutator
    }
    inline const int& operator [](int i) const {
        return board[i];
    }
    string toString() {
        string s;
        for (int i=0; i<n; i++) s+=to_string(board[i]+1)+ " ";
        return s;
    }

    int n=0, n1=0;
    vector<int> board;
    vector<bool>ld, rd, cl;
};


// Queens

static bool globalRunning = false; // shared by all Queens instances, static simulator w/out .cpp

class Queens {
  public:
    Queens() {}
    Queens(int n) : n(n), board(Board(n)), running(&globalRunning) {
        *running=false;
    }
    Queens(const Queens&q) {
        *this=q; // shallow copy
        this->board=q.board; // explicit copy vector
        this->solutions=q.solutions;
    }

    virtual ~Queens() {}

    int n=0;
    Board board;
    uint1024_t countEvals=0;
    vector<Board>solutions;
    int currentSol=0, countSolutions=0, maxSolutions=0;
    bool *running=nullptr;

    inline bool isRunning() {
        return *running;
    }

    void saveSolution() {
        if (isValid()) solutions.push_back(board);
    }

    void saveSolution(Board&b) {
        if (isValid()) solutions.push_back(b);
    }

    void clear() {
        *this = Queens(n);
    }

    inline void addEvalN() {
        countEvals += n;
    }

    bool isValid() {
        for (int i=0; i<n-1; i++) {
            for (int j=i+1; j<n; j++) {
                if (board[i] == board[j]) return false; // horizontal -> ci=cj
                if (i - board[i] == j - board[j]) return false; // vertical  / ri-ci = rj-cj
                if (abs(board[i] - board[j]) == abs(i - j)) return false; // vertical \ |ci-cj| = |i-j|
            }
        }
        return true;
    }

    void scanFirst(int col = 0) {
        if (*running) {
            if (col == n) {
                saveSolution();
                *running = false;
            } else {
                for (int i=0; i<n; i++) {
                    if (board.isValidPosition(col, i)) {
                        board.set(col, i);
                        scanFirst(col + 1); // recur to place rest
                        board.reset(col, i); // unmove
                    }
                }
                addEvalN();
            }
        }
    }

  public:

    void stop() {
        *running=false;
    }

    void loadSolution(int sn) {
        if (sn<(int)solutions.size())
            board=solutions[sn];
    }

    void findFirst() {
        clear();

        int nth=min(n, Thread::getnthreads());
        countEvals=0;
        vector<Queens>qs(nth, *this);

        for (int i=0; i<nth; i++) {
            qs[i].board.set(0, i);
            qs[i].board.set(1, ((n / 2) + i + 1) % n);
        }

        *running=true;
        Thread(nth).run([&qs](int i) {
            qs[i].scanFirst(2);
        });

        for (auto &q:qs) {// add all found solutions
            solutions.insert(solutions.end(), q.solutions.begin(), q.solutions.end());
            countEvals += q.countEvals;
        }
    }


// transformations

    void translate_vert() { // up
        for (int i=0; i<n; i++)
            board[i]=(board[i] + 1) % n;
        saveSolution();
    }

    void translate_horz() { // right
        Board v(n);

        for (int i=0; i<n-1; i++)
            v[i + 1] = board[i];
        v[0] = board[n - 1];
        saveSolution(v);
    }

    void rotate90() {
        Board rot_queens(n);

        for (int i=0; i<n; i++) {
            rot_queens[i] = 0;
            for (int j=0; j<n; j++) { // find i
                if (board[j] == i) {
                    rot_queens[i] = n - j - 1;
                    break;
                }
            }
        }
        saveSolution(rot_queens);
    }

    void mirror_horz() {
        for (int i=0; i<n; i++)
            board[i] = (n - 1) - board[i];
        saveSolution();
    }

    void mirror_vert() {
        for (int i=0; i<n / 2; i++)
            swap(board[i], board[n - 1 - i]);
        saveSolution();
    }

    void transformations() {
        solutions.clear();
        currentSol = 0;

        auto b = board;

        for (int mv=0; mv<=1; mv++) {
            for (int mh=0; mh<=1; mh++) {
                for (int r90=0; r90<=3; r90++) {
                    for (int tv=0; tv<n; tv++) { // translations
                        for (int th=0; th<n; th++)
                            translate_vert(); // tV
                        translate_horz(); // tH
                    }
                    rotate90(); // R90
                }
                mirror_horz(); // mH
            }
            mirror_vert(); // mV
        }

        // sort_solutions_unique()
        board = b;
        sort( solutions.begin(), solutions.end() );
        solutions.erase( unique( solutions.begin(), solutions.end() ), solutions.end() );
    }

  protected:

  private:
};
