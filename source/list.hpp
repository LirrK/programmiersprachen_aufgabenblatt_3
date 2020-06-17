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


//TODO: Implementierung der Methoden des Iterators 
//      (nach Vorlesung STL-1 am 09. Juni) (Aufgabe 3.12)
template <typename T>
struct ListIterator {
  using Self              = ListIterator<T>;
  using value_type        = T;
  using pointer           = T*;
  using reference         = T&;
  using difference_type   = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;


  /* DESCRIPTION  operator*() */
  T&  operator*()  const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator* (Aufgabe 3.12 - Teil 1)

  } //call *it

  /* DESCRIPTION  operator->() */
  T* operator->() const {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: remaining implementation of derefenciation of 
    //      iterator using operator-> (Aufgabe 3.12 - Teil 2)
  }  //call it->method() or it->member


  /* PREINCREMENT, call: ++it, advances one element forward */
  ListIterator<T>& operator++() {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 3)
    
  }

  /* POSTINCREMENT (signature distinguishes the iterators), 
                    call:  it++, advances one element forward*/
  ListIterator<T> operator++(int) {
    if(nullptr == node) {
      throw "Iterator does not point to valid node";
    }

    //TODO: Implement Postincrement-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 4)

  }


  /* ... */
  bool operator==(ListIterator<T> const& x) const {
    //TODO: Implement Equality-Operation for Iterator
    //      (Aufgabe 3.12 - Teil 5)
    // Iterators should be the same if they refer to the same node
    return false;
  } // call it: == it

  /* ... */
  bool operator!=(ListIterator<T> const& x) const {
    //TODO: Implement Inequality-Operation for Iterator  
    //      (Aufgabe 3.12 - Teil 6)
    // Reuse operator==
    return false;
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
    /*
    List(List const& originalList) {
      if(originalList.first_ == nullptr) {
        return;
      }
      ListNode<T>* tmp = originalList.first_->next; //error: invalid conversion from ‘ListNode<int>*’ to ‘int’ [-fpermissive]
      first_ = push_back(*originalList.first_);
      while(tmp->next != nullptr) {
        push_back(*tmp->next);
        tmp = tmp->next;
        if(tmp->next == nullptr) {
          last_ = tmp;
        }
      }
      
    }
    */

    // test and implement:
    // TODO: Move-Konstruktor (Aufgabe 3.9)

    //TODO: Initializer-List Konstruktor (3.10 - Teil 1)
    /* ... */
    // test and implement:
    List(std::initializer_list<T> ini_list) {
      //not implemented yet
    }

    /* ... */
    // test and implement:
    //TODO: (unifying) Assignment operator (Aufgabe 3.6)

    /* ... */
    // test and implement:

    bool operator==(List const& rhs) const
    {
      //TODO: operator== (Aufgabe 3.8)
    }

    bool operator!=(List const& rhs) const
    {
      //TODO: operator!= (Aufgabe 3.8)
      // make use of operator==
    }

    // Destructor of the list class
    ~List() {
      clear();
    }

    /* ... */
    ListIterator<T> begin() {
      //TODO: begin-Method returning an Iterator to the 
      //      first element in the List (Aufgabe 3.11)
      return {};
    }

    /* ... */
    ListIterator<T> end() {
      //TODO: end-Method returning an Iterator to element after (!) 
      //      the last element in the List (Aufgabe 3.11)
      return {};
    }

    // Deletes all nodes in the list.
    void clear() {
      while(empty() == false) {
        pop_back();
      }
    }


    /* ... */
    //TODO: member function insert (Aufgabe 3.13)

    /* ... */
    //TODO: member function insert (Aufgabe 3.14)

    /* ... */

    //TODO: member function reverse (Aufgabe 3.7 - Teil 1)


    // Adds a new ListNode with value = element
    // as first node in the list.
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
    // as last node in the list.
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

/* ... */
//TODO: Freie Funktion reverse 
//(Aufgabe 3.7 - Teil 2, benutzt Member-Funktion reverse)

/* ... */
//TODO: Freie Funktion operator+ (3.10 - Teil 2)


#endif // # define BUW_LIST_HPP
