# Atividade1

# Atividade 1
Computação Gráfica 


Gustavo Gualberto Rocha de Lemos 


 **RA**: 21008313


O programa é um jogo da memória, onde são mostrados números de 1 a 9 num tabuleiro para o usuário memorizar, e depois que ele aperta o botão de começar o jogo os números desaparecem e ele deve clicar nos botões na ordem correta. Inicialmente o tabuleiro é cinza, e cada botão acertado fica na cor verde e se um botão errado for pressionado, ele fica na cor vermelha. A posição dos números no tabuleiro é alterada a cada reinício de partida.
Há um menu com nome "jogo" na parte superior, com as opções "começar" e "reiniciar"; 9 botões dispostos em forma de grade e dois botões na parte inferior: "COMEÇAR" na cor verde e "Reiniciar" na cor azul.

Os botões da grade são gerados por dois laços "for" e para cada botão é verificado o número daquela posição e se o estado do jogo espera tal número.
Caso o botão seja clicado e o estado seja o que espera o número 1 o jogo vai para o estado "Play2", caso contrário o jogo vai para o estado "Lose". Isso é repetido para os números de 1 a 9. Caso o jogador acerte até o número 9, o jogo vai para o estado "Win".

As cores do tabuleiro são controladas pelo vetor correct. Se ele tiver o valor 0, o botão é cinza, se tiver o valor 1, ele fica verde e se tiver o valor -1 ele fica vermelho, como mostra o código:
    if (correct.at(offset) == 1) {

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0, 0.5f, 0, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                        ImVec4{0, 0.4f, 0, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                        ImVec4{0, 0.5f, 0, 1.0f});

                } else if (correct.at(offset) == -1) {

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.5f, 0, 0, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                        ImVec4{0.4f, 0, 0, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                        ImVec4{0.5f, 0, 0, 1.0f});
                } else {
                ImGui::PushStyleColor(ImGuiCol_Button,
                                        ImVec4{0.5f, 0.5f, 0.5f, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered,
                                        ImVec4{0.4f, 0.4f, 0.4f, 1.0f});
                ImGui::PushStyleColor(ImGuiCol_ButtonActive,
                                        ImVec4{0.5f, 0.5f, 0.5f, 1.0f});
                }

Cada um dos botões da grade é criado dentro de dois laços for, um representando as linhas e o outro as colunas. Abaixo está o código do caso do texto do botão clicado ser '1':
    switch (nums.at(offset)) {
    case '1':
                    if (ch == ' ' && m_gameState == GameState::Play1) {
                    m_board.at(offset) = nums.at(offset);
                    correct.at(offset) = 1;
                    m_gameState = GameState::Play2;
                    } else if (m_gameState != GameState::Win &&
                            m_gameState != GameState::Lose &&
                            m_gameState != GameState::Wait) {
                    m_gameState = GameState::Lose;
                    correct.at(offset) = -1;
                    texto = "Não foi dessa vez";
                    }
                    break;

A variável offset é usada como índice para as posições dos botões, das respostas e também para indicar a cor que deve ser usada. O vetor nums contém as respostas, logo se o jogo estiver esperando o número 1 e o vetor nums tiver esse valor no mesmo índice do botão, ele está correto. Então o vetor m_board recebe o valor de nums, para que o número apareça no tabuleiro, e o vetor correct recebe o valor 1 naquela posição, para que o botão fique verde. Caso essas condições não sejam cumpridas, o jogo vai para o estado de Lose, o vetor correct recebe o valor -1 para que fique vermelho, e o texto do botão abaixo fica "Não foi dessa vez".

A cada reinício a função restartGame mostra as posições dos números e coloca o jogo no estado "Wait", para que o usuário possa memorizá-los.

    void Window::restartGame() {
    correct.fill(0);
    auto g = rand();
    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(g));
    for (auto m : iter::range(9)) {
        m_board.at(m) = nums.at(m);
    }

    texto = "COMEÇAR";
    m_gameState = GameState::Wait;
    }


O vetor correct é preenchido com o valor 0, A função shuffle é usada para reordenar as posições dos números do vetor nums, que são atribuídas ao vetor do tabuleiro, chamado m_board.