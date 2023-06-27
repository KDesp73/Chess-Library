#pragma once

#include <vector>
#include <string>

using namespace std;

namespace TestFens{
static vector<string> mate_fens = {
    "8/1k6/8/8/4PPP1/4PKP1/3n1R2/5q2",
    "8/6q1/8/4k3/8/8/5n1P/6NK",
    "7q/8/8/5k1K/8/8/8/8",
    "K6q/8/1k6/8/8/8/8/8",
    "8/8/8/8/8/5k2/5q2/5K2",
    "8/8/8/8/8/5k2/6q1/7K",
    "8/8/8/K1k5/8/8/8/q7",
    "r7/8/6k1/8/K7/8/8/1r6",
    "3rq3/7k/8/8/4K3/8/8/5r2",
    "8/7k/8/8/1n6/8/PPq5/2K5",
    "KR6/PPn4k/8/8/8/8/8/8",
    "4k3/8/4r3/8/8/8/3P1P2/3RKB1q",
    "K5k1/3n4/8/8/8/5b2/5b2/8",
    "K6q/7k/8/8/8/5b2/5b2/8",
    "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR",
    "KN5q/7k/8/8/8/8/5bb1/8",
    "KN5r/7k/8/8/8/8/5bb1/8",
    "3k4/8/8/2b1p3/4P3/2N2N2/PPPP1qPP/R1BQKB1R",
    "K6q/1N5k/8/8/8/8/5bb1/8",
    "4k3/8/8/8/1qP5/3P4/4PP2/3BKQ2",
    "4k3/8/8/8/6Pq/5P2/3PP3/3QKB2",
    "rnb1kbnr/pppp1ppp/8/4p3/6Pq/5P2/PPPPP2P/RNBQKBNR",
    "3k4/8/8/2b1p3/4P3/2N2N2/PPPP1qPP/R1BQKB1R",
    "KN5r/7k/8/8/8/8/5bb1/8",
    "KR6/PPn5/8/8/8/4k3/4p3/8"
};

static vector<string> pin_fens = {
    "rnbqkbnr/pppp1ppp/8/4p3/8/4Q3/PPPPPPPP/RNB1KBNR",
    "8/1k6/8/8/4PPP1/4PKP1/3n1R2/5q2",
    "KN5q/7k/8/8/8/8/5bb1/8",
    "KN5r/7k/8/8/8/8/5bb1/8",
    "7k/6r1/8/8/8/8/1Q6/8",
    "k7/b7/8/8/8/8/Q7/8",
    "5r2/k7/8/5R2/r3QK2/8/8/8",
    "5r2/k7/8/5R2/r3QK2/8/8/8",
    "5R2/K7/8/5r2/R3qk2/8/8/8",
    "5R2/K7/8/5r2/R3qk2/8/8/8",
    "5r2/k7/5R2/8/r1Q2K2/8/8/8",
    "5r2/k7/5R2/8/r1Q2K2/8/8/8",
};

static vector<string> pinned_squares = {
    "e5",
    "f2",
    "b8",
    "b8",
    "g7",
    "a7",
    "f5",
    "e4",
    "f5",
    "e4",
    "c4",
    "f6"
};


static vector<string> check_fens = {
    "8/8/K7/8/8/8/8/5b2",
    "8/8/2q3K1/8/8/8/8/5b2",
};

static vector<string> should_not_be_check_fens = {
    "8/8/2q2RK1/8/8/8/8/5b2",
    "5R2/K7/8/5r2/R3qk2/8/8/8",
    "5r2/k7/8/5R2/r3QK2/8/8/8"
};

static vector<string> stalemate_fens = {
    "8/8/1b6/8/8/7q/5P2/6K1",
    "K7/8/1q6/8/5k2/8/8/8",
    "8/8/8/8/8/7k/7p/7K",
    "2r1r2k/8/8/7r/3K4/7r/8/8",
    "7k/8/8/2r1r3/3K4/2r5/8/8",
    "1r6/4k2b/8/8/1q6/3P4/2K5/7r",
    "1r6/4k2b/8/3q2p1/6Pp/7P/8/K7",
    "8/8/8/8/8/4k3/4p3/4K3",
    "bb6/b7/8/8/8/8/6P1/7K",
    "6bb/7b/8/8/8/8/1P6/K7",
    "6b1/7b/8/4K3/7b/b7/8/2b3b1",
    "8/8/8/8/8/2q1q3/8/3K4",
    "8/5q2/7K/5q2/8/8/8/8",
    "2K5/8/1q1q4/8/8/8/8/8",
    "8/8/8/8/2q5/K7/2q5/8",
    "5K2/r7/8/3p4/2kP2r1/2P3p1/8/4r3"
};

static vector<string> ddtim_fens = {
    "8/4k3/8/8/3K4/8/8/8",
    "8/4k3/6n1/8/3K4/8/8/8",
    "8/4k3/8/8/3K4/6N1/8/8",
    "8/4k3/8/8/3K4/6B1/8/8",
    "8/4k3/8/8/3K4/6b1/8/8",
    "8/4k3/8/8/3K4/6N1/1N6/8",
    "8/4k3/8/8/3K4/6n1/1n6/8",
    "8/8/3n1K2/8/8/3k2n1/8/8",
    "8/8/3N1K2/8/8/3k2N1/8/8",
};

};