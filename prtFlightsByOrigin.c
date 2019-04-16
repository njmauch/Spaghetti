
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"


void prtFlightsByOrigin(Graph graph)
{
    EdgeNode *e;
    int iVertices;
    int iNumVertices; 
    int bFirst=TRUE;
    
    
    
    printf("%3s %3s %3s %3s %4s %5s \n", "Apt", "F#", "Dest", "Dep", "Arr", "Dur");
    

    
    for(iVertices=0; iVertices <=graph->iNumVertices; iVertices++)
        if(graph->vertexM[iVertices].successorList !=NULL){
        
            for(e=graph->vertexM[iVertices].successorList;e->pNextEdge !=NULL;
            e=e->pNextEdge){
        
            
            Flight flight=e->flight;
            

            int iArrivalTime=(flight.iDepTm2400 + flight.iDurationMins) - flight.iZoneChange ;
            if(bFirst==TRUE)
            {
                printf("%3s %3s %3s %5d %4d %4d \n", graph->vertexM[iVertices].szAirport, flight.szFlightNr, flight.szDest, flight.iDepTm2400, 
                        iArrivalTime, flight. iDurationMins);
                        bFirst==FALSE;
            }
            else
            {
                printf("\t %3s %3s %3d %3d %3d \n", flight.szFlightNr, flight.szDest, flight.iDepTm2400,
                        iArrivalTime, flight.iDurationMins);

            }
        }
    }
}
    
   

    