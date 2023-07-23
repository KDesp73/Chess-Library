#pragma once

#include <vector>
#include <string>

using namespace std;

namespace Test{
    bool testCheckMate(vector<string> mate_fens);
    bool testCheckMate(string mate_fen);
    bool testStaleMate(vector<string> stalemate_fens);
    bool testStaleMate(string stalemate_fen);
    bool testCheck(vector<string> check_fens);
    bool testCheck(string check_fen);
    bool testNotCheck(vector<string> should_not_be_check_fens);
    bool testNotCheck(string should_not_be_check_fens);
    bool testDrawDueToInsufficientMaterial(vector<string> ddtim_fens);
} // namespace Test
