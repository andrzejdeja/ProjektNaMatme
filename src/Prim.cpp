#include "Debug.hpp"
#include "Prim.h"

#include <string>

bool Prim::run(Graph& graph) {
    for (unsigned i = 0; i < graph.GraphRow(); i++) {
        LOG_debug("Prim iteration: " + std::to_string(i));
        unsigned id = Prim::getMinCostNodeID(graph);
        graph.GetNode(id).SetVisited();
        for (auto& const e : graph.GetNode(id).GetEdges()) {
            LOG_debug("Prim: Node: " + std::to_string(id) + " Edge: n:" + std::to_string(e.first) + " e:" + std::to_string(e.second));
            if (!graph.GetNode(e.first).WasVisited())
            {
                LOG_debug("Prim: Node: Edge wasn't visited");
                if (graph.GetNode(e.first).GetPrevCost() > graph.GetNode(id).GetPrevCost() + graph.GetEdge(e.second).GetCost())
                {
                    graph.GetNode(e.first).SetPrevID(id);
                    graph.GetNode(e.first).SetPrevCost(graph.GetNode(id).GetPrevCost() + graph.GetEdge(e.second).GetCost());
                    graph.GetNode(e.first).SetPrevEdgeID(e.second);
                    LOG_debug("Prim: Node: Edge chosen");
                }
            }
        }
        graph.printNodes();
    }
    for (unsigned i = 0; i < graph.GraphRow(); i++)
        if (graph.GetNode(i).GetPrevCost() == UINT32_MAX)
            return false;
        else
            if (!graph.GetNode(i).IsRoot())
                graph.GetEdge(graph.GetNode(i).GetPrevEdgeID()).SetMST();
    return true;
}

unsigned Prim::getMinCostNodeID(Graph& graph) {
    unsigned min = UINT32_MAX, id = 0;

    for (unsigned i = 0; i < graph.GraphRow(); i++) {
        if (!graph.GetNode(i).WasVisited() && !graph.GetNode(i).IsPrevCostWorse(min)) {
            min = graph.GetNode(i).GetPrevCost();
            id = i;
        }
    }
    return id;
}

std::vector<unsigned> Prim::getIDsOfEdgesNotInMST(Graph& graph) {
    std::vector<unsigned> tmp;
    for (unsigned i = 0; i < graph.GetNumberOfEdges(); i++)
        if (!graph.GetEdge(i).IsInMST())
            tmp.push_back(i);
    return tmp;
}

void Prim::printEdgesNotInMST(Graph& graph) {
    std::vector<unsigned> tmp = Prim::getIDsOfEdgesNotInMST(graph);
    if (tmp.empty()) {
        LOG_info("Nie znaleziono autostrad spelniajacych kryteria");
        return;
    }
    LOG_info("Znaleziono autostrady spelniajace kryteria:");
    for (auto& e : tmp) {
        LOG_info("Autostrada " + std::to_string(graph.GetEdge(e).GetID()) + " laczaca miasta " + graph.GetNodeName(graph.GetEdge(e).GetNodeID1()) + " i " + graph.GetNodeName(graph.GetEdge(e).GetNodeID2()) + " o dlugosci " + std::to_string(graph.GetEdge(e).GetCost())); //TODO: pls fix it :(
    }
}