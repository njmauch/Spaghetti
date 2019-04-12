#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

int main(int argc, char * argv[])
{
	Graph graph = newGraph();
	getFlights(graph);
}
void getFlights(Graph graph)
{
	char szInputBuffer[MAX_LINE_SIZE];
	char szRecordType[MAX_TOKEN];
	char szAirport[4];
	char *pszRemainingTxt;
	int iIndent = 0;
	int iPrevArrTm2400;
	Flight flight;
	int iVertex = 0;

	while (fgets(szInputBuffer, MAX_LINE_SIZE, stdin) != NULL)
	{
		if (szInputBuffer[0] == '\n')
		{
			continue;
		}
		printf("%s", szInputBuffer);
		pszRemainingTxt = getToken(szInputBuffer, szRecordType, sizeof(szRecordType) - 1);
		if (strcmp(szRecordType, "FLIGHT") == 0)
		{
			sscanf(pszRemainingTxt, "%s %s %s %d %d %d", flight.szFlightNr, flight.szOrigin, flight.szDest, &flight.iDepTm2400, &flight.iDurationMins, &flight.iZoneChange);
			if (findAirport(graph, flight.szOrigin) < 0)
			{
				insertVertex(graph, flight.szOrigin);
			}
			if (findAirport(graph, flight.szDest) < 0)
			{
				insertVertex(graph, flight.szDest);
			}
			insertFlight(graph, flight, &graph->vertexM[findAirport(graph, flight.szDest)].predecessorList);
			insertFlight(graph, flight, &graph->vertexM[findAirport(graph, flight.szOrigin)].successorList);
		}
		/*
		if (strcmp(szRecordType, "PRTFLIGHTBYORIGIN") == 0)
		{
			prtFlightsByOrigin(graph);
		}
		setNotVisited(Graph graph);
		if (strcmp(szRecordType, "PRTFLIGHTBYDEST") == 0)
		{
			prtFlightsByDest(graph);
		}
		setNotVisited(Graph graph);
		if (strcmp(szRecordType, "PRTONE") == 0)
		{
			sscanf(pszRemainingTxt, "%s", szAirport);
			iVertex = findAirport(graph, szAirport);
			prtOne(graph, iVertex);
		}
		setNotVisited(Graph graph);
		if (strcmp(szRecordType, "PRTALL") == 0)
		{
			printAll(graph);
		}
		setNotVisited(Graph graph);
		if (strcmp(szRecordType, "PRTSUCC") == 0)
		{
			sscanf(pszRemainingTxt, "%s", szAirport);
			iVertex = findAirport(graph, szAirport);
			prtTraversal(graph, iVertex, iIndent);
		}
		setNotVisited(Graph graph);
		if (strcmp(szRecordType, "PRTCHRON") == 0)
		{
			sscanf(pszRemaintingTxt, "%s", szAiport);
			iVertex = findAirport(graph, szAirport);
			iPrevArrTm2400 = calcArr2400(flight.iDepTm2400, flight.iDurationMins, flight.iZoneChange);
			prtTraversalChron(graph, iVertex, iIndent, iPrevArrTm2400);
		}
		setNotVisited(Graph graph);
		*/
	}

}
int insertFlight(Graph graph, Flight flight, EdgeNode **eList)
{
	EdgeNode *eNew;
	EdgeNode *eFind;
	EdgeNode *ePrecedes;

	eFind = searchEdgeNode(*eList, flight.szFlightNr, &ePrecedes);
	if (eFind != NULL)
	{
		eNew = allocateEdgeNode(graph, flight);
		eNew->pNextEdge = eFind->pNextEdge;
		eFind->pNextEdge = eNew;
		return;
	}
	eNew = allocateEdgeNode(graph, flight);
	if (ePrecedes == NULL)
	{
		eNew->pNextEdge = *eList;
		*eList = eNew;
	}
	else
	{
		eNew->pNextEdge = ePrecedes->pNextEdge;
		ePrecedes->pNextEdge = eNew;
	}
	return;
}
void insertVertex(Graph graph, char szAirport[])
{
	strcpy(graph->vertexM[graph->iNumVertices].szAirport, szAirport);
	graph->vertexM[graph->iNumVertices].bExists = TRUE;
	graph->vertexM[graph->iNumVertices].bVisited = FALSE;
	graph->vertexM[graph->iNumVertices].successorList = NULL;
	graph->vertexM[graph->iNumVertices].predecessorList = NULL;
	graph->iNumVertices++;
}
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
Graph newGraph()
{
	Graph graph = malloc(sizeof(GraphImp));
	if (graph == NULL)
		errExit("Unable to allocate memory");
	graph->iNumVertices = 0;
	return graph;
}
EdgeNode * allocateEdgeNode(Graph graph, Flight flight)
{
	// allocate memory for an edge node
	EdgeNode *eNew;

	eNew = (EdgeNode *)malloc(sizeof(EdgeNode));

	// check if memory is available
	if (eNew == NULL)
		errExit("Unable to allocate memory for edgenode");

	eNew->flight = flight;
	eNew->iDestVertex = findAirport(graph, flight.szDest);
	eNew->iOriginVertex = findAirport(graph, flight.szOrigin);
	// make this node's next edge NULL
	eNew->pNextEdge = NULL;

	return eNew;
}
EdgeNode *searchEdgeNode(EdgeNode *e, char szFlightNr[3], EdgeNode **ePrecedes)
{
	*ePrecedes = NULL;
	for (e; e != NULL; e = e->pNextEdge)
	{
		if (strcmp(szFlightNr, e->flight.szFlightNr) == 0)
		{
			errExit("Duplicate flight number");
			return e;
		}
		if (strcmp(szFlightNr, e->flight.szFlightNr) < 0)
		{
			return NULL;
		}
		*ePrecedes = e;
	}
	return NULL;
}
/******************** getToken **************************************
char * getToken (char *pszInputTxt, char szToken[], int iTokenSize)
Purpose:
	Examines the input text to return the next token.  It also
	returns the position in the text after that token.
Parameters:
	I   char *pszInputTxt       input buffer to be parsed
	O   char szToken[]          Returned token.
	I   int iTokenSize          The size of the token variable.  This is used
								to prevent overwriting memory.  The size
								should be the memory size minus 1 (for
								the zero byte).
Returns:
	Functionally:
		 Pointer to the next character following the delimiter after the token.
		 NULL - no token found.
	szToken parm - the returned token.  If not found, it will be an
		 empty string.
Notes:
	- If the token is larger than the szToken parm, we return a truncated value.
	- If a token isn't found, szToken is set to an empty string
	- This function does not skip over white space occurring prior to the token.
	- If the input buffer pointer is NULL, the function terminates with
	  an algorithm error.
**************************************************************************/
char * getToken(char *pszInputTxt, char szToken[], int iTokenSize)
{
	int iDelimPos;                      // found position of delim
	int iCopy;                          // number of characters to copy
	char szDelims[20] = " \n\r";        // delimiters
	szToken[0] = '\0';

	// check for NULL pointer 
	if (pszInputTxt == NULL)
		errExit("getToken passed a NULL pointer");

	// Check for no token if at zero byte
	if (*pszInputTxt == '\0')
		return NULL;

	// get the position of the first delim
	iDelimPos = strcspn(pszInputTxt, szDelims);

	// See if the token has no characters before delim
	if (iDelimPos == 0)
		return NULL;

	// see if we have more characters than target token, if so, trunc
	if (iDelimPos > iTokenSize)
		iCopy = iTokenSize;             // truncated size
	else
		iCopy = iDelimPos;

	// copy the token into the target token variable
	memcpy(szToken, pszInputTxt, iCopy);
	szToken[iCopy] = '\0';              // null terminate

	// advance the position
	pszInputTxt += iDelimPos;
	if (*pszInputTxt == '\0')
		return pszInputTxt;
	else
		return pszInputTxt + 1;
}
/******************** errExit **************************************
	void errExit(char szFmt[], ... )
Purpose:
	Prints an error message defined by the printf-like szFmt and the
	corresponding arguments to that function.  The number of
	arguments after szFmt varies dependent on the format codes in
	szFmt.
	It also exits the program, returning ERR_EXIT.
Parameters:
	I   char szFmt[]            This contains the message to be printed
								and format codes (just like printf) for
								values that we want to print.
	I   ...                     A variable-number of additional arguments
								which correspond to what is needed
								by the format codes in szFmt.
Returns:
	Returns a program exit return code:  the value of ERR_EXIT.
Notes:
	- Prints "ERROR: " followed by the formatted error message specified
	  in szFmt.
	- Prints the file path and file name of the program having the error.
	  This is the file that contains this routine.
	- Requires including <stdarg.h>
**************************************************************************/
void errExit(char szFmt[], ...)
{
	va_list args;               // This is the standard C variable argument list type
	va_start(args, szFmt);      // This tells the compiler where the variable arguments
								// begins.  They begin after szFmt.
	printf("ERROR: ");
	vprintf(szFmt, args);       // vprintf receives a printf format string and  a
								// va_list argument
	va_end(args);               // let the C environment know we are finished with the
								// va_list argument
	printf("\n\tEncountered in file %s\n", __FILE__);  // this 2nd arg is filled in by
								// the pre-compiler
	exit(ERR_EXIT);
}
