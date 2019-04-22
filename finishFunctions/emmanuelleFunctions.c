#include "cs2123p5.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/****************************** prtOne ******************************
void prtOne(Graph graph, int iVertex);
Purpose:
 Prints information for airport at specified vertex.
 
Parameters:
    I Graph graph          		Graph containing connections of airports/flights.
    I int iVertex        		Specified vertex that the function will print information
    							from.
Notes:
    Prints information including Vertex#, Airport, Predecessors and Successors.
    A maximum of 8 predecessors is assumed. If there are less than 8, empty spots
    are replaced with "....."
Returns 
    N/A
*******************************************************************************/

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


	//print demographics of airport at vertex
	printf("  %d %s ", iVertex, airport.szAirport);	//vertex #, airport name
	
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


/****************************** prtAll ******************************
void prtAll(Graph graph);
Purpose:
 Prints all vertices in a list/graph.
 
Parameters:
    I Graph graph          		Graph containing connections of airports/flights.
Notes:
    Prints all vertices in a list. Utilizes prtOne() to accomplish this.
Returns 
    N/A
*******************************************************************************/


void prtAll(Graph graph)
{
	int iVertex;							//vertex # initialized for loop
	
	//for each vertex in a list, call printall
	for(iVertex = 0; iVertex < graph->iNumVertices; iVertex++)
		prtOne(graph, iVertex);


}


/****************************** prtTraversal ******************************
void prtTraversal(Graph graph, int iAirportVertex, int indent);
Purpose:
 Prints flights that begin at the specified origin.
 
Parameters:
    I Graph graph          		Graph containing connections of airports/flights.
    I int iAirportVertex        Specified vertex that the function will begin printing
    							from.
    I int indent          		int representing indentions in printed output.
Notes:
    prtTraversal is a recursive function. It will continue to make calls to itself
    until the criteria for the base case is met (if aiport at specified vertex has
    already been visited).
Returns 
    N/A
*******************************************************************************/


void prtTraversal(Graph graph, int iAirportVertex, int indent)
{
	
	EdgeNode *e;
	int i;

	//base case —— see if airport has been visited
	if(graph->vertexM[iAirportVertex].bVisited == TRUE)
		return;

	//change bVisited to TRUE
	graph->vertexM[iAirportVertex].bVisited = TRUE;
	char * successorAirport = "";


	for(e = graph->vertexM[iAirportVertex].successorList; e != NULL; e=e->pNextEdge)
	{

		//calculate vertex for recursive call
		int iVertexRecursive = findAirport(graph, graph->vertexM[iAirportVertex].szAirport);

		//calculate arrivalTime using calcArr2400();
		int iArrivalTime = calcArr2400(e->flight.iDepTm2400, e->flight.iDurationMins, e->flight.iZoneChange);
		
		//for-loop for indent
		for(i = 0; i < indent; i++)
		{
			printf(" "); 	//print a space for from 0 to value specified at indent
		}	

		//print values
		//F#-Apt DeptTime-ArrivalTime
		printf("%s-%s %d-%d", e->flight.szFlightNr, graph->vertexM[iAirportVertex].szAirport, e->flight.iDepTm2400, iArrivalTime);
		printf("\n");		//newline

		prtTraversal(graph, iVertexRecursive, indent + 1);
	}
}
