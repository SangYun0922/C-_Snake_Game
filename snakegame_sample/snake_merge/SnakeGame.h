#include <ncurses.h> // for using ncurses library
#include <queue> // for using queue
#include <utility> // for using pair
using namespace std;

#ifndef __SNAKEGAME_H_
#define __SNAKEGAME_H_

struct point{
	int x;
	int y;
};

class SnakeGame
{
private:
	///* Attribute *///
	/* Map parameter */
	int row=0, col=0;

	/* Snake parameter */
	queue<pair<int,int> > xy; // queue for storing snake location
	point head; // x, y of head
	point body; // x, y of body
	point tail; // x, y of tail
	int max_length; // maximum length of snake
	int length=3; // length of snake (snake length is 3 at the start)
	char direction; // direction of snake

	/* ScoreBoard parameter */
	int score; // score of game
  int tick; // checking time delay
  int height, width;
  int vertical , horizontal; // length of terminal
  int Randheight, Randwidth; // location of snake head
  int ch; // keyboard
	point start; // x,y of start
	int count1=0,count2=0,count3=0,count4=0,countCobra=0; // time count for growth(count1), poison(count2) item, gate(count3) and hole(count4)
	int num_gate=0; // number of gate snake passed

	/* Wall parameter */
	int wall[21][42]={0,}; // wall->1, not wall->0
	int wallCopy[21][42]={0,};

	/* Gate parameter */
	point gate1; // x,y of gate1
	point gate2; // x,y of gate2
	point in; // x,y of entrance
	point out; // x,y of exit

	/* Cobra parameter */
	queue<pair<int,int> > cobra; // queue for storing snake location
	point cbody; // x, y of cobra body
	char cdirection; // direction of cobra

	/* Growth item parameter */
	point growth; // x,y of growth item
	int num_growth=0; // number of growth item

	/* Poison item parameter */
	point poison; // x,y of poison item
	int num_poison=0; // number of poison item

	/* Hole parameter */
  point hole; // x,y of hole

  /* Mission parameter */
  int mission_length; // mission length of snake
  int mission_growth; // mission number of growth item
  int mission_poison; // mission number of poison item
  int mission_gate; // mission number of gate


	///* Method *///
	void StartWindow(); // initalize window

	/* Snake function */
	void LocateSnake(); // put snake on the map
	void WrongDirection(); // if snake moves to wrong direction, game over
	void BumpedintoBody(); // check whether snake head bumped into body or not
	void SizeofSnake(); // check whether snake length is shorter than 3
	int ControlSnake(); // get input + movement by tick
	bool IsBody(int,int); // check whether snake head bumped into body

	/* Map function */
	void MakeMap1(); // make map1
	void MakeMap2(); // make map2
  void MakeMap3(); // make map3
  void MakeMap4(); // make map4

	/* Wall function */
	void BumpedintoWall(); // check whether snake bumped into wall or not

	/* Growth item function */
	void RandGrowthItem(); // put growth item(5) randomly on the map
	bool EatGrowthItem(); // check whether snake eat growth item or not

	/* Poison item function */
	void RandPoisonItem(); // put poison item(6) randomly on the map
	bool EatPoisonItem(); // check whether snake eat poison item or not

	/* Hole function */
	void RandHole(); // put hole(@) randomly on the map
	void BumpedintoHole(); // check whether snake bumped into hole or not
	bool IsHole(); // check whether snake fall into a hole

	/* Cobra function */
	void BumpedintoCobra(); // check whether snake bumped into cobra or not
  void DangerousCobra(); // watch out for cobra!!!
	void LocateCobra(); // locate cobra first
	bool IsCobra(); // check whether snake bumped into cobra
	bool DestroyedbyCobra(int,int); // check whether cobra destroy item(growth item, poison item, hole)

	/* Gate function */
	void RandGate(); // put gate(0) randomly on the map
	void ControlGate(); // rule of using gate
	bool IsGate(); // check whether snake head bumped into gate
	bool IsEdgeGate(); // check whether gate is at edge or not

	/* ScoreBoard function */
	void ScoreBoard(); // scoreboard

	/* Mission function */
	bool CheckMission(); // check whether player complete mission or not


public:
	SnakeGame(); // constructor
	~SnakeGame(); // destructor
	void Start(int); // start new snake game
	bool death = false; // check death
	bool GameStart = false; // check select gamestart
  int stage=1; // parameter for checking stage
};

#endif
