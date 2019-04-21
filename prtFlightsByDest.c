/*******************************prtFlightsByDest*************************************
 * Written By: Vedika Khanna 
 * 
 * void prtFlightsByDest(Graph graph)
Purpose:
    Print all flights from the graph in order by destination.
Parameters:
    O Graph graph       Graph used to track connections of flights/airports.
Notes:
    N/A
Returns:
    Print Statement with all flights information (Airport, Origin, Flight Number, 
 *  Departure time, Arrival Time, and Duration of flights in order by Destination.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

void prtFlightsByDest(Graph graph)
{
    EdgeNode *e;
    int iVertices; //i
     
   
    
    printf(" %-3s %3s %2s %3s %4s %4s \n", "Apt", "Orig", "Fl", "Dep", "Arr", "Dur");
    
    
    
    
for(iVertices=0; iVertices <graph->iNumVertices; iVertices++)

{       int bFirst=TRUE;
        if(graph->vertexM[iVertices].predecessorList ==NULL)
        {
            continue;
        }
        for(e=graph->vertexM[iVertices].predecessorList;e!=NULL; e=e->pNextEdge){
          
            if (bFirst == TRUE)
            {
                printf(" %-3s %3s %3s %04d %04d %3d\n", graph->vertexM[iVertices].szAirport, e->flight.szOrigin, e->flight.szFlightNr,
                        e->flight.iDepTm2400, calcArr2400(e->flight.iDepTm2400, e->flight.iDurationMins, e->flight.iZoneChange), 
                        e->flight.iDurationMins);
                bFirst = FALSE;
            }
            else
            {
                printf(" %7s %3s %04d %04d %3d\n", e->flight.szOrigin, e->flight.szFlightNr, e->flight.iDepTm2400, 
                        calcArr2400(e->flight.iDepTm2400, e->flight.iDurationMins, e->flight.iZoneChange), e->flight.iDurationMins);
            }
            
                }
            }
        } 
   
