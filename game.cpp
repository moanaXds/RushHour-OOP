//============================================================================
// Name        : .cpp
// Author      : Muanna Hamid
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game...
//============================================================================


#ifndef RushHour_CPP_
#define RushHour_CPP_


#include <SFML/Audio.hpp> 
#include "util.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>


using namespace std;

class Taxi {
	private:
	    int xI, yI; // initially
	    string *color;
	
	public:
	    Taxi(int x, int y, string *c) : xI(x), yI(y), color(c) {}
	
	    void draw() 
        {
            DrawSquare(xI,  yI,  50,  colors[BLUE]);
            DrawCircle(xI+10,  yI+5,  5,  colors[BLACK]); // Left tire
            DrawCircle(xI+40,  yI+5,  5,  colors[BLACK]); // Right tire
            DrawRectangle(xI+10,  yI+40,  30,  10,  colors[CYAN]);
        }
	
	    // Getters and setters for player-controlled movement
	    int getX() const { return xI; }
	    int getY() const { return yI; }
	    void setX(int x) { xI = x; }
	    void setY(int y) { yI = y; }
};

Taxi *taxi;	


template<typename T>

class FixedXTaxi {
private:
    T x, y; // Position
    T fixedX; // Constant x
    T yMin, yMax; // Random y range
    bool isReDisplay; // Call glutPostRedisplay
    T color; // Color index

public:
    FixedXTaxi(T fx, T ylow, T ymx, T carColor , bool redisp = false)
        : fixedX(fx), yMin(ylow), yMax(ymx), isReDisplay(redisp), color(carColor) 
    {
        x = fixedX;
        y = GetRandInRange(yMin, yMax);
    }

    void draw() 
    {
        x=fixedX;
        y=y+2; // 2 pixels per frame
        if(y>yMax)
        {
            y=yMin; // Wrap aroud
        }  
        DrawSquare(x,y,50,colors[RED]);
        DrawCircle(x+10,y+5,5,colors[color]);
        DrawCircle(x+40,y+5,5,colors[color]);
        DrawRectangle(x+10,y+40,30,10,colors[color]);
        if (isReDisplay) glutPostRedisplay();
    }

    T get1X() const { return x; }
	T get1Y() const { return y; }
};


template<typename T>

class FixedYTaxi {
private:
    T x, y; // Positions
    T xMin, xMax; 
    T fixedY; 
    bool isReDisplay; // Call glutPostRedisplay
    bool initRandomizer; // Call InitRandomizer
    T color; 

public:
    FixedYTaxi(T x1, T x2, T fy, T carColor, bool redisp = false, bool initRand = true)
        : xMin(x1), xMax(x2), fixedY(fy), isReDisplay(redisp), initRandomizer(initRand), color(carColor) 
    {
        x = GetRandInRange(xMin, xMax);
        y = fixedY;
        if (initRandomizer) InitRandomizer();
    }

    void draw() 
    {
        y=fixedY; 
        x=x+2; 
        if(x>xMax)
        {
            x=xMin;
        }   
        else if(x<xMin)  x=xMax; 
    
        DrawSquare(x,y,50,colors[RED]);
        DrawCircle(x+10,y+5,5,colors[color]); 
        DrawCircle(x+40,y+5,5,colors[color]); 
        DrawRectangle(x+10,y+40,30,10,colors[color]); 
        if (isReDisplay) glutPostRedisplay();
    }

    T get2X() const { return x; }
	T get2Y() const { return y; }
};

FixedXTaxi<int> c1(300, 10, 300, BLUE, true);

FixedXTaxi<int> c2(250, 400, 600, PINK, true);

FixedYTaxi<int> c3(550, 800, 100, YELLOW, false);

FixedYTaxi<int> c4(500, 880, 400, ORANGE, true);

FixedYTaxi<int> c5(550, 800, 750, VIOLET, true);


//---------------------------     helper variables ------------------------------
bool isMenu=true;
bool isdelivery=false;
bool ispassenger=false;
int score =0;
int TotalTime=180; 
int timelap=0; 
bool isbuilding=false;
bool ismove=true;
int wallet=0;
int fuel=100;
bool overGame=false;
bool showLeaderboard = true;


//  ------------------------------    helper function -----------------------------

bool checkCollision(int xi,int yi,int wi,int hi,int xf,int yf,int wf,int hf)
{
    if((xi+wi<=xf)|| (yi+hi<=yf ) || (xf+wf<=xi) || (yf+hf<=yi))
    {
        return false;
    }
    return true;
}




struct Block{

    int x, y, l, w;
};

Block b[]={
    {400,100,50,50},{400,150,50,50},{400,200,50,50},{400,250,50,50},{330,350,50,50},{380,350,50,50},
    {430,350,50,50},{480,350,50,50},{530,350,50,50},{580,350,50,50},{630,350,50,50},{600,500,50,50},{650,500,50,50},
    {700,500,50,50},{750,500,50,50},{800,500,50,50},{850,500,50,50},{400,400,50,50},{200,500,50,50},{200,550,50,50},
    {200,600,50,50},{200,650,50,50},{200,700,50,50},{200,750,50,50},{0,0,50,50},{0,50,50,50},{0,100,50,50},{0,150,50,50},
    {0,200,50,50},{0,250,50,50},{0,300,50,50},{0,350,50, 50},{50,0,50,50},{50,50,50,50},{50,100,50,50},{50,150,50,50},
    {50,200,50,50},{50,250,50,50},{150,0,50,50}, {200,0,50,50},{400,550,50,50},{400,600,50,50},{400,650,50,50},
    {400,700,50,50},{400,750,50,50},{550,50,50,50},{600,50,50,50},{650,50,50,50},{700,450,50,50},{700,500,50,50},
    {700,550,50,50},{700,600,50,50},{700,650,50,50},{200,450,50,50},{200,500,50,50},{200,550,50,50},{200,600,50,50},
    {200,650,50,50},{550,250,50,50},{600,250,50,50},{650,250,50,50},{970,50,50,50},{970,100,50,50},{970,150,50,50}
};
int len=sizeof(b)/sizeof(b[0]);


class FuelStation{

    private:
        int x,y;
    
    public:
        FuelStation()
        {
            do
            {
                isbuilding=false;
                x=(rand()%19 +1)*50;
                y=(rand()%15 +1)*50;

                for(int i=0;i<len;i++)
                {
                    if(x==b[i].x && y==b[i].y )
                    {
                        isbuilding=true;
                        break;
                    }
                }
            }
            while(isbuilding);

                         
            for(int i=0;i<2;i++)
            {
                int dx=x-b[i].x;
                int dy=y-b[i].y;
                int dis=dx*dx + dy*dy;

                if(dis< 10000) // 2 50X50  // (distance²<10000)
                {
                    isbuilding = true;
                    break;
                }
            }
        }

        void draw()
        {
            DrawRectangle(x, y, 25, 50, colors[BROWN]);
        }

        int get4X() { return x; }
        int get4Y() { return y; }

};

FuelStation * fuelstation;


class Tree {


    private:
        int x, y; 
    
    public:
        Tree(int X, int Y) : x(X), y(Y) {}
    
        void draw() 
        {
            DrawRectangle(x - 5, y - 20, 10, 20, colors[BROWN]);
            
            DrawTriangle(x - 20, y - 10, x + 20, y - 10, x, y + 20, colors[GREEN]); 
            DrawTriangle(x - 12, y, x + 12, y, x, y + 15, colors[GREEN]);
        }
    
        int get6X() const { return x; }
        int get6Y() const { return y; }
    };



    Tree t1(30, 520);
    Tree t2(100, 520);


class RoleStation{

    private:
    int x,y;

    public:
        RoleStation()
        {
            do
            {
                isbuilding=false;

                x=(rand()%19 +1)*50;  // rand()%19 = 0 TO 18  X  50
                y=250+(rand()%11)*50;

                for(int i=0;i<len;i++)
                {
                    if((x==b[i].x && y==b[i].y))
                    {
                        isbuilding=true;
                        break;
                    }
                }
            }
            while(isbuilding);

                        
            for(int i=0;i<2;i++)
            {
                int dx=x-b[i].x;
                int dy=y-b[i].y;
                int dis=dx*dx + dy*dy;

                if (dis< 22500) // 2 50X50  // (distance²<22500)
                {
                    isbuilding = true;
                    break;
                }

            }
        } 
  

        void draw()
        {
            DrawCircle(x, y, 23, colors[GREEN]);
            DrawCircle(x+2, y+2, 10, colors[ORANGE]);

        }

        int get7X() { return x; }
        int get7Y() { return y; }
};

   
RoleStation r1;
RoleStation r2;




class Passenger { 

    private:
        int x,y;
        bool isPicked;
        bool isDropped;
        int xdrop;
        int ydrop;

    public:
        Passenger()
        {
            do
            {
                isbuilding=false;
                x = (rand() % 19+1)*50; // x in [50, 950]
                y = (rand() % 15+1)*50;

                for(int i=0;i<len;i++)
                {
                    if(x==b[i].x && y==b[i].y )
                    {
                        isbuilding=true;
                        break;
                    }
                }
            }
            while(isbuilding);

            for(int i=0;i<2;i++)
            {
                int dx=x-b[i].x;
                int dy=y-b[i].y;

                int dis=dx*dx + dy*dy;

                if (dis< 40000) // 2 50X50  // (distance²<22500)
                {
                    isbuilding = true;
                    break;
                }
            }

            isPicked=false;
            isDropped=false;
            xdrop=-1;
            ydrop=-1;
        }


        void draw()
        {
            if(!isPicked && !isDropped)
            {   
                DrawCircle(x, y, 10, colors[WHITE]);
                DrawLine(x, y+10, x, y-20, 3, colors[WHITE]);
                DrawLine(x, y-20, x+10, y-40, 3, colors[WHITE]);
                DrawLine(x, y-20, x-10, y-40, 3, colors[WHITE]);

                /*
                DrawCircle(500, 540, 10, colors[WHITE]);
                DrawLine(500, 550, 500, 520, 3, colors[WHITE]);
                DrawLine(500, 520, 510, 500, 3, colors[WHITE]);
                DrawLine(500, 520, 490, 500, 3, colors[WHITE]);
                */
            }
            else if(isPicked && !isDropped)
            {
                DrawCircle(xdrop, ydrop, 25, colors[YELLOW]);
            }
            else if (isDropped) 
            {                // AT DESTINY
                DrawCircle(xdrop, ydrop, 10, colors[WHITE]);
                DrawLine(xdrop, ydrop+10, xdrop, ydrop-20, 3, colors[WHITE]);
                DrawLine(xdrop, ydrop-20, xdrop+10, ydrop-40, 3, colors[WHITE]);
                DrawLine(xdrop, ydrop-20, xdrop-10, ydrop-40, 3, colors[WHITE]);
            }
            
        }

        void pick1(int xtaxi, int ytaxi)
        {
            if (!isPicked && checkCollision(xtaxi,ytaxi,50,50,x,y,10,10))
            {
                isPicked = true;
                ispassenger=true; // able to pick other
                score=score+5;
                wallet=wallet+20;
                
                do
                {
                    xdrop =(rand()%20)*50;
                    ydrop =(rand()%16)*50;
                    isbuilding = false;
                    for(int i=0; i<len; i++)
                    {
                        if (xdrop==b[i].x && ydrop==b[i].y)
                        {
                            isbuilding = true;
                            break;
                        }
                    }
                } 
                while (isbuilding);
                
                for(int i=0;i<2;i++)
                {
                    int dx=xdrop-fuelstation[i].get4X();
                    int dy=ydrop-fuelstation[i].get4Y();
                    int dis=dx*dx + dy*dy;

                    if (dis< 22500) // 2 50X50  // (distance²<22500)
                    {
                        isbuilding = true;
                        break;
                    }

                }

                if(xdrop<=100 || xdrop>950 || ydrop<=50 || ydrop>=750)isbuilding =true;


                glutPostRedisplay();
            }
        }

        void Drop1(int xtaxi, int ytaxi)
        {
            if(!isDropped && isPicked && (checkCollision(xtaxi,ytaxi,50,50, xdrop,ydrop,50,50)))
            {
                isDropped=true;
                isPicked=false;
                score=score+10;
                wallet=wallet+50;
                glutPostRedisplay();
            }
        }

        bool getIsPicked1() { return isPicked; }
        bool getIsDropped1() { return isDropped; } 

        int get5X() { return x-20; }
        int get5Y() { return y-20; }      
};


Passenger* passenger=nullptr;


class Delievery{

    private:

        int x,y;
        bool isPicked;
        bool isDropped;
        int xdrop;
        int ydrop;

    public:

        Delievery()
        {   
            do
            {
                isbuilding=false;
                x=(rand()%20)*50;
                y=(rand()%16)*50;

                for(int i=0;i<len;i++)
                {
                    if(x==b[i].x && y==b[i].y )
                    {
                        isbuilding=true;
                        break;
                    }
                }
            }
            while(isbuilding);


            for(int i=0;i<2;i++)
            {
                int dx=x-b[i].x;
                int dy=y-b[i].y;
                int dis=dx*dx + dy*dy;

                if (dis<22500) // 2 50X50  // (distance²<22500)
                {
                    isbuilding = true;
                    break;
                }

            }
            isPicked=false;
            isDropped=false;
            xdrop=-1;
            ydrop=-1;
        }
      

        void draw()
        {
            if(!isPicked && !isDropped)
            {   
                DrawRectangle(x,y,50,50,colors[ORANGE]); 
            }
            else if(isPicked && !isDropped)
            {
                DrawCircle(xdrop, ydrop, 25, colors[YELLOW]);
            }
            else if(isDropped)
            {   
                DrawRectangle(xdrop,ydrop,50,50,colors[ORANGE]); 
            }
        }


        void pick(int xtaxi, int ytaxi)
        {
            if(!isPicked && checkCollision(xtaxi,ytaxi,50,50,x,y,40,40))
            {
                isPicked = true;
                isdelivery = true; 
                score=score+5;
                wallet=wallet+20;

                
                do
                {
                    xdrop=(rand()%20)*50;
                    ydrop =(rand()%16)*50;
                    isbuilding = false;
                    for(int i=0; i<len; i++)
                    {
                        if (xdrop==b[i].x && ydrop==b[i].y)
                        {
                            isbuilding = true;
                            break;
                        }
                    }
                } 

                while (isbuilding);


                for(int i=0;i<2;i++)
                {
                    int dx=xdrop-fuelstation[i].get4X();
                    int dy=ydrop-fuelstation[i].get4Y();
                    int dis=dx*dx + dy*dy;

                    if (dis< 22500) // 2 50X50
                    {
                        isbuilding = true;
                        break;
                    }
                }
                if(xdrop<=50 || xdrop>950 || ydrop<=50 || ydrop>=750)isbuilding =true;

                glutPostRedisplay();
            }
        }

        void Drop(int xtaxi, int ytaxi)
        {
            if(!isDropped && isPicked && (checkCollision(xtaxi,ytaxi,50,50, xdrop,ydrop,50,50)))
            {
                isDropped=true;
                isPicked=false;
                score=score+10;
                wallet=wallet+50;
                glutPostRedisplay();
            }
        }

        int get3X() { return x; }
        int get3Y() { return y; }
        bool getIsPicked() { return isPicked; }
        bool getIsDropped() { return isDropped; } 
};

Delievery* delivery;



class highScore 
{
    public:
    char name[32]; 
    int score;
};

class Leaderboard {

private:

    highScore s[10];                  //         composition
    string name;

public:
    Leaderboard(const string& name): name(name) 
    {

        for(int i=0; i<10;i++) 
        {
            strcpy(s[i].name, "Player");
            s[i].score = i+17;
        }
        LoadfileData();
    }

    void LoadfileData() 
    {
        ifstream in("highscores.txt");
        in.close();
    }

    void SaveToFile() 
    {
        ofstream out("highscores.txt");
        out.close();
    }



    void Display() 
    {
        DrawRectangle(200,50,600,750,colors[GRAY]);

        DrawString(400, 750, "LEADERBOARD", colors[BLACK]);

        for(int i=0;i<10;i++) 
        {
            string player = to_string(i+1) + ": "+s[i].name+" - "+to_string(s[i].score);

            DrawString(350, 700-(i*40),  player, colors[INDIGO]);
        }
        

        DrawString(350, 100, "Press Any Key to Continue", colors[VIOLET]);
    }
};



Leaderboard* leaderboard;

class Board{

public:

    void draw() 
    {
        glClearColor(0.5, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        
        
        
        if (showLeaderboard && leaderboard) 
        {
            leaderboard->Display();
        }

        else if(isMenu)
        {
            DrawRectangle(210, 220, 600, 400, colors[INDIGO]); 
            DrawString(470, 550, "Menu", colors[WHITE]); 


            DrawRectangle(310, 300, 180, 200, colors[VIOLET]); 
            DrawCircle(400, 450, 10, colors[WHITE]); 
            DrawLine(400, 450, 400, 400, 3, colors[WHITE]); 
            DrawLine(400, 400, 410, 380, 3, colors[WHITE]); 
            DrawLine(400, 400, 390, 380, 3, colors[WHITE]); 
            DrawString(330, 330, "Driver (P)", colors[WHITE]); 


            DrawRectangle(510, 300, 180, 200, colors[VIOLET]); 
            DrawRectangle(570, 400, 50, 50, colors[BROWN]); 
            DrawString(520, 330, "Delivery (Q)", colors[WHITE]); 
        }

        else
        {  // Draw Buildings
            for (int i = 100; i < 300; i += 50) 
            {
                DrawSquare(400, i, 50, colors[BLACK]);
            }
            for (int i = 330; i < 650; i += 50) 
            {
                DrawSquare(i, 350, 50, colors[BLACK]);
            }
            for (int i = 600; i < 900; i += 50) 
            {
                DrawSquare(i, 500, 50, colors[BLACK]);
            }
            for (int i = 400; i < 450; i += 50) 
            {
                DrawSquare(400, i, 50, colors[BLACK]);
            }
            for (int i = 500; i < 800; i += 50) 
            {
                DrawSquare(200, i, 50, colors[BLACK]);
            }
            for (int i = 0; i < 400; i += 50) 
            {
                DrawSquare(0, i, 50, colors[BLACK]);
            }
            for (int i = 0; i < 300; i += 50) 
            {
                DrawSquare(50, i, 50, colors[BLACK]);
            }
            for (int i = 150; i < 250; i += 50) 
            {
                DrawSquare(i, 0, 50, colors[BLACK]);
            }
            for (int i = 550; i < 800; i += 50) 
            {
                DrawSquare(400,i , 50, colors[BLACK]);
            }
            for (int i = 550; i < 700; i += 50) 
            {
                DrawSquare(i,50 , 50, colors[BLACK]);
            }
            for (int i = 450; i < 700; i += 50) 
            {
                DrawSquare(700,i , 50, colors[BLACK]);
            }
            for (int i = 450; i < 700; i += 50) 
            {
                DrawSquare(200,i , 50, colors[BLACK]);
            }
            for (int i = 550; i < 700; i += 50) 
            {
                DrawSquare(i,250 , 50, colors[BLACK]);
            }
            for (int i = 50; i < 200; i += 50) 
            {
                DrawSquare(970,i , 50, colors[BLACK]);
            }


            // Draw Roads
            for (int i = 50; i < 1020; i += 50) {
                DrawLine(0, i, 1020, i, 2, colors[WHITE]);
            }

            
            //                     fuel counter
            if(fuel>0)
            {
                DrawRectangle(970, 700, 50, fuel, colors[LIME]);
            }
            string scoreText="Score=" + to_string(score);
            DrawString(50, 810, scoreText, colors[WHITE]);

            wallet=(wallet>0)? wallet:0;
            
            string walletText="Wallet=" + to_string(wallet)+" $";

            DrawString(450, 810, walletText, colors[WHITE]);

            string timeText="Time Left: "+to_string(TotalTime)+" s";

            DrawString(750, 810, timeText, colors[WHITE]);

            if(overGame)
            {
                if(!isMenu && (TotalTime <= 0 || TotalTime >=180|| fuel <= 0 || score < 0)) 
                {
                    DrawString(400, 400, "Game Over!", colors[RED]);
                }
                if(score >= 100) 
                {
                    DrawString(400, 400, "You Win!", colors[GREEN]);
                }
            }
            


   
            /*
            if(isdelivery)
            {

                // Delievery
                DrawRectangle(310, 700, 50, 50, colors[ORANGE]);
                DrawRectangle(510, 500, 50, 50, colors[ORANGE]);
                DrawRectangle(710, 300, 50, 50, colors[ORANGE]);

            }

            // fuel station
            DrawRectangle(num+210, 300, 25, 50, colors[BROWN]); 
            DrawRectangle(num+610, 350, 25, 50, colors[BROWN]); 
            DrawRectangle(num+510, 0,  25, 50, colors[BROWN]); 

                */
            
        }

    }
};

Board *board;


void SetCanvasSize(int width, int height) 
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//                              function call all objects on board
void GameDisplay() 
{
    board->draw();

    if(!isMenu && !overGame)
    {
        taxi->draw();

        c1.draw();
        c2.draw();
        c3.draw();
        c4.draw();
        c5.draw();

        r1.draw();
        r2.draw();

        t1.draw();
        t2.draw();

        for(int i=0;i<2;i++)
        {
            passenger[i].draw();
        }
        for(int i=0;i<2;i++)
        {
            delivery[i].draw();
        }
        for(int i=0;i<2;i++)
        {
            fuelstation[i].draw();
        }
    }
    glutSwapBuffers();
}

/*

sf::Music backgroundMusic;

void loadMusic() {
    if (!backgroundMusic.openFromFile("audio/a1.ogg")) 
    { 
        return;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(80);  // 70% volume
    backgroundMusic.play();
}
*/

class SoundManager {
private:
    sf::Music bgMusic;
    sf::Sound collisionSound;
    sf::SoundBuffer collisionBuffer;

public:
    void init() {
        // Load background music (no error check)
        bgMusic.openFromFile("audio/a1.ogg");
        bgMusic.setLoop(true);
        bgMusic.setVolume(70);
        bgMusic.play();

        // Load collision sound (no error check)
        collisionBuffer.loadFromFile("audio/a2.ogg");
        collisionSound.setBuffer(collisionBuffer);
    }

    void playCollision() {
        collisionSound.play();
    }
};

SoundManager sounds;

void musicplay() {
    sounds.init();  
}




    

void NonPrintableKeys(int key, int x, int y) 
{
    x = taxi->getX();
    y = taxi->getY();

    ismove=true;
    
    if(!isMenu && !overGame)
    {
        if(key==GLUT_KEY_LEFT) 
        {
            x=x-10;
            if(x<=0)ismove=false;
            
            if(ispassenger && ! isdelivery)
            {
                for(int i = 0; i < 2; i++)
                {              
                    if (!passenger[i].getIsPicked1()) 
                    {
                        passenger[i].pick1(x, y);  // Try to pick up if not picked and not dropped
                    }             
                }
            }   
        }

        else if (key == GLUT_KEY_UP) 
        {
            y=y+10;
            if(y>800)ismove=false;
            if(!ispassenger &&  isdelivery)
            {
                for(int i = 0; i < 2; i++)
                {            
                    if(!delivery[i].getIsPicked())
                    {
                        delivery[i].pick(x, y);
                    }                  
                }
            }
            
           
        } 

        else if (key == GLUT_KEY_RIGHT) 
        {
            x=x+10;
            if(x>=970)ismove=false;
        } 

        else if (key == GLUT_KEY_DOWN)     
        {
            y=y-10;
            if(y<0)ismove=false;        
        }

        //       drop 
        
        for(int i = 0; i < 2; i++)
        {            
            passenger[i].Drop1(x, y); 
            delivery[i].Drop(x, y); 
        }
          
    }
    
    // BUILDINGS
    if(ismove)
    {
        for(int i=0;i<len ;i++)
        {
            if(checkCollision(x, y, 50, 50, b[i].x, b[i].y, b[i].l, b[i].w))
            {
                ismove=false;
                sounds.playCollision();
                break;
            }
        }
    }

    // other taxi

    if(ismove)
    {
        if(checkCollision(x,y,50,50,c1.get1X(),c1.get1Y(),50,50) ||
          checkCollision(x,y,50,50,c2.get1X(),c2.get1Y(),50,50)  ||
          checkCollision(x,y,50,50,c3.get2X(),c3.get2Y(),50,50)  ||
          checkCollision(x,y,50,50,c4.get2X(),c4.get2Y(),50,50)  ||
          checkCollision(x,y,50,50,c4.get2X(),c5.get2Y(),50,50)) 
        {
            if(ispassenger)
            {
                score=score-3;
            }
            
            if(isdelivery)
            {
                score=score-5;
            }
            ismove=false;
            sounds.playCollision();
        }
    }

    // Fuel Station  

    if(ismove)
    {
        for(int i=0;i<2;i++)
        {
            if(checkCollision(x,y,50,50,fuelstation[i].get4X(),fuelstation[i].get4Y(),25,50))
            {
                if(wallet>0 || wallet<10)
                {
                    fuel+=30;
                    if(fuel>100)fuel=100;
                    wallet=wallet-5;
                }
                else if(wallet>=10 || wallet<30)
                {
                    fuel=fuel+50;
                    if(fuel>100)fuel=100;
                    wallet=wallet-10;

                }
                else if(wallet>=30)
                {
                    fuel+=100;
                    if(fuel>100)fuel=100;
                    wallet=wallet-30;
                }
                
                ismove=false;
                sounds.playCollision();
            }
        }
       
    }
    // Trees

    if(ismove)
    {
        if(checkCollision(x,y,50,50,t1.get6X()-20, t1.get6Y()-20, 40, 40) ||

            checkCollision(x,y,50,50,t2.get6X()-20,t2.get6Y()-20,40,40)) 
        {
            ismove=false;
            sounds.playCollision();
            if(isdelivery)
            {
                score=score-4;
            }
            if(ispassenger)
            {
                score=score-2;
            }
            
        }
    }

    // Passenger 

    if(ismove)
    {
        for(int i=0;i<2;i++)
        {
            if(checkCollision(x,y,50,50,passenger[i].get5X(),passenger[i].get5Y(),20,20)) 
            {
                ismove=false;
                sounds.playCollision();
                if(ispassenger)
                {
                    score=score-5;
                }
                
                if(isdelivery)
                {
                    score=score-8;
                }
                glutPostRedisplay();
            }
        }
    }

    // Delivery box 

    if(ismove)
    {
        for(int i=0;i<2;i++)
        {
            if(checkCollision(x,y,50,50,delivery[i].get3X(),delivery[i].get3Y(),50,50))
            {
                ismove=false;
                sounds.playCollision();
                if(isdelivery)
                {
                    score=score-5;
                }

                if(ispassenger)
                {
                    score=score-2;
                }
                
                glutPostRedisplay();
            }
        }
    }



    if(ismove)
    {
        taxi->setX(x);
        taxi->setY(y);
    }
    glutPostRedisplay();
}

void PrintableKeys(unsigned char key, int x, int y) 
{
       if (showLeaderboard) 
       {
        showLeaderboard = false;
        isMenu = true;
        glutPostRedisplay();
        return;
    }

    x = taxi->getX();
    y = taxi->getY();

    if(isMenu)
    {
        if (key == 27) 
        {
            exit(1);
        }

        else if(key=='P' || key=='p')
        {
            isdelivery=false;
            ispassenger=true;
            isMenu=false;
            glutPostRedisplay();
        }
        else if(key=='Q' || key=='q')
        {
            isdelivery=true;
            ispassenger=false;
            isMenu=false;
            glutPostRedisplay();
        }
    } 
    
    else
    {   
        if (key == 27) 
        {
            exit(1);
            glutPostRedisplay();
        }           
    }     
    glutPostRedisplay();

    // Role station 

    if(ismove)
    {
        if(checkCollision(x,y,50,50,r1.get7X(),r1.get7Y(),50,50) ||
          checkCollision(x,y,50,50,r2.get7X(),r2.get7Y(),50,50)) 
        {
            ismove=false;
            if(key=='P' || key=='p')
            {
                score=0;
                isdelivery=false;
                ispassenger=false;
                taxi->setX(8);
                taxi->setY(750);
                isMenu=true;
                TotalTime =180;
                timelap =0;

                glutPostRedisplay();
            }
            return;  
        }

     
    } 
}



void Timer(int m)
{
    if(!isMenu)
    {
        timelap++;          // increment 10 times == -1s

        if(timelap==10)     // == 1s
        {
            TotalTime=TotalTime-1;
            fuel=fuel-2;
            timelap=0;

            if(TotalTime==0 || fuel==0 || score<0 || score>=100)
            {
                overGame=true;
                isdelivery=false;
                ispassenger=false;
                TotalTime=60.0f;
                timelap=0;
                score=0;
                fuel=0;
                
            }

        }
    }
    glutPostRedisplay();
    glutTimerFunc(100, Timer, 0);  // call after every 100 milliseconds,
}

void MousePressedAndMoved(int x, int y) 
{
    cout << x << " " << y << endl;
    glutPostRedisplay();
}

void MouseMoved(int x, int y) 
{
    glutPostRedisplay();
}

void MouseClicked(int button, int state, int x, int y) 
{
    if (button == GLUT_LEFT_BUTTON) 
    {
        cout << GLUT_DOWN << " " << GLUT_UP << endl;
    } 
    else if (button == GLUT_RIGHT_BUTTON) 
    {
        cout << "Right Button Pressed" << endl;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[]) 
{
    int width = 1020, height = 840;
    string *ptr;

    string name;
    cout<<"Enter your name : ";
    cin>>name;

    leaderboard = new Leaderboard(name); 
    // Initialize game objects
    taxi = new Taxi(8, 750, ptr);
    board = new Board();
    passenger=new Passenger[2];
    delivery=new Delievery[2];

    fuelstation=new FuelStation[2];

    InitRandomizer();
    
    musicplay();
    
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE  |  GLUT_RGBA);

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("Rush Hour by Muanna Hamid");
    SetCanvasSize(width, height);

    glutDisplayFunc(GameDisplay);

    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);
    glutTimerFunc(1000.0, Timer, 0);
    glutMouseFunc(MouseClicked);
    glutPassiveMotionFunc(MouseMoved);
    glutMotionFunc(MousePressedAndMoved);

    glutMainLoop();

    delete taxi;
    delete board;
    delete passenger;
    delete delivery;
    delete leaderboard;
    return 1;
}
#endif /* RushHour_CPP_ */















