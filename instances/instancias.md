# Formatação das instancias

As instacias são dividas em 3 blocos:
 1. Configuração do grafo
 2. Vértices
 3. Arestas

---
## Configurações do grafo

Sempre a primeira linha do arquivo, estara num formato `V E D` onde:
- `V` é o numero de vértices no grafo.
- `E` é o numero de arestas no grafo
- `D` é a densidade do grafo no grafo.

````bash
5 5 0.5
````

## Vértices
Da linha 2 até a linha de valor V + 1 teremos os vértices, cada vértice ocupa uma linha.

```bash
5 5 0.5
A
B
C
D
E
```

## Arestas
Da linha V + 2 para frente teremos as arestas, cada aresta ocupa uma linha mostrando origem e destino separados por espaç.

```bash
5 5 0.5
A
B
C
A B
A C
B C
```

