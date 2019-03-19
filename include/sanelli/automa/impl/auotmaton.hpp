#pragma once

#include <memory>
#include <map>
#include <utility>
#include <set>
#include <cstddef>
#include <algorithm>

#include <sanelli/automa/impl/exception.hpp>

namespace sanelli::automa
{
template <
    typename TValue,
    typename TState = unsigned int>
class automaton
{
   TState state_counter;
   std::multimap<TState, std::pair<TValue, TState>> map;
   TState initial_state;
   std::set<TState> final_states;

   automaton() : state_counter(0)
   {
      initial_state = zero_state();
   }

   inline void check_state_and_throw(TState state) const
   {
      if (state == zero_state())
      {
         throw automa_error("Invalid zero state for operation");
      }
      if (!has_state(state))
      {
         std::string message("State ");
         message += std::to_string(state);
         message += " does not exist.";
         throw automa_error(message);
      }
   }

 public:
   static std::shared_ptr<automaton<TValue, TState>> make()
   {
      return std::shared_ptr<automaton<TValue, TState>>(new automaton());
   }

  std::shared_ptr<automaton<TValue, TState>> copy() const
   {
      auto result = make();
      result->state_counter = state_counter;
      result->initial_state = initial_state;
      result->final_states = final_states;
      result->map = map;
      return result;
   }

   // Zeroes
   auto epsilon() const { return (TValue)0; }
   auto zero_state() const { return (TState)0; }

   // State management
   TState get_number_of_states() const { return state_counter; }
   auto add_state()
   {
      ++state_counter;
      return state_counter;
   }
   void add_states(int count) {
      state_counter += count;
   }
   bool has_state(TState state) const
   {
      return state != zero_state() && state <= state_counter;
   }
   void set_initial_state(TState initial_state)
   {
      check_state_and_throw(initial_state);
      this->initial_state = initial_state;
   }
   void set_final_state(TState final_state)
   {
      check_state_and_throw(final_state);
      final_states.insert(final_state);
   }
   void remove_final_state(TState final_state)
   {
      check_state_and_throw(final_state);
      if(final_states.size() < 1) throw automa_error("Automaton does not contain any state.");
      final_states.erase(final_state);
   }
   TState get_initial_state() const
   {
      check_state_and_throw(initial_state);
      return initial_state;
   }
   bool is_final_state(TState final_state) const
   {
      check_state_and_throw(final_state);
      return final_states.find(final_state) != final_states.end();
   }
   size_t get_number_of_final_states() const {
      return final_states.size();
   }
   TState get_unique_final_state() const {
      if(final_states.size() != 1) throw automa_error("Automaton must contain exactly one final state.");
      return *final_states.begin();
   }

   // Edge management
   auto get_edges(TState from) const
   {
      check_state_and_throw(from);
      return map.equal_range(from);
   }
   bool has_edge(TState from, TValue value, TState to) const
   {
      if (!has_state(from))
         return false;
      if (!has_state(to))
         return false;
      auto edges = get_edges(from);
      for (auto it = edges.first; it != edges.second; ++it)
      {
         auto edge = (*it).second;
         if (edge.first == value && edge.second == to)
            return true;
      }
      return false;
   }
   void add_edge(TState from, TValue value, TState to)
   {
      if (has_edge(from, value, to))
      {
         std::string message("An edge from state ");
         message += std::to_string(from);
         message += " to state ";
         message += std::to_string(to);
         message += " with value ";
         message += value;
         message += " has already been added.";
      }
      map.insert(std::make_pair(from,std::make_pair(value, to)));
   }
};

} // namespace sanelli::automa