# Algoritmos de Grafos — Implementações em C++

Implementações de algoritmos de grafos, escritas em C++, com suporte a entrada e saída via linha de comando. Projeto solicitado pelo docente Rian Gabriel para a disciplina de Teoria dos Grafos 2025.1 do IC/UFAL.
O repositório inclui as seguintes implementações:

- Kruskal — Gera a árvore geradora mínima com união e busca disjunta (DSU).
- Prim — Alternativa para gerar a árvore geradora mínima usando fila de prioridade.
- Dijkstra — Calcula o menor caminho a partir de um vértice fonte em grafos ponderados e não negativos.
- Kosaraju — Encontra as componentes fortemente conexas (CFCs) em grafos direcionados.

Cada arquivo .cpp implementa um algoritmo independente, mas todos compartilham o mesmo formato de execução.

## 🧠 Observações

- Todos os programas usam 1-indexação apenas na saída, mas internamente operam em 0-index.
- Se o arquivo de entrada não for informado, o programa exibe um erro e encerra.
