#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <time.h>

using namespace sf;

int n=30,m=20;
int canvas=16;
int width=canvas*n;
int height=canvas*m;

int dir,num=4;
struct Snake
{
    int x,y;
}s[100];
struct Fruct
{
    int x,y;
}f;
void Tick()
{
    for(int i=num;i>0;i--)
    {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
    }
    if(dir==0)s[0].y+=1;
    if(dir==1)s[0].x-=1;
    if(dir==2)s[0].x+=1;
    if(dir==3)s[0].y-=1;
    if((s[0].x==f.x)&&(s[0].y==f.y))
    {
        num++;
        f.x=rand()%n;
        f.y=rand()%m;
    }
    if(s[0].x>n)s[0].x=0;if(s[0].x<0)s[0].x=n;
    if(s[0].y>m)s[0].y=0;if(s[0].y<0)s[0].y=m;

    for(int i=1;i<num;i++)
        if(s[0].x==s[i].x&&s[0].y==s[i].y)std::cout<<num<<std::endl,num=i;
}
int main()
{
    srand(time(0));
   RenderWindow window(VideoMode(width,height),"Snake AI");

   Texture t1,t2,t3;
   t1.loadFromFile("white.png");
   t2.loadFromFile("red.png");
   t3.loadFromFile("green.png");
   Sprite sprite1(t1);
   Sprite sprite2(t2);
   Sprite sprite3(t3);

   Clock clock;
   float timer=0,delay=0.1;
   f.x=10;
   f.y=10;
   bool AI=false;
    while(window.isOpen())
    {
        float time=clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;
        Event evnt;
        while(window.pollEvent(evnt))
            if(evnt.type==Event::Closed)
            window.close();

            if(Keyboard::isKeyPressed(Keyboard::Left)&&dir!=2)dir=1;
            if(Keyboard::isKeyPressed(Keyboard::Right)&&dir!=1)dir=2;
            if(Keyboard::isKeyPressed(Keyboard::Up)&&dir!=0)dir=3;
            if(Keyboard::isKeyPressed(Keyboard::Down)&&dir!=3)dir=0;
       if(Keyboard::isKeyPressed(Keyboard::F)&&!AI)
            AI=true;

        if(Keyboard::isKeyPressed(Keyboard::R)&&AI)
        AI=false;

        if(AI)
        {


        if(f.y>s[0].y&&dir!=3)dir=0;
        if(f.y<s[0].y&&dir!=0)dir=3;
        if(f.y==s[0].y)
        {
            if(f.x>s[0].x&&dir!=1)dir=2;
            if(f.x<s[0].x&&dir!=2)dir=1;
        }
        }



            if(timer>delay)
            {
                timer=0;
                Tick();
            }


        window.clear();
        for(int i=0;i<n;i++)
            for(int j=0;j<m;j++)
        {
            sprite1.setPosition(i*canvas,j*canvas);window.draw(sprite1);
        }
        for(int i=0;i<num;i++)
        {
            sprite2.setPosition(s[i].x*canvas,s[i].y*canvas);window.draw(sprite2);
        }
        sprite3.setPosition(f.x*canvas,f.y*canvas);
        window.draw(sprite3);

        window.display();
    }
}
