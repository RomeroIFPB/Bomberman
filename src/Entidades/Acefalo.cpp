#include "Acefalo.hpp"
#include <limits>
#include <cmath>

char Acefalo::decisao(char entrada, std::vector<std::vector<int>> &matriz) 
{
    int linhas = matriz.size();             // Deve ser 10
    if (linhas == 0) return 'n';
    int colunas = matriz[0].size();         // Deve ser 19

    // Posição atual do Acefalo no grid lógico
    int posL = (getPosL() / 3) - 1;
    int posC = (getPosC() / 7) - 1;

    // Verificação de segurança
    if (posL < 0 || posL >= linhas || posC < 0 || posC >= colunas)
        return 'n';

    // Buscar o alvo (ex: primeiro 5 que encontrar, exceto si próprio)
    int alvoL = -1, alvoC = -1;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] == 5 && !(i == posL && j == posC)) {
                alvoL = i;
                alvoC = j;
                break;
            }
        }
        if (alvoL != -1) break;
    }

    if (alvoL == -1) return 'n';  // Nenhum alvo encontrado

    // Direções possíveis
    std::vector<std::pair<char, std::pair<int, int>>> direcoes = {
        {'w', {-1,  0}},
        {'a', { 0, -1}},
        {'s', { 1,  0}},
        {'d', { 0,  1}}
    };

    char melhorMov = 'n';
    int menorDist = std::numeric_limits<int>::max();

    for (const auto& [mov, delta] : direcoes) {
        int nx = posL + delta.first;
        int ny = posC + delta.second;

        // Verificar limites e se não é uma barreira
        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && matriz[nx][ny] == 0) {
            int dist = std::abs(nx - alvoL) + std::abs(ny - alvoC);  // Heurística Manhattan
            if (dist < menorDist) {
                menorDist = dist;
                melhorMov = mov;
            }
        }
    }

    return melhorMov;
}



