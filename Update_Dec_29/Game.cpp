//
// Created by Ayman on 12/29/2022.
//

#include "Game.h"

// Constructors
Game::Game() {
    is_window_on_start_frame = 1;
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
bool Game::GetIsRunning() {
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
                if (start_btn->isMouseOver(*window)) {
                    is_window_on_start_frame = 0;
                    break;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    MouseClick();
                    break;
                }
            }
        }
    }
}

void Game::MouseClick() {
    std::cout << sf::Mouse::getPosition(*window).x << " : " << sf::Mouse::getPosition(*window).y << "\n";
    // Test
    int st_x = DRAW_STACK_X_POS - CARD_WIDTH / 2;
    int st_y = DRAW_STACK_Y_POS - CARD_HEIGHT / 2;
    int en_x = DRAW_STACK_X_POS + CARD_WIDTH / 2;
    int en_y = DRAW_STACK_Y_POS + CARD_HEIGHT / 2;
    if (sf::Mouse::getPosition(*window).x >= st_x && sf::Mouse::getPosition(*window).x <= en_x
        && sf::Mouse::getPosition(*window).y >= st_y && sf::Mouse::getPosition(*window).y <= en_y) {
        MoveFromDrawCardsStack();
    }
    // Clicking a card in the draw cards stack
    else if (!draw_cards_stack.empty() && draw_cards_stack.top()->getGlobalBounds().contains(
                window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
        MoveFromDrawCardsStack();
    }
    // Clicking a card in the drawn flipped cards stack
    else if (!drawn_flipped_cards_stack.empty() && drawn_flipped_cards_stack.top()->getGlobalBounds().contains(
                     window->mapPixelToCoords(sf::Mouse::getPosition(*window)))) {
        MoveFromFlippedCardsStack();
    }
    // Clicking a card in the 7 vectors
    else {
        MoveFromVectorsCards();
    }
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

void Game::MoveFromVectorsCards() {
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
                    final_cards_stacks[i].push(playing_card);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 1 && playing_card->getSymbol() == "spades") {
                    final_cards_stacks[i].push(playing_card);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 2 && playing_card->getSymbol() == "hearts") {
                    final_cards_stacks[i].push(playing_card);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 3 && playing_card->getSymbol() == "clover") {
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
            final_cards_stacks[i].push(playing_card);
            break;
        }
    }
    return finale_stack_flag;
}

// This function is not complete
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
                card_vectors_array[vec].push_back(playing_card);
                vector_flag = 1;
                break;
            }
        }
        // Check if the current vector is empty and the card to be moved is a king
        else if(sz == 0 && playing_card->getNumber() == 13){
            card_vectors_array[vec].push_back(playing_card);
            vector_flag = 1;
            break;
        }
    }
    // Complete the condition of moving a group of cards
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
    // Draw the cards in the draw_cards_stack
    if (!draw_cards_stack.empty()) {
        draw_cards_stack.top()->setPosition({DRAW_STACK_X_POS, DRAW_STACK_Y_POS});
        draw_cards_stack.top()->drawTo(*window);
    }
    // Draw the cards in the drawn_flipped_cards_stack
    if (!drawn_flipped_cards_stack.empty()) {
        drawn_flipped_cards_stack.top()->setPosition({DRAW_STACK_X_POS + DIST_BETWEEN_VECTORS, DRAW_STACK_Y_POS});
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
            card_vectors_array[vec][i]->UpdatePosition(vec, i);
            card_vectors_array[vec][i]->drawTo(*window);
        }
    }
    // Display
    window->display();
}

