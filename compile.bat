@echo off
g++ -std=c++17 -Wall -Istructures %1 structures/Graph.cpp structures/GraphLa.cpp structures/GraphMa.cpp structures/GraphMi.cpp -o graphs_test.exe
cls
graphs_test.exe %2
del graphs_test.exe