#include "model/dijkstra.h"

Dijkstra::Dijkstra(const Graph &graph): graph(graph)
{

}

Dijkstra::~Dijkstra()
{

}

void Dijkstra::calculateWay(TrafficParticipant *object)
{   //TODO
    NameOfVertex source = object -> start_point, dest = object -> target_point;   //get source & destination of point
    Vertex tmp = graph.getVertex(source);
    Vertex destVertex = graph.getVertex(dest);  //finding a destination vertex
    while(tmp != destVertex || tmp != graph.end())
    {   //run dijkstra
        calculateWeightForEdge(tmp);
        tmp = selectLeastVertix();
    }
}

void Dijkstra::calculateWeightForEdge(Vertex &ver)
{
    //TODO obliczamy ile kosztuje przejscie do kazdego wierzcholka polaczonego krawedzia
}

Vertex Dijkstra::selectLeastVertix()
{

    //TODO wybieramy najmniejszy z posrod nieodwiedzony grafow
    //return tmp;
}
