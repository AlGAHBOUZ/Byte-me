//
// Created by Ayman on 12/29/2022.
//

#include "Game.h"

// Constructors
Game::Game() {
    is_window_on_start_frame = 1;
    seconds = 0;
    hours = 0;
    minutes = 0;
    InitWindow();
    InitStartBtn();
    InitCards();
    ShuffleCards();
    DistributeCards();
}

// Destructor
Game::~Game() {
    delete window;
    delete bg_sprite;
    delete start_btn;
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        delete all_cards_array[i];
    }
}

// Private Functions
void Game::InitWindow(){
    videoMode.width = WINDOW_WIDTH;
    videoMode.height = WINDOW_HEIGHT;
    window = new sf::RenderWindow(videoMode, "Klondike", sf::Style::Titlebar | sf::Style::Close);
    window->setFramerateLimit(144);
    // Load the background images
    if (!bg_texture.loadFromFile("img/MS-BG-Empty.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    if (!bg_texture_updated.loadFromFile("img/MS-BG.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    // Load the font of the timer
    if (!font.loadFromFile("img/3X5.ttf")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    // Load the background image
    UpdateBackgroundImage();
}

void Game::InitStartBtn() {
    start_btn = new Button("Start the Game!", {312, 312}, 42, sf::Color::Blue, sf::Color::Black);
    float btn_x_pos = ((window->getSize().y / 2) + 70);
    float btn_y_pos = (window->getSize().x / 3) + 50;
    start_btn->setPosition({btn_y_pos, btn_x_pos});

    btn_shape.setSize({312, 312});
    btn_shape.setPosition({btn_y_pos, btn_x_pos});
    // Load Button image
    if (!btn_texture.loadFromFile("img/start.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    btn_shape.setTexture(&btn_texture);
}

void Game::InitCards() {
    // Initializing the 52 cards and storing them in all_cards_array
    for (int num = 1; num <= 13; num++) {
        for (int i = 0; i < 4; i++) {
            std::string card_type;
            if (i == 0)
                card_type = "spades";
            else if (i == 1)
                card_type = "hearts";
            else if (i == 2)
                card_type = "diamond";
            else if (i == 3)
                card_type = "clover";
            all_cards_array[num - 1 + i * 13] = new Card(num, card_type);
        }
    }
}

void Game::UpdateBackgroundImage() {
    // Load the background image
    if (is_window_on_start_frame) {
        // Link the texture with the background sprite
        bg_sprite = new sf::Sprite(bg_texture);
    }
    else {
        // Link the texture with the background sprite
        bg_sprite = new sf::Sprite(bg_texture_updated);
    }

    bg_sprite->setTextureRect(sf::IntRect(0, 0, 1280, 960));
    bg_sprite->setColor(sf::Color(255, 255, 255));
}

void Game::ShuffleCards() {
    // To obtain a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    // Shuffling our array
    shuffle(all_cards_array, all_cards_array + NUMBER_OF_CARDS, std::default_random_engine(seed));
}

void Game::DistributeCards() {
    // Moving the Cards from all_cards_array to the draw_cards_stack
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        draw_cards_stack.push(all_cards_array[i]);
    }

    // Distributing the Cards in the beginning of the game to the 7 vectors of cards
    for (int vec = 0; vec < 7; vec++) {
        for (int i = 0; i < vec + 1; i++) {
            card_vectors_array[vec].push_back(draw_cards_stack.top());
            draw_cards_stack.pop();
        }
        // Flipping the last card of each vector
        card_vectors_array[vec][vec]->setHidden(0);
    }
}

// Functions
bool Game::IsRunning() {
    return window->isOpen();
}

void Game::PollEvents() {
    // Event Polling
    while (window->pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
                // Event of clicking the mouse
            case sf::Event::MouseButtonPressed: {
                // Clicking the start button in the beginning of the game
                if (sf::Mouse::Button::Left == event.mouseButton.button){
                    if (start_btn->isMouseOver(*window)) {
                        is_window_on_start_frame = 0;
                        break;
                    }
                    // Checking if the user clicked on any card
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                        MouseClick();
                        break;
                    }
                    break;
                }
                break;
            }
        }
    }
}

void Game::DragDrop() {
    for (int vec = 0; vec < 7; vec++) {
        int sz = card_vectors_array[vec].size();
        for (int i = 0; i < sz; i++) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && card_vectors_array[vec][i]->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))) &&!card_vectors_array[vec][i]->getHidden()) {
                card_vectors_array[vec][i]->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
            }
//            else
//            {
//                card_vectors_array[vec][i]->setPosition(card_vectors_array[vec][i]->get_last_valid_position());
//            }
        }
    }
}

void Game::MouseClick() {
    int st_x = DRAW_STACK_X_POS - CARD_WIDTH / 2;
    int st_y = DRAW_STACK_Y_POS - CARD_HEIGHT / 2;
    int en_x = DRAW_STACK_X_POS + CARD_WIDTH / 2;
    int en_y = DRAW_STACK_Y_POS + CARD_HEIGHT / 2;

    bool click_on_4_stacks = 0;
    Card * click;
    for (int i =0; i < 4; i++){
        if(final_cards_stacks[i].size() != 0 && final_cards_stacks[i].top()->getGlobalBounds().contains(
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)))){
            click_on_4_stacks = 1;
            click = final_cards_stacks[i].top();
            break;
        }
    }
    // Clicking a card in the draw cards stack
    if (sf::Mouse::getPosition(*window).x >= st_x && sf::Mouse::getPosition(*window).x <= en_x
        && sf::Mouse::getPosition(*window).y >= st_y && sf::Mouse::getPosition(*window).y <= en_y) {
        MoveFromDrawCardsStack();
    }
    // Clicking a card in the drawn flipped cards stack
    else if (!drawn_flipped_cards_stack.empty() && drawn_flipped_cards_stack.top()->getGlobalBounds().contains(
            window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
        MoveFromFlippedCardsStack();
    }
    // Clicking a card in the final 4 cards
    else if(click_on_4_stacks){
        MoveFromFinalCardsStack(click);
    }
    // Clicking a card in the 7 vectors
    else {
        MoveLastCardFromVectors();
        MoveMultipleCardsFromVectors();
    }
}

// Winning and losing functions
bool Game::CheckWinStatus() {
    for(int i =0; i < 4;i++){
        if(final_cards_stacks[i].size() != 13){
            return false;
        }
    }
    return true;
}

// NEEDS TESTING
bool Game::CheckLossStatus() {
    for (int vec = 0; vec < 7; vec++) {
        int sz = card_vectors_array[vec].size();
        bool card_moved = 0;
        for (int i = 0; i < sz-1; i++) {
            Card * card_played = card_vectors_array[vec][i];
            if (!card_played->getHidden()) {
                for (int vec2 = 0; vec2 < 7; vec2++) {
                    int sz2 = card_vectors_array[vec2].size();
                    // Check if the current vector is not empty
                    if (sz2 != 0) {
                        // Check if the card can move to the current vector
                        if (card_vectors_array[vec2][sz2 - 1]->getNumber() ==
                            card_played->getNumber() + 1 &&
                            card_played->getColor() != card_vectors_array[vec2][i]->getColor()) {
                            return false;
                        }
                    }
                        // Check if the current vector is empty and the card to be moved is a king
                    else if (sz2 == 0 && card_played->getNumber() == 13) {
                        return false;
                    }

                }

            }

        }
        card_moved = MoveToFinalCardsStacks(card_vectors_array[vec][sz-1]);
        if(!card_moved){
            card_moved = MoveToVectorsCards(card_vectors_array[vec][sz-1]);
        }

        if(card_moved){
            return false;
        }

    }
    bool stack_card_moved = 0;
    stack_card_moved= MoveToFinalCardsStacks(drawn_flipped_cards_stack.top());
    if(!stack_card_moved){
        stack_card_moved = MoveToVectorsCards(drawn_flipped_cards_stack.top());
    }

    if(stack_card_moved){
        return false;
    }
    return true;
// but i am pretty sure there are more stuff we need to add
}

// Move From functions
void Game::MoveFromDrawCardsStack() {
    // Check if The stack is empty (contains a dummy card)
    if (draw_cards_stack.empty()) {
        // return all the flipped cards to the draw_cards_stack
        while (!drawn_flipped_cards_stack.empty()) {
            drawn_flipped_cards_stack.top()->setHidden(1);
            draw_cards_stack.push(drawn_flipped_cards_stack.top());
            drawn_flipped_cards_stack.pop();
        }
    }
        // Check The stack is not empty (contains some cards)
    else {
        // draw a card
        Card *stored_card = draw_cards_stack.top();
        stored_card->setHidden(0);
        drawn_flipped_cards_stack.push(stored_card);
        draw_cards_stack.pop();
    }
}

void Game::MoveFromFlippedCardsStack() {
    bool card_moved = 0;
    // Check the 4 final stacks
    card_moved = MoveToFinalCardsStacks(drawn_flipped_cards_stack.top());
    // Check the 7 vectors of cards
    if (!card_moved)
        card_moved = MoveToVectorsCards(drawn_flipped_cards_stack.top());
    // If the move is valid remove the card from the flipped cards stack
    if (card_moved)
        drawn_flipped_cards_stack.pop();
}

void Game::MoveLastCardFromVectors() {
    bool card_moved = 0;
    // start of the vectors part
    for(int vec = 0; vec < 7; vec++){
        int vec_size = card_vectors_array[vec].size();
        // Check if the user clicked on the last card of the current vector
        if(card_vectors_array[vec].size() != 0 && card_vectors_array[vec][vec_size -1]->getGlobalBounds().contains(
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)))){
            // Check the 4 final stacks
            card_moved = MoveToFinalCardsStacks(card_vectors_array[vec][vec_size -1]);
            // Check the 7 vectors of cards
            if (!card_moved)
                card_moved = MoveToVectorsCards(card_vectors_array[vec][vec_size -1]);
            // If the move is valid remove the card from the current vector of cards
            if (card_moved) {
                card_vectors_array[vec].pop_back();
                int sz = card_vectors_array[vec].size();
                if (sz != 0)
                    card_vectors_array[vec][sz - 1]->setHidden(0);
                break;
            }
        }
    }
}

void Game::MoveMultipleCardsFromVectors() {
    bool card_moved = 0;
    // start of the vectors part
    for(int vec = 0; vec < 7; vec++){
        int vec_size = card_vectors_array[vec].size();
        // Check if the user clicked on any card of the vector
        for (int i = 0; i < vec_size - 1; i++) {
            int st_x = card_vectors_array[vec][i]->getPosition().x - CARD_WIDTH / 2;
            int en_x = card_vectors_array[vec][i]->getPosition().x + CARD_WIDTH / 2;
            int st_y = card_vectors_array[vec][i]->getPosition().y - CARD_HEIGHT / 2;
            int en_y = st_y + DIST_BETWEEN_CARDS;
            if (!card_vectors_array[vec][i]->getHidden() &&
                sf::Mouse::getPosition(*window).x >= st_x && sf::Mouse::getPosition(*window).x <= en_x
                && sf::Mouse::getPosition(*window).y >= st_y && sf::Mouse::getPosition(*window).y <= en_y) {
                // Check the 7 vectors of cards
                card_moved = MoveMultipleCardsToVectors(vec, i);
                // If the move is valid remove the cards from the current vector
                if (card_moved) {
                    for (int k = i; k < vec_size; k++)
                        card_vectors_array[vec].pop_back();
                    if (i != 0)
                        card_vectors_array[vec][i - 1]->setHidden(0);
                    break;
                }
            }
        }
        if (card_moved)
            break;
    }
}

void Game::MoveFromFinalCardsStack(Card *playing_card) {
    bool card_moved = 0;
    // start of the vectors part
    for(int idx = 0; idx < 4; idx++){
        // Check if the user clicked on the last card of the current vector
        if(final_cards_stacks[idx].size() != 0 && final_cards_stacks[idx].top() == playing_card){
            card_moved = MoveToVectorsCards(final_cards_stacks[idx].top());
            // If the move is valid remove the card from the current vector of cards
            if (card_moved) {
                final_cards_stacks[idx].pop();
                break;
            }
        }
    }
}

// Move To functions
bool Game::MoveToFinalCardsStacks(Card *playing_card) {
    bool finale_stack_flag = 0;
    // checking if the user can play in the final cards stack
    for (int i = 0; i < 4; i++) {
        // Check if one of the stacks is empty
        if (final_cards_stacks[i].empty()) {
            // Check if the card is an ace
            if (playing_card->getNumber() == 1) {
                if (i == 0 && playing_card->getSymbol() == "diamond") {
                    if(final_cards_stacks[i].size() == 0){
                        sco += 15;
                    }
                    else if (final_cards_stacks[i].size() >0 && final_cards_stacks[i].size() < 12){
                        sco += 10;
                    }
                    final_cards_stacks[i].push(playing_card);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 1 && playing_card->getSymbol() == "spades") {
                    if(final_cards_stacks[i].size() == 0) {
                        sco += 15;
                    }
                    else if (final_cards_stacks[i].size() >0 && final_cards_stacks[i].size() < 12){
                        sco += 10;
                    }
                    final_cards_stacks[i].push(playing_card);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 2 && playing_card->getSymbol() == "hearts") {
                    if(final_cards_stacks[i].size() == 0){
                        sco += 15;
                    }
                    else if (final_cards_stacks[i].size() >0 && final_cards_stacks[i].size() < 12){
                        sco += 10;
                    }
                    final_cards_stacks[i].push(playing_card);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 3 && playing_card->getSymbol() == "clover") {
                    if(final_cards_stacks[i].size() == 0){
                        sco += 15;
                    }
                    else if (final_cards_stacks[i].size() >0 && final_cards_stacks[i].size() < 12){
                        sco += 10;
                    }
                    final_cards_stacks[i].push(playing_card);
                    finale_stack_flag = 1;
                    break;
                }
            }
        }
            // Check if one of the stacks wasn't empty
        else if (final_cards_stacks[i].top()->getNumber() == playing_card->getNumber() - 1 &&
                 final_cards_stacks[i].top()->getSymbol() == playing_card->getSymbol()) {
            finale_stack_flag = 1;
            if(final_cards_stacks[i].size() == 0) {
                sco += 15;
            }
            else if (final_cards_stacks[i].size() >0 && final_cards_stacks[i].size() < 12){
                sco += 10;
            }
            final_cards_stacks[i].push(playing_card);

            break;
        }
    }
    return finale_stack_flag;
}

bool Game::MoveToVectorsCards(Card *playing_card) {
    bool vector_flag = 0;
    // looping on all vectors and comparing with the last element to check if we can play on it
    for (int vec = 0; vec < 7; vec++) {
        int sz = card_vectors_array[vec].size();
        // Check if the current vector is not empty
        if(sz != 0){
            // Check if the card can move to the current vector
            if (card_vectors_array[vec][sz - 1]->getNumber() == playing_card->getNumber() + 1 &&
                card_vectors_array[vec][sz - 1]->getColor() != playing_card->getColor()) {
                sco +=5;
                card_vectors_array[vec].push_back(playing_card);
                vector_flag = 1;
                break;
            }
        }
            // Check if the current vector is empty and the card to be moved is a king
        else if(sz == 0 && playing_card->getNumber() == 13){
            card_vectors_array[vec].push_back(playing_card);
            sco +=5;
            vector_flag = 1;
            break;
        }
    }
    // Complete the condition of moving a group of cards
    return vector_flag;
}

bool Game::MoveMultipleCardsToVectors(int vec_idx, int card_idx) {
    bool vector_flag = 0;
    // looping on all vectors and comparing with the last element to check if we can play on it
    for (int vec = 0; vec < 7; vec++) {
        int sz = card_vectors_array[vec].size();
        // Check if the current vector is not empty
        if(sz != 0){
            // Check if the card can move to the current vector
            if (card_vectors_array[vec][sz - 1]->getNumber() == card_vectors_array[vec_idx][card_idx]->getNumber() + 1 &&
                card_vectors_array[vec][sz - 1]->getColor() != card_vectors_array[vec_idx][card_idx]->getColor()) {
                // Put all the cards (starting from the clicked card) in the current vector
                int vec_sz = card_vectors_array[vec_idx].size();
                for (int i = card_idx; i < vec_sz; i++)
                    card_vectors_array[vec].push_back(card_vectors_array[vec_idx][i]);
                sco +=5;
                vector_flag = 1;
                break;
            }
        }
            // Check if the current vector is empty and the card to be moved is a king
        else if(sz == 0 && card_vectors_array[vec_idx][card_idx]->getNumber() == 13){
            // Put all the cards (starting from the clicked card) in the current vector
            int vec_sz = card_vectors_array[vec_idx].size();
            for (int i = card_idx; i < vec_sz; i++){
                card_vectors_array[vec].push_back(card_vectors_array[vec_idx][i]);
                sco +=5;
            }

            vector_flag = 1;
            break;
        }
    }
    return vector_flag;
}

// Draw to window function
void Game::DrawFrame() {
    // Drawing The first frame which contains the start button
    if (is_window_on_start_frame) {
        window->clear();
        window->draw(*bg_sprite);
        window->draw(btn_shape);
        window->display();
        return;
    }
    // Update the background image
    UpdateBackgroundImage();
    // Drawing other frames
    window->clear();
    window->draw(*bg_sprite);

    // Drawing the Timer
    sf::Text timetext("", font);
    timetext.setPosition(WINDOW_WIDTH / 2 - 40,20);
    timetext.setCharacterSize(40);
    ss.str("");
    time = clock.getElapsedTime();
    seconds = time.asSeconds();
    hours = seconds / 3600;
    minutes = (seconds - (hours * 3600)) / 60;
    seconds = seconds - (hours * 3600 + minutes * 60);
    if(minutes < 10) {
        ss << "0" << minutes;
    }
    else {
        ss << minutes;
    }
    if(seconds < 10) {
        ss << ":" << "0" << seconds;
    }
    else {
        ss << ":" << seconds;
    }
    timetext.setString(ss.str());
    window->draw(timetext);
    // Draw Score
    sf::Text score("", font);
    // M_K change the position
    score.setPosition(70,20);
    score.setCharacterSize(35);
    ss2.str("");
    int sth = sco;
    ss2 << "Score: " << sth;
    score.setString(ss2.str());
    window->draw(score);

    // Draw the cards in the draw_cards_stack
    if (!draw_cards_stack.empty()) {
        draw_cards_stack.top()->setPosition({DRAW_STACK_X_POS, DRAW_STACK_Y_POS});
        draw_cards_stack.top()->drawTo(*window);
    }
    // Draw the cards in the drawn_flipped_cards_stack
    if (!drawn_flipped_cards_stack.empty()) {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
            drawn_flipped_cards_stack.top()->setPosition({DRAW_STACK_X_POS + DIST_BETWEEN_VECTORS, DRAW_STACK_Y_POS});
        }
        drawn_flipped_cards_stack.top()->drawTo(*window);
    }
    // Draw the cards in the 4 final stacks
    for (int i = 0; i < 4; i++) {
        if (!final_cards_stacks[i].empty()) {
            final_cards_stacks[i].top()->setPosition({static_cast<float>(DRAW_STACK_X_POS + (3 + i) * DIST_BETWEEN_VECTORS), DRAW_STACK_Y_POS});
            final_cards_stacks[i].top()->drawTo(*window);
        }
    }
    // Draw the cards in the 7 vectors
    for (int vec = 0; vec < 7; vec++) {
        int sz = card_vectors_array[vec].size();
        for (int i = 0; i < sz; i++) {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
                card_vectors_array[vec][i]->UpdatePosition(vec, i);
            }
            card_vectors_array[vec][i]->set_last_valid_position(vec, i);
            card_vectors_array[vec][i]->drawTo(*window);
        }
    }
    // Display
    window->display();
}

void Game::DrawWinFrame() {
    window->clear();
    // Load the image
    sf::Texture win_texture;
    if (!win_texture.loadFromFile("img/WIN-FRAME.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    // Link the texture with the sprite
    bg_sprite = new sf::Sprite(win_texture);
    bg_sprite->setTextureRect(sf::IntRect(0, 0, 1280, 960));
    bg_sprite->setColor(sf::Color(255, 255, 255));
    // Draw the win frame
    window->draw(*bg_sprite);
    window->display();
}
