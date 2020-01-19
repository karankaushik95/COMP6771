#ifndef ASSIGNMENTS_DG_GRAPH_H_
#define ASSIGNMENTS_DG_GRAPH_H_

#include <algorithm>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace gdwg {

template <typename N, typename E>
class Graph {
 public:
  // Comparison function for map of nodes
  struct mapCompare {
    bool operator()(const std::unique_ptr<N>& lhs, const std::unique_ptr<N>& rhs) const {
      return *lhs < *rhs;
    }
  };

  // Comparison function for set of edges
  struct setCompare {
    bool operator()(const std::unique_ptr<std::tuple<N&, E>>& lhs,
                    const std::unique_ptr<std::tuple<N&, E>>& rhs) const {
      return (std::get<0>(*lhs) < std::get<0>(*rhs)) ||
             (std::get<0>(*lhs) == std::get<0>(*rhs) && std::get<1>(*lhs) < std::get<1>(*rhs));
    }
  };

  // Edge type declaration
  using edge = std::set<std::unique_ptr<std::tuple<N&, E>>, setCompare>;

  // Custom iterator
  class const_iterator {
    // typename std::tuple<N,N,E>::iterator current;
    // typename std::tuple<N,N,E>::iterator end;
   public:
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = std::tuple<N, N, E>;
    using reference = std::tuple<const N&, const N&, const E&>;
    using pointer = std::tuple<N, N, E>*;
    using difference_type = int;

    reference operator*();
    pointer operator->() const { return &(operator*()); }
    const_iterator& operator++();
    const const_iterator operator++(int) {
      auto const copy{*this};
      ++(*this);
      return copy;
    }
    const_iterator& operator--();
    const const_iterator operator--(int) {
      auto copy{*this};
      --(*this);
      return copy;
    }
    friend bool operator==(const_iterator lhs, const_iterator rhs) {
      if (lhs.key_ == lhs.end_ || rhs.key_ == rhs.end_) {
        return (lhs.key_ == rhs.key_);
      }
      return (lhs.key_ == rhs.key_) && (lhs.value_ == rhs.value_);
    }
    friend bool operator!=(const_iterator lhs, const_iterator rhs) { return !(lhs == rhs); }

   private:
    typename std::map<std::unique_ptr<N>, edge, mapCompare>::const_iterator key_;
    typename std::map<std::unique_ptr<N>, edge, mapCompare>::const_iterator begin_;
    typename std::map<std::unique_ptr<N>, edge, mapCompare>::const_iterator end_;
    typename edge::const_iterator value_;

    friend class Graph;

    // Iterator constructors
    const_iterator(const decltype(key_)& key,
                   const decltype(begin_)& begin,
                   const decltype(end_)& end,
                   const decltype(value_)& value)
      : key_{key}, begin_{begin}, end_{end}, value_{value} {}
    const_iterator(const decltype(key_)& key, const decltype(begin_)& begin)
      : key_{key}, begin_{begin}, end_{key} {}
  };

  // Iterator methods
  const_iterator begin() const;
  const_iterator end() const;
  const_iterator find(const N& src, const N& dst, const E& w);
  const_iterator erase(const_iterator it);
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Reverse iterators
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;
  const_reverse_iterator rbegin() const { return crbegin(); }
  const_reverse_iterator rend() const { return crend(); }
  const_reverse_iterator crbegin() const { return const_reverse_iterator{cend()}; }
  const_reverse_iterator crend() const { return const_reverse_iterator{cbegin()}; }

  // Constructors
  Graph();
  Graph(typename std::vector<N>::const_iterator, typename std::vector<N>::const_iterator);
  Graph(const Graph<N, E>&);
  Graph(typename std::vector<std::tuple<N, N, E>>::const_iterator,
        typename std::vector<std::tuple<N, N, E>>::const_iterator);
  Graph(std::initializer_list<N>);
  Graph(Graph<N, E>&&) noexcept;
  // Destructors
  ~Graph<N, E>() noexcept;
  // Operators
  Graph& operator=(const gdwg::Graph<N, E>&);
  Graph& operator=(gdwg::Graph<N, E>&&) noexcept;
  // Methods
  bool InsertNode(const N& val);
  bool InsertEdge(const N& src, const N& dst, const E& w);
  bool DeleteNode(const N& val);
  bool Replace(const N& oldData, const N& newData);
  void MergeReplace(const N& oldData, const N& newData);
  void Clear();
  bool IsNode(const N& val);
  bool IsConnected(const N& src, const N& dst);
  std::vector<N> GetNodes();
  std::vector<N> GetConnected(const N& src);
  std::vector<E> GetWeights(const N& src, const N& dst);
  bool erase(const N& src, const N& dst, const E& w);

  // Friends
  friend class const_iterator;
  friend std::ostream& operator<<(std::ostream& os, const Graph<N, E>& source) {
    for (auto it = source.graph_.begin(); it != source.graph_.end(); ++it) {
      std::cout << *(it->first) << " (\n";
      for (auto jt = it->second.begin(); jt != it->second.end(); ++jt) {
        // first * dereferences iterator, second * dereferences unique_ptr
        std::cout << "\t" << std::get<0>(*(*jt)) << " | " << std::get<1>(*(*jt)) << "\n";
      }
      std::cout << ")\n";
    }

    return os;
  }

  friend bool operator==(const gdwg::Graph<N, E>& lhs, const gdwg::Graph<N, E>& rhs) {
    auto first_iterator = lhs.graph_.begin();
    auto second_iterator = rhs.graph_.begin();

    while (first_iterator != lhs.graph_.end() && second_iterator != rhs.graph_.end()) {
      if (*(first_iterator->first) != *(second_iterator->first)) {
        return false;
      }

      auto first_set = first_iterator->second.begin();
      auto second_set = second_iterator->second.begin();

      while (first_set != first_iterator->second.end() &&
             second_set != second_iterator->second.end()) {
        if (*(*first_set) != *(*second_set)) {
          return false;
        }
        first_set++;
        second_set++;
      }
      if (first_set != first_iterator->second.end() ||
          second_set != second_iterator->second.end()) {
        return false;
      }
      first_iterator++;
      second_iterator++;
    }
    return first_iterator == lhs.graph_.end() && second_iterator == rhs.graph_.end();
  }

  friend bool operator!=(const gdwg::Graph<N, E>& lhs, const gdwg::Graph<N, E>& rhs) {
    return !(lhs == rhs);
  }

 private:
  std::map<std::unique_ptr<N>, edge, mapCompare> graph_;
};

}  // namespace gdwg

#endif  // ASSIGNMENTS_DG_GRAPH_H_

#include "assignments/dg/graph.tpp"
