//Steven Salmons
//HW#4
//CSC 130

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

class RailStation
{
	public:

//Edge stores the connections between stations as a linked list.
		struct edge
		{
			RailStation* neighbor;
			int cost;
			edge* next;
		};

//ListNode acts as a node for the adjacency table.
		struct listNode
		{
			RailStation* member;
			int stationID;
			int known;
			int cost;
			RailStation* adjPath;
			listNode* next;
		};

		int stationID;
		int routeTable[3][12];
		int known;

//Cost is our D(v)
		int cost;

//adjPath is our P(v)
		int adjPath;

//This is the pointer to the beginning of our adj table.
		listNode *masterList;
		string name;
		edge* head;
		RailStation () {};
		RailStation (string, int);
		void addEdge(int, RailStation*);
		void buildTable();
		void buildMasterList(RailStation*);
		void printTable();
		void shortestPath(RailStation s);
		int returnCost(RailStation s);
};

//Adds a previously unknown station to the adjacency table.
//Initializes it to having known = 0, an infinite cost, and no adj link.
//**************************************************************************
void RailStation::buildMasterList(RailStation *newStation)
{
	listNode *newNode = new listNode();
	newNode->next = masterList;
	newNode->member=newStation;
	newNode->stationID = newStation->stationID;
	newNode->known = 0;
	newNode->cost = 9999;
	newNode->adjPath = NULL;
        masterList = newNode;
}	

//RailStation constructor.
//***************************************************************************
RailStation::RailStation(string newName, int newID)
{
	name = newName;
	stationID = newID;
	head = new edge();
	head = NULL;
	masterList = new listNode();
	masterList = NULL;
}

//addEdge adds the edge objects to the edge list.
//These are the connections that signify adjacencies and costs.
//***************************************************************************
void RailStation::addEdge(int cost, RailStation *neighbor)
{
	edge *newEdge = new edge();
	newEdge->neighbor = neighbor;
	newEdge->cost = cost;
	newEdge->next= head;
	head = newEdge;
}

//The main function.  buildTable constructs the adjacency table
//using dijekstra's SPF algorithm.  Dynamically adds new stations
//to the list as it finds them, and calculates the adjacencies until
//all stations' shortest paths are "known"
//**************************************************************************		
void RailStation::buildTable()
{
	int lowCost = 9999;
	int lowID = 0;
	listNode *lowPtr;
	bool done;
	
	edge *edgePtr = head;
	listNode *listPtr;
	buildMasterList(this);
	masterList->known = 0;
	masterList->cost = 0;
	masterList->adjPath = this;
	lowPtr = masterList;
	while (done == false)
	{
		lowPtr = NULL;
		lowCost = 9999;
		listPtr = masterList;
		done = true;
		listPtr = masterList;
		while (listPtr != NULL)
		{
			if ((listPtr->cost < lowCost) && (listPtr->known == 0))
			{
				done = false;
				lowCost = listPtr->cost;
				lowID = listPtr->stationID;
				lowPtr = listPtr;
			}
			listPtr = listPtr->next;
		}
		if (done == true)
			break;
		edgePtr = lowPtr->member->head;
		lowPtr->known = 1;
		bool exist;
		while (edgePtr != NULL)
		{
			exist = false;	
			listPtr = masterList;
			while (listPtr != NULL)
			{
				if (listPtr->member->stationID == edgePtr->neighbor->stationID)
				{
					exist = true;
					if (listPtr->cost > (lowPtr->cost + edgePtr->cost))
					{
						listPtr->cost = (lowPtr->cost + edgePtr->cost);
						listPtr->adjPath = lowPtr->member;
					}
				}
				listPtr = listPtr->next;
			}
			if (exist == false)
			{
				buildMasterList(edgePtr->neighbor);
				masterList->known = 0;
				masterList->cost = (lowPtr->cost + edgePtr->cost);
				masterList->adjPath = lowPtr->member;
			}
			edgePtr = edgePtr-> next;
		}
	}
}

//Prints the station's route table.  Mainly for debugging.
//******************************************************************************
void RailStation::printTable()
{
	listNode *listPtr = masterList;
	while (listPtr != NULL)
	{
		cout <<"Node: " <<listPtr->member->name <<" - known: " <<listPtr->known <<" cost: " <<listPtr->cost;
		cout <<" adjacent source: " <<listPtr->adjPath->name <<endl;
		listPtr = listPtr->next;
	}
}

//Uses the adjacency table (in reverse) to print a shortest path 
//from start to destination.
//*******************************************************************************
void RailStation::shortestPath(RailStation s)
{
	listNode *listPtr = masterList;
	RailStation target = s;
	if (target.stationID == stationID)
	{
		cout <<name <<" -> ";
		return;
	}
	else
	{
	while (listPtr != NULL)
	{
		if (listPtr->stationID == target.stationID)
		{
			shortestPath(*listPtr->adjPath);
			cout <<listPtr->member->name <<" -> ";
			break;
		}
		listPtr = listPtr->next;
	}
	return;
	}
}
	

//Returns the cost of a route from the source station to target.
//Returns -1 if no path exists.
//*******************************************************************************
int RailStation::returnCost(RailStation s)
{
	listNode *listPtr = masterList;
	RailStation target = s;
	while (listPtr != NULL)
	{
		if (listPtr->stationID == target.stationID)
		{
			return listPtr->cost;
		}
		listPtr = listPtr->next;
	}
	return -1;
}

	
int main ()
{

//Build all the vertexes.
	RailStation sacramento("Sacramento", 1);
	RailStation sfo("SFO", 2);
	RailStation la("LA", 3);
	RailStation atlanta("Atlanta", 4);
	RailStation detroit("Detroit", 5);
	RailStation chicago("Chicago", 6);
	RailStation nj("New Jersey", 7);
	RailStation vegas("Las Vegas", 8);
	RailStation miami("Miami", 9);
	RailStation dallas("Dallas", 10);
	RailStation dc("Washington DC", 11);
	RailStation boston("Boston", 12);
	RailStation ny("New York", 13);
	
//Add all the edges to each vertex.
	sacramento.addEdge(50, &sfo);
	sacramento.addEdge(35, &atlanta);
	sfo.addEdge(60, &la);
	sfo.addEdge(35, &chicago);
	sfo.addEdge(70, &detroit);
	detroit.addEdge(10, &chicago);
	atlanta.addEdge(20, &detroit);
	atlanta.addEdge(60, &chicago);
	atlanta.addEdge(45, &nj);
	la.addEdge(30, &vegas);
	chicago.addEdge(5, &vegas);
	chicago.addEdge(40, &miami);
	nj.addEdge(30, &miami);
	nj.addEdge(25, &boston);
	vegas.addEdge(20, &dallas);
	miami.addEdge(50, &dc);
	boston.addEdge(20, &ny);
	dallas.addEdge(10, &ny);
	dc.addEdge(15, &ny);

//Menu system to ask the user for start and end stations.
	cout <<"1.  Sacramento " <<endl;
	cout <<"2.  San Francisco" <<endl;
	cout <<"3.  Los Angeles" <<endl;
	cout <<"4.  Atlanta" <<endl;
	cout <<"5.  Detroit" <<endl;
	cout <<"6.  Chicago" <<endl;
	cout <<"7.  New Jersey" <<endl;
	cout <<"8.  Las Vegas" <<endl;
	cout <<"9.  Miami" <<endl;
	cout <<"10. Dallas" <<endl;
	cout <<"11. Washington DC" <<endl;
	cout <<"12. Boston" <<endl;
	cout <<"13. New York" <<endl;
	int start, end; 
	RailStation startStation, endStation;
	cout <<"Enter a starting city from the list:";
	cin >>start;
	cout <<"Select a destination city from the list:";
	cin >>end;
	cout <<endl <<endl;
	switch (start)
	{
		case 1: 
			startStation = sacramento;
			break;
		case 2:
			startStation = sfo;
			break;
		case 3:
			startStation = la;
			break;
		case 4: 
			startStation = atlanta;
			break;
		case 5:
			startStation = detroit;
			break;
		case 6:
			startStation = chicago;
			break;
		case 7:
			startStation = nj;
			break;
		case 8:
			startStation = vegas;
			break;
		case 9:
			startStation = miami;
			break;
		case 10:
			startStation = dallas;
			break;
		case 11:
			startStation = dc;
			break;
		case 12:
			startStation = boston;
			break;
		case 13:
			startStation = ny;
			break;
		default:
			cout <<"Invalid start selection. ";
			return 1;
	}
	switch (end)
	{
		case 1: 
			endStation = sacramento;
			break;
		case 2:
			endStation = sfo;
			break;
		case 3:
			endStation = la;
			break;
		case 4: 
			endStation = atlanta;
			break;
		case 5:
			endStation = detroit;
			break;
		case 6:
			endStation = chicago;
			break;
		case 7:
			endStation = nj;
			break;
		case 8:
			endStation = vegas;
			break;
		case 9:
			endStation = miami;
			break;
		case 10:
			endStation = dallas;
			break;
		case 11:
			endStation = dc;
			break;
		case 12:
			endStation = boston;
			break;
		case 13:
			endStation = ny;
			break;
		default:
			cout <<"Invalid end selection. ";
			return 1;
	}
	
//Builds the ajacency table for the starting city.
	startStation.buildTable();
	int pathCost = 0;

//Calculates the path cost.  If -1, tell the user no path exists.
//otherwise, print it and the price.
	pathCost = startStation.returnCost(endStation);
	if (pathCost != -1)
	{
		startStation.shortestPath(endStation);		
		cout <<"Total Cost = " <<pathCost <<"$" <<endl;
	}
	else
		cout <<"No path exists from " <<startStation.name <<" to " <<endStation.name <<endl;
	return 0;
}
