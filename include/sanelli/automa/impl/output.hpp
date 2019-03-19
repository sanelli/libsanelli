#pragma once

#include <string>
#include <memory>
#include <sstream>

#include <sanelli/automa/impl/auotmaton.hpp>

namespace sanelli::automa
{

template <typename TValue, typename TState>
std::string to_graphziv(std::shared_ptr<automaton<TValue, TState>> atm)
{
   std::stringstream stream;

   stream << "digraph { " << std::endl;
   stream << "rankdir = LR " << std::endl;

   for (TState state = 1; state <= atm->get_number_of_states(); ++state)
   {
      if (!atm->has_state(state))
         continue;
      auto shape = (atm->get_initial_state() == state) ? "diamond"
                                                       : (atm->is_final_state(state) ? "doublecircle"
                                                                                     : "circle");
      stream << "node [ label = \"" << std::to_string(state) << "\", shape = " << shape << "]; " << std::to_string(state) << ";" << std::endl;
   }
   for (TState state = 1; state <= atm->get_number_of_states(); ++state)
   {
      if (!atm->has_state(state))
         continue;
      auto edges = atm->get_edges(state);
      for (auto itEdge = edges.first; itEdge != edges.second; ++itEdge)
      {
         auto edge = (*itEdge).second;
         stream << std::to_string(state) << " -> " << std::to_string(edge.second);
         if (edge.first != atm->epsilon())
            stream << " [label = \"" << edge.first << "\"]";
         stream << std::endl;
      }
   }

   stream << "}" << std::endl;

   return stream.str();
}

} // namespace sanelli::automa