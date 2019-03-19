#pragma once

#include <array>
#include <memory>
#include <sanelli/automa/impl/auotmaton.hpp>
#include <sanelli/automa/impl/exception.hpp>

namespace sanelli::automa
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
   result->add_states(atm->get_number_of_states() - 1);

   // Create a lmabda function that given the right state ID return the result state ID
   auto convert_state = [junction_state](TState rs) -> TState { return junction_state + rs - 1; };

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
std::shared_ptr<automaton<TValue, TState>> operator*(std::shared_ptr<automaton<TValue, TState>> left)
{
   return nullptr;
}

template <typename TValue, typename TState = unsigned int>
std::shared_ptr<automaton<TValue, TState>> operator+(std::shared_ptr<automaton<TValue, TState>> left)
{
   return nullptr;
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
   return nullptr;
}

} // namespace sanelli::automa