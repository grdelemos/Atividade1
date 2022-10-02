# Atividade1

# Atividade 1
Computação Gráfica 
Gustavo Gualberto Rocha de Lemos 
 **RA**: 21008313
O programa é um jogo da memória, onde são mostrados números de 1 a 9 num tabuleiro para o usuário memorizar, e depois que ele aperta o botão de começar o jogo os números desaparecem e ele deve clicar nos botões na ordem correta. A posição dos números no tabuleiro é alterada a cada reinício de partida.
Há um menu com nome "jogo" na parte superior, com as opções "começar" e "reiniciar"; 9 botões dispostos em forma de grade e dois botões na parte inferior: "COMEÇAR" e "Reiniciar".

A cada reinício a função restartGame mostra as posições dos números e coloca o jogo no estado "Wait", para que o usuário possa memorizá-los.

A geração aleatória das posições dos números é feita pelo seguinte código:

    auto  g = rand();

    std::shuffle(nums.begin(), nums.end(), std::default_random_engine(g));
    
    for (auto  m : iter::range(9)) {
    
    m_board.at(m) = nums.at(m);

    }
a função shuffle é usada para reordenar as posições dos números do vetor nums, que são atribuídas ao vetor do tabuleiro, chamado m_board.

Ao clicar no botão "COMEÇAR" o tabuleiro é esvaziado e esse botão fica com o texto "jogando...", até o jogo ser reiniciado novamente.

Os botões da grade são gerados por dois laços "for" e para cada botão é verificado o número daquela posição e se o estado do jogo espera tal número. Por exemplo, o número 1:

    switch (nums.at(offset)) {
        case '1':
            if (ch == ' ' && m_gameState == GameState::Play1) {
            m_board.at(offset) = nums.at(offset);
            m_gameState = GameState::Play2;
            } else {
            m_gameState = GameState::Lose;
            }
            break;

Caso o botão seja clicado e o estado seja o que espera o número 1 o jogo vai para o estado "Play2", caso contrário o jogo vai para o estado "Lose". Isso é repetido para os números de 1 a 9. Caso o jogador acerte até o número 9, o jogo vai para o estado "Win".