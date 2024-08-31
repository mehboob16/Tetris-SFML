/*Name: Mehboob Ali
Student-id: 22I-1208
Project*/

/* PROGRAMMING FUNDAMENTAL'S PROJECT FOR FALL 2022 BS(CS)
 * You need to define the required function in the part instructed here below.
 * Avoid making any unnecessary changes, particularly the ones you don't understand.
 * The different pieces should be defined using an array - uncomment the following code once you are done creating the array.
 * TIP: Understand thoroughly before getting started with coding.
 * */

//---Piece Starts to Fall When Game Starts---//

// ...

void fallingPiece(float& timer, float& delay,float& delayo, int& colorNum, int numOfblocks, int uninteraciveRows){
    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];
            point_1[i][1]+=1;                   //How much units downward
		}
        if (!anamoly(uninteraciveRows)){
            for(int i=0 ; i<4 ; i++){
				gameGrid[point_2[i][1]][point_2[i][0]] = colorNum;
			}
            colorNum = 1+rand()%7;
            int n=rand()%numOfblocks;
            //--- Un-Comment this Part When You Make BLOCKS array---//	
           
           	for (int i=0;i<4;i++){
            	point_1[i][0] = BLOCKS[n][i] % 2;
                point_1[i][1] = BLOCKS[n][i] / 2;
            }
            
        }

        timer=0;
    }
    
}
//list of all function made
bool rowFilled(int row);
void removeBlock(int y, int x);
void removeRow(int rowCompleted) ;
void calculatePoints(int& points, int level, int rowsRemoved,bool levelAdvance);
void removeCalcPoints(int& points, int level,bool levelAdvance);
void boundX(int& delta_x);
void xmovement(float& timer, float& delay, int& colorNum, int& delta_x);
void movement(float& timer, float& delay,float& delayo, int& colorNum, int& delta_x, int numOfblocks, int uninteractiveRows);
void rotateBound(int center_x, int center_y);
void rotation(bool& rotate);
void shadows(int shadow[4][2]);
void dropping(bool& drop, int shadow[4][2]);
bool isGameOver();
void bombing(int& bomb, int& bombColor, int& x_position, int& y_position);
void changingLevel(int& level, float& playTime, float& delayo, int& uninteractiveRows);
void readFile(std::string fileName);
void writeFile(std::string fileName, const int SIZE=10);
void updateHighScore(std::string name1, int points);


/////////////////////////////////////////////
///*** START CODING YOUR FUNTIONS HERE ***///
bool rowFilled(int row)   // checks row is filled
{
	for(int i=0 ; i<N ; i++)							
	{
		if(gameGrid[row][i] == 0)
			return false;		
	}
	return true;
}

void removeBlock(int y, int x)
{
	for(int i=y ; i>0  ; i--)  //shifting block one down until there is no block
	{
		gameGrid[i][x] = gameGrid[i-1][x];
	}
}

void removeRow(int rowCompleted)  //transfers the row one below the current position (does this for completed row and above the completed row)
{
	for(int i=0; i<N ; i++)
	{
		removeBlock(rowCompleted, i);
	}
}
void calculatePoints(int& points, int level, int rowsRemoved,bool levelAdvance)
{
	if(levelAdvance)				//double points will be offer on every row distruction if advance level is being played
		level*=2;

	switch(rowsRemoved)
	{
		case 1: 
			points = points + (level*10); 	
			break;
		case 2: 
			points = points + (level*30); 	
			break;
		case 3: 
			points = points + (level*60); 		
			break;
		case 4: 
			points = points + (level*100); 	
			break;
	}
}
void removeCalcPoints(int& points, int level,bool levelAdvance)  
{
	int counter = 0;
	for(int i=0 ; i<M ; i++)
	{
		if(rowFilled(i))
		{
			removeRow(i);
			counter++;
		}
	}
	calculatePoints(points, level, counter,levelAdvance);
}

void boundX(int& delta_x) //bounds the block inside the side boundries
{						
	for(int i=0; i<4 ; i++)        //if any part of piece has other piece of borders on left and left arrow is pressed no movement will happen as we making delta_x =0 and viseversa for right
	{
		if((point_1[i][0] <=0 || gameGrid[point_1[i][1]][point_1[i][0]-1]) &&  delta_x ==-1)
		{
			delta_x=0;
		}
		else if((point_1[i][0] >= N-1 || gameGrid[point_1[i][1]][point_1[i][0]+1]) && delta_x ==1)
		{
			delta_x=0;
		}
	}


}
void xmovement(float& timer, float& delay, int& colorNum, int& delta_x)
{
	    if (timer>delay){
        for (int i=0;i<4;i++){
            point_2[i][0]=point_1[i][0];
            point_2[i][1]=point_1[i][1];                  
            point_1[i][0]+=delta_x;             //right and left movement      
        }
        delta_x = 0;							//reseting delta_x for next frame
        timer=0;
    }
}

void movement(float& timer, float& delay,float& delayo, int& colorNum, int& delta_x, int numOfblocks, int uninteractiveRows)
{
	if(delta_x)      // if x!=0
	{
		xmovement(timer, delay, colorNum, delta_x);
	}
	else
	{
		fallingPiece(timer, delay, delayo, colorNum, numOfblocks, uninteractiveRows);
	}
	delay = delayo;     	//reseting delay for the next frame
}
void rotateBound(int center_x, int center_y)
{
	//preservers original position of the block in the frame
	while(point_1[1][0] > center_x)
	{
		for(int i=0 ; i<4 ; i++)
			point_1[i][0]--;
	}	
	while(point_1[1][0] < center_x)
	{
		for(int i=0 ; i<4 ; i++)
			point_1[i][0]++;
	}
	while (point_1[1][1] > center_y)
	{
		for(int i=0 ; i<4 ; i++)
			point_1[i][1]--;
	}
	while(point_1[1][1] < center_y)
	{
		for(int i=0 ; i<4 ; i++)
			point_1[i][1]++;
	}

	// after the above step, block could be outside the frame so checking it
	bool right = false, left = false; 		// outside from right or left

	for(int i=0 ; i<4 ; i++)
	{
		if(point_1[i][0]>=N)
			right = true;
	
		if(point_1[i][0]<0)
			left = true;
	}
	//while the block is out from the grid from left adding one to it
	while(left)
	{
		left = false;
		for(int i=0 ; i<4 ; i++)
		{
			point_1[i][0]++;
			if(point_1[i][0] < 0)
				left = true;
		}
	}
	while(right)
	{
		right = false;
		for(int i=0 ; i<4 ; i++)
		{
			point_1[i][0]--;
			if(point_1[i][0] >= N)
				right = true;
		}
	}
}


void rotation(bool& rotate)
{
	
	if(!rotate)
		return;
	
	int center_x = point_1[1][0];
	int center_y = point_1[1][1];
	static bool clockwise = false;
	//transposes the 2d array
	//first time clockwise is false so it it will simply transpose
	//second time it will transpose and flip the matrix
	if(clockwise){
		for(int i=0 ; i<4 ; i++)
		{
			int temp = -point_1[i][0];
			point_1[i][0] = -point_1[i][1];
			point_1[i][1] = temp;
			
		}
		clockwise = false;
	}		
	else{
		for(int i=0 ; i<4 ; i++){
			int temp = point_1[i][0];
			point_1[i][0] = point_1[i][1];
			point_1[i][1] = temp;
		}
		clockwise = true;
		
	}
	rotate = false;
	rotateBound(center_x, center_y);
}
void shadows(int shadow[4][2], int uninteractiveRows)
{
	int shadow2[4][2];
	bool check = false;
	
	for(int i=0 ; i<4 ; i++)
	{
		for(int j=0 ; j<2 ; j++)
		{
			shadow[i][j] = point_1[i][j];
		}
	}
	
	
	//adds 1 to shadow_arr until it is touching any piece or ground(lower boundry)
	while(!check)
	{
		
		for(int i=0 ; i<4 ; i++)
		{
			shadow2[i][0] = shadow[i][0];
			shadow2[i][1] = shadow[i][1]+1;
		}
		
		for(int i=0 ; i<4 ; i++)
		{
			check = gameGrid[shadow2[i][1]][shadow2[i][0]] || shadow2[i][1] >= M-uninteractiveRows;		
			if(check)
				break;
		}
		
		if(!check)
		{
			for(int i=0 ;i<4 ; i++)
				shadow[i][1] = shadow2[i][1];
		}
	}
}

void dropping(bool& drop, int shadow[4][2]) //drops piece if space is pressed
{											//shadow_arr has coordinated to where piece is supposed to be droped	
	if(!drop)								//just copying shadow array to point_1 array
		return;
		
	for(int i=0 ; i<4 ; i++)
	{
		for(int j=0 ; j<4; j++)
			point_1[i][j] = shadow[i][j];
	}
	drop = false;
}

bool isGameOver()
{
	for(int i=0 ; i<M ; i++)		//checking top row of the grid and if there is any block game is over
	{
		if(gameGrid[0][i])
			return true;
	}
	return false;
}

void bombing(int& bomb, int& bombColor, int& x_position, int& y_position)
{
	if(!bomb)
		return;
	
	else if(bomb == 1)
	{
		bomb=2 ;
		x_position = rand()%N;			//total column in grid
		y_position = rand()%M;			//total rows in grid	
		bombColor =  1+rand()%7; 
		return;
	}


		
	if(gameGrid[y_position][x_position])    //if there is a block are x,y
	{
		if(gameGrid[y_position][x_position] == bombColor)  //if color of bomb and block color are same removing all block of the color
		{
		//iterating through all the gameGrid elements and if the element is equal to bombColor it is removed
			for(int i=0 ; i<M ; i++)
			{
				for(int j=0 ; j<N ; j++)	
					removeBlock(i,j);
						
			}
		}
		else
		{
			for(int i=y_position-1 ; i<=y_position+1 ; i++)         //removing the block and the surrounding blocks total 9 blocks distroyed
			{
				if( i<0 || i>=M)										//if i is outside side boundries
					continue; 
					
				for(int j=x_position-1 ; j<=x_position+1  ; j++)
				{
					if(j<0 || j>=N) continue;
					
					removeBlock(i,j);
				}
			}
		}
	}
	bomb = 0;	
}

void changingLevel(int& level, float& playTime, float& delayo, int& uninteractiveRows)
{
	if(playTime < 60)
		return;
	
	level++;
	uninteractiveRows = level/5;     //makes last row uninteractive every 5 min
	playTime -= 60;
	delayo -= 0.01;				//decreasing delay to increase difficulty
}
#include <fstream>  
void readFile(std::string fileName){			               
 
	std::ifstream infile(fileName);
	int index=0;

 	while(infile>>name[index]>>highScore[index]){
 		//infile>>str>>score;
		index++;
	}
    infile.close();                   

}
void writeFile(std::string fileName, const int SIZE){

	std::ofstream file(fileName);
	int index=0;

	while(index<SIZE){
		file << name[index] <<" " << highScore[index]<<std::endl;
		index++;
	}

	file.close();
}

void updateHighScore(std::string name1, int points){
	int index = 9;  //index at which we have to put new high score
	for(int i=9 ; i>=0 ; i--){
		if(points > highScore[i])
			index = i;
	}

	for(int i=9 ; i>index ; i--){   //transfer points to one lower till index on which we have to put new highScore and putting new highScore on index
		highScore[i] = highScore[i-1];
		name[i] = name[i-1];
	}
	highScore[index] = points;
	name[index]= name1;
}

#include <sstream>
using namespace sf;

//list of all functions made
void resetGlobalVar();
void manage(RenderWindow& window, Sprite& background, Sprite& button, bool& levelAdvance);
void levelUi(RenderWindow& window, Sprite& button, Sprite& background,bool& levelAdvance);
void mainMenu();
int gameOver(RenderWindow& window, Sprite& background, int points);
int gameMenu(RenderWindow& window, Sprite& background,Sprite& button, int points, Sound& sound, bool& musicPlay);    //menu shown when game is paused
void showPoints(RenderWindow& window,int points, int level, int numOfBombs);
void resizeGrid(RenderWindow& window, int uninteractiveRows);
void playSound(Sound& sound, bool play);
void highScoreUi(RenderWindow& window,Sprite& background);

/*********************************************  Game Function  ****************************************/

int game(RenderWindow& window, Sprite& background, Sprite& button, bool &levelAdvance,Sound& sound, bool& musicPlay)
{
	Texture obj1, obj2, obj3, obj4;
	obj1.loadFromFile("img/tiles.png");
	obj2.loadFromFile("img/frame.png");
    obj3.loadFromFile("img/shadow.png");
    obj4.loadFromFile("img/bombs.png");
	
	Sprite sprite(obj1), frame(obj2), shadow(obj3), bombs(obj4);
	
    int delta_x=0, colorNum=1, points = 0, bomb = 0,level = 1, bombColorNum = 0, bomb_x =0 , bomb_y = 0, numOfblocks = 4, numOfBombs = 3, uninteractiveRows = 0;
    float timer=0, delayo = 0, delay = 0, playTime = 0;
    bool rotate=0, drop = false ;
    int shadow_arr[4][2];
    
    if(levelAdvance){
    	delayo = 0.1;
    	numOfblocks = 7;
    }	
    else
    	delayo = 0.3;
    
    delay = delayo;
    Clock clock;

    while (window.isOpen()){
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
		playTime += time;         //playTime stores how much time user has played one round in seconds
	
        //---Event Listening Part---//
        Event e;
        while (window.pollEvent(e)){                    //Event is occurring - until the game is in running state
            if (e.type == Event::Closed)                   //If cross/close is clicked/pressed
                window.close();                            //Opened window disposes
            if (e.type == Event::KeyPressed) {             //If any other key (not cross) is pressed
                if (e.key.code == Keyboard::Up)            //Check if the other key pressed is UP key
                    rotate = true;                         //Rotation gets on
                else if (e.key.code == Keyboard::Left)     //Check if the other key pressed is LEFT key
                    delta_x = -1;                          //Change in X-Axis - Negative
                else if (e.key.code == Keyboard::Right)    //Check if the other key pressed is RIGHT key
                    delta_x = 1;                               //Change in X-Axis - Positive
            	else if(e.key.code == Keyboard::Space)
            		drop = true;
            	else if(e.key.code == Keyboard::P){
            		int n = gameMenu(window, background,button, points,sound,musicPlay);
            		if(n)  //n is not equal to zero
            			return n;
            	}		
            								//if paused then it will make paused false
            	
            	if(bomb==2)				//2 is assigned by bombing function so it can draw bomb first and then remove block in the next frame 
            		continue;
            	else if(e.key.code == Keyboard::B && numOfBombs)
            	{	bomb = 1;
					numOfBombs--;
				}
			}
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))   //Just another way to detect key presses without event listener
            delay=0.05;                                    //If DOWN key is pressed, delay in falling piece decreases from 0 to 0.05

        ///////////////////////////////////////////////
        ///*** START CALLING YOUR FUNCTIONS HERE ***///

        boundX(delta_x);									//avoids collision of block with other and boundry horizontaly
        rotation(rotate);
        shadows(shadow_arr,uninteractiveRows);        									//assigns shadow_arr corrdinates of shadow		
        dropping(drop, shadow_arr);
        movement(timer, delay, delayo, colorNum, delta_x, numOfblocks, uninteractiveRows);				                 //controls both x and y movement
        //fallingPiece(timer, delay, colorNum);          //Example: fallingPiece() function is called here
        removeCalcPoints(points, level,levelAdvance);						// removes row if completed and calculates points
		bombing(bomb, bombColorNum, bomb_x, bomb_y);
		changingLevel(level, playTime, delayo, uninteractiveRows);				//changes level every minute and makes last row uninteractive every 5 min
        if(isGameOver())
        	return gameOver(window , background, points);		//made in graphics.h
		
		//this function is called after the backgroung has been drawn
		//resizeGrid(window,uninteractiveRows);							//will draw gray blocks in uninteractive rows
        
		///*** YOUR CALLING STATEMENTS END HERE ***///
        //////////////////////////////////////////////

        window.clear(Color::Black);
        window.draw(background);
        
		resizeGrid(window,uninteractiveRows);							//will draw gray blocks in uninteractive rows

		showPoints(window, points,level, numOfBombs);							//shows point and current level
        for (int i=0; i<(M-uninteractiveRows); i++){
            for (int j=0; j<N; j++){
                if (gameGrid[i][j]==0)
                    continue;
                sprite.setTextureRect(IntRect(gameGrid[i][j]*18,0,18,18));
                sprite.setPosition(j*18,i*18);
                sprite.move(28,31); //offset
                window.draw(sprite);
              
            }
        }
        //drawing bomb
        if(bomb == 2)
        {
        	bombs.setTextureRect(IntRect(bombColorNum*19,0,19,21));    //each bomb is of size 19,21
        	bombs.setPosition(bomb_x*18, bomb_y*18);
        	bombs.move(28,31);
        	window.draw(bombs);
        }
        for (int i=0; i<4; i++){
            sprite.setTextureRect(IntRect(colorNum*18,0,18,18));
            sprite.setPosition(point_1[i][0]*18,point_1[i][1]*18);
            sprite.move(28,31);
            window.draw(sprite);
         
         	//drawing shadow	
         	shadow.setTextureRect(IntRect(0,0,18,18));
         	shadow.setPosition(shadow_arr[i][0]*18, shadow_arr[i][1]*18);
         	shadow.move(28,31);
         	window.draw(shadow);
         	
          }
        //---The Final on Which Everything is Drawn Over is Loaded---//
        window.draw(frame);
        //---The Window that now Contains the Frame is Displayed---//
        window.display();
        
		if(bomb == 2)				//the instance bomb is dropped the screen will pause for 1.5 sec
        {
        	sleep(milliseconds(1500));
        }
        
    }
    return 0;
}

void resetGlobalVar()
{
	for(int i=0 ; i<4 ; i++)
	{
		for(int j=0 ; j<2 ; j++)
		{
			point_1[i][j] = 0;
			point_2[i][j] = 0;
		}
	}
	for(int i=0 ; i<M; i++)
	{
		for(int j=0 ; j<N ; j++)
			gameGrid[i][j] = 0;
	}
}

void manage(RenderWindow& window, Sprite& background, Sprite& button, bool& levelAdvance,Sound& sound, bool& musicPlay)
{
	
	int n = game(window, background, button, levelAdvance,sound, musicPlay);
	while(n== 1){
		resetGlobalVar();
		n = game(window, background, button, levelAdvance,sound, musicPlay);
	}
	resetGlobalVar();
	return;            //returns to main menu if game returns 2;
}

void levelUi(RenderWindow& window, Sprite& button, Sprite& background,bool& levelAdvance)
{
	while(window.isOpen())
	{
		Event e;
		while(window.pollEvent(e))
		{
			if(e.type == Event::Closed)  	window.close();
			
			else if(e.type == Event::MouseButtonPressed)
			{
				if(e.mouseButton.button == Mouse::Left)
				{
					int x_pos = Mouse::getPosition(window).x;	//getting coordinates of mouse if left key pressed with respect to windows
					int y_pos = Mouse::getPosition(window).y;	
					
					if(x_pos>30 && x_pos <230)
					{
						if(y_pos>125 && y_pos< (125+43))					//beginner
							levelAdvance = false;
							
						else if(y_pos>180 && y_pos<(180+43))				//advanced
							levelAdvance = true;
						
						else if(y_pos >275 && y_pos<(275+43))				//to main menu
							return;
					}	
					
   				} 				
			}
		}
		window.draw(background);
		
		//drawing while rect behind advance or beginner button(on what button is selected)
		RectangleShape rect;
		rect.setSize(Vector2f(210,53));     // just bigger than the button
		if(levelAdvance)
		{
			rect.setPosition(25,175);
		}
		else
		{
			rect.setPosition(25,120);
		}
		window.draw(rect);
		
		button.setPosition(30,125);
		window.draw(button);
		button.setPosition(30,180);
		window.draw(button);
		button.setPosition(30,275);
		window.draw(button);
		
		Font font;
		font.loadFromFile("font/Pacifico.ttf");
		
		Text text;
		text.setCharacterSize(25);
		text.setFont(font);
		text.setStyle(Text::Bold);
		text.setFillColor(Color::White);
		text.setString("Beginner");	
		text.setPosition(80,130);
		// Draw it
		window.draw(text);		
		
		text.setString("Advance");
		text.setPosition(80,185);
		window.draw(text);
		
		text.setString("Main Menu");
		text.setPosition(65,280);
		window.draw(text);
		
		window.display();
		
	}
	
	
}
void mainMenu()
{
	readFile("highScore.txt");			//reads score and name from the file and updates name and highScore array

	RenderWindow window(VideoMode(320, 480), title, (Style::Titlebar | Style::Close));
    Texture obj1, obj2;
    SoundBuffer buffer;
	/*
        Load "frames.png","tiles.png" and "background.png" for Texture objects
    */
    obj1.loadFromFile("img/background.png");
    obj2.loadFromFile("img/button.png");
    buffer.loadFromFile("sound/music.wav");
    
	Sound sound;
    sound.setBuffer(buffer);
    sound.setVolume(20.f);
	Sprite background(obj1), button(obj2);
	
	bool levelAdvance = false;
	bool musicPlay = false;
	while(window.isOpen())
	{
		Event e;
		while(window.pollEvent(e))
		{
			if(e.type == Event::Closed) window.close();
			
			else if (e.type == Event::MouseButtonPressed)
			{

   				 if (e.mouseButton.button == Mouse::Left)
   				 {
       				
					int x_pos = Mouse::getPosition(window).x;	//getting coordinates of mouse if left key pressed
					int y_pos = Mouse::getPosition(window).y;	
					
					if(x_pos>30 && x_pos<230)					//if mouse above start button 
					{
						if(y_pos>100 && y_pos<143){
							window.clear(Color::Black);
							manage(window, background, button, levelAdvance, sound,musicPlay);
						}
						else if(y_pos>150 && y_pos<(150+43))
							highScoreUi(window,background);
							
						else if(y_pos>200 && y_pos<243){
							musicPlay = !musicPlay;
							playSound(sound,musicPlay);			 //parameters are sound and issoundButton pressed
						}
						else if(y_pos>250 && y_pos<293)							//level button pressed
							levelUi(window, button, background,levelAdvance);
						
					}
   				 }
			}
	
		}
		
		window.clear(Color::Black);
		window.draw(background);
		button.setPosition(30,100);
		window.draw(button);
		button.setPosition(30,150);
		window.draw(button);
		button.setPosition(30,200);
		window.draw(button);	
		button.setPosition(30,250);
		window.draw(button);
		
		Font font;
		font.loadFromFile("font/Pacifico.ttf");
		
		Text text;
		text.setCharacterSize(25);
		text.setFont(font);
		text.setStyle(Text::Bold);
		text.setFillColor(Color::White);
		text.setString("New Game");	
		text.setPosition(65,105);
		// Draw it
		window.draw(text);
		
		text.setString("High Scores");
		text.setPosition(55,155);
		window.draw(text);
		
		text.setString("Sound");
		text.setPosition(90,205);
		window.draw(text);
		
		text.setString("Level");
		text.setPosition(95,255);
		window.draw(text);
		window.display();
	}
} 
#include <iostream>
int gameOver(RenderWindow& window, Sprite& background, int points)
{
	
	if(points > highScore[9])
	{
		char str[8];	
		std::cout << "Enter your name(max 8 characters): ";
		std::cin.get(str, 8);
		updateHighScore(str,points);
		writeFile("highScore.txt");
	}
	while(window.isOpen())
	{
		Event e;
		while(window.pollEvent(e))
		{
			if(e.type == Event::Closed)   window.close();		
			
			if (e.type == Event::KeyPressed) 
			{
				return 2;
			} 
		}
		
		window.draw(background);
		Font font;
		font.loadFromFile("font/Pacifico.ttf");
		
		Text text;
		text.setCharacterSize(50);
		text.setFont(font);
		text.setStyle(Text::Bold);
		text.setFillColor(Color::White);
		text.setString("Game Over");	
		text.setPosition(35,105);
		window.draw(text);
		
		text.setString("your points");
		text.setPosition(35,205);
		window.draw(text);
		
		std::stringstream ss;
		ss << points;
		
		text.setString(ss.str());
		text.setPosition(35,305);
		window.draw(text);
		
		window.display();
	}
	return 0;
}

int gameMenu(RenderWindow& window, Sprite& background,Sprite& button, int points,Sound& sound, bool& musicPlay)    //menu shown when game is paused
{
	while(window.isOpen())
	{
		Event e;
		while(window.pollEvent(e))
		{
			if(e.type == Event::Closed) window.close();
			
			else if (e.type == Event::MouseButtonPressed)
			{

   				 if (e.mouseButton.button == Mouse::Left)
   				 {
       				
					int x_pos = Mouse::getPosition(window).x;	//getting coordinates of mouse if left key pressed
					int y_pos = Mouse::getPosition(window).y;	
					
					if(x_pos>30 && x_pos<230)					 
					{
						if(y_pos>100 && y_pos<143)				//if mouse above continue button	
							return 0;
					
						else if(y_pos>150 && y_pos<193)							//start button pressed
							return 1;
						
						else if(y_pos>200 && y_pos<243)							//high score button
							highScoreUi(window,background);
						
						else if(y_pos>250 && y_pos<293){ 				//sound button
							musicPlay = !musicPlay;
							playSound(sound,musicPlay);
						}							

						
						else if(y_pos>300 && y_pos<343)							//main menu button
   				 			return 2;
   				 	}
				}
	
			}
		}
		
		window.draw(background);
		button.setPosition(30,100);
		window.draw(button);
		button.setPosition(30,150);
		window.draw(button);
		button.setPosition(30,200);
		window.draw(button);	
		button.setPosition(30,250);
		window.draw(button);
		button.setPosition(30,300);
		window.draw(button);
		
		Font font;
		font.loadFromFile("font/Pacifico.ttf");
		
		Text text;
		text.setCharacterSize(25);
		text.setFont(font);
		text.setStyle(Text::Bold);
		text.setFillColor(Color::White);
		text.setString("Continue");	
		text.setPosition(65,105);
		
		window.draw(text);
		
		text.setString("New Game");
		text.setPosition(65,155);
		window.draw(text);
		
		text.setString("High Score");
		text.setPosition(55,205);
		window.draw(text);
		
		text.setString("Sound");
		text.setPosition(90,255);
		window.draw(text);
		
		text.setString("Main Menu");
		text.setPosition(55,305);
		window.draw(text);
		
		window.display();
	}	
	return 0;
}

void showPoints(RenderWindow& window,int points, int level, int numOfBombs)
{
		Font font;
		font.loadFromFile("font/Pacifico.ttf");
		
		Text text;
		text.setCharacterSize(25);
		text.setFont(font);
		text.setStyle(Text::Bold);
		text.setFillColor(Color::White);
		
		std::stringstream ss;
		ss << "Points\n" << points<< "\nlevel\n"<< level<< "\nBombs\n"<<numOfBombs;
		
		text.setString(ss.str());	
		text.setPosition(235,115);
		window.draw(text);
}

void resizeGrid(RenderWindow& window, int uninteractiveRows)
{
	Texture obj;
	obj.loadFromFile("img/greyBlock.png");
	Sprite grayBlock(obj);

	for(int i= M-uninteractiveRows ; i<M ; i++)
	{
		for(int j=0 ; j<N ; j++){
			grayBlock.setTextureRect(IntRect(0,0,18,18));
			grayBlock.setPosition(j*18,i*18);
			grayBlock.move(28,31);
			window.draw(grayBlock);
		}
	}
}

#include <iomanip>
void playSound(Sound& sound, bool play){
	if(play){
		sound.play();
		sound.setLoop(true);
	}
	else
		sound.pause();
}
void highScoreUi(RenderWindow& window,Sprite& background)
{	
	window.clear(Color::Black);
	readFile("highScore.txt");
	window.draw(background);

	while(window.isOpen()){
		
		Event e;
		while(window.pollEvent(e))
		{
			if(e.type == Event::Closed) window.close();
			
			else if (e.type == Event::MouseButtonPressed)
			{

   				if (e.mouseButton.button == Mouse::Left)
   				{
					int x_pos = Mouse::getPosition(window).x;	//getting coordinates of mouse if left key pressed
					int y_pos = Mouse::getPosition(window).y;	
				

					if((x_pos>230 && x_pos<(230+80))&& (y_pos>20 && y_pos<(80+20)))		//if fast logo is pressed
						return;
				}
			}
		}
		std::stringstream ss;
		ss << "No.     Name     Score\n";

		for(int i=0 ; i<10 ; i++){
			ss <<(i+1) << ". "<< std::setw(10)<< name[i] << std::setw(10)<<highScore[i]<<std::endl;
		}
	

		Font font;
		font.loadFromFile("font/Carpet.ttf");

		Text text;
		text.setFont(font);
		text.setCharacterSize(30);
		text.setStyle(Text::Bold);
		text.setFillColor(Color::White);
		
		text.setString(ss.str());
		text.setPosition(10,10);
		window.draw(text);
		window.display();
	}	
}
///*** YOUR FUNCTIONS END HERE ***///
/////////////////////////////////////
