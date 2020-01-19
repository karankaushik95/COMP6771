#ifndef ASSIGNMENTS_DG_GRAPH_TPP_
#define ASSIGNMENTS_DG_GRAPH_TPP_

#include "assignments/dg/graph.h"

#include <algorithm>
#include <memory>
#include <utility>

// Begin constructors
template <typename N, typename E>
gdwg::Graph<N, E>::Graph() = default;

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<N>::const_iterator start,
                         typename std::vector<N>::const_iterator end) {
  while (start != end) {
    InsertNode(*start);
    start++;
  }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(const gdwg::Graph<N, E>& source) {
  // Copy construct nodes
  for (auto it = source.graph_.begin(); it != source.graph_.end(); it++) {
    graph_[std::make_unique<N>(*(it->first))] = edge();
  }

  // Copy construct edges
  for (auto it = source.graph_.begin(); it != source.graph_.end(); it++) {
    if (it->second.size() != 0) {
      for (auto iter = it->second.begin(); iter != it->second.end(); iter++) {
        N node = std::get<0>(*(*iter));

        // Find the destination node to be connected to
        auto search = find_if(graph_.begin(), graph_.end(),
                              [&node](auto const& pair) { return *pair.first == node; });
        E value = std::get<1>(*(*iter));
        graph_[std::make_unique<N>(*(it->first))].emplace(
            std::make_unique<std::tuple<N&, E>>(std::forward_as_tuple(*search->first, value)));
      }
    }
  }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator start,
                         typename std::vector<std::tuple<N, N, E>>::const_iterator end) {
  while (start != end) {
    N source = std::get<0>(*start);
    N destination = std::get<1>(*start);
    E weight = std::get<2>(*start);
    if (!IsNode(source))
      InsertNode(source);
    if (!IsNode(destination))
      InsertNode(destination);
    InsertEdge(source, destination, weight);
    start++;
  }
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(std::initializer_list<N> input_list) {
  for (auto it = input_list.begin(); it != input_list.end(); it++)
    InsertNode(*it);
}

template <typename N, typename E>
gdwg::Graph<N, E>::Graph(gdwg::Graph<N, E>&& source) noexcept {
  for (auto it = source.graph_.begin(); it != source.graph_.end(); it++) {
    graph_[std::make_unique<N>(*(it->first))] = edge();
  }

  // Copy construct edges
  for (auto it = source.graph_.begin(); it != source.graph_.end(); it++) {
    if (it->second.size() != 0) {
      for (auto iter = it->second.begin(); iter != it->second.end(); iter++) {
        N node = std::get<0>(*(*iter));

        // Find the destination node to be connected to
        auto search = find_if(graph_.begin(), graph_.end(),
                              [&node](auto const& pair) { return *pair.first == node; });
        E value = std::get<1>(*(*iter));
        graph_[std::make_unique<N>(*(it->first))].emplace(
            std::make_unique<std::tuple<N&, E>>(std::forward_as_tuple(*search->first, value)));
      }
    }
  }

  source.graph_.clear();
}
// end constructors

// destructor

template <typename N, typename E>
gdwg::Graph<N, E>::~Graph<N, E>() noexcept = default;

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertNode(const N& val) {
  auto search = find_if(graph_.begin(), graph_.end(),
                        [&val](auto const& pair) { return *pair.first == val; });

  if (search != graph_.end()) {
    return false;
  } else {
    graph_[std::make_unique<N>(val)] = edge();
    return true;
  }
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::InsertEdge(const N& src, const N& dst, const E& w) {
  try {
    // Search graph for source node
    auto search_src = find_if(graph_.begin(), graph_.end(),
                              [&src](auto const& pair) { return *pair.first == src; });
    // Search graph for dst node
    auto search_dst = find_if(graph_.begin(), graph_.end(),
                              [&dst](auto const& pair) { return *pair.first == dst; });
    if (search_src == graph_.end() || search_dst == graph_.end()) {
      throw std::runtime_error(
          "Cannot call Graph::InsertEdge when either src or dst node does not exist");
    }

    // Search source node edge list for dst node and w edge weight
    auto search_vec =
        find_if(search_src->second.begin(), search_src->second.end(), [&dst, &w](auto const& pair) {
          return (std::get<0>(*pair) == dst && std::get<1>(*pair) == w);
        });

    // If edge not found, create new one
    if (search_vec == search_src->second.end()) {
      search_src->second.emplace(
          std::make_unique<std::tuple<N&, E>>(std::forward_as_tuple(*search_dst->first, w)));
      return true;
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }
  return false;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::DeleteNode(const N& val) {
  auto search = find_if(graph_.begin(), graph_.end(),
                        [&val](auto const& pair) { return (*pair.first == val); });
  if (search == graph_.end()) {
    return false;
  } else {
    // Delete edges connected to target node
    for (auto it = graph_.begin(); it != graph_.end(); ++it) {
      for (auto jt = it->second.begin(); jt != it->second.end();) {
        if (std::get<0>(*(*jt)) == *search->first) {
          it->second.erase(jt);
        } else {
          ++jt;
        }
      }
    }

    // Delete node
    graph_.erase(search);
    return true;
  }
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::Replace(const N& oldData, const N& newData) {
  try {
    auto search = find_if(graph_.begin(), graph_.end(),
                          [&oldData](auto const& pair) { return (*pair.first == oldData); });
    if (search == graph_.end()) {
      throw std::runtime_error("Cannot call Graph::Replace on a node that doesn't exist");
    }

    auto search_new = find_if(graph_.begin(), graph_.end(),
                              [&newData](auto const& pair) { return (*pair.first == newData); });
    if (search_new == graph_.end()) {
      *search->first = newData;
      return true;
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }
  return false;
}

template <typename N, typename E>
void gdwg::Graph<N, E>::MergeReplace(const N& oldData, const N& newData) {
  try {
    // Search graph for old node
    auto search_old = find_if(graph_.begin(), graph_.end(),
                              [&oldData](auto const& pair) { return *pair.first == oldData; });
    // Search graph for new node
    auto search_new = find_if(graph_.begin(), graph_.end(),
                              [&newData](auto const& pair) { return *pair.first == newData; });
    if (search_old == graph_.end() || search_new == graph_.end()) {
      throw std::runtime_error(
          "Cannot call Graph::MergeReplace on old or new data if they don't exist in the graph");
    }

    // Merge old node edges to new
    search_new->second.merge(search_old->second);
    search_old->second.clear();

    // Redirect incoming edges from old node to new
    for (auto it = graph_.begin(); it != graph_.end(); ++it) {
      for (auto iter = it->second.begin(); iter != it->second.end(); ++iter) {
        if (std::get<0>(*(*iter)) == oldData) {
          it->second.emplace(std::make_unique<std::tuple<N&, E>>(
              std::forward_as_tuple(*search_new->first, std::get<1>(*(*iter)))));
          it->second.erase(iter);
        }
      }
    }

    // Delete old node
    graph_.erase(search_old);
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }
}

template <typename N, typename E>
void gdwg::Graph<N, E>::Clear() {
  graph_.clear();
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsNode(const N& val) {
  auto search = find_if(graph_.begin(), graph_.end(),
                        [&val](auto const& pair) { return (*pair.first == val); });
  if (search == graph_.end()) {
    return false;
  }
  return true;
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::IsConnected(const N& src, const N& dst) {
  try {
    // Search graph for source node
    auto search_src = find_if(graph_.begin(), graph_.end(),
                              [&src](auto const& pair) { return *pair.first == src; });
    // Search graph for dst node
    auto search_dst = find_if(graph_.begin(), graph_.end(),
                              [&dst](auto const& pair) { return *pair.first == dst; });
    if (search_src == graph_.end() || search_dst == graph_.end()) {
      throw std::runtime_error(
          "Cannot call Graph::IsConnected if src or dst node don't exist in the graph");
    }

    // Search source node edge list for dst node
    auto search_vec = find_if(search_src->second.begin(), search_src->second.end(),
                              [&dst](auto const& pair) { return (std::get<0>(*pair) == dst); });

    // If edge not found return false
    if (search_vec == search_src->second.end()) {
      return false;
    }
  } catch (const std::runtime_error& e) {
    std::cout << e.what() << '\n';
  }
  return true;
}

template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetNodes() {
  std::vector<N> vec;
  for (auto it = graph_.begin(); it != graph_.end(); ++it) {
    vec.emplace_back(*it->first);
  }
  return vec;
}

template <typename N, typename E>
std::vector<N> gdwg::Graph<N, E>::GetConnected(const N& src) {
  std::vector<N> vec;
  try {
    // Search graph for source node
    auto search_src = find_if(graph_.begin(), graph_.end(),
                              [&src](auto const& pair) { return *pair.first == src; });
    if (search_src == graph_.end()) {
      throw std::out_of_range("Cannot call Graph::GetConnected if src doesn't exist in the graph");
    }

    for (auto it = search_src->second.begin(); it != search_src->second.end(); ++it) {
      vec.emplace_back(std::get<0>(*(*it)));
    }
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << '\n';
  }
  return vec;
}

template <typename N, typename E>
std::vector<E> gdwg::Graph<N, E>::GetWeights(const N& src, const N& dst) {
  std::vector<E> vec;
  try {
    // Search graph for source node
    auto search_src = find_if(graph_.begin(), graph_.end(),
                              [&src](auto const& pair) { return *pair.first == src; });
    // Search graph for dst node
    auto search_dst = find_if(graph_.begin(), graph_.end(),
                              [&dst](auto const& pair) { return *pair.first == dst; });
    if (search_src == graph_.end() || search_dst == graph_.end()) {
      throw std::out_of_range(
          "Cannot call Graph::GetWeights if src or dst node don't exist in the graph");
    }

    for (auto it = search_src->second.begin(); it != search_src->second.end(); ++it) {
      if (std::get<0>(*(*it)) == dst) {
        vec.emplace_back(std::get<1>(*(*it)));
      }
    }
  } catch (const std::out_of_range& e) {
    std::cout << e.what() << '\n';
  }
  return vec;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator
gdwg::Graph<N, E>::find(const N& src, const N& dst, const E& w) {
  // Search graph for source node
  auto search_src = find_if(graph_.begin(), graph_.end(),
                            [&src](auto const& pair) { return *pair.first == src; });
  // Search source node edge list for dst node
  auto search_vec =
      find_if(search_src->second.begin(), search_src->second.end(), [&dst, &w](auto const& pair) {
        return ((std::get<0>(*pair) == dst) && (std::get<1>(*pair) == w));
      });

  // Return end if edge or node not found
  if (search_src == graph_.end() || search_vec == search_src->second.end()) {
    return end();
  }

  // Return iterator to edge
  return const_iterator{search_src, graph_.cbegin(), graph_.cend(), search_vec};
}

template <typename N, typename E>
bool gdwg::Graph<N, E>::erase(const N& src, const N& dst, const E& w) {
  // Search graph for source node
  auto search_src = find_if(graph_.begin(), graph_.end(),
                            [&src](auto const& pair) { return *pair.first == src; });
  // Search source node edge list for dst node
  auto search_vec =
      find_if(search_src->second.begin(), search_src->second.end(), [&dst, &w](auto const& pair) {
        return ((std::get<0>(*pair) == dst) && (std::get<1>(*pair) == w));
      });

  // Return false if edge or node not found
  if (search_src == graph_.end() || search_vec == search_src->second.end()) {
    return false;
  }
  search_src->second.erase(*search_vec);
  return true;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::erase(const_iterator it) {
  auto jt = it;
  jt++;
  if (erase(std::get<0>(*it), std::get<1>(*it), std::get<2>(*it))) {
    return jt;
  }
  return end();
}

template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(const gdwg::Graph<N, E>& source) {
  this->graph_.clear();

  // Copy construct nodes
  for (auto it = source.graph_.begin(); it != source.graph_.end(); it++) {
    graph_[std::make_unique<N>(*(it->first))] = edge();
  }

  // Copy construct edges
  for (auto it = source.graph_.begin(); it != source.graph_.end(); it++) {
    if (it->second.size() != 0) {
      for (auto iter = it->second.begin(); iter != it->second.end(); iter++) {
        N node = std::get<0>(*(*iter));

        // Find the destination node to be connected to
        auto search = find_if(graph_.begin(), graph_.end(),
                              [&node](auto const& pair) { return *pair.first == node; });
        E value = std::get<1>(*(*iter));
        graph_[std::make_unique<N>(*(it->first))].emplace(
            std::make_unique<std::tuple<N&, E>>(std::forward_as_tuple(*search->first, value)));
      }
    }
  }
  return *this;
}
template <typename N, typename E>
gdwg::Graph<N, E>& gdwg::Graph<N, E>::operator=(gdwg::Graph<N, E>&& source) noexcept {
  *this = source;
  source.graph_.clear();

  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator& gdwg::Graph<N, E>::const_iterator::operator++() {
  if (key_ != end_) {
    value_++;
    if (value_ == (key_->second).cend()) {
      key_++;
      while (key_ != end_) {
        if (!key_->second.empty()) {
          value_ = key_->second.begin();
          return *this;
        }
        key_++;
      }
    }
  }
  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator& gdwg::Graph<N, E>::const_iterator::operator--() {
  if (key_ != begin_) {
    if (key_ == end_ || value_ == (key_->second).cbegin()) {
      while (key_ != begin_) {
        key_--;
        if (!key_->second.empty()) {
          value_ = key_->second.end();
          value_--;
          return *this;
        }
      }
    } else {
      value_--;
    }
  }

  return *this;
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator::reference gdwg::Graph<N, E>::const_iterator::
operator*() {
  const N& node1 = *key_->first;
  const N& node2 = std::get<0>(*(*value_));
  const E& edge = std::get<1>(*(*value_));

  return {node1, node2, edge};
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cbegin() const {
  for (auto it = graph_.cbegin(); it != graph_.cend(); ++it) {
    if (!it->second.empty()) {
      return const_iterator{it, graph_.cbegin(), graph_.cend(), it->second.cbegin()};
    }
  }
  return end();
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::begin() const {
  return cbegin();
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::cend() const {
  return const_iterator{graph_.cend(), graph_.cbegin()};
}

template <typename N, typename E>
typename gdwg::Graph<N, E>::const_iterator gdwg::Graph<N, E>::end() const {
  return cend();
}

#endif
