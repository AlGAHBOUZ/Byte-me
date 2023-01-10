//
// Created by Ayman on 12/29/2022.
//

#include "Game.h"

// Constructor
Game::Game() {
    is_window_on_start_frame = 1;
    // Initialize timer variables
    seconds = 0;
    hours = 0;
    minutes = 0;
    // Initialize score variables
    sco = 0;
    // Initialize hint variables
    hint_pressed = 0;
    // Initialize Undo button variables
    undo_pressed = 0;
    was_hidden = 0;

    // Initialize Drag and Drop variables
    hover = 0;
    dragable = 0;
    picked_up = 0;
    selected_card = nullptr;
    last_card_dragged = 0;
    multiple_cards_dragged = 0;

    // Call Initializing functions
    InitWindow();
    InitStartBtn();
    InitCards();
    ShuffleCards();
    DistributeCards();
    InitHintBtn();
    InitUndoBtn();
}

// Destructor
Game::~Game() {
    delete window;
    delete bg_sprite;
    delete start_btn;
    delete hint_btn;
    delete undo_btn;
    delete selected_card;
    // delete the pointers to cards
    for (int i = 0; i < NUMBER_OF_CARDS; i++) {
        delete all_cards_array[i];
    }
}

// Private Functions
void Game::InitWindow() {
    // Initialize window variables
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
    // Load the font of the timer and the score
    if (!font.loadFromFile("img/3X5.ttf")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    // Load the background image
    UpdateBackgroundImage();
}

void Game::InitStartBtn() {
    // Initialize start button variables
    start_btn = new Button("Start the Game!", {312, 312}, 42, sf::Color::Blue, sf::Color::Black);
    float btn_x_pos = ((window->getSize().y / 2) + 70);
    float btn_y_pos = (window->getSize().x / 3) + 50;
    start_btn->setPosition({btn_y_pos, btn_x_pos});

    btn_shape.setSize({312, 312});
    btn_shape.setPosition({btn_y_pos, btn_x_pos});
    // Load start Button image
    if (!btn_texture.loadFromFile("img/start.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    btn_shape.setTexture(&btn_texture);
}

void Game::InitHintBtn() {
    // Initialize hint button variables
    sf::Vector2f hint_size = {185, 53};
    hint_btn = new Button("Hints!", hint_size, 12, sf::Color::Blue, sf::Color::Black);
    float btn_x_pos = 30;
    float btn_y_pos = 15;
    hint_btn->setPosition({btn_x_pos, btn_y_pos});
    hint_shape.setSize(hint_size);
    hint_shape.setPosition({btn_x_pos, btn_y_pos});
    // Load hint Button image
    if (!hint_texture.loadFromFile("img/hint_btn.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    hint_shape.setTexture(&hint_texture);
}

void Game::InitUndoBtn() {
    // Initialize undo button variables
    sf::Vector2f hint_size = {185, 53};
    undo_btn = new Button("Undo!", hint_size, 12, sf::Color::Blue, sf::Color::Black);
    float btn_x_pos = 30;
    float btn_y_pos = 900;
    undo_btn->setPosition({btn_x_pos, btn_y_pos});
    undo_shape.setSize(hint_size);
    undo_shape.setPosition({btn_x_pos, btn_y_pos});
    // Load undo Button image
    if (!undo_texture.loadFromFile("img/undo_btn.png")) {
        std::cout << "Load failed" << std::endl;
        system("pause");
    }
    undo_shape.setTexture(&undo_texture);
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
    } else {
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
    for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
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
            // If the user closed the program
            case sf::Event::Closed:
                window->close();
                break;
            // If the user clicked escape key and closed the program
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window->close();
                break;
            // Event of clicking the mouse
            case sf::Event::MouseButtonPressed: {
                if (sf::Mouse::Button::Left == event.mouseButton.button) {
                    // If the user clicked the start button
                    if (start_btn->isMouseOver(*window)) {
                        is_window_on_start_frame = 0;
                    }
                    // If the user clicked the hint button
                    if (hint_btn->isMouseOver(*window)) {
                        hint_pressed = Hint();
                        break;
                    }
                    // If the user clicked the undo button
                    if (undo_btn->isMouseOver(*window)) {
                        undo_pressed = Undo();
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

bool Game::MouseIntersects(Card * card) {
    return card->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}

/**********************************************************************/
// Drag and Drop functions
Card* Game::get_selected_card(){
    return selected_card;
}
void Game::set_picked_up(bool a){
    picked_up = a;
}
void Game::set_selected_card_toNull(){
    selected_card = nullptr;
}

void Game::selectCard(){
    if (!picked_up){
        for (int i = 0; i < 7; i++) {
            int sz = card_vectors_array[i].size();
            for (int j = 0; j < sz; j++) {
                hover = MouseIntersects(card_vectors_array[i][j]);
                if (hover && !card_vectors_array[i][j]->getHidden() && j == sz - 1) {
                    selected_card = card_vectors_array[i][j];
                    selected_card_i = i;
                    selected_card_j = j;
                }
            }
        }
    }
}

void Game::DragDrop() {
    bool hover_over_selected_card = MouseIntersects(selected_card);
    if (hover_over_selected_card){
        selected_card->setPosition(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y));
    }
    else{
        selected_card = nullptr;
    }
}

bool Game::DragLastCardFromVectors() {
    bool card_moved = 0;
    if (selected_card != nullptr) {
        int sz = card_vectors_array[selected_card_i].size();
        if (selected_card_j == sz - 1) {

            //sending the previous location that we came from to our function
            // so if we can move the last card it will be added to the command pushed in the undo stack
            std::string prev_location = "card_vectors_array[";
            prev_location += std::to_string(selected_card_i);
            prev_location += "]";
            if(sz > 1){
                was_hidden = card_vectors_array[selected_card_i][sz - 2]->getHidden();
            }
            // adding if it was hidden to our command
            prev_location += "{";
            prev_location += std::to_string(was_hidden);
            prev_location += "}";

            card_moved = DragLastCardToVectors(prev_location);
            if (card_moved) {
                card_vectors_array[selected_card_i].pop_back();
                sz = card_vectors_array[selected_card_i].size();
                if (sz != 0)
                    card_vectors_array[selected_card_i][sz - 1]->setHidden(0);
            }
        }
    }
    last_card_dragged = card_moved;
    return card_moved;
}

bool Game::DragLastCardToVectors(std::string previous_location){
    bool vector_flag = 0;
    // looping on all vectors and comparing with the last element to check if we can play on it
    for (int vec = 0; vec < 7; vec++) {
        int st_y = FIRST_CARD_Y_POS;
        int en_y = st_y + CARD_HEIGHT;
        int st_x = FIRST_CARD_X_POS + vec * DIST_BETWEEN_VECTORS;
        int en_x = st_x + CARD_WIDTH;

        int sz = card_vectors_array[vec].size();
        // Check if the current vector is not empty
        if(sz != 0){
            // Check if the card can move to the current vector
            bool intersects = MouseIntersects(card_vectors_array[vec][sz - 1]);
            if (card_vectors_array[vec][sz - 1]->getNumber() == selected_card->getNumber() + 1 &&
            card_vectors_array[vec][sz - 1]->getColor() != selected_card->getColor() && intersects) {
                sco +=5;

                // if we can move then we add the ending location to our command
                std::string new_location = "card_vectors_array[";
                new_location += std::to_string(vec);
                new_location += "]";
                std::string undo_message = previous_location;
                undo_message += "=";
                undo_message += new_location;
                // then push the whole command into our stack
                undo.push(undo_message);

                card_vectors_array[vec].push_back(selected_card);
                vector_flag = 1;
                break;
            }
        }
        // Check if the current vector is empty and the card to be moved is a king
        else if(sz == 0 && selected_card->getNumber() == 13
        &&sf::Mouse::getPosition(*window).x >= st_x && sf::Mouse::getPosition(*window).x <= en_x
        && sf::Mouse::getPosition(*window).y >= st_y && sf::Mouse::getPosition(*window).y <= en_y ){
            card_vectors_array[vec].push_back(selected_card);

            std::string new_location = "card_vectors_array[";
            new_location += std::to_string(vec);
            new_location += "]";
            std::string undo_message = previous_location;
            undo_message += "=";
            undo_message += new_location;
            undo.push(undo_message);

            sco +=5;
            vector_flag = 1;
            break;
        }
    }
    // Complete the condition of moving a group of cards
    return vector_flag;
}

/**********************************************************************/

// Click function
void Game::MouseClick() {
    // Calculate the start position of the draw stack
    int st_x = DRAW_STACK_X_POS - CARD_WIDTH / 2;
    int st_y = DRAW_STACK_Y_POS - CARD_HEIGHT / 2;
    int en_x = DRAW_STACK_X_POS + CARD_WIDTH / 2;
    int en_y = DRAW_STACK_Y_POS + CARD_HEIGHT / 2;

    bool click_on_4_stacks = 0;
    Card *click;
    for (int i = 0; i < NUMBER_OF_FINAL_STACKS; i++) {
        if (final_cards_stacks[i].size() != 0 && MouseIntersects(final_cards_stacks[i].top())) {
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
    else if (!drawn_flipped_cards_stack.empty() && MouseIntersects(drawn_flipped_cards_stack.top())){
        MoveFromFlippedCardsStack();
    }
    // Clicking a card in the final 4 cards
    else if (click_on_4_stacks) {
        MoveFromFinalCardsStack(click, "FinalCardsStack");
    }
    // Clicking a card in the 7 vectors
    else {
        MoveLastCardFromVectors();
        MoveMultipleCardsFromVectors();
    }
}

// Winning function
bool Game::CheckWinStatus() {
    // Check if the final stacks are complete
    for (int i = 0; i < NUMBER_OF_FINAL_STACKS; i++) {
        if (final_cards_stacks[i].size() != 13) {
            return false;
        }
    }
    return true;
}

// Hint button function
bool Game::Hint() {
    // checking if we can move any cards from the drawn flipped stack
    bool stack_card_moved = 0;
    if (drawn_flipped_cards_stack.size() != 0) {
        hint = " ";
        stack_card_moved = testMoveToFinalCardsStacks(drawn_flipped_cards_stack.top());
        if (!stack_card_moved) {
            stack_card_moved = testMoveToVectorsCards(drawn_flipped_cards_stack.top());
        }

    }

    if (stack_card_moved) {
// if a card can be moved from the drawn flipped stack then we see which card was it
// and turn the hint message to the information about that card:
// the card's number, and it's symbol
        if (drawn_flipped_cards_stack.top()->getNumber() < 11) {
            hint += std::to_string(drawn_flipped_cards_stack.top()->getNumber());
        }
            // if the number is greater than 10 we check if it's a J or a Q or a K
        else if (drawn_flipped_cards_stack.top()->getNumber() == 11) {
            hint += "J";
        } else if (drawn_flipped_cards_stack.top()->getNumber() == 12) {
            hint += "Q";
        } else if (drawn_flipped_cards_stack.top()->getNumber() == 13) {
            hint += "K";
        }
        hint += " of ";
        hint += drawn_flipped_cards_stack.top()->getSymbol();
        return true;
    }
    // looping to see if we can move any card from the 7 vectors
    for (int vec = 0; vec < 7; vec++) {
        int sz = card_vectors_array[vec].size();
        hint = " ";
        bool card_moved = 0;
        if (sz != 0) {
            card_moved = testMoveToFinalCardsStacks(card_vectors_array[vec][sz - 1]);
            if (!card_moved) {
                card_moved = testMoveToVectorsCards(card_vectors_array[vec][sz - 1]);
            }
        }


// if the last card can be moved from any of the vectors then we see which card was it
// and turn the hint message to the information about that card:
// the card's number, and it's symbol
        if (card_moved) {
            if (card_vectors_array[vec][sz - 1]->getNumber() < 11) {
                hint += std::to_string(card_vectors_array[vec][sz - 1]->getNumber());
            }
            // if the number is greater than 10 we check if it's a J or a Q or a K
            else if (card_vectors_array[vec][sz - 1]->getNumber() == 11) {
                hint += "J";
            } else if (card_vectors_array[vec][sz - 1]->getNumber() == 12) {
                hint += "Q";
            } else if (card_vectors_array[vec][sz - 1]->getNumber() == 13) {
                hint += "K";
            }
            hint += " of ";
            hint += card_vectors_array[vec][sz - 1]->getSymbol();
            return true;

        }

        for (int i = 0; i < sz - 1; i++) {
            Card *card_played = card_vectors_array[vec][i];
            if (!card_played->getHidden() && card_played->getNumber() == 1) {
                //checking if we have an Ace
                hint += std::to_string(card_played->getNumber());
                hint += " of ";
                hint += card_played->getSymbol();
                return true;
            }
            if (!card_played->getHidden()) {
// checking if was can press a card that moves more than one card with it (moving multiple cards)
// and turn the hint message to the information about that card:
// the card's number, and it's symbol
                for (int vec2 = 0; vec2 < NUMBER_OF_VECTORS; vec2++) {
                    int sz2 = card_vectors_array[vec2].size();
                    // Check if the current vector is not empty
                    if (sz2 != 0) {
                        // Check if the card can move to the current vector
                        if (card_vectors_array[vec2][sz2 - 1]->getNumber() ==
                            card_played->getNumber() + 1 &&
                            card_played->getColor() != card_vectors_array[vec2][sz2 - 1]->getColor()) {
                            if (card_played->getNumber() < 11) {
                                hint += std::to_string(card_played->getNumber());
                            } else if (card_played->getNumber() == 11) {
                                hint += "J";
                            } else if (card_played->getNumber() == 12) {
                                hint += "Q";
                            }
                            hint += " of ";
                            hint += card_played->getSymbol();
                            return true;
                            // string: you can play: card_played->getNumber() (convert to J AND Q) card_played->getSymbol()
                        }
                    }
                        // Check if the current vector is empty and the card to be moved is a king
                    else if (sz2 == 0 && card_played->getNumber() == 13) {
                        hint += "K";
                        hint += " of ";
                        hint += card_played->getSymbol();
                        return true;
                        // string: you can play: card_played->getNumber() (convert to J AND Q) card_played->getSymbol()

                    }

                }

            }

        }


    }
    //if there are no hints we tell the user to draw more cards
    hint = "Draw a card";
    return false;
}

// Undo button function
bool Game::Undo() {
    if (undo.size() != 0) {
// a flag declared to see where we can find the = which separates between the start location and the end location
        bool found_equal = 0;
//declaring flags to see where the card came from and where it went
        bool start_location_flipped_stack = 0;
        bool start_location_final_stack = 0;
        bool start_location_card_vector = 0;
        bool start_location_many_cards = 0;
        bool end_location_final_stack = 0;
        bool end_location_card_vector = 0;
 // a flag to check if we had drawn a card from the drawn_cards_stack
        bool drawn_flipped = 0;
  // declaring some integer varailbes to store the indexes of any vectors we moved to or from
        int start_idx, end_idx, many_card_idx;
        std::string start_index = "", end_index = "", many_card_index = "";
        // intilazing the command with the latest comman which is the top of the undo stack
        std::string command = undo.top();
        // intialinzg two strings to store the start location and end location
        std::string from_where = "";
        std::string to_where = "";
        // a flag to see if the card that was behind a card (or cards) moved to another location was hidden or not
        bool was_card_hidden;

        for (int i = 0; i < command.length(); i++) {
//if the = isn't found then we're still in the previous location
// so we determine which location was it and setting the flag of that location to 1
            if (command[i] != '=' && !found_equal) {
                from_where += command[i];
                if (from_where == "Flipped") {
                    start_location_flipped_stack = 1;
                } else if (from_where == "final") {
                    start_location_final_stack = 1;
                } else if (from_where == "card") {
                    start_location_card_vector = 1;
                } else if (from_where == "many") {
                    start_location_many_cards = 1;
                }
                else if (from_where == "drawn"){
                    drawn_flipped = 1;
                }
// if we found [ then that means we have a vector index, so we store that index
                if (command[i] == '[') {
                    int j = i + 1;
                    while (command[j] != ']') {
                        start_index += command[j];
                        j++;
                    }
                    start_idx = std::stoi(start_index);
                }
// if we found { then that means we want to check on the card that was behind the card(s) moved
                if (command[i] == '{') {
                    //tunring the number after the { to an integer using ASCII
                    was_card_hidden = command[i+1] - 48;
                }

            }
            // if we found the = we start storing the ending location
            else if (command[i] == '=') {
                found_equal = 1;
            }
            else if (command[i] != '=' && found_equal) {
                to_where += command[i];
                if (to_where == "final") {
                    end_location_final_stack = 1;

                } else if (to_where == "card") {
                    end_location_card_vector = 1;

                }
// if we found [ then that means we have a vector index, so we store that index
                if (command[i] == '[') {
                    int j = i + 1;
                    while (command[j] != ']') {
                        end_index += command[j];
                        j++;
                    }
                    end_idx = std::stoi(end_index);

                }
  // if we found ( then that means we moved more than one card, so we need to store the index of the card we plan to
  // move back with all the cards below it
                if (command[i] == '(') {
                    int k = i + 1;
                    while (command[k] != ')') {
                        many_card_index += command[k];
                        k++;
                    }
                    many_card_idx = std::stoi(many_card_index);
                }

            }
        }
  // All the possible start and end locations
  //while decrmenting the score (or even incrementing the score) when needed
        if (start_location_flipped_stack && end_location_final_stack) {

            drawn_flipped_cards_stack.push(final_cards_stacks[end_idx].top());


            if (final_cards_stacks[end_idx].size() != 0) {
                final_cards_stacks[end_idx].pop();
            }
            if (final_cards_stacks[end_idx].size() == 0) {
                if (sco >= 15){
                    sco -= 15;
                }
            } else {
                if (sco >= 10){
                    sco -= 10;
                }
            }
        }
        else if (start_location_flipped_stack && end_location_card_vector) {
            int sz = card_vectors_array[end_idx].size();
            if (sz != 0) {
                drawn_flipped_cards_stack.push(card_vectors_array[end_idx][sz - 1]);
            }

            sz = card_vectors_array[end_idx].size();
            if (sz != 0) {
                card_vectors_array[end_idx].pop_back();
            }
            if (sco > 0){
                sco -= 5;
            }

        }
        else if (start_location_final_stack && end_location_card_vector) {
            int sz = card_vectors_array[end_idx].size();
            if (sz != 0) {
                final_cards_stacks[start_idx].push(card_vectors_array[end_idx][sz - 1]);
            }
            sz = card_vectors_array[end_idx].size();
            if (sz != 0) {
                card_vectors_array[end_idx].pop_back();
            }
   // since we moved back to a final stack we see if it's an Ace to add 15 or any other card to add 10
            if (final_cards_stacks[end_idx].size() == 1) {
                sco += 15;
            } else {
                sco += 10;
            }
        }
        else if (start_location_card_vector && end_location_final_stack) {
            int sz = card_vectors_array[start_idx].size();


            card_vectors_array[start_idx].push_back(final_cards_stacks[end_idx].top());



            if (final_cards_stacks[end_idx].size() != 0) {
                final_cards_stacks[end_idx].pop();
            }

            int sz2 = card_vectors_array[start_idx].size();
            //setting the card behind the card that we just added to the way it was before moving
            if (sz2 > 1) {
                card_vectors_array[start_idx][sz2 - 2]->setHidden(was_card_hidden);
            }
            if (final_cards_stacks[end_idx].size() == 0) {
                if (sco >= 15){
                    sco -= 15;
                }
            } else {
                if (sco >= 10){
                    sco -= 10;
                }
            }
        }
        else if (start_location_card_vector && end_location_card_vector) {
            int sz = card_vectors_array[end_idx].size();
            if (sz != 0) {
                card_vectors_array[start_idx].push_back(card_vectors_array[end_idx][sz - 1]);
            }

            sz = card_vectors_array[end_idx].size();
            if (sz != 0) {
                card_vectors_array[end_idx].pop_back();
            }

            int sz2 = card_vectors_array[start_idx].size();
            //setting the card behind the card that we just added to the way it was before moving
            if (sz2 > 1) {
                card_vectors_array[start_idx][sz2 - 2]->setHidden(was_card_hidden);
            }
            if (sco > 0){
                sco -= 5;
            }
        }
        else if (start_location_many_cards && end_location_card_vector) {
            int sz = card_vectors_array[end_idx].size();
            int sz2 = card_vectors_array[start_idx].size();
            //setting the card behind the card that we just added to the way it was before moving
            if(sz2 != 0){
                card_vectors_array[start_idx][sz2 - 1]->setHidden(was_card_hidden);
            }
            //looping from the index we stored above to the end and pushing all these cards
            // to the previous vector we came from
            for (int move = many_card_idx; move < sz; move++) {
                card_vectors_array[start_idx].push_back(card_vectors_array[end_idx][move]);
            }
            // looping to pop the cards we just moved to it's previous location
            for (int move = sz - 1; move >= many_card_idx; move--) {
                sz = card_vectors_array[end_idx].size();
                if (sz != 0) {
                    card_vectors_array[end_idx].pop_back();
                    if(sco >= 5){
                        sco -= 5;
                    }

                }
            }
        }
        // if we pressed on a card from the draw stack we return it back after making it hidden again
        else if (drawn_flipped){
            if (drawn_flipped_cards_stack.size() != 0){
                drawn_flipped_cards_stack.top()->setHidden(1);
                draw_cards_stack.push(drawn_flipped_cards_stack.top());
                drawn_flipped_cards_stack.pop();
            }
        }
        // removing the command we just did from out stack
        undo.pop();
        return 1;
    }
    if (undo.size() == 1){
// if we reach the first command of our stack we loop to turn the vectors the same way they were at the start of the game
        sco  = 0;
        for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
            for (int i = 0; i < vec-1; i++) {
                card_vectors_array[vec][i]->setHidden(1);
            }
            // Flipping the last card of each vector
            card_vectors_array[vec][vec]->setHidden(0);
        }
    }
    sco  = 0;
    return 0;
}

// Move From functions
void Game::MoveFromDrawCardsStack() {
    // Check if the stack is empty (contains a dummy card)
    if (draw_cards_stack.empty()) {
        // return all the flipped cards to the draw_cards_stack
        while (!drawn_flipped_cards_stack.empty()) {
            drawn_flipped_cards_stack.top()->setHidden(1);
            draw_cards_stack.push(drawn_flipped_cards_stack.top());
            drawn_flipped_cards_stack.pop();
        }
    }
    // Check if the stack is not empty (contains some cards)
    else {
        // draw a card
        Card *stored_card = draw_cards_stack.top();
        stored_card->setHidden(0);
        drawn_flipped_cards_stack.push(stored_card);
        std::string undo_message = "drawn_flipped_pressed";
        //puhsing the command (that we had drawn a card) to our stack
        undo.push(undo_message);
        draw_cards_stack.pop();
    }
}

void Game::MoveFromFlippedCardsStack() {
    bool card_moved = 0;
    // Check the 4 final stacks
    //sending the prevoius location that we came from to our function
    // so if we can move the card it will be added to the command pushed in the undo stack
    card_moved = MoveToFinalCardsStacks(drawn_flipped_cards_stack.top(), "FlippedCardsStack");
    // Check the 7 vectors of cards
    if (!card_moved) {
        card_moved = MoveToVectorsCards(drawn_flipped_cards_stack.top(), "FlippedCardsStack");
        if (card_moved)
            sco += 5;
    }
    // If the move is valid remove the card from the flipped cards stack
    if (card_moved)
        drawn_flipped_cards_stack.pop();
}

void Game::MoveLastCardFromVectors() {
    bool card_moved = 0;
    // start of the vectors part
    for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
        int vec_size = card_vectors_array[vec].size();
        // Check if the user clicked on the last card of the current vector
        if (card_vectors_array[vec].size() != 0 && MouseIntersects(card_vectors_array[vec][vec_size - 1])) {

            // Check the 4 final stacks
            //sending the previous location that we came from to our function
            // so if we can move the last card it will be added to the command pushed in the undo stack
            std::string prev_location = "card_vectors_array[";
            prev_location += std::to_string(vec);
            prev_location += "]";
            if(vec_size > 1){
               was_hidden = card_vectors_array[vec][vec_size - 2]->getHidden();
            }
            // adding if it was hidden to our command
            prev_location += "{";
            prev_location += std::to_string(was_hidden);
            prev_location += "}";
            card_moved = MoveToFinalCardsStacks(card_vectors_array[vec][vec_size - 1], prev_location);
            bool final_cards_stack = card_moved;
            // Check the 7 vectors of cards
            if (!card_moved)
                card_moved = MoveToVectorsCards(card_vectors_array[vec][vec_size - 1], prev_location);
            // If the move is valid remove the card from the current vector of cards
            if (card_moved) {
                card_vectors_array[vec].pop_back();
                int sz = card_vectors_array[vec].size();
                if (sz != 0) {
                    card_vectors_array[vec][sz - 1]->setHidden(0);
                    if (!final_cards_stack)
                        sco += 5;
                }
                break;
            }
        }
    }
}

void Game::MoveMultipleCardsFromVectors() {
    bool card_moved = 0;
    // start of the vectors part
    for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
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
                //sending the previous location that we came from to our function
                // so if we can move many cards it will be added to the command pushed in the undo stack
                std::string prev_location = "many_card_vectors_array[";
                prev_location += std::to_string(vec);
                prev_location += "]";
                if(i != 0){
                    was_hidden = card_vectors_array[vec][i - 1]->getHidden();
                }
                // adding if it was hidden to our command
                prev_location += "{";
                prev_location += std::to_string(was_hidden);
                prev_location += "}";
                card_moved = MoveMultipleCardsToVectors(vec, i, prev_location);
                // If the move is valid remove the cards from the current vector
                if (card_moved) {
                    for (int k = i; k < vec_size; k++){
                        card_vectors_array[vec].pop_back();
                        sco += 5;
                    }
                    if (i != 0) {
                        card_vectors_array[vec][i - 1]->setHidden(0);

                    }
                    break;
                }
            }
        }
        if (card_moved)
            break;
    }
}

void Game::MoveFromFinalCardsStack(Card *playing_card, std::string previous_location) {
    bool card_moved = 0;
    // start of the vectors part
    for (int idx = 0; idx < NUMBER_OF_FINAL_STACKS; idx++) {
        // Check if the user clicked on the last card of the current vector
        if (final_cards_stacks[idx].size() != 0 && final_cards_stacks[idx].top() == playing_card) {
            //sending the previous location that we came from to our function
            // so if we can move the card it will be added to the command pushed in the undo stack
            std::string prev_location = "final_cards_stacks[";
            prev_location += std::to_string(idx);
            prev_location += "]";
            card_moved = MoveToVectorsCards(final_cards_stacks[idx].top(), prev_location);
            // If the move is valid remove the card from the current vector of cards
            if (card_moved) {
                final_cards_stacks[idx].pop();
                if (final_cards_stacks[idx].size() == 0) {
                    if (sco >= 15){
                        sco -= 15;
                    }
                } else {
                    if (sco >= 10){
                        sco -= 10;
                    }
                }
                break;
            }
        }
    }
}

// Move To functions
bool Game::MoveToFinalCardsStacks(Card *playing_card, std::string previous_location) {
    bool finale_stack_flag = 0;
    // checking if the user can play in the final cards stack
    for (int i = 0; i < NUMBER_OF_FINAL_STACKS; i++) {
        // Check if one of the stacks is empty
        if (final_cards_stacks[i].empty()) {
            // Check if the card is an ace
            if (playing_card->getNumber() == 1) {
                if (i == 0 && playing_card->getSymbol() == "diamond") {
                    final_cards_stacks[i].push(playing_card);
                    // if we can move then we add the ending location to our command
                    std::string new_location = "final_cards_stacks[";
                    new_location += std::to_string(i);
                    new_location += "]";
                    std::string undo_message = previous_location;
                    undo_message += "=";
                    undo_message += new_location;
                    // then push the whole command into our stack
                    undo.push(undo_message);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 1 && playing_card->getSymbol() == "spades") {
                    final_cards_stacks[i].push(playing_card);
                    std::string new_location = "final_cards_stacks[";
                    new_location += std::to_string(i);
                    new_location += "]";
                    std::string undo_message = previous_location;
                    undo_message += "=";
                    undo_message += new_location;
                    undo.push(undo_message);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 2 && playing_card->getSymbol() == "hearts") {
                    final_cards_stacks[i].push(playing_card);
                    std::string new_location = "final_cards_stacks[";
                    new_location += std::to_string(i);
                    new_location += "]";
                    std::string undo_message = previous_location;
                    undo_message += "=";
                    undo_message += new_location;
                    undo.push(undo_message);
                    finale_stack_flag = 1;
                    break;
                } else if (i == 3 && playing_card->getSymbol() == "clover") {
                    final_cards_stacks[i].push(playing_card);
                    std::string new_location = "final_cards_stacks[";
                    new_location += std::to_string(i);
                    new_location += "]";
                    std::string undo_message = previous_location;
                    undo_message += "=";
                    undo_message += new_location;
                    undo.push(undo_message);
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
            std::string new_location = "final_cards_stacks[";
            new_location += std::to_string(i);
            new_location += "]";
            std::string undo_message = previous_location;
            undo_message += "=";
            undo_message += new_location;
            undo.push(undo_message);
            break;
        }
    }
    if (finale_stack_flag)
        sco += 15;
    return finale_stack_flag;
}

bool Game::MoveToVectorsCards(Card *playing_card, std::string previous_location) {
    bool vector_flag = 0;
    // looping on all vectors and comparing with the last element to check if we can play on it
    for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
        int sz = card_vectors_array[vec].size();
        // Check if the current vector is not empty
        if (sz != 0) {
            // Check if the card can move to the current vector
            if (card_vectors_array[vec][sz - 1]->getNumber() == playing_card->getNumber() + 1 &&
                card_vectors_array[vec][sz - 1]->getColor() != playing_card->getColor()) {
                card_vectors_array[vec].push_back(playing_card);
                // if we can move then we add the ending location to our command
                std::string new_location = "card_vectors_array[";
                new_location += std::to_string(vec);
                new_location += "]";
                std::string undo_message = previous_location;
                undo_message += "=";
                undo_message += new_location;
                // then push the whole command into our stack
                undo.push(undo_message);
                vector_flag = 1;
                break;
            }
        }
            // Check if the current vector is empty and the card to be moved is a king
        else if (sz == 0 && playing_card->getNumber() == 13) {
            card_vectors_array[vec].push_back(playing_card);
            std::string new_location = "card_vectors_array[";
            new_location += std::to_string(vec);
            new_location += "]";
            std::string undo_message = previous_location;
            undo_message += "=";
            undo_message += new_location;
            undo.push(undo_message);
            vector_flag = 1;
            break;
        }
    }
    // Complete the condition of moving a group of cards
    return vector_flag;
}

bool Game::MoveMultipleCardsToVectors(int vec_idx, int card_idx, std::string previous_location) {
    bool vector_flag = 0;
    // looping on all vectors and comparing with the last element to check if we can play on it
    for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
        int sz = card_vectors_array[vec].size();
        // Check if the current vector is not empty
        if (sz != 0) {
            // Check if the card can move to the current vector
            if (card_vectors_array[vec][sz - 1]->getNumber() ==
                card_vectors_array[vec_idx][card_idx]->getNumber() + 1 &&
                card_vectors_array[vec][sz - 1]->getColor() != card_vectors_array[vec_idx][card_idx]->getColor()) {
                // Put all the cards (starting from the clicked card) in the current vector
                int vec_sz = card_vectors_array[vec_idx].size();
                for (int i = card_idx; i < vec_sz; i++)
                    card_vectors_array[vec].push_back(card_vectors_array[vec_idx][i]);
                // if we can move then we add the ending location to our command
                std::string new_location = "card_vectors_array[";
                new_location += std::to_string(vec);
                new_location += "]";
                int idx_moved_to = sz;
                new_location += "(";
                new_location += std::to_string(idx_moved_to);
                new_location += ")";
                std::string undo_message = previous_location;
                undo_message += "=";
                undo_message += new_location;
                // then push the whole command into our stack
                undo.push(undo_message);
                vector_flag = 1;
                break;
            }
        }
            // Check if the current vector is empty and the card to be moved is a king
        else if (sz == 0 && card_vectors_array[vec_idx][card_idx]->getNumber() == 13) {
            // Put all the cards (starting from the clicked card) in the current vector
            int vec_sz = card_vectors_array[vec_idx].size();
            for (int i = card_idx; i < vec_sz; i++) {
                card_vectors_array[vec].push_back(card_vectors_array[vec_idx][i]);
            }
            std::string new_location = "card_vectors_array[";
            new_location += std::to_string(vec);
            new_location += "]";
            int idx_moved_to = sz;
            new_location += "(";
            new_location += std::to_string(idx_moved_to);
            new_location += ")";
            std::string undo_message = previous_location;
            undo_message += "=";
            undo_message += new_location;
            undo.push(undo_message);
            vector_flag = 1;
            break;
        }
    }
    return vector_flag;
}

// Testing functions for hint option
bool Game::testMoveToFinalCardsStacks(Card *playing_card) {
    bool finale_stack_flag = 0;
    // checking if the user can play in the final cards stack
    for (int i = 0; i < NUMBER_OF_FINAL_STACKS; i++) {
        // Check if one of the stacks is empty
        if (final_cards_stacks[i].empty()) {
            // Check if the card is an ace
            if (playing_card->getNumber() == 1) {
                if (i == 0 && playing_card->getSymbol() == "diamond") {

                    finale_stack_flag = 1;
                    break;
                } else if (i == 1 && playing_card->getSymbol() == "spades") {

                    finale_stack_flag = 1;
                    break;
                } else if (i == 2 && playing_card->getSymbol() == "hearts") {

                    finale_stack_flag = 1;
                    break;
                } else if (i == 3 && playing_card->getSymbol() == "clover") {
                    finale_stack_flag = 1;
                    break;
                }
            }
        }
            // Check if one of the stacks wasn't empty
        else if (final_cards_stacks[i].top()->getNumber() == playing_card->getNumber() - 1 &&
                 final_cards_stacks[i].top()->getSymbol() == playing_card->getSymbol()) {
            finale_stack_flag = 1;

            break;
        }
    }
    return finale_stack_flag;
}

bool Game::testMoveToVectorsCards(Card *playing_card) {
    bool vector_flag = 0;
    // looping on all vectors and comparing with the last element to check if we can play on it
    for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
        int sz = card_vectors_array[vec].size();
        // Check if the current vector is not empty
        if (sz != 0) {
            // Check if the card can move to the current vector
            if (card_vectors_array[vec][sz - 1]->getNumber() == playing_card->getNumber() + 1 &&
                card_vectors_array[vec][sz - 1]->getColor() != playing_card->getColor()) {
                vector_flag = 1;
                break;
            }
        }
            // Check if the current vector is empty and the card to be moved is a king
        else if (sz == 0 && playing_card->getNumber() == 13) {
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
        time_start_btn = clock.getElapsedTime();
        return;
    }
    // Update the background image
    UpdateBackgroundImage();

    // Drawing other frames
    window->clear();
    window->draw(*bg_sprite);

    // Drawing the hint shape
    window->draw(hint_shape);

    // Drawing the undo shape
    window->draw(undo_shape);

    // Draw the Timer
    sf::Text timetext("", font);
    timetext.setPosition(WINDOW_WIDTH / 2 - 40, 20);
    timetext.setCharacterSize(40);
    ss.str("");
    time = clock.getElapsedTime() - time_start_btn;
    seconds = time.asSeconds();
    hours = seconds / 3600;
    minutes = (seconds - (hours * 3600)) / 60;
    seconds = seconds - (hours * 3600 + minutes * 60);
    if (minutes < 10) {
        ss << "0" << minutes;
    } else {
        ss << minutes;
    }
    if (seconds < 10) {
        ss << ":" << "0" << seconds;
    } else {
        ss << ":" << seconds;
    }
    timetext.setString(ss.str());
    window->draw(timetext);

    // Draw Score
    sf::Text score("", font);
    score.setPosition(1000, 20);
    score.setCharacterSize(35);
    ss2.str("");
    int sth = sco;
    ss2 << "Score " << sth;
    score.setString(ss2.str());
    window->draw(score);

    // Draw hint button
    sf::Text hintsth("", font);
    hintsth.setPosition(220, 20);
    hintsth.setCharacterSize(35);
    hinto.str("");
    hinto << hint;
    hintsth.setString(hinto.str());
    if (!hint_pressed){
        hintsth.setCharacterSize(30);
    }
    window->draw(hintsth);

    // Draw undo button
    sf::Text undosth("", font);
    undosth.setPosition(220, 900);
    undosth.setCharacterSize(35);
    undo_string.str("Undo Done");
    undosth.setString(undo_string.str());
    if (undo_pressed) {
        window->draw(undosth);
    }

    // Drawing the cards
    // Draw the cards in the draw_cards_stack
    if (!draw_cards_stack.empty()) {
        draw_cards_stack.top()->setPosition({DRAW_STACK_X_POS, DRAW_STACK_Y_POS});
        draw_cards_stack.top()->drawTo(*window);
    }
    // Draw the cards in the drawn_flipped_cards_stack
    if (!drawn_flipped_cards_stack.empty()) {
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
            drawn_flipped_cards_stack.top()->setPosition({DRAW_STACK_X_POS + DIST_BETWEEN_VECTORS, DRAW_STACK_Y_POS});
        }
        drawn_flipped_cards_stack.top()->drawTo(*window);
    }
    // Draw the cards in the 4 final stacks
    for (int i = 0; i < NUMBER_OF_FINAL_STACKS; i++) {
        if (!final_cards_stacks[i].empty()) {
            final_cards_stacks[i].top()->setPosition(
                    {static_cast<float>(DRAW_STACK_X_POS + (3 + i) * DIST_BETWEEN_VECTORS), DRAW_STACK_Y_POS});
            final_cards_stacks[i].top()->drawTo(*window);
        }
    }
    // Draw the cards in the 7 vectors
    for (int vec = 0; vec < NUMBER_OF_VECTORS; vec++) {
        int sz = card_vectors_array[vec].size();
        for (int i = 0; i < sz; i++) {
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)){
                if (!last_card_dragged && !multiple_cards_dragged){
                    card_vectors_array[vec][i]->UpdatePosition(vec, i);
                }
            }
            card_vectors_array[vec][i]->set_last_valid_position(vec, i);
            if (card_vectors_array[vec][i] != selected_card){
                card_vectors_array[vec][i]->drawTo(*window);
            }
//            if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
//                card_vectors_array[vec][i]->UpdatePosition(vec, i);
//            }
//            card_vectors_array[vec][i]->set_last_valid_position(vec, i);
//            card_vectors_array[vec][i]->drawTo(*window);
        }
    }
    if (selected_card != nullptr){
        selected_card->drawTo(*window);
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
