#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <fstream>
#include <stdio.h>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int Size = 30;
int width = Size * Size, heigth = Size * Size;
int corps = 3;
int dir = 1;
int diff = 1;
int startgame = 1;
int game = 0;
int endgame = 0;
int snum = 0;

struct snake
{
    int x, y;
}s[50];

struct fruit
{
    int x, y;
}f;

void action()
{
    for (int i = corps; i > 0; i--)
    {
        s[i].x = s[i - 1].x;
        s[i].y = s[i - 1].y;
    }

    //Définit les directions 0,1,2 et 3, et ce qu'ils feront, exemple : si une touche est pressé avec pour instruction de prendre la direction 0, la shape va se déplacer de 1 sur l'axe y
    if (dir == 0) s[0].y -= 1;
    if (dir == 1) s[0].x += 1;
    if (dir == 2) s[0].y += 1;
    if (dir == 3) s[0].x -= 1;

    if (s[0].x == f.x && s[0].y == f.y)
    {
        corps++;
        snum++;
        f.x = rand() % 42;
        f.y = rand() % 23;
    }


}

void reset()
{
    dir = 1;
    corps = 3;
    f.x = rand() % 42;
    f.y = rand() % 23;
    s[0].x = 10;
    s[0].y = 10;
}

void endGame()
{
    endgame = 1;
    game = 0;
}

void move()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && dir != 2)
        dir = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && dir != 3)
        dir = 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && dir != 0)
        dir = 2;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && dir != 1)
        dir = 3;
}


int main()
{
    srand(time(NULL));

    sf::Music music;
        music.openFromFile("acceuil.wav");
        music.setVolume(50);

    sf::Music mus;
        mus.openFromFile("ost.wav");
        mus.setVolume(50);

    sf::Music end;
        end.openFromFile("end.wav");
        end.setVolume(50);

    RenderWindow app(VideoMode(1280, 720), "Snake", Style::Titlebar);
        app.setFramerateLimit(120);

    RectangleShape box(Vector2f(Size, Size));
        box.setFillColor(Color::Green);

    RectangleShape apple(Vector2f(Size, Size));
        apple.setFillColor(Color::Red);

    sf::Font Typo;
        Typo.loadFromFile("ARCADE.TTF");

    sf::Text Score;
        Score.setFont(Typo);
        Score.setString("Score :");
        Score.setCharacterSize(30);


    Clock timer;
    f.x = rand() % 42;
    f.y = rand() % 23;


    while (app.isOpen())
    {
        Event event;

        music.play();
        music.setPlayingOffset(sf::seconds(1.f));

        while (startgame == 1)
        {
            sf::Texture ecranDebut;


            if (diff == 1)
            {
                ecranDebut.loadFromFile("menufacile.png");
            }

            if (diff == 2)
            {
                ecranDebut.loadFromFile("menunormal.png");
            }

            if (diff == 3)
            {
                ecranDebut.loadFromFile("menudifficile.png");
            }


            sf::Sprite startscreen;
                startscreen.setTexture(ecranDebut);

            app.clear();
            app.draw(startscreen);
            app.display();


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                diff++;

                if (diff >= 4)
                {
                    diff = 3;
                }

            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                diff--;

                if (diff <= 0)
                {
                    diff = 1;
                }

            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return 0;
            }


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                startgame = 0;
                game = 1;
                music.stop();
                mus.play();
            }


            sf::Event event;
            while (app.pollEvent(event))

            {
                if (event.type == sf::Event::Closed)
                {

                }

            }

        }


        while (app.pollEvent(event))
        {
            if (event.key.code == Keyboard::Escape) return 0;
        }


        while (game == 1)
        {
            sf::Texture background;
                background.loadFromFile("fond.png");

            sf::Sprite bground;
                bground.setTexture(background);

            std::string snum_str = std::to_string(snum);

            sf::Text ScoreNum;

            sf::Font Typoo;
                Typoo.loadFromFile("ARCADE.TTF");
                ScoreNum.setFont(Typoo);
                ScoreNum.setString(snum_str);
                ScoreNum.setCharacterSize(30);
                ScoreNum.setPosition(200, 0);


            move();


            if (diff == 1 && timer.getElapsedTime().asMilliseconds() > 200) //timer d'intervale entre les déplacement de notre shape
            {
                action();


                for (int i = 1; i < corps; i++)

                    if (s[0].x == s[i].x && s[0].y == s[i].y)
                    {
                        mus.stop();
                        end.play();
                        endGame();

                    }

                timer.restart();
            }


            if (diff == 2 && timer.getElapsedTime().asMilliseconds() > 50) //timer d'intervale entre les déplacement de notre shape
            {
                action();


                for (int i = 1; i < corps; i++)

                    if (s[0].x == s[i].x && s[0].y == s[i].y)
                    {
                        endGame();
                        mus.stop();
                        end.play();
                    }

                timer.restart();
            }



            if (diff == 3 && timer.getElapsedTime().asMilliseconds() > 10) //timer d'intervale entre les déplacement de notre shape
            {
                action();


                for (int i = 1; i < corps; i++)

                    if (s[0].x == s[i].x && s[0].y == s[i].y)
                    {
                        endGame();
                        mus.stop();
                        end.play();
                    }

                timer.restart();
            }


            if (s[0].x < 0)
            {
                endGame();
                mus.stop();
                end.play();
            }

            if (s[0].x > 42)
            {
                endGame();
                mus.stop();
                end.play();
            }

            if (s[0].y < 0)
            {
                endGame();
                mus.stop();
                end.play();
            }

            if (s[0].y > 23)
            {
                endGame();
                mus.stop();
                end.play();
            }


            app.clear();

            app.draw(bground);


            for (int i = 0; i < corps; i++)
            {
                box.setPosition(s[i].x * Size, s[i].y * Size);

                app.draw(box);
            }


            apple.setPosition(f.x * Size, f.y * Size);
            app.draw(apple);
            app.draw(Score);
            app.draw(ScoreNum);
            app.display();


            sf::Event event;

            while (app.pollEvent(event))

            {
                if (event.type == sf::Event::Closed)
                {

                }

            }



        }


        while (endgame == 1)
        {
            sf::Texture ecranFin;
                ecranFin.loadFromFile("menu.png");

            sf::Sprite endscreen;
                endscreen.setTexture(ecranFin);

            std::string snum_str = std::to_string(snum);

            sf::Text ScoreNum;

            sf::Font Typoo;
                Typoo.loadFromFile("ARCADE.TTF");
                ScoreNum.setFont(Typoo);
                ScoreNum.setString(snum_str);
                ScoreNum.setCharacterSize(30);
                ScoreNum.setPosition(200, 0);


            app.clear();
            app.draw(endscreen);
            app.draw(Score);
            app.draw(ScoreNum);
            app.display();


            reset();


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            {
                endgame = 0;
                snum = 0;
                startgame = 1;
                end.stop();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                return 0;
            }

            sf::Event event;
            while (app.pollEvent(event))

            {
                if (event.type == sf::Event::Closed)
                {

                }

            }

        }

    }

    return (0);
}
