#ifndef MAX_PLANAR_SUBSET_H
#define MAX_PLANAR_SUBSET_H

#include <vector>
#include <fstream>
#include <iostream>

// Structure to represent a chord
struct Chord {
    int start, end;
};

// MPS class for handling the Maximum Planar Subset problem
class MaximumPlanarSubset {
private:
    int n; // # of points on the circle
    std::vector<Chord> chords; // stores all chords
    std::vector<std::vector<int> > dp; // dynamic programming matrix
    std::vector<std::vector<int> > solution; // record the end point of the chord

public:
    MaximumPlanarSubset(int n, std::vector<Chord> chords);
    void calculateMPS();
    void printResult(std::ostream& out = std::cout);
    void traceSolution(int i, int j, std::ostream& out = std::cout);
    
    static int solve(const char* inputFile, const char* outputFile);
};

#endif