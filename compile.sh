# Lembre de rodar o comando
# chmod +x compile.sh

g++ -std=c++17 -Wall -Istructures $1 structures/Graph.cpp structures/GraphLa.cpp structures/GraphMa.cpp structures/GraphMi.cpp -o graphs_test
clear
./graphs_test $2
rm graphs_test