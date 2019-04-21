/******************************************prtFlightsByOrigin**************************
 * Written By: Vedika Khanna
 void prtFlightsByOrigin(Graph graph)
Purpose:
    Print all flights from the graph in order by origin.
Parameters:
    O Graph graph       Graph used to track connections of flights/airports.
Notes:
    
Returns:
    Print Statement with all flights information (Airport, Flight Number, Destination,
 *  Departure time, Arrival Time, and Duration of flight in order by Origin.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"



   

    void prtFlightsByOrigin(Graph graph)
{
    EdgeNode *e;
    int iVertices; 
     
   
    
    printf(" %-3s %3s %2s %3s %4s %4s \n", "Apt", "F#", "Dest", "Dep", "Arr", "Dur");
    
   
    
for(iVertices=0; iVertices <graph->iNumVertices; iVertices++)

{       int bFirst=TRUE;
        if(graph->vertexM[iVertices].successorList ==NULL)
            {
                continue;
            }
        for(e=graph->vertexM[iVertices].successorList;e!=NULL; e=e->pNextEdge)
        {
          
            if (bFirst == TRUE)
            {
                printf(" %-3s %3s %3s %04d %04d %3d\n", graph->vertexM[iVertices].szAirport, e->flight.szFlightNr, e->flight.szDest,
                        e->flight.iDepTm2400, calcArr2400(e->flight.iDepTm2400, e->flight.iDurationMins, e->flight.iZoneChange), 
                        e->flight.iDurationMins);
                bFirst = FALSE;
            }
            else
            {
                printf(" %7s %3s %04d %04d %3d\n", e->flight.szFlightNr, e->flight.szDest,e->flight.iDepTm2400, 
                        calcArr2400(e->flight.iDepTm2400, e->flight.iDurationMins, e->flight.iZoneChange), 
                        e->flight.iDurationMins);
            }
            
        }
    }
}
