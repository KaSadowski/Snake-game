#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include <time.h>
#include <stdlib.h>

int xF, yF;				//wspolrzedne jedzenia
int a[100][2];			//tablica wspolrzednych ciala weza 
int V = 10;				//Predkosc poruszania sie weza
int S = 4;				//poczatkowa dlugosc weza
int D = 37;				//kierunek (37 to poczatkowa)
int t;					//poziom trudnosci

void Field(){							//funkcja wywolujaca plansze
		rectangle(50,50,800,600);
}

void LocateFood(){						//losowanie wsp jablka
	xF = 10*(rand()%75) + 50;
	yF = 10*(rand()%55) + 50;			
}

void PrintFood(){						//drukowanie jablka
	rectangle (xF,yF,xF+10,yF+10);
}

void Body(){							//poczatkowe wartosci polozenia weza
	
	a[0][0]=270;
	a[0][1]=270;
	a[1][0]=280;
	a[1][1]=270;
	a[2][0]=290;
	a[2][1]=270;
	a[3][0]=300;
	a[3][1]=270;
}

void PrintBody(){						//drukowanie elementow weza
	line(a[0][0],a[0][1],a[0][0]+10,a[0][1]+10);
	line(a[0][0]+10,a[0][1],a[0][0],a[0][1]+10);
	for(int i=0; i<S; i++){
			rectangle(a[i][0],a[i][1],a[i][0]+10,a[i][1]+10);
	}
}

void MoveBody(){						//poruszanie sie weza (polega na zamianie wartosci wsp, komorka wczsniejsza dostaje wartosc poprzedzajacej)
	for(int i=S-1; i>0; i--){
		a[i][0] = a[i-1][0];			
		a[i][1] = a[i-1][1];
	}
}

void MoveHead(){						//ruch glowy weza
	int i;
	i = getkey();

	if(i != -1)
		D = i;


	switch(D){
		case 38:
			a[0][1] -=V;
			break;
		case 40:
			a[0][1] +=V;
			break;
		case 37:
			a[0][0] -=V;
			break;
		case 39:
			a[0][0] +=V;
			break;
	}
}

void CheckCollision(){				//sprawdzanie kolizjii
	for (int i=1; i<S; i++){
		if( a[0][0] == a[i][0] && a[0][1] == a[i][1]){			
			puts("GAME OVER");
			printf("Your score is %d\n", S-4);
			line(50,50,800,600);
			line(800,50,50,600);
			wait();
		}
		if( a[0][0] > 790 || a[0][1] > 590 || a[0][0] < 50 || a[0][1] < 50){			
			puts("GAME OVER");
			printf("Your score is %d\n", S-4);
			line(50,50,800,600);
			line(800,50,50,600);
			wait();
		}
	}
}

void CheckApple(){					//sprawdzanie zjedzienia jablka
	if(a[0][0] == xF && a[0][1] == yF){
		S++;
		LocateFood();
	}
}

void Start(){
	puts("S N A K E");
	printf("\n\n\n");
	puts("Please select difficulty");
	printf("\n");
	puts("1 = easy");
	puts("2 = medium");
	puts("3 = hard");
	printf("\n\n");
	int o;
	scanf("%d", &o);
	printf("\n\n");

	switch (o){
		case 1:
			t = 2;
			break;
		case 2:
			t = 6;
			break;
		case 3:
			t = 10;
			break;
	}
}

void main()
{

	srand(time(NULL));
	Start();
	graphics(850,650);
	Body();
	LocateFood();
	while(animate(t)){
		clear();
		Field();
		PrintFood();
		PrintBody();
		CheckCollision();
		CheckApple();
		MoveBody();
		MoveHead();
	}

}