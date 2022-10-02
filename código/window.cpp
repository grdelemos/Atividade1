#include "window.hpp"

void Window::onCreate() {

  auto const filename{abcg::Application::getAssetsPath() +
                      "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 72.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError{"Cannot load font file"};
  }

  restartGame();
}

void Window::onPaintUI() {
  // Get size of application's window
  auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
  auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};

  {
    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    auto const flags{ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse};
    ImGui::Begin("Jogo da memória", nullptr, flags);

    // Menu
    {
      bool restartSelected{};
      bool startSelected{};
      if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("Jogo")) {
          ImGui::MenuItem("Reiniciar", nullptr, &restartSelected);
          ImGui::MenuItem("Começar", nullptr, &startSelected);
          ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
      }
      if (restartSelected) {
        restartGame();
      }
      if (startSelected) {
        texto = "Jogando...";
        startGame();
      }
    }

    {
      std::string text;
      switch (m_gameState) {
      case GameState::Play1:
        text = "Onde está o 1?";
        break;
      case GameState::Play2:
        text = "Onde está o 2?";
        break;
      case GameState::Play3:
        text = "Onde está o 3?";
        break;
      case GameState::Play4:
        text = "Onde está o 4?";
        break;
      case GameState::Play5:
        text = "Onde está o 5?";
        break;
      case GameState::Play6:
        text = "Onde está o 6?";
        break;
      case GameState::Play7:
        text = "Onde está o 7?";
        break;
      case GameState::Play8:
        text = "Onde está o 8?";
        break;
      case GameState::Play9:
        text = "Onde está o 9?";
        break;
      case GameState::Win:
        text = "Você venceu! Clique em Reiniciar para jogar de novo";
        break;
      case GameState::Lose:
        text = "Você errou... Clique em Reiniciar para jogar de novo";
        break;
      case GameState::Wait:
        text = "Memorize as posições e clique em COMEÇAR quando estiver pronto";
        break;
      }
      // Center text
      ImGui::SetCursorPosX(
          (appWindowWidth - ImGui::CalcTextSize(text.c_str()).x) / 2);
      ImGui::Text("%s", text.c_str());
      ImGui::Spacing();
    }

    ImGui::Spacing();

    // Game board
    {
      auto const gridHeight{appWindowHeight - 22 - 60 - (m_N * 10) - 60 - 50};
      auto const buttonHeight{gridHeight / m_N};

      // Use custom font
      ImGui::PushFont(m_font);

      if (ImGui::BeginTable("Game board", m_N)) {
        for (auto i : iter::range(m_N)) {
          ImGui::TableNextRow();
          for (auto j : iter::range(m_N)) {
            ImGui::TableSetColumnIndex(j);
            auto const offset{i * m_N + j};

            // Get current character
            auto ch{m_board.at(offset)};

            // Replace null character with whitespace because the button label
            // cannot be an empty string
            if (ch == 0) {
              ch = ' ';
            }

            // Button text is ch followed by an ID in the format ##ij
            auto buttonText{fmt::format("{}##{}{}", ch, i, j)};
            if (ImGui::Button(buttonText.c_str(), ImVec2(-1, buttonHeight))) {
              if (i == 0) {
                if (j == 0 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play5) {
                    m_board.at(offset) = '5';
                    m_gameState = GameState::Play1;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }

                if (j == 1 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play3) {
                    m_board.at(offset) = '3';
                    m_gameState = GameState::Play9;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }

                if (j == 2 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play1) {
                    m_board.at(offset) = '1';
                    m_gameState = GameState::Play8;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }
              }

              if (i == 1) {
                if (j == 0 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play8) {
                    m_board.at(offset) = '8';
                    m_gameState = GameState::Play6;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }

                if (j == 1 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play6) {
                    m_board.at(offset) = '6';
                    m_gameState = GameState::Win;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }

                if (j == 2 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play2) {
                    m_board.at(offset) = '2';
                    m_gameState = GameState::Play5;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }
              }

              if (i == 2) {
                if (j == 0 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play7) {
                    m_board.at(offset) = '7';
                    m_gameState = GameState::Play4;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }

                if (j == 1 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play9) {
                    m_board.at(offset) = '9';
                    m_gameState = GameState::Play2;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }

                if (j == 2 && ch == ' ' && m_gameState != GameState::Win &&
                    m_gameState != GameState::Lose) {
                  if (m_gameState == GameState::Play4) {
                    m_board.at(offset) = '4';
                    m_gameState = GameState::Play3;
                  } else {
                    m_gameState = GameState::Lose;
                  }
                }
              }
            }
          }
          ImGui::Spacing();
        }
        ImGui::EndTable();
      }
      ImGui::PopFont();
    }

    ImGui::Spacing();

    {

      auto buttonStart{fmt::format("{}", texto)};
      if (ImGui::Button(buttonStart.c_str(), ImVec2(-1, 50))) {
        if (m_gameState == GameState::Wait) {
          texto = "Jogando...";
          startGame();
        }
      }
    }

    {
      if (ImGui::Button("Reiniciar", ImVec2(-1, 50))) {
        restartGame();
      }
    }

    ImGui::End();
  }
}

void Window::startGame() {
  m_board.fill('\0');
  m_gameState = GameState::Play7;
}

void Window::restartGame() {
  m_board.at(0) = '5';
  m_board.at(1) = '3';
  m_board.at(2) = '1';
  m_board.at(3) = '8';
  m_board.at(4) = '6';
  m_board.at(5) = '2';
  m_board.at(6) = '7';
  m_board.at(7) = '9';
  m_board.at(8) = '4';
  texto = "COMEÇAR";
  m_gameState = GameState::Wait;

  // m_board.fill('\0');
  // m_gameState = GameState::Play1;
}