// Copyright 2021 ykvopich Kravchenko_vlad2001@bk.ru

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#endif // INCLUDE_HEADER_HPP_

#include <iostream>
#include <atomic>
#include <utility>

using std::move;
using std::atomic_uint;

template <typename T>
class SharedPtr {
 public:
  SharedPtr(): pointer(nullptr), counter(nullptr){}

  explicit SharedPtr(T* newPointer) {
    pointer=newPointer;
    if (newPointer==nullptr){
      counter=nullptr;
    }
    else {
      counter = new std::atomic_uint;
      *counter=1;
    }
  };

  SharedPtr(const SharedPtr& sharedPtr){
    if (sharedPtr.pointer){
      pointer = sharedPtr.pointer;
      counter = sharedPtr.counter;
      if (pointer){
        *counter = *counter+1;
      }
      else{
        counter = nullptr;
      }
    }
  };

  SharedPtr& operator=(const SharedPtr& sharedPtr){
    if (this != &sharedPtr) {
      pointer = sharedPtr.pointer;
      counter = sharedPtr.counter;
      if (pointer){
        *counter = *counter-1;
      }
      else{
        counter=nullptr;
      }
    }
    return *this;
  };

  SharedPtr(SharedPtr&& sharedPtr){
    if (sharedPtr.pointer) {
      pointer = move(sharedPtr.pointer);
      counter = move(sharedPtr.counter);
    }
  };

  SharedPtr& operator=(SharedPtr&& sharedPtr){
    if (this != &sharedPtr) {
      std::swap(pointer, sharedPtr.pointer);
      std::swap(counter, sharedPtr.counter);
    }
    return *this;
  };

  operator bool() const{
    if(pointer){
      return true;
    }
    else{
      return false;
    }
  }

  T& operator*() const{
    return *pointer;
  };

  T* get() {
    return pointer;
  }

  T* operator->() const{
    return pointer;
  }

  void swap(SharedPtr& sharedPtr){
    T* tmpPointer = sharedPtr.pointer;
    sharedPtr.pointer = pointer;
    pointer = tmpPointer;
    atomic_uint* tmpCounter = sharedPtr.counter;
    sharedPtr.counter = counter;
    counter = tmpCounter;
  };

  void reset() {
    if (*counter==1) {
      delete pointer;
      delete counter;
    } else {
      *counter = *counter - 1;
    }
    pointer=nullptr;
    counter=nullptr;
  };

  void reset(T* anyPointer) {
    if (*counter==1) {
      delete pointer;
      delete counter;
    }
    else {
      *counter = *counter - 1;
    }
    pointer = anyPointer;
    if (anyPointer==nullptr) {
      counter = nullptr;
    }
    else{
      counter=new atomic_uint;
      *counter=1;
    }
  }

  ~SharedPtr(){
    if (counter) {
      if (!--*counter){
        delete pointer;
        delete counter;
      }
    }
  }

  [[nodiscard]] size_t use_count() const{
    if(counter){
      return *counter;
    }else{
      return 0;
    }
  }


 private:
  T* pointer;
  atomic_uint* counter;
};
