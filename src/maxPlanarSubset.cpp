#include "maxPlanarSubset.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

MaximumPlanarSubset::MaximumPlanarSubset(int points, vector<Chord> chords)
    : n(points / 2), chords(chords), dp(2 * n, vector<int>(2 * n, 0)), solution(2 * n, vector<int>(2 * n, -1)) {
    calculateMPS();
}

void MaximumPlanarSubset::printResult(ostream& out) {
    #ifdef _DEBUG_ON_
    cout << "Final result: " << dp[0][2 * n - 1] << endl;
    #endif
    out << dp[0][2 * n - 1] << endl;
    traceSolution(0, 2 * n - 1, out);
}

int MaximumPlanarSubset::solve(const char* inputFile, const char* outputFile) {
    ifstream fin(inputFile);
    if (!fin) {
        cerr << "Error: Cannot open input file " << inputFile << endl;
        return 1;
    }

    ofstream fout(outputFile);
    if (!fout) {
        cerr << "Error: Cannot open output file " << outputFile << endl;
        return 1;
    }

    int points;
    while (fin >> points) {
        if (points == 0) break;
        
        #ifdef _DEBUG_ON_
        cout << "Processing " << points << " points (" << points/2 << " chords)" << endl;
        #endif
        
        vector<Chord> chords;
        for (int i = 0; i < points/2; ++i) {
            int start, end;
            if (!(fin >> start >> end)) {
                cerr << "Error: Invalid input format." << endl;
                return 1;
            }
            #ifdef _DEBUG_ON_
            cout << "Read chord " << i + 1 << ": " << start << " " << end << endl;
            #endif
            
            Chord chord;
            chord.start = start;
            chord.end = end;
            chords.push_back(chord);
        }

        MaximumPlanarSubset mps(points, chords);
        mps.printResult(fout);
    }

    fin.close();
    fout.close();
    return 0;
}

void MaximumPlanarSubset::calculateMPS() {
    #ifdef _DEBUG_ON_
    cout << "Starting calculateMPS with n = " << n << endl;
    #endif

    // Initialize the DP table
    for (int i = 0; i < 2 * n; ++i) {
        for (int j = i; j < 2 * n; ++j) {
            dp[i][j] = (i == j) ? 0 : dp[i][j-1];
            solution[i][j] = -1;
        }
    }

    // Main DP computation
    for (int len = 1; len < 2 * n; ++len) {
        for (int i = 0; i + len < 2 * n; ++i) {
            int j = i + len;
            
            #ifdef _DEBUG_ON_
            cout << "Processing dp[" << i << "][" << j << "]" << endl;
            #endif

            // Check all chords starting at point i
            for (const Chord &chord : chords) {
                if (chord.start == i && chord.end <= j) {
                    int k = chord.end;
                    
                    #ifdef _DEBUG_ON_
                    cout << "Found chord: " << i << " -> " << k << endl;
                    #endif

                    // Calculate score when using this chord
                    int score = 1;
                    if (i + 1 < k) {
                        score += dp[i + 1][k - 1];  // Add score from left subproblem
                    }
                    if (k + 1 <= j) {
                        score += dp[k + 1][j];  // Add score from right subproblem
                    }

                    // Update if better solution found
                    if (score > dp[i][j]) {
                        dp[i][j] = score;
                        solution[i][j] = k;
                        #ifdef _DEBUG_ON_
                        cout << "Updated dp[" << i << "][" << j << "] = " << score << endl;
                        #endif
                    }
                }
            }
        }
    }

    #ifdef _DEBUG_ON_
    cout << "DP table filled" << endl;
    #endif
}

void MaximumPlanarSubset::traceSolution(int i, int j, ostream& out) {
    #ifdef _DEBUG_ON_
    cout << "Tracing solution for [" << i << ", " << j << "]" << endl;
    #endif

    if (i >= j) return;

    int k = solution[i][j];
    #ifdef _DEBUG_ON_
    cout << "solution[" << i << "][" << j << "] = " << k << endl;
    #endif

    if (k != -1) {
        // Find and output the corresponding chord
        for (const Chord &chord : chords) {
            if (chord.start == i && chord.end == k) {
                out << i << " " << k << endl;
                break;
            }
        }
        
        // Process left and right subproblems
        if (i + 1 < k) {
            traceSolution(i + 1, k - 1, out);
        }
        if (k + 1 < j) {
            traceSolution(k + 1, j, out);
        }
    } else {
        traceSolution(i + 1, j, out);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }
    return MaximumPlanarSubset::solve(argv[1], argv[2]);
}