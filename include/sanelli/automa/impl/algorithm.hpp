#pragma once

#include <array>
#include <memory>
#include <utility>
#include <set>
#include <algorithm>
#include <cmath>
#include <sanelli/automa/impl/automaton.hpp>
#include <sanelli/automa/impl/exception.hpp>
#include <sanelli/debug/debug.hpp>

#include <iostream>

namespace sanelli
{

namespace impl
{
template <typename TValue, typename TState = unsigned int>
TState join(std::shared_ptr<automaton<TValue, TState>> result,
            TState junction_state,
            std::shared_ptr<automaton<TValue, TState>> atm,
            bool keep_final_states = true)
{
   // Add N-1 states from the right state
   // (-1 because we do not need to add the initial state from right
   // because it will be the same as the final state of left automaton)

   auto delta = result->get_number_of_states();
   auto right_initial = atm->get_initial_state();

   result->add_states(atm->get_number_of_states() - 1);

   // Create a lmabda function that given the right state ID return the result state ID
   auto convert_state = [delta, junction_state, right_initial](TState rs) -> TState {
      if (rs == right_initial)
         return junction_state;
      return delta + rs - 1;
   };

   TState last_final_state = result->zero_state();

   // For each right state add the corresponding edges to result automaton
   for (auto right_state = atm->zero_state() + 1; right_state <= atm->get_number_of_states(); ++right_state)
   {
      if (!atm->has_state(right_state))
         continue;
      auto result_state = convert_state(right_state);

      if (atm->is_final_state(right_state))
      {
         last_final_state = result_state;
         if (keep_final_states)
            result->set_final_state(result_state);
      }
      auto right_edges = atm->get_edges(right_state);
      for (auto itEdge = right_edges.first; itEdge != right_edges.second; ++itEdge)
      {
         auto edge = *itEdge;
         auto value = edge.second.first;
         auto target_state = convert_state(edge.second.second);
         // No need to check if edge has been added already
         // If it was then the right automa was malformed
         result->add_edge(result_state, value, target_state);
      }
   }

   return last_final_state;
}
} // namespace impl

/**
 * @brief 
 * 
 * @tparam TValue 
 * @tparam int 
 * @param left 
 * @param right 
 * @return std::shared_ptr<automaton<TValue, TState>> 
 */
template <typename TValue, typename TState = unsigned int>
std::shared_ptr<automaton<TValue, TState>> operator&(std::shared_ptr<automaton<TValue, TState>> left, std::shared_ptr<automaton<TValue, TState>> right)
{
   if (left->get_number_of_final_states() != 1)
      throw automa_error("left automaton must contain exactly one final state");

   // Create a copy of the left state and strip the final_state flag
   // from the unique final state from the resulting automaton
   auto result = left->copy();
   auto junction_state = left->get_unique_final_state();
   result->remove_final_state(junction_state);

   // Join!
   impl::join(result, junction_state, right);

   // Done!
   return result;
}

template <typename TValue, typename TState = unsigned int>
std::shared_ptr<automaton<TValue, TState>> operator|(std::shared_ptr<automaton<TValue, TState>> left, std::shared_ptr<automaton<TValue, TState>> right)
{
   if (left->get_number_of_final_states() != 1)
      throw automa_error("left automaton must contain exactly one final state");
   if (right->get_number_of_final_states() != 1)
      throw automa_error("right automaton must contain exactly one final state");

   auto result = automaton<TValue, TState>::make();
   auto initial_state = result->add_state();
   result->set_initial_state(initial_state);
   auto final_state = result->add_state();
   result->set_final_state(final_state);

   // Add the left automaton
   auto begin_left = result->add_state();
   result->add_edge(initial_state, result->epsilon(), begin_left);
   auto end_left = impl::join(result, begin_left, left, false);
   result->add_edge(end_left, result->epsilon(), final_state);

   // Add right automaton
   auto begin_right = result->add_state();
   result->add_edge(initial_state, result->epsilon(), begin_right);
   auto end_right = impl::join(result, begin_right, right, false);
   result->add_edge(end_right, result->epsilon(), final_state);

   return result;
}

template <typename TValue, typename TState = unsigned int>
std::shared_ptr<automaton<TValue, TState>> operator*(std::shared_ptr<automaton<TValue, TState>> other)
{
   if (other->get_number_of_final_states() != 1)
      throw automa_error("automaton must contain exactly one final state");
   auto atm = other->copy();
   // Need to check the edge is not present because user could apply star operator twice
   if (!atm->has_edge(atm->get_initial_state(), atm->epsilon(), atm->get_unique_final_state()))
      atm->add_edge(atm->get_initial_state(), atm->epsilon(), atm->get_unique_final_state());

   // Need to add the edge back also in order to be able to handle repetition
   if (!atm->has_edge(atm->get_unique_final_state(), atm->epsilon(), atm->get_initial_state()))
      atm->add_edge(atm->get_unique_final_state(), atm->epsilon(), atm->get_initial_state());

   return atm;
}

template <typename TValue, typename TState = unsigned int>
std::shared_ptr<automaton<TValue, TState>> operator+(std::shared_ptr<automaton<TValue, TState>> other)
{
   auto left = other->copy();
   auto right = sanelli::operator*(other);
   return left & right;
}

/**
 * @brief Given an iterator over a sequence of values create a new automaton
 * having two state (initial and final) and an edge for each of the values
 * in the sequence.
 * 
 * @tparam TValue 
 * @tparam TState 
 * @tparam TIterator 
 * @param first 
 * @param last 
 * @return std::shared_ptr<automaton<TValue, TState>> 
 */
template <typename TValue, typename TState, typename TIterator>
std::shared_ptr<automaton<TValue, TState>> create_selection_automaton(TIterator first, TIterator last)
{
   auto atm = automaton<TValue, TState>::make();

   auto initial_state = atm->add_state();
   atm->set_initial_state(initial_state);

   auto final_state = atm->add_state();
   atm->set_final_state(final_state);

   for (auto it = first; it != last; ++it)
      atm->add_edge(initial_state, *it, final_state);

   return atm;
}

/**
 * @brief Create a new automaton with two state (initial and final) and with a single edge
 * between them having as value the value passed as parameter
 * 
 * @tparam TValue 
 * @tparam TState 
 * @param value 
 * @return std::shared_ptr<automaton<TValue, TState>> 
 */
template <typename TValue, typename TState = unsigned int>
std::shared_ptr<automaton<TValue, TState>> create_single_value(TValue value)
{
   std::array<TValue, 1> values = {value};
   return create_selection_automaton<TValue, TState>(values.begin(), values.end());
}

/**
 * @brief Create a determinist version of automaton passed as input parameter
 * 
 * @tparam TValue 
 * @tparam TState 
 * @return std::shared_ptr<automaton<TValue, TState>> 
 */
template <typename TValue, typename TState = unsigned int>
std::shared_ptr<automaton<TValue, TState>> make_deterministic(std::shared_ptr<automaton<TValue, TState>>)
{
   // TODO: Implement me
   return nullptr;
}

namespace impl
{

template <typename TValue, typename TState = unsigned int>
void close_states(const std::shared_ptr<automaton<TValue, TState>> atm, std::set<TState> &states)
{
   for (auto state = states.begin(); state != states.end(); ++state)
   {
      auto edges = atm->get_edges(*state);
      for (auto itEdge = edges.first; itEdge != edges.second; ++itEdge)
      {
         auto edge = (*itEdge).second;
         if (edge.first == atm->epsilon())
            states.insert(edge.second);
      }
   }
}

template <typename TValue, typename TIterator, typename TState = unsigned int>
std::pair<TState, TIterator> run_non_deterministic(const std::shared_ptr<automaton<TValue, TState>> atm, TIterator first, TIterator last)
{
   std::set<TState> states;
   states.insert(atm->get_initial_state());
   auto it = first;

   close_states(atm, states);

   // For each input element
   for (; it != last; ++it)
   {
      // No more states to investigate
      if (states.size() == 0)
         break;

      // Get all the possible
      std::set<TState> new_states;
      for (auto state = states.begin(); state != states.end(); ++state)
      {
         auto edges = atm->get_edges(*state);
         bool has_following_edge = false;
         for (auto itEdge = edges.first; itEdge != edges.second; ++itEdge)
         {
            auto edge = (*itEdge).second;
            if (edge.first == *it)
            {
               new_states.insert(edge.second);
               has_following_edge = true;
            }
         }
      }

      states = new_states;
      close_states(atm, states);
   }

   // Compute the final state if any
   auto final_state_it = std::find_if(states.begin(), states.end(), [&atm](TState s) -> bool { return atm->is_final_state(s); });
   auto final_state = final_state_it != states.end() ? *final_state_it : atm->zero_state();
   return std::make_pair(final_state, it);
}

template <typename TValue, typename TIterator, typename TState = unsigned int>
std::pair<TState, TIterator> run_deterministic(const std::shared_ptr<automaton<TValue, TState>> atm, TIterator first, TIterator last)
{
   // TODO: implement me
   return nullptr;
}

} // namespace impl

template <typename TValue, typename TIterator, typename TState = unsigned int>
std::pair<TState, TIterator> run_automaton(const std::shared_ptr<automaton<TValue, TState>> atm, TIterator first, TIterator last)
{
   return impl::run_non_deterministic(atm, first, last);
}

} // namespace sanelli