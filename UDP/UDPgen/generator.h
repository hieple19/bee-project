#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <random>
#include <vector>
#include <fstream>
#include <string>

using namespace std;
class Generator
{
public:
    Generator(string file_name, int seed);
    vector<int> generate();
    void print_times();
private:
    int seed;
    string file_name;
    vector<int> lambdas;
    vector<double> times;
};

#endif // GENERATOR_H
