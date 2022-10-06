#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include <string>

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  void onPaintUI() override;

private:
  static int const m_N{3}; // Board size is m_N x m_N

  std::string texto = "COMEÇAR";

  enum class GameState {
    Lose,
    Win,
    Play1,
    Play2,
    Play3,
    Play4,
    Play5,
    Play6,
    Play7,
    Play8,
    Play9,
    Wait
  };
  GameState m_gameState;

  std::array<int, m_N * m_N> correct{};
  std::array<char, m_N * m_N> m_board{};
  std::array<char, m_N * m_N> nums{'1', '2', '3', '4', '5', '6', '7', '8', '9'};
  ImFont *m_font{};

  void restartGame();
  void startGame();
};

#endif
