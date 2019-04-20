#include "cs2123p5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	
	return 0;
}

//non-recursive functions
// void prtAll(Graph graph); 
// void prtOne(Graph graph, int iVertex);

void prtOne(Graph graph, int iVertex)
{

	int iEllipsisCnt = 7;							//counter for ellipsis in final print
	Vertex airport = graph->vertexM[iVertex]; 		//shortcut to refer to vertex directly
	//>>PRTONE SAT
	//VX APT PREDECESSORS                          SUCCESSORS
	// 0 SAT H1/IAH  ... ... ... ... ... ... ...   S1-IAH S2-MCO S3-ATL 

	//check to see if airport exists
	if(iVertex >= graph->iNumVertices)
	{
		//if not, print warning and then return
		printf("WARNING: airport at specified vertex does not exist");
		return;
	}

	//print header	
	printf("Vx Apt Predecessors %-44s\n", "Successors");

	//print demographics of airport at vertex
	printf("%d %s", iVertex, airport.szAirport);	//vertex #, airport name
	
	//get list of predecessors
	EdgeNode *e; 									//to be initialized in for loop
	for(e = airport.predecessorList; e != NULL; e = e->pNextEdge)
	{
		//for each successor found, print it 
		printf("%s/%s ", e->flight.szFlightNr, e->flight.szOrigin);
		//and decrement iEllipsisCnt
		iEllipsisCnt--;
	}
	//print ellipsis if iEllipsisCnt > 0;
	while(iEllipsisCnt > 0)
	{
		printf("...... ");
		iEllipsisCnt--;
	}

	//get list of successors
	for(e = airport.successorList; e != NULL; e = e->pNextEdge)
	{
		//for each successor found, print it 
		printf("%s-%s ", e->flight.szFlightNr, e->flight.szDest);
	}

	printf("\n");

}

void prtAll(Graph graph)
{
	printf("All Vertices In a List");
	int iVertex;							//vertex # initialized for loop
	
	//for each vertex in a list, call printall
	for(iVertex = 0; iVertex < graph->iNumVertices; iVertex++)
		prtOne(graph, iVertex);


}


void printWithIndent(int indent, char * string);

void printWithIndent(int indent, char * string)
{
    printf("%*s%s", indent, "", string);
}

//recursive functions
// void prtTraversal(Graph graph, int iAirportVertex, int indent);

//prtsucc szOrigin flight->szOrigin ? 

// DFT
// int countE(Graph g, int v, int visitedM[])
// {
//     int iCount= 0;
// 	   EdgeNode *e;

//    if(visitedM[v])
// 	     return 0;
//    visitedM[v] = TRUE;

// for(e=g->vertexM[v].successorList; e != NULL; e=e->pNextEdge)
// {
//     iCount += + countE(g,e->iVertex, visitedM);
// }
//     }


void prtTraversal(Graph graph, int iAirportVertex, int indent)
{
	
	EdgeNode *e;

	//base case
	if(graph->vertexM[iAirportVertex].bVisited == TRUE)
		return;

	//change bVisited to TRUE
	graph->vertexM[iAirportVertex].bVisited = TRUE;
	char * successorAirport = "";
	// printWithIndent(indent, string);
	//idk how to use the indent lol


	for(e = graph->vertexM[iAirportVertex].successorList; e != NULL; e=e->pNextEdge)
	{
		int iVertexRecursive = findAirport(graph, graph->vertexM[iAirportVertex].szAirport);
		//unsure about this one

		prtTraversal(graph, iVertexRecursive, indent + 1);
	}
}


//NOTE: copied from cs2123p5Driver.c just to check for compiler issues for prtTraversal()
int findAirport(Graph graph, char szAirport[])
{
	int i;
	for (i = 0; i <= graph->iNumVertices; i++)
	{
		if (strcmp(szAirport, graph->vertexM[i].szAirport) == 0)
		{
			return i;
		}
	}
	return -1;
}

//program 6
//deleteFlight

