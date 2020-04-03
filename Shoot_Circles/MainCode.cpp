#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
using namespace sf;
using namespace std;

//Menu settings
void menu(RenderWindow & window)
{
	bool isMenu = true;
	//Text settings 
	Font font;
	font.loadFromFile("Amble-Bold.ttf");
	Text textPlay, textGame;
	textPlay.setFont(font);
	textPlay.setString("Play");
	textPlay.setCharacterSize(24);
	textPlay.setFillColor(Color::Black);
	textPlay.setPosition(350-25, 300);
	textGame.setFont(font);
	textGame.setString("SHOOT CIRCLE");
	textGame.setCharacterSize(70);
	textGame.setFillColor(Color::Red);
	textGame.setPosition(125.f,100.f);
	//Button settings
	RectangleShape box;
	box.setSize(Vector2f(70,30));
	box.setPosition(350 - 35, 300);
	box.setFillColor(Color::Red);

	while (isMenu)
	{
		Event event;
		while(window.pollEvent(event))
		{
			if (event.type == Event::Closed) 
			{
				window.close();
				isMenu = false;
			}

			//KeyPressed event for ESCAPE
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == 36)
				{
					window.close();
					isMenu = false;
				}
			}

			//Text highlight
			if(event.type == Event::MouseMoved)
			{
				if(event.mouseMove.x>=box.getPosition().x && event.mouseMove.x <= box.getPosition().x+70 && event.mouseMove.y >= box.getPosition().y && event.mouseMove.y <= box.getPosition().y+30)
				{
					box.setOutlineThickness(2.5f);
					box.setOutlineColor(Color::White);
				}
				else 
				{
					box.setOutlineThickness(0);
				}
			}

			//Menu exit
			if(event.type == Event::MouseButtonPressed)
			{
				if (box.getOutlineThickness() == 2.5f && event.mouseButton.button == Mouse::Left)
					isMenu = false;
			}
		}
		window.clear();
		window.draw(box);
		window.draw(textGame);
		window.draw(textPlay);
		window.display();
	}
}

//Game over call
void game_over(RenderWindow & window, int & score) 
{
	bool isOver = true;
	//Text settings
	Font font;
	font.loadFromFile("Amble-Bold.ttf");
	Text textGameOver, textRestart, textScore;
	textGameOver.setFont(font);
	textRestart.setFont(font);
	textScore.setFont(font);
	textGameOver.setString("Game is Over");
	textRestart.setString("Restart");
	textScore.setString("Your score is: " + to_string(score));
	textGameOver.setFillColor(Color::Red);
	textScore.setFillColor(Color::Red);
	textRestart.setFillColor(Color::Black);
	textGameOver.setCharacterSize(70);
	textRestart.setCharacterSize(30);
	textScore.setCharacterSize(45);
	textGameOver.setPosition(150, 100);
	textScore.setPosition(200, 200);
	textRestart.setPosition(300, 300);
	//Button settings
	RectangleShape box;
	box.setSize(Vector2f(125, 40));
	box.setFillColor(Color::Red);
	box.setPosition(289, 300);
	//Sound setup
	SoundBuffer appbuf, sadbuf;
	appbuf.loadFromFile("applause.wav");
	sadbuf.loadFromFile("sad-trombone.wav");
	Sound applause, sad;
	applause.setBuffer(appbuf);
	sad.setBuffer(sadbuf);
	
	if (score < 50)
		sad.play();
	else
		applause.play();

	while (isOver) 
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				isOver = false;
			}

			//KeyPressed event for ESCAPE
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == 36)
				{
					window.close();
					isOver = false;
				}
					
			}
			//Button highlight
			if (event.type == Event::MouseMoved)
			{
				if (event.mouseMove.x >= box.getPosition().x && event.mouseMove.x <= box.getPosition().x+ 125 && event.mouseMove.y >= box.getPosition().y && event.mouseMove.y <= box.getPosition().y +40)
				{
					box.setOutlineThickness(3);
					box.setOutlineColor(Color::White);
				}
				else {
					box.setOutlineThickness(0);
				}	
			}
			//Game_over exit call
			if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left && box.getOutlineThickness() > 0)
					isOver = false;
			}
		}
		window.clear();
		window.draw(box);
		window.draw(textGameOver);
		window.draw(textScore);
		window.draw(textRestart);
		window.display();
		
	}
}

int main()
{
	srand(time(NULL));

	//Window settings
	RenderWindow window(VideoMode(700, 700), "My Game", Style::Close);
	window.setFramerateLimit(60);

	//Menu call
	menu(window);
	
	//Ball settings
	CircleShape shape(5+rand()%45);
	shape.setFillColor(Color::Red);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	shape.setPosition(50+rand()%600,50+rand()%600);
	//Cursor settings
	Cursor cursor;
	cursor.loadFromSystem(cursor.Cross);
	window.setMouseCursor(cursor);
	//Clock setup
	Clock clock;
	//Score and time settings
	int score = 0;
	Font font;
	font.loadFromFile("Amble-Bold.ttf");
	Text textScore, textTime;
	textScore.setFont(font);
	textScore.setCharacterSize(30);
	textScore.setPosition(560.f, 650.f);
	textScore.setFillColor(Color::Red);
	textTime.setFont(font);
	textTime.setCharacterSize(30);
	textTime.setFillColor(Color::Red);
	textTime.setPosition(10.f, 650.f);
	//Sound setup;
	SoundBuffer bufGun,bufMiss;
	bufGun.loadFromFile("GunshotStrike.wav");
	bufMiss.loadFromFile("GunshotMiss.wav");
	Sound gunshot, missedShot;
	gunshot.setBuffer(bufGun);
	missedShot.setBuffer(bufMiss);
	
	while (window.isOpen())
	{
		Event event;
		Time time = clock.getElapsedTime();
		textScore.setString("Score: " + to_string(score));
		textTime.setString("Time: " + to_string(60-(int)time.asSeconds()));
		
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			
			//Ball shotting setup
			if (event.type == Event::MouseButtonPressed) 
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					if (powf(event.mouseButton.x - shape.getPosition().x, 2.f) + powf(event.mouseButton.y - shape.getPosition().y, 2.f) <= powf(shape.getRadius(), 2.f)) 
					{
						score++;
						gunshot.play();
					}
					else 
					{
						score--;
						missedShot.play();
					}
					textScore.setString("Score: " + to_string(score));
					shape.setPosition(rand() % 600 + 50, rand() % 600 + 50);
					shape.setRadius(5 + rand() % 45);
					shape.setOrigin(shape.getRadius(), shape.getRadius());
					shape.setFillColor(Color(5+rand() % 250, rand() % 255, rand() % 255, 255));
				}
			}

			//KeyPressed event for ESCAPE
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == 36) 
					window.close();
			}
			
		}
		//GameOver call
		if (60 - (int)time.asSeconds() == 0)
		{
			game_over(window, score);
			clock.restart();
			score = 0;
		}
		window.clear();
		window.draw(shape);
		window.draw(textScore);
		window.draw(textTime);
		window.display();

	}

	return 0;
}