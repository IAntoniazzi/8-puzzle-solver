//"Eight is Enough" by Irene Antoniazzi and Mahmudul Hasan
//York College CS377 Artificial Intelligence, Professor Minhua Huang

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stack>
#include <stdio.h>
#include <ctime>

using namespace std;

const int MAX = 3;
bool hasSolution;
string str_s; 
string tiles;
int cost[MAX];
vector<vector<int> > goal(3, vector<int>(3)); //3x3
vector<vector<int> > intermediate(3, vector<int>(3)); //3x3
int startChecker=0;
int step;
int step2;
int counter;
bool done;
bool checker;
string grand; 
string parent;
string start;
string goalState = "123456780";
string repeat = "Y";

struct state{
	int cval;
	string board;
	int step;
	vector<string> ancestors;
	state* previous;
	state* next;	
	};

state starter;
state openAnchor;
state closedAnchor;

state* x;
state* openCurrent;
state* openStart;
state* openEnd;
state* closedCurrent;
state* closedStart;
state* closedEnd;
state* temp;
state* Omarker;
state* Cmarker;

bool checkOpen(state y);
bool checkClosed(state y);
void makeState(string s, state parentState);
bool check(string s);
bool CheckForSolution(string str_s);
int Heuristic(string interState);
void Cost(vector<string>, state x);
void children(string parent, state parentState);



using namespace std;

bool check(string s){
int x=0;

if (s.size()!=9){
	return false;
}

for(int i=0; i<9; i++){
	for(int j=0; j<9; j++){
		if(i!=j&&s[i]==s[j]){
			return false;
		}
	}
}

for(int k=0; k<9; k++){
	x+=(s[k]-48);
}

if(x!=36){
	return false;
}

else{
	return true;
}


}

bool CheckForSolution(string str_s){
int j=0;
int m=0;
int n=0;

	for(int i=0; i<9; i++){		//iterate thru string
		if((str_s[i]-48)>1){		//take first character as int	
			j=str_s[i]-48;	
			m=0;
			for(int k=0; k<=i; k++){		//iterate thru list up to and including current j
				if(str_s[k]-48<j&&str_s[k]-48!=0){	//if the value is less than j
					m++;
				}
			}
			n+=(j-m-1);						//this accumulates the total
		}
	}
if(n%2==0){
	return true;
}

else{
	return false;
}

}


int Heuristic(string interState)
{
	//int estimate = 0;
	int manhattanDistance = 0;
	//converting the intermediate state to a vector 2d array
	intermediate[0][0] = interState[0] - 48; //sub 48 from goal state (for ascii to dec)
    intermediate[0][1] = interState[1] - 48;
    intermediate[0][2] = interState[2] - 48;
    intermediate[1][0] = interState[3] - 48;
    intermediate[1][1] = interState[4] - 48;
    intermediate[1][2] = interState[5] - 48;
    intermediate[2][0] = interState[6] - 48;
    intermediate[2][1] = interState[7] - 48;
    intermediate[2][2] = interState[8] - 48;
    
	//converting the goal state to a vector 2d array
	goal[0][0] = goalState[0] - 48; //sub 48 from goal state (for ascii to dec)
    goal[0][1] = goalState[1] - 48;
    goal[0][2] = goalState[2] - 48;
    goal[1][0] = goalState[3] - 48;
    goal[1][1] = goalState[4] - 48;
    goal[1][2] = goalState[5] - 48;
    goal[2][0] = goalState[6] - 48;
    goal[2][1] = goalState[7] - 48;
    goal[2][2] = goalState[8] - 48;
    
	for(int i=0; i<3; ++i) //intermediate_x coordinates
    {
        for(int j=0; j<3; ++j) //intermediate_y coordinates
        {
            for(int k=0; k<3; ++k) //goal_x coordinates
            {
                for(int l=0; l<3; ++l) //goal_y coordinates
                {
					if (intermediate[i][j] == goal[k][l] && goal[k][l] !=  0)
					{
						//Heuristic Estimation = sum of the Manhattan distance
						// between intermediate state and goal state
                       	manhattanDistance = manhattanDistance + abs(k - i) + abs(l - j);
					}
                }
            }
        }
	}
	return manhattanDistance;
}


void children(string parent, state parentState){
	if(parentState.ancestors.size()>0){
		grand=parentState.ancestors[(parentState.ancestors.size()-1)];
	}
	else{
		grand="";
	}
	
	if(parent[0] == '0'){
		if (parent.substr(3,1)+parent.substr(1,1)+parent.substr(2,1)+parent.substr(0,1)+parent.substr(4,5)!=grand){
			makeState(parent.substr(3,1)+parent.substr(1,1)+parent.substr(2,1)+parent.substr(0,1)+parent.substr(4,5), parentState);
			}
		if((parent.substr(1,1)+parent.substr(0,1)+parent.substr(2,7))!=grand){
			makeState(parent.substr(1,1)+parent.substr(0,1)+parent.substr(2,7), parentState);
				}
	}
	else if(parent[1]=='0'){
		if ((parent.substr(1,1)+parent.substr(0,1)+parent.substr(2,7))!=grand){
			makeState(parent.substr(1,1)+parent.substr(0,1)+parent.substr(2,7), parentState);
			}
		if ((parent.substr(0,1)+parent.substr(2,1)+parent.substr(1,1)+parent.substr(3,6))!=grand){
			makeState(parent.substr(0,1)+parent.substr(2,1)+parent.substr(1,1)+parent.substr(3,6), parentState);
			}
		if((parent.substr(0,1)+parent.substr(4,1)+parent[2,2]+parent.substr(1,1)+parent.substr(5,4))!=grand){
			makeState(parent.substr(0,1)+parent.substr(4,1)+parent.substr(2,2)+parent.substr(1,1)+parent.substr(5,4), parentState);
			}
	}
	else if(parent[2] == '0'){
		if((parent.substr(0,1)+parent.substr(2,1)+parent.substr(1,1)+parent.substr(3,6))!=grand){
			makeState(parent.substr(0,1)+parent.substr(2,1)+parent.substr(1,1)+parent.substr(3,6), parentState);
			}
		if((parent.substr(0,2)+parent.substr(5,1)+parent.substr(3,2)+parent.substr(2,1)+parent.substr(6,3))!=grand){
			makeState(parent.substr(0,2)+parent.substr(5,1)+parent.substr(3,2)+parent.substr(2,1)+parent.substr(6,3), parentState);
			}
	}	
	else if(parent[3]== '0'){
		if((parent.substr(3,1)+parent.substr(1,2)+parent.substr(0,1)+parent.substr(4,5))!=grand){
			makeState(parent.substr(3,1)+parent.substr(1,2)+parent.substr(0,1)+parent.substr(4,5), parentState);
			}
		if((parent.substr(0,3)+parent.substr(4,1)+parent.substr(3,1)+parent.substr(5,4))!=grand){
			makeState(parent.substr(0,3)+parent.substr(4,1)+parent.substr(3,1)+parent.substr(5,4), parentState);
			}
		if((parent.substr(0,3)+parent.substr(6,1)+parent.substr(4,2)+parent.substr(3,1)+parent.substr(7,2))!=grand){
			makeState((parent.substr(0,3)+parent.substr(6,1)+parent.substr(4,2)+parent.substr(3,1)+parent.substr(7,2)), parentState);
			}
	}
	else if(parent[4]== '0'){
		if((parent.substr(0,1)+parent.substr(4,1)+parent.substr(2,2)+parent.substr(1,1)+parent.substr(5,4))!=grand){
			makeState(parent.substr(0,1)+parent.substr(4,1)+parent.substr(2,2)+parent.substr(1,1)+parent.substr(5,4), parentState);
			}
		if((parent.substr(0,3)+parent.substr(4,1)+parent.substr(3,1)+parent.substr(5,4))!=grand){
			makeState(parent.substr(0,3)+parent.substr(4,1)+parent.substr(3,1)+parent.substr(5,4), parentState);
			}
		if((parent.substr(0,4)+parent.substr(5,1)+parent.substr(4,1)+parent.substr(6,3))!=grand){
			makeState(parent.substr(0,4)+parent.substr(5,1)+parent.substr(4,1)+parent.substr(6,3), parentState);
			}
		if((parent.substr(0,4)+parent.substr(7,1)+parent.substr(5,2)+parent.substr(4,1)+parent.substr(8,1))!=grand){
			makeState(parent.substr(0,4)+parent.substr(7,1)+parent.substr(5,2)+parent.substr(4,1)+parent.substr(8,1), parentState);
			}
	}
	else if(parent[5]== '0'){
		if((parent.substr(0,2)+parent.substr(5,1)+parent.substr(3,2)+parent.substr(2,1)+parent.substr(6,3))!=grand){
			makeState(parent.substr(0,2)+parent.substr(5,1)+parent.substr(3,2)+parent.substr(2,1)+parent.substr(6,3), parentState);
			}
		if((parent.substr(0,4)+parent.substr(5,1)+parent.substr(4,1)+parent.substr(6,3))!=grand){
			makeState(parent.substr(0,4)+parent.substr(5,1)+parent.substr(4,1)+parent.substr(6,3), parentState);
			}
		if((parent.substr(0,5)+parent.substr(8,1)+parent.substr(6,2)+parent.substr(5,1))!=grand){
			makeState(parent.substr(0,5)+parent.substr(8,1)+parent.substr(6,2)+parent.substr(5,1), parentState);
			}
	}
	else if(parent[6]=='0'){
		if((parent.substr(0,3)+parent.substr(6,1)+parent.substr(4,2)+parent.substr(3,1)+parent.substr(7,2))!=grand){
			makeState(parent.substr(0,3)+parent.substr(6,1)+parent.substr(4,2)+parent.substr(3,1)+parent.substr(7,2), parentState);
			}
		if((parent.substr(0,6)+parent.substr(7,1)+parent.substr(6,1)+parent.substr(8,1))!=grand){
			makeState(parent.substr(0,6)+parent.substr(7,1)+parent.substr(6,1)+parent.substr(8,1), parentState);
			}
	}
	else if(parent[7]=='0'){
		if((parent.substr(0,4)+parent.substr(7,1)+parent.substr(5,2)+parent.substr(4,1)+parent.substr(8,1))!=grand){
			makeState(parent.substr(0,4)+parent.substr(7,1)+parent.substr(5,2)+parent.substr(4,1)+parent.substr(8,1), parentState);
			}
		if((parent.substr(0,6)+parent.substr(7,1)+parent.substr(6,1)+parent.substr(8,1))!=grand){
			makeState(parent.substr(0,6)+parent.substr(7,1)+parent.substr(6,1)+parent.substr(8,1), parentState);
			}
		if((parent.substr(0,7)+parent.substr(8,1)+parent.substr(7,1))!=grand){
			makeState(parent.substr(0,7)+parent.substr(8,1)+parent.substr(7,1), parentState);
			}
	}
	else if(parent[8]=='0'){
		if((parent.substr(0,5)+parent.substr(8,1)+parent.substr(6,2)+parent.substr(5,1))!=grand){
			makeState(parent.substr(0,5)+parent.substr(8,1)+parent.substr(6,2)+parent.substr(5,1), parentState);
			}
		if((parent.substr(0,7)+parent.substr(8,1)+parent.substr(7,1))!=grand){
			makeState(parent.substr(0,7)+parent.substr(8,1)+parent.substr(7,1), parentState);
			}
	}	
}

bool openCheck(state y){
	openCurrent=openStart;
	while(openCurrent!=openEnd){
		if(openCurrent->board==y.board){
			Omarker=openCurrent;
			return true;
		}
		openCurrent=openCurrent->next;
		}
	return false;
	}


bool closedCheck(state y){
	closedCurrent=closedStart;
	while(closedCurrent!=closedEnd){
		if(closedCurrent->board==y.board){
			Cmarker=closedCurrent;
			return true;
		}
		closedCurrent=closedCurrent->next;
	}
	return false;
	}
		
	

void makeState(string s, state parentState){
	checker=false;
	
	
	temp=new state;
	temp->board=s;
	temp->step=parentState.step+1;
	temp->cval=Heuristic(s)+parentState.ancestors.size()+1;
	temp->ancestors=parentState.ancestors;
	temp->ancestors.push_back(parentState.board);
	temp->step=temp->ancestors.size();
	temp->previous=NULL;
	temp->next=NULL;
	
	
	
	
	if(openStart==openEnd){
		openEnd->previous=temp;
		temp->next=openEnd;
		openStart=temp;
		openCurrent=temp;
		
	}
	
	else if(!openCheck(*temp)&&!closedCheck(*temp)){
		openCurrent=openStart;
		while(checker!=true){
			if(temp->cval <= openCurrent->cval){
				if(openCurrent->previous==NULL){
					openCurrent->previous=temp;
					temp->next=openCurrent;
					openStart=temp;
					temp->previous=NULL;
				}
				else{
					Omarker=openCurrent->previous;
					Omarker->next=temp;
					temp->previous=Omarker;
					openCurrent->previous=temp;
					temp->next=openCurrent;
				}
				checker=true;
			}
			openCurrent=openCurrent->next;
		}
	
		}

	
	
	else if(!openCheck(*temp)&&closedCheck(*temp)){
		closedCurrent=closedStart;
		openCurrent=openStart;
		if(temp->cval < Cmarker->cval){
			delete Cmarker;
			closedCurrent->previous=temp;
			temp->next=closedCurrent;
			closedCurrent=temp;
			closedStart=temp;
			while(checker==false){
				if((temp->cval) <= (openCurrent->cval)){
					if(openCurrent->previous==NULL){
						openCurrent->previous=temp;
						temp->next=openCurrent;
						openStart=temp;
					}
					else{
						Omarker=openCurrent->previous;
						Omarker->next=temp;
						temp->previous=Omarker;
						openCurrent->previous=temp;
						temp->next=openCurrent;
					}
					checker=true;
				}
			openCurrent=openCurrent->next;
			}
	
		}	

	}

	
	else if(openCheck(*temp)&&!closedCheck(*temp)){
		if(temp->cval < Omarker->cval){
			openCurrent=Omarker->previous;
			openCurrent->next=Omarker->next;
			delete Omarker;
			Omarker=openCurrent->next;
			Omarker->previous=openCurrent;
		}
		openCurrent=openStart;
		
		while(checker==false){
			if((temp->cval) <= (openCurrent->cval)){
				if(openCurrent->previous==NULL){
					openCurrent->previous=temp;
					temp->next=openCurrent;
					openStart=temp;
				}
				else{
					Omarker=openCurrent->previous;
					Omarker->next=temp;
					temp->previous=Omarker;
					openCurrent->previous=temp;
					temp->next=openCurrent;
				}
				checker=true;
			}
			openCurrent=openCurrent->next;
			}
	
	}
temp=NULL;

}




////////////////////////////////////////MAIN///////////////////////////////////////////////////////////
int main (){
	
double sTime, eTime, totalTime, totalSec;
	
openAnchor.cval=400000;
openAnchor.board="Open Anchor";
openAnchor.next=NULL;

closedAnchor.cval=400000;
closedAnchor.board="Closed Anchor";
closedAnchor.next=NULL;



cout<< "Welcome to the 8-puzzle Solver!" << endl<< endl;



cout<< "Please enter the starting state in the form of a string."<<endl<<"Your string should consist of the digits 0-8."<<endl<<"Each digit should appear once and only once." << endl;




getline (cin, start);

while (startChecker <2){
	startChecker=0;
	while (!check(start)){ 
		cout << "This is not a valid string. Please try again."<<endl;
		getline(cin, start);
		}
	startChecker++;

	while(CheckForSolution(start)==false){
		cout << "This puzzle has no solution. Please try again."<<endl;
		getline(cin, start);
		startChecker=0;
		}
		
	startChecker++;
	}


sTime = clock();  	//clock starts


openCurrent=new state;
openCurrent->board=start;
openCurrent->cval=Heuristic(start);
openCurrent->step=0;
openCurrent->next=&openAnchor;
openStart=openCurrent;
openEnd=&openAnchor;
openAnchor.previous=openCurrent;

closedCurrent=&closedAnchor;
closedStart=&closedAnchor;
closedEnd=&closedAnchor;

done = false;

cout<< endl<< "Processing..."<<endl<<endl;

///////////////////A-STAR///////////////////
while(done==false){
	x=openCurrent;
	x->previous=NULL;
	openStart=openCurrent->next;
	openCurrent=openCurrent->next;
	openCurrent->previous=NULL;
	x->next=NULL;
	if(x->board=="123456780"){
		done = true;
		}
	if(done==false){
		children(x->board, *x);
		closedCurrent=closedStart;
		openCurrent=openStart;
		closedCurrent->previous=x;
		x->next=closedCurrent;
		x->previous=NULL;
		closedCurrent=x;
		closedStart=x;
		}
	}

eTime=clock();

totalTime=eTime-sTime;
totalSec=totalTime/CLOCKS_PER_SEC;

int final=x->ancestors.size();


for(int i=0; i<final; i++){
	cout<<"     "<<x->ancestors[i].substr(0,3)<<endl<<"     "<<x->ancestors[i].substr(3,3)<<endl<<"     "<<x->ancestors[i].substr(6,3)<<endl<<endl;
	}

cout<<"     "<<x->board.substr(0,3)<<endl<<"     "<<x->board.substr(3,3)<<endl<<"     "<<x->board.substr(6,3)<<endl<<endl;

cout<< "We reached the goal state in "<< totalSec<<" seconds, traversing "<<final << " steps."<<endl<<endl;

cout<<"Press any key to exit"<<endl;

getline(cin, repeat);


cout<<endl<<endl;

return 0;
}


