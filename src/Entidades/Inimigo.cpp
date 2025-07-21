#include "Inimigo.hpp"
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <cmath>
#include <limits>
#include <algorithm>
#include <set>

char Inimigo::decisao(char entrada, std::vector<std::vector<int>> &matriz) {
    int linhas = matriz.size();     // 11
    if (linhas == 0) return 'n';
    int colunas = matriz[0].size(); // 19

    int posL = (getPosL() / 3) - 1;
    int posC = (getPosC() / 7) - 1;

    if (posL < 0 || posL >= linhas || posC < 0 || posC >= colunas)
        return 'n';

    static int ultimaBombaL = -1;
    static int ultimaBombaC = -1;
    static int contadorAposBomba = 0;

    // Direções (cima, baixo, esquerda, direita)
    std::vector<std::pair<char, std::pair<int, int>>> direcoes = {
        {'w', {-1,  0}},
        {'a', { 0, -1}},
        {'s', { 1,  0}},
        {'d', { 0,  1}}
    };

    // 🔥 1. Calcular células em risco por explosões em cruz
    std::set<std::pair<int, int>> perigo;
    int alcance = 2;

    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] == 2) { // bomba encontrada
                perigo.insert({i, j}); // posição da bomba

                // Verificar 4 direções até o alcance
                for (const auto& d : direcoes) {
                    for (int k = 1; k <= alcance; ++k) {
                        int ni = i + d.second.first * k;
                        int nj = j + d.second.second * k;

                        if (ni < 0 || ni >= linhas || nj < 0 || nj >= colunas)
                            break;

                        perigo.insert({ni, nj});

                        if (matriz[ni][nj] == 1) // Bloco destrutível interrompe a explosão
                            break;
                    }
                }
            }
        }
    }

    // 2. Se estamos em perigo, fugir
    if (perigo.count({posL, posC}) || matriz[posL][posC] == 3) {
        for (const auto& [mov, delta] : direcoes) {
            int nx = posL + delta.first;
            int ny = posC + delta.second;
            if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas &&
                matriz[nx][ny] == 0 && !perigo.count({nx, ny})) {
                return mov;
            }
        }
    }

    // 3. Fugir da própria bomba (mesmo raciocínio anterior)
    if (contadorAposBomba > 0) {
        contadorAposBomba--;
        for (const auto& [mov, delta] : direcoes) {
            int nx = posL + delta.first;
            int ny = posC + delta.second;
            if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas &&
                matriz[nx][ny] == 0 && !perigo.count({nx, ny}) &&
                !(nx == ultimaBombaL && ny == ultimaBombaC)) {
                return mov;
            }
        }
    }

    // 4. Jogador ou bloco adjacente → só solta bomba se tem fuga segura
    for (const auto& [mov, delta] : direcoes) {
        int nx = posL + delta.first;
        int ny = posC + delta.second;
        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas &&
            (matriz[nx][ny] == 5 || matriz[nx][ny] == 1)) {

            // Verifica se há rota de fuga segura
            bool temFuga = false;
            for (const auto& [fuga, df] : direcoes) {
                int fx = posL + df.first;
                int fy = posC + df.second;
                if (fx >= 0 && fx < linhas && fy >= 0 && fy < colunas &&
                    matriz[fx][fy] == 0 && !perigo.count({fx, fy})) {
                    temFuga = true;
                    break;
                }
            }

            if (temFuga) {
                ultimaBombaL = posL;
                ultimaBombaC = posC;
                contadorAposBomba = 3;
                return 'l';
            }
        }
    }

    // 5. Power-up adjacente
    for (const auto& [mov, delta] : direcoes) {
        int nx = posL + delta.first;
        int ny = posC + delta.second;
        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && matriz[nx][ny] == 4) {
            return mov;
        }
    }

    // 6. Ir atrás do jogador
    int alvoL = -1, alvoC = -1;
    for (int i = 0; i < linhas; ++i) {
        for (int j = 0; j < colunas; ++j) {
            if (matriz[i][j] == 5) {
                alvoL = i;
                alvoC = j;
                break;
            }
        }
        if (alvoL != -1) break;
    }

    if (alvoL != -1) {
        char melhorMov = 'n';
        int menorDist = std::numeric_limits<int>::max();

        for (const auto& [mov, delta] : direcoes) {
            int nx = posL + delta.first;
            int ny = posC + delta.second;
            if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas &&
                matriz[nx][ny] == 0 && !perigo.count({nx, ny})) {
                int dist = std::abs(nx - alvoL) + std::abs(ny - alvoC);
                if (dist < menorDist) {
                    menorDist = dist;
                    melhorMov = mov;
                }
            }
        }

        if (melhorMov != 'n') return melhorMov;
    }

    // 7. Movimento aleatório seguro
    std::vector<char> opcoes;
    for (const auto& [mov, delta] : direcoes) {
        int nx = posL + delta.first;
        int ny = posC + delta.second;
        if (nx >= 0 && nx < linhas && ny >= 0 && ny < colunas &&
            matriz[nx][ny] == 0 && !perigo.count({nx, ny})) {
            opcoes.push_back(mov);
        }
    }

    if (!opcoes.empty()) {
        std::srand(time(0));
        return opcoes[std::rand() % opcoes.size()];
    }

    return 'n';
}
