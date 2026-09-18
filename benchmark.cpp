#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include "Graph.h"
#include "GraphLa.h"
#include "GraphMa.h"
#include "GraphMi.h"
#include "Node.h"

namespace col
{
    const std::string reset = "\033[0m";
    const std::string bold = "\033[1m";
    const std::string dim = "\033[2m";
    const std::string cyan = "\033[36m";
    const std::string green = "\033[32m";
    const std::string yellow = "\033[33m";
    const std::string red = "\033[31m";
    const std::string magenta = "\033[35m";
}

struct BenchResult
{
    std::string instance;
    int numNodes;
    std::string testNode;
    std::string firstNode;
    std::string lastNode;
    double loadTime[4];    // Graph, GraphLa, GraphMa, GraphMi
    double searchTime[4];
    double connectTime[4];
};

// Mede o tempo de execução de uma função em milissegundos
template <typename Func>
double benchMs(Func fn)
{
    auto start = std::chrono::high_resolution_clock::now();
    fn();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

// Formata número com separador de milhar (ponto) — padrão brasileiro
std::string fmtNum(int n)
{
    std::string s = std::to_string(n);
    for (int i = (int)s.length() - 3; i > 0; i -= 3)
        s.insert(i, ".");
    return s;
}

// Formata tempo em ms com precisão adequada ao valor
std::string fmtMs(double ms)
{
    std::ostringstream oss;
    if (ms >= 100.0)
        oss << std::fixed << std::setprecision(1) << ms;
    else if (ms >= 1.0)
        oss << std::fixed << std::setprecision(4) << ms;
    else
        oss << std::fixed << std::setprecision(6) << ms;
    return oss.str();
}

// Imprime uma linha da tabela markdown
void printRow(const std::string &c1, const std::string &c2,
              const std::string &c3, const std::string &c4, const std::string &c5)
{
    printf("| %-17s | %-12s | %-12s | %-12s | %-12s |\n",
           c1.c_str(), c2.c_str(), c3.c_str(), c4.c_str(), c5.c_str());
}

void printSep()
{
    printf("| ----------------- | ------------ | ------------ | ------------ | ------------ |\n");
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Uso: " << argv[0] << " <instancia1> [instancia2] ...\n";
        std::cout << "Exemplo: " << argv[0] << " graph_09.txt graph_10.txt graph_11.txt\n";
        return 1;
    }

    std::cout << col::magenta << col::bold
              << "\n*** Benchmark - Teoria dos Grafos DCC059 ***\n"
              << col::reset << "\n";

    std::vector<BenchResult> results;

    for (int i = 1; i < argc; i++)
    {
        std::string instance = argv[i];
        BenchResult r;
        r.instance = instance;

        // Lê número de nós do arquivo
        {
            std::ifstream f("instances/" + instance);
            if (!f.is_open())
            {
                std::cout << col::red << "Erro: nao foi possivel abrir instances/"
                          << instance << col::reset << "\n";
                continue;
            }
            f >> r.numNodes;
        }

        std::cout << col::cyan << "[" << i << "/" << (argc - 1) << "] "
                  << col::reset << col::bold << instance << col::reset
                  << " (" << fmtNum(r.numNodes) << " nos)\n";

        Graph *graph = nullptr;
        GraphLa *graphLa = nullptr;
        GraphMa *graphMa = nullptr;
        GraphMi *graphMi = nullptr;

        // ── Carregamento ──
        std::cout << col::dim << "  Graph...    " << col::reset << std::flush;
        r.loadTime[0] = benchMs([&]() { graph = new Graph(instance); });
        std::cout << fmtMs(r.loadTime[0]) << " ms\n";

        std::cout << col::dim << "  GraphLa...  " << col::reset << std::flush;
        r.loadTime[1] = benchMs([&]() { graphLa = new GraphLa(instance); });
        std::cout << fmtMs(r.loadTime[1]) << " ms\n";

        std::cout << col::dim << "  GraphMa...  " << col::reset << std::flush;
        r.loadTime[2] = benchMs([&]() { graphMa = new GraphMa(instance); });
        std::cout << fmtMs(r.loadTime[2]) << " ms\n";

        std::cout << col::dim << "  GraphMi...  " << col::reset << std::flush;
        r.loadTime[3] = benchMs([&]() { graphMi = new GraphMi(instance); });
        std::cout << fmtMs(r.loadTime[3]) << " ms\n";

        // ── Nós de teste ──
        auto nodes = graph->getNodes();
        int testIdx = std::min(499, (int)nodes.size() - 1);
        r.testNode = nodes[testIdx]->getName();
        r.firstNode = nodes.front()->getName();
        r.lastNode = nodes.back()->getName();

        // ── Busca de arestas ──
        std::cout << col::dim << "  Buscas...   " << col::reset << std::flush;
        r.searchTime[0] = benchMs([&]() { graph->searchNodeEdges(r.testNode); });
        r.searchTime[1] = benchMs([&]() { graphLa->searchNodeEdges(r.testNode); });
        r.searchTime[2] = benchMs([&]() { graphMa->searchNodeEdges(r.testNode); });
        r.searchTime[3] = benchMs([&]() { graphMi->searchNodeEdges(r.testNode); });
        std::cout << col::green << "OK" << col::reset << "\n";

        // ── Conexão ──
        std::cout << col::dim << "  Conexao...  " << col::reset << std::flush;
        r.connectTime[0] = benchMs([&]() { graph->isNodesConected(r.firstNode, r.lastNode); });
        r.connectTime[1] = benchMs([&]() { graphLa->isNodesConected(r.firstNode, r.lastNode); });
        r.connectTime[2] = benchMs([&]() { graphMa->isNodesConected(r.firstNode, r.lastNode); });
        r.connectTime[3] = benchMs([&]() { graphMi->isNodesConected(r.firstNode, r.lastNode); });
        std::cout << col::green << "OK" << col::reset << "\n\n";

        delete graph;
        delete graphLa;
        delete graphMa;
        delete graphMi;

        results.push_back(r);
    }

    if (results.empty())
        return 1;

    // ══════════════════════════════════════════
    //  Tabelas de Resultados
    // ══════════════════════════════════════════

    std::cout << col::cyan << col::bold
              << "### Resultados de Desempenho (Tempo em ms)\n"
              << col::reset << "\n";

    // ── Tabela 1: Carregamento ──
    std::cout << col::yellow << col::bold
              << "#### 1. Carregamento de Instancias\n"
              << col::reset << "\n";
    printRow("Quantidade de Nos", "Graph", "GraphLa", "GraphMa", "GraphMi");
    printSep();
    for (const auto &r : results)
        printRow("**" + fmtNum(r.numNodes) + "**",
                 fmtMs(r.loadTime[0]), fmtMs(r.loadTime[1]),
                 fmtMs(r.loadTime[2]), fmtMs(r.loadTime[3]));
    std::cout << "\n";

    // ── Tabela 2: Busca de arestas ──
    std::cout << col::yellow << col::bold
              << "#### 2. Busca por arestas de um no (No " << results[0].testNode << ")\n"
              << col::reset << "\n";
    printRow("Quantidade de Nos", "Graph", "GraphLa", "GraphMa", "GraphMi");
    printSep();
    for (const auto &r : results)
        printRow("**" + fmtNum(r.numNodes) + "**",
                 fmtMs(r.searchTime[0]), fmtMs(r.searchTime[1]),
                 fmtMs(r.searchTime[2]), fmtMs(r.searchTime[3]));
    std::cout << "\n";

    // ── Tabela 3: Conexão ──
    std::cout << col::yellow << col::bold
              << "#### 3. Busca de conexao entre dois nos (Primeiro e Ultimo)\n"
              << col::reset << "\n";
    printRow("Quantidade de Nos", "Graph", "GraphLa", "GraphMa", "GraphMi");
    printSep();
    for (const auto &r : results)
        printRow("**" + fmtNum(r.numNodes) + "**",
                 fmtMs(r.connectTime[0]), fmtMs(r.connectTime[1]),
                 fmtMs(r.connectTime[2]), fmtMs(r.connectTime[3]));
    std::cout << "\n";

    return 0;
}
