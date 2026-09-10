#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val){

  if(tail_ == nullptr || tail_->last == ARRSIZE){ //if empty or full 
    Item *newItem = new Item(); 
    newItem->prev = tail_; 
    newItem->next = nullptr; 

    if(tail_ != nullptr){
      tail_->next = newItem; 
    } 
    tail_ = newItem; 

    if(head_ == nullptr){
      head_ = newItem; 
    }
  }

  tail_->val[tail_->last] = val; 
  ++tail_->last; 
  ++size_;
}

void ULListStr::pop_back(){
  if(tail_== nullptr){
    return; 
  }

  //decrease index 
  --tail_->last; 

  if(tail_->first == tail_->last){
    Item *toDelete = tail_;
    tail_ = toDelete->prev; 

    if(tail_ != nullptr){
      tail_->next = nullptr; 
    } else {
      head_ = nullptr; 
    } 

    delete toDelete;
  }
  --size_;
}

void ULListStr::push_front(const std::string& val){
    if(head_ == nullptr || head_->first == 0){
      Item *newItem = new Item(); 
      newItem->next = head_; 
      newItem->prev = nullptr; 

      newItem->first = ARRSIZE -1; 
      newItem->last = ARRSIZE; 

      if(head_ != nullptr){
        head_->prev = newItem;
      }
      head_ = newItem; 

      if(tail_ == nullptr){
        tail_ = newItem; 
      }

      head_->val[head_->first] = val; 
    } else {
      --head_->first;
      head_->val[head_->first] = val;
    }

    ++size_; 
}

void ULListStr::pop_front(){
  if(head_ == nullptr){
    return;
  }

  ++head_->first; 

  if(head_->first == head_->last){
    item *toDelete = head_; 
    head_ = toDelete->next; 

    if(head_ != nullptr){
      head_->prev = nullptr;
    } else{
      tail_ = nullptr; 
    }

    delete toDelete;
  }

  --size_;
}

std::string const & ULListStr::back() const{
  return tail_->val[tail_->last-1];
}

std::string const & ULListStr::front() const{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const{
  if(loc >= size_){
    return nullptr; 
  }

  size_t remain = loc; 
  Item *curr = head_; 

  while(curr != nullptr){
    size_t c = curr->last - curr->first;
    if(remain < c){
      return const_cast<std::string*>(&curr->val[curr->first + remain]);
    }
    remain -= c; 
    curr = curr->next;
  }

  return nullptr;

}


