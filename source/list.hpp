#ifndef BUW_LIST_HPP
#define BUW_LIST_HPP
#include <cassert>
#include <cstddef>  //ptrdiff_t
#include <iterator> //std::bidirectional_iterator_tag
#include <iostream>

#include <initializer_list>

template <typename T>
class List;

template <typename T>
struct ListNode {
  T         value = T{};
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
};


template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  // returns value pointed to by iterator
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    return node->value;
  } //call *it

  // returns value of an of an object pointed to by iterator
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    // using & to get the objects address that is pointed to by node
    // then using ->value to access the requested value, since &node is
    // still just an integer (address): so &node.value is NOT POSSIBLE
    return &node->value;
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    node = node->next;
    return *this;
  }
/*
  ListIterator<T>& operator--() {
    if (nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    node = node->prev;
    return *this;
  }
*/
  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }
    ListIterator<T> newIt = *this;
    node = node->next;
    return newIt;
  }

  // returns true if lhs and rhs iterators point to THE SAME
  // object/node
  bool operator==(ListIterator<T> const& x) const {
    if(x.node == node) {
      return true;
    }
    return false;
  } // call it: == it

  // returns true if lhs and rhs iterators point to DIFFERENT
  // objects/nodes
  bool operator!=(ListIterator<T> const& x) const {
    if(*this == x) {
      return false;
    }
    return true;
  } // call it: != it

  /* Advances Iterator */
  ListIterator<T> next() const {
    if (nullptr != node) {
      return ListIterator{node->next};
    } else {
      return ListIterator{nullptr};
    }
  }


  ListNode <T>* node = nullptr;
};



template <typename T>
class List {
  public:

    //friend declarations for testing the members   
    template <typename TEST_TYPE>
    friend size_t get_size(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_first_pointer(List<TEST_TYPE> const& list_to_test);
    template <typename TEST_TYPE>
    friend ListNode<TEST_TYPE>* get_last_pointer(List<TEST_TYPE> const& list_to_test);

    using value_type      = T;
    using pointer         = T*;
    using const_pointer   = T const*;
    using reference       = T&;
    using const_reference = T const&;
    using iterator        = ListIterator<T>;

    // Default constructor & initializer list constructor
    List(ListNode<T>* const& first, ListNode<T>* const& last): first_(first), last_(last) {}
    List() {}

    
    // Deep Copy Constructor
    // Returns w/o doing anything if the original list is empty.
    // Uses a temporary node 'tmp' to iterate over original list.
    List(List const& originalList) {
      if(originalList.first_ == nullptr) {
        return;
      }
      ListNode<T>* tmp = originalList.first_;
      //first_ = push_back(*originalList.first_);
      while(tmp != nullptr) {
        push_back(tmp->value);
        tmp = tmp->next;
      }
      delete tmp;
    }
    

    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.9)

    //TODO: Initializer-List Konstruktor (3.10 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    // Own swap function for class List
    // Uses std::swap to swap information about
    // size aswell as pointers to first and last
    // element with a given list.
    void swap(List& list) {
      std::swap(size_, list.size_);
      std::swap(first_, list.first_);
      std::swap(last_, list.last_);
    }

    // Unifying assignment operator
    // ° cont& was not used because rhs is gonna
    //   to be changed by swap.
    List& operator=(List rhs) {
      swap(rhs);
      return *this;
    }

    // Operator that compares two lists.
    // For equality, size (number of containing nodes)
    // has to be equal.
    // Further, every nodes that share the same index
    // have to contain the same value.
    bool operator==(List const& rhs) const
    {
      // if size is not equal, no further comparing
      // is necessary: returns false
      if(size_ == rhs.size_) {
        ListNode<T>* tempLhs = first_;
        ListNode<T>* tempRhs = rhs.first_;
        // could also be (tempRhs != nullptr), since both
        // need to be equal or it returns false anyway
        while(tempLhs != nullptr) {
          if(tempLhs->value == tempRhs->value) {
            tempLhs = tempLhs->next;
            tempRhs = tempRhs->next;
          }
          else {
            return false;
          }
        }
        return true;
      }
      return false;
    }

    // basically negates operator==
    bool operator!=(List const& rhs) const
    {
      if(*this == rhs) {
        return false;
      }
      else {
        return true;
      }
    }

    // Destructor of the list class
    ~List() {
      clear();
    }

    // returns iterator that points to first node in the list
    ListIterator<T> begin() {
      auto begin = first_;
      return {begin};
    }

    // returns iterator that points to nullptr
    ListIterator<T> end() {
      auto end = nullptr;
      return {end};
    }

    // Deletes all nodes in the list.
    void clear() {
      while(empty() == false) {
        pop_back();
      }
    }

/*
    
    //TODO: member function insert (Aufgabe 3.13)
    ListIterator<T> insert(ListNode<T> const& newNode, ListIterator<T> const& it) {
      if(begin() == nullptr) {
        return;
      }
      else if(begin() == end()) {
        push_front(newNode);
      }
      else if(it == end()) {
        push_back(newNode);
      }
      else {
        it->node->prev = newNode;
      }

      return it--
    }
  */
    /* ... */
    //TODO: member function erase (Aufgabe 3.14)

    /* ... */

    // Changes the prev and next pointers of every node so that
    // the last element becomes first and the first element
    // becomes last.
    // After hours of trying on my own, this explanation helped:
    // https://www.youtube.com/watch?v=uz6dimvl40Q
    void reverse() {
      if(first_ == nullptr) {
        return;
      }

      ListNode<T>* current = first_;
      ListNode<T>* temp = current->prev;

      while(current != nullptr) {
        // temp is needed to save current-> prev for swap
        temp = current->prev;
        // the node we are looking at changes prev to next
        // and next to prev
        current->prev = current->next;
        current->next = temp;
        // changing current node for the upcoming loop
        current = current->prev;
      }
      // last thing: changing the pointers of the list
      temp = last_;
      last_ = first_;
      first_ = temp;
    }


    // Adds a new ListNode with value = element
    // as first node of the list.
    void push_front(T const& element) {
      if(first_ == nullptr) {
        ListNode<T> *newNode = new ListNode<T>{element};
        first_ = newNode;
        last_ = newNode;
        size_++;
      }
      else {
        ListNode<T> *newNode = new ListNode<T>{element};
        newNode->next = first_;
        first_->prev = newNode;
        first_ = newNode;
        size_++;
      }
    }

    // Adds a new ListNode with value = element
    // as last node of the list.
    void push_back(T const& element) {
      if(first_ == nullptr) {
        ListNode<T>* newNode = new ListNode<T>{element};
        first_ = newNode;
        last_ = newNode;
        size_++;
      }
      else {
        ListNode<T>* newNode = new ListNode<T>{element};
        newNode->prev = last_;
        last_->next = newNode;
        last_ = newNode;
        size_++;
      }
    }

    // Removes first ListNode in the list.
    // Former second ListNode becomes first_.
    // If the removed ListNode was the only node,
    // first_ and last_ will then point to nullptr.
    void pop_front() {
      if(empty()) {
        throw "List is empty";
      }
      else if(first_ == last_) {
        delete first_;
        first_ = nullptr;
        last_ = nullptr;
        size_--;
      }
      else {
        first_ = first_->next;
        delete first_->prev;
        first_->prev = nullptr;
        size_--;
      }
    }

    // Removes last ListNode in the list.
    // Former second last node becomes last_.
    // If the removed node was the only node,
    // first_ and last_ will then point to nullptr.
    void pop_back() {
      if(empty()) {
        throw "List is empty";
      }
      else if(first_ == last_) {
        delete last_;
        first_ = nullptr;
        last_ = nullptr;
        size_--;
      }
      else {
        last_ = last_->prev;
        delete last_->next;
        last_->next = nullptr;
        size_--;
      }
    }

    // Returns value of first node in list.
    T& front() {
      if(empty()) {
        throw "List is empty";
      }
      else {
        return first_->value;
      }
    }

    // Returns value of last node in list.
    T& back() {
      if(empty()) {
        throw "List is empty";
      }
      else {
        return last_->value;
      }
    }

    // Returns
    //    true if empty
    //    false if not empty
    bool empty() const {
      if(size_ != 0){
        return false;
      }
      return true;
    };


    // Returns size variable of List object
    std::size_t size() const{ 
      return size_;
  };


  // list members
  private: 
    std::size_t size_ = 0;
    ListNode<T>* first_ = nullptr;
    ListNode<T>* last_ = nullptr;
};

// Uses the member function reverse() and the
// deep copy constructor to return a new list, which
// is a mirrored given list.
template<typename T>
List<T> reverse(List<T> const& originalList) {
  List<T> newList = new List<T>{originalList};
  newList.reverse();
  return newList;
  delete newList;
}

/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)


#endif // # define BUW_LIST_HPP
