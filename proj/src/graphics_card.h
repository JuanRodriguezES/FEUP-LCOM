#pragma once

#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphics_card_const.h"
#include <math.h>

typedef enum {UP, DOWN, LEFT, RIGHT} Direction;

/**
 *  @brief Mete a Placa Gráfica no Modo especificado
 *  @param mode Modo a utilizar na Placa Gráfica
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (set_graphics_card_mode)(uint16_t mode);

/**
 *  @brief Muda a cor de um pixel para a cor especificada
 *  @param x Posição dos x do pixel a alterar
 *  @param y Posição dos y do pixel a alterar
 *  @param color Nova Cor do pixel
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (changePixelColor)(uint16_t x, uint16_t y, uint32_t color);

/**
 *  @brief Muda a cor de uma linha horizontal do ecrã
 *  @param x Posição dos x da linha horizontal
 *  @param y Posição dos y da linha horizontal
 *  @param len Comprimento da linha horizontal
 *  @param color Nova Cor da linha horizontal
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color);

/**
 *  @brief Muda a cor de uma secção retangular do ecrã
 *  @param x Posição dos x do retângulo
 *  @param y Posição dos y do retângulo
 *  @param width Comprimento do retângulo
 *  @param height Altura do retângulo
 *  @param color Nova Cor do retângulo
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color);

/**
 *  @brief Cor indexada
 *  @param col Número da coluna a mudar a cor
 *  @param row Número da linha a mudar a cor
 *  @param step Parâmetro de cálculo da cor
 *  @param first Parâmetro de cálculo da cor
 *  @param no_rectangles Número de retângulos a apresentar no ecrã
 *  @return Cor indexada calculada
 */
uint32_t (indexed_color)(uint16_t col, uint16_t row, uint8_t step, uint32_t first, uint8_t no_rectangles);

/**
 *  @brief Cor direta
 *  @param red Parte vermelha da cor
 *  @param green Parte verde da cor
 *  @param blue Parte azul da cor
 *  @return Cor direta calculada
 */
uint32_t (direct_color)(uint32_t red, uint32_t green, uint32_t blue);

/**
 *  @brief Cálculo de parâmetro R_First utilizado no cálculo da cor
 *  @param first Parâmetro usado no cálculo de R_First
 *  @return R_First - Parâmetro utilizado no cálculo da cor
 */
uint32_t (R_First)(uint32_t first);

/**
 *  @brief Cálculo de parâmetro G_First utilizado no cálculo da cor
 *  @param first Parâmetro usado no cálculo de G_First
 *  @return G_First - Parâmetro utilizado no cálculo da cor
 */
uint32_t (G_First)(uint32_t first);

/**
 *  @brief Cálculo de parâmetro B_First utilizado no cálculo da cor
 *  @param first Parâmetro usado no cálculo de B_First
 *  @return B_First - Parâmetro utilizado no cálculo da cor
 */
uint32_t (B_First)(uint32_t first);

/**
 *  @brief Cálculo de parâmetro R utilizado no cálculo da cor
 *  @param h Parâmetro usado no cálculo de R
 *  @param step Parâmetro usado no cálculo de R
 *  @param first Parâmetro usado no cálculo de R
 *  @return R - Parâmetro utilizado no cálculo da cor
 */
uint32_t (R)(unsigned int h, uint8_t step, uint32_t first);

/**
 *  @brief Cálculo de parâmetro G utilizado no cálculo da cor
 *  @param h Parâmetro usado no cálculo de G
 *  @param step Parâmetro usado no cálculo de G
 *  @param first Parâmetro usado no cálculo de G
 *  @return G - Parâmetro utilizado no cálculo da cor
 */
uint32_t (G)(unsigned int w, uint8_t step, uint32_t first);

/**
 *  @brief Cálculo de parâmetro B utilizado no cálculo da cor
 *  @param h Parâmetro usado no cálculo de B
 *  @param step Parâmetro usado no cálculo de B
 *  @param first Parâmetro usado no cálculo de B
 *  @return B - Parâmetro utilizado no cálculo da cor
 */
uint32_t (B)(unsigned int w, unsigned int h, uint8_t step, uint32_t first);

/**
 *  @brief Obtenção da Informação sobre o Modo da placa gráfica
 *  @param info Pacote que armazena a Informação sobre o Modo da placa gráfica
 *  @return 0 em caso de sucesso, 1 caso contrário
 */
int (controller_info)(vg_vbe_contr_info_t * info);

/**
 *  @brief Implementação da técnica Double-Buffering
 */
void (double_buffer)();

/**
 *  @brief Libertação da memória utilizada pela placa gráfica
 */
void free_memory();

