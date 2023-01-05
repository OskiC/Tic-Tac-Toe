#include <SFML/Graphics.hpp>
#include <iostream>


void InputHan(int x, int y);
void Draw(sf::RenderTarget& target);
int Update();
void PlayAgain(sf::RenderWindow& target);

int Board[3][3] = { 0 };
int PlayerTurn = 1;
int score = 0;
sf::Texture crossTxt;
sf::Texture circleTxt;
sf::Texture Background;
sf::Text Play;
sf::Font font;



int main()
{
    sf::RenderWindow window(sf::VideoMode(750, 750), "kolko-krzyzyk!");
    font.loadFromFile("ARIAL.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(70);
    text.setFillColor(sf::Color::Red);

    
    while (window.isOpen())
    {

        sf::Event event;

        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
                window.close();

            else if (score == 0 && event.type == sf::Event::MouseButtonPressed)
            {
                InputHan(event.mouseButton.x, event.mouseButton.y);
                score = Update();
                std::cout << score << std::endl;

            }

        }
        window.clear();

        Draw(window);
        // Check for winner and draw text
        if (score == 1)
        {
            text.setString("CROSS WIN!");
            text.setPosition(sf::Vector2f(145, 167));
            window.draw(text);
            PlayAgain(window);
        }
        else if (score == 2)
        {
            text.setString("CIRCLE WIN!");
            text.setPosition(sf::Vector2f(145, 167));
            window.draw(text);
            PlayAgain(window);
        }
        else if (score == 3)
        {
            text.setString("DRAW!");
            text.setPosition(sf::Vector2f(250, 167));
            window.draw(text);
            PlayAgain(window);
        }
        window.display();

    }

    return 0;
}



void InputHan(int x, int y)
{

    if (x >= 0 && x <= 750 && y >= 0 && y <= 750)
    {
        float tempI = (float)(y - 250) / 250;
        float tempJ = (float)(x - 250) / 250;
        int i = static_cast<int>(std::ceil(tempI));
        int j = static_cast<int>(std::ceil(tempJ));

        if (Board[i][j] == 0)
        {
            Board[i][j] = PlayerTurn;

            if (PlayerTurn == 1) {
                PlayerTurn = 2;
            }
            else
            {
                PlayerTurn = 1;
            }

        }
    }
}

int Update()
{
    bool isDraw = true;
    //Check for Col and Row win and return winner
    for (int i = 0; i < 3; i++)
    {

        if (Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2] && Board[i][0] != 0)
            return Board[i][0];

        if (Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i] && Board[0][i] != 0)
            return Board[0][i];

    }
    // Check for Diag win
    if (Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2] && Board[0][0] != 0)
        return Board[0][0];

    if (Board[2][0] == Board[1][1] && Board[1][1] == Board[0][2] && Board[2][0] != 0)
        return Board[2][0];

    // Check for Draw
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board[i][j] == 0)
            {
                isDraw = false;
                break;
            }
        }
    }

    if (isDraw)
        return 3;
    else
    {
        return 0;
    }

}

void Draw(sf::RenderTarget& target)
{
    Background.loadFromFile("images/backgrou.png");
    sf::Sprite Back(Background);
    crossTxt.loadFromFile("images/cross.png");
    sf::Sprite Cross(crossTxt);
    circleTxt.loadFromFile("images/kolko.png");
    sf::Sprite Circle(circleTxt);
    target.draw(Back);

    Cross.setScale(0.92, 0.92);
    Circle.setScale(0.92, 0.92);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (Board[i][j] == 1)
            {
                Cross.setPosition(sf::Vector2f(250 * j + 10, 250 * i + 15));
                target.draw(Cross);
            }
            else if (Board[i][j] == 2)
            {
                Circle.setPosition(250 * j + 10, 250 * i + 15);
                target.draw(Circle);
            }
        }
    }
}

void PlayAgain(sf::RenderWindow &target)
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(325,100));
    rect.setFillColor(sf::Color(66, 160, 253));
    rect.setPosition(sf::Vector2f(215, 375));
    target.draw(rect);

    sf::Font font;
    font.loadFromFile("ARIAL.ttf");
    sf::Text ButtonText;
    ButtonText.setFont(font);
    ButtonText.setCharacterSize(50);
    ButtonText.setFillColor(sf::Color::Green);
    ButtonText.setString("Play Again!");
    ButtonText.setPosition(sf::Vector2f(248,395));
    target.draw(ButtonText);

    sf::Event Pause;

    while (target.pollEvent(Pause))
    {
        if (Pause.type == sf::Event::Closed)
            target.close();

        else if (Pause.type == sf::Event::MouseButtonPressed)
        {
            
            int i = Pause.mouseButton.y;
            int j = Pause.mouseButton.x;
            std::cout << i << std::endl;
            std::cout << j << std::endl;

            if ( (j > 215 && j < 539) && (i > 374 && i < 475)) 
            {
                PlayerTurn = 1;
                score = 0;
                for (int i = 0; i < 3; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        Board[i][j] = 0;
                    }
                }
                break;
            }
        }
    }

    
    

}