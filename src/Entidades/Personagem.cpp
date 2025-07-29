#include "Personagem.hpp"
#include <iostream>

void Personagem::mover(char entrada) {
   switch (entrada) {
        case 'w': 
            // Mover para cima
            moveUp(3);
            break;
        case 's': // Mover para baixo   
            moveDown(3);
            break;
        case 'a': // Mover para a esquerda
            moveLeft(7);
            break;
        case 'd': // Mover para a direita
            moveRight(7);
            break;
        default:
            std::cout << "Movimento inválido." << std::endl;
    }
}

void Personagem::diminuirVida() {
    if (vidas > 0) {
        vidas--;
    } else {
    }
}

void Personagem::aumentarVida() {
    vidas++;
}

void Personagem::diminuirBombas() {
    bombasDisponiveis--;
}

