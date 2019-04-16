/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "cs2123p5.h"

void prtFlightsByDest(Graph graph)
{
    EdgeNode *e;
    int iVertices;
    int iNumVertices; 
    
    
    printf("%3s %3s %3s %3s %3s %3s \n", "Apt", "Orig", "Fl", "Dep", "Arr", "Dur");
    

    
    for(iVertices=0; iVertices <=graph->iNumVertices; iVertices++)
        if(graph->vertexM[iVertices].predecessorList!=NULL)
        {
            for(e=graph->vertexM[iVertices].predecessorList;e->pNextEdge !=NULL;
            e=e->pNextEdge)
            {
                Flight flight=e->flight;
                int bFirst=TRUE;
        
                int iArrivalTime=(flight.iDepTm2400 + flight.iDurationMins)+ flight.iZoneChange ;
                if(bFirst)
                {
                    printf("%3s %3s %3s %3d %3d %3d \n", flight.szAirport, flight.szOrigin, flight.szFlightNr, flight.iDepTm2400,
                            iArrivalTime, flight.iDurationMins);
                            bFirst=FALSE;
                }
                else
                {
                    printf("%3s %3s %3s %3d %3d %3d \n", flight.szAirport, flight.szOrigin, flight.szFlightNr, flight.iDepTm2400,
                            iArrivalTime, flight.iDurationMins);
            
                }
            }
        } 
    }