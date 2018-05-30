#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <iterator>

template<class T, class Allocator = std::allocator<T>>
class Vector {
 public:
  typedef T* iterator;
  typedef const T* const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

 private:
  Allocator allocator_;
  std::size_t capacity_;
  std::size_t size_;
  T* element_;

 public:

  //######### Member functions #########
  //constructors
  Vector() noexcept(noexcept(Allocator()));
  explicit Vector(const Allocator& alloc) noexcept;
  Vector(std::size_t size, const T& value/*, Allocator alloc = Allocator()*/);
  explicit Vector(std::size_t size, Allocator alloc = Allocator());
  template<typename InputIt/*, typename = std::_RequireInputIter<InputIt>*/>
  Vector(InputIt first, InputIt last, Allocator alloc = Allocator()); //works, needs finish TODO
  Vector(const Vector& other, Allocator alloc);
  Vector(Vector&& other) noexcept;
  //Vector(Vector&& other, const Allocator& alloc); (??) would need special case handling(?) when alloc=/=allocator_
  Vector(std::initializer_list<T>);

  // destructors
  ~Vector() {allocator_.deallocate(element_, capacity_);}

  // operator=
  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other);
  Vector& operator=(std::initializer_list<T>);

  // assign
  void assign(std::size_t size, const T& value);
  template<typename InputIt/*, typename = std::_RequireInputIter<InputIt>*/>
  void assign(InputIt first, InputIt last);             //TODO
  void assign(std::initializer_list<T> input);

  // get_allocator
  Allocator get_allocator() const {return allocator_;}

  //######### Element access #########
  // at
  T& at(std::size_t pos);
  const T& at(std::size_t pos) const;

  // operator[]
  T& operator[](std::size_t i) {return (element_[i]);}
  const T& operator[](std::size_t i) const {return (element_[i]);}

  // front
  T& front() {return element_[0];}
  const T& front() const {return element_[0];}

  // back
  T& back() {return element_[size_ - 1];}
  const T& back() const {return element_[size_ - 1];}

  // data
  T& data() noexcept {return element_;}
  const T& data() const noexcept {return element_;}

  //######### Iterators #########
  // begin/cbegin
  iterator begin() noexcept {return element_;}
  const_iterator begin() const noexcept {return element_;}
  const_iterator cbegin() const noexcept {return element_;} //should it be different from 'const_iterator begin() const noexcept'?
  //both are the same in STL vector

  // end/cend
  iterator end() noexcept {return &element_[size_];}
  const_iterator end() const noexcept {return &element_[size_];}
  const_iterator cend() const noexcept {return &element_[size_];} //same as cbegin(), should it be different from const_iterator end()?

  // rbegin/crbegin
  reverse_iterator rbegin() noexcept {return reverse_iterator(end());}
  const_reverse_iterator rbegin() const noexcept {return reverse_iterator(end());}
  const_reverse_iterator crbegin() const noexcept {return reverse_iterator(cend());} //once again cbegin() == begin()??

  // rend/crend
  reverse_iterator rend() noexcept {return reverse_iterator(begin());}
  const_reverse_iterator rend() const noexcept {return reverse_iterator(begin());}
  const_reverse_iterator crend() const noexcept {return reverse_iterator(cbegin());}



  //######### Capacity #########
  // empty
  bool empty() const noexcept {return (size_ == 0 ? true : false);}

  // size
  int size() const noexcept {return size_;}

  // max_size
  std::size_t max_size() const noexcept {return allocator_.max_size();}

  // reserve
  void reserve(std::size_t new_cap);

  // capacity
  std::size_t capacity() const noexcept {return capacity_;}

  // shrink_to_fit
  void shrink_to_fit();



  //######### Modifiers #########
  // clear
  void clear();

  // insert
  iterator insert(const_iterator pos, const T& value);
  iterator insert(const_iterator pos, T&& value);
  iterator insert(const_iterator pos, std::size_t count, const T& value);
  template<typename InputIt/*, typename = std::_RequireInputIter<InputIt>*/>
  iterator insert(const_iterator pos, InputIt first, InputIt last);
  iterator insert(const_iterator pos, std::initializer_list<T> ilist);

  // emplace
  template<class Args>
  iterator emplace(const_iterator pos, Args&& args);

  // erase
  iterator erase(const_iterator pos);
  iterator erase(const_iterator first, const_iterator last);

  // push_back
  void push_back(T&& value);
  void push_back(const T& value);

  // emplace_back
  template<class Args>
  T& emplace_back(Args&& args);

  // pop_back
  void pop_back();

  // resize
  void resize(std::size_t count);
  void resize(std::size_t count, const T& value);

  // swap
  void swap(Vector& other);
};

template<class T, class Allocator>
Vector<T, Allocator>::Vector() noexcept(noexcept(Allocator()))
  : capacity_(0), size_(0), element_{allocator_.allocate(capacity_)} {

}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Allocator& alloc) noexcept
  : capacity_(0), size_(0), element_{alloc.allocate(capacity_)} {

}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::size_t size, const T& value /*, Allocator alloc*/)
  : capacity_(size), size_(size), element_{allocator_.allocate(capacity_)} {
  std::fill_n(element_, size, value);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::size_t size, Allocator alloc)
  : capacity_(size), size_(size), element_{alloc.allocate(capacity_)} {
  std::fill_n(element_, size, T());
}

template<class T, class Allocator>
template<typename InputIt/*, typename*/>
Vector<T, Allocator>::Vector(InputIt first, InputIt last, Allocator alloc)
  : size_{0} {
  int count = 0;
  InputIt tempFirst = first;
  while (tempFirst != last) {
    tempFirst++;
    count++;
  }
  capacity_ = count;
  element_ = alloc.allocate(count);
  for (auto i = first; first != last; ++i) {
    element_[size_] = *i;
    size_++;
  }
  size_++;
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& other, Allocator alloc)
  : capacity_{other.capacity_}, size_{other.size_}, element_{alloc.allocate(capacity_)} {
  for (std::size_t i = 0; i != size_; ++i) {
    element_[i] = other.element_[i];
  }
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& other) noexcept
  : capacity_{other.capacity_}, size_{other.size_}, element_{other.element_} {
  other.element_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<T> input) {
  size_ = input.size();
  capacity_ = size_;
  element_ = allocator_.allocate(capacity_);
  std::copy(input.begin(), input.end(), element_);
}

template<class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& other) {
  if (&other == this) return *this;

  T* temp = allocator_.allocate(other.capacity_);
  for (size_t i = 0; i < other.size_; ++i) {
    temp[i] = other.element_[i];
  }

  allocator_.deallocate(element_, capacity_);
  element_ = temp;
  size_ = other.size_;
  capacity_ = other.capacity_;
  return *this;
}

template<class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& other) {
  if (&other == this) return *this;

  allocator_.deallocate(element_, capacity_);
  element_ = other.element_;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.element_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
  return *this;
}

template<class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(std::initializer_list<T> input) {
  allocator_.deallocate(element_, capacity_);
  capacity_ = input.size();
  size_ = input.size();
  element_ = allocator_.allocate(capacity_);
  std::copy(input.begin(), input.end(), element_);
  return *this;
}

template<class T, class Allocator>
void Vector<T, Allocator>::assign(std::size_t size, const T& value) {
  if (size <= capacity_) {
    clear();
    size_ = size;
    std::fill_n(element_, size_, value);
  } else {
    allocator_.deallocate(element_, capacity_);
    capacity_ = size;
    size_ = size;
    element_ = allocator_.allocate(capacity_);
    std::fill_n(element_, size_, value);
  }
}

template<class T, class Allocator>
template<typename InputIt/*, typename*/>
void Vector<T, Allocator>::assign(InputIt first, InputIt last) {
  int count = 0;
  InputIt tempFirst = first;
  while (tempFirst != last) {
    tempFirst++;
    count++;
  }
  if (count <= capacity_) {
    clear();
    for (auto i = first; first != last; ++i) {
      element_[size_] = *i;
      size_++;
    }
  } else {
    allocator_.deallocate(element_, capacity_);
    capacity_ = count;
    size_ = 0;
    element_ = allocator_.allocate(capacity_);
    for (auto i = first; first != last; ++i) {
      element_[size_] = *i;
      size_++;
    }
  }
  size_++;
}

template<class T, class Allocator>
void Vector<T, Allocator>::assign(std::initializer_list<T> input) {
  if (input.size() <= capacity_) {
    clear();
    size_ = input.size();
    std::copy(input.begin(), input.end(), element_);
  } else {
    allocator_.deallocate(element_, capacity_);
    capacity_ = input.size();
    size_ = input.size();
    element_ = allocator_.allocate(capacity_);
    std::copy(input.begin(), input.end(), element_);
  }
}

template<class T, class Allocator>
T& Vector<T, Allocator>::at(std::size_t pos) {
  if (pos > size_) {
    throw std::out_of_range{"Vector position out of range"};
  }
  return element_[pos];
}

template<class T, class Allocator>
const T& Vector<T, Allocator>::at(std::size_t pos) const {
  if (pos > size_) {
    throw std::out_of_range{"Vector position out of range"};
  }
  return element_[pos];
}

template<class T, class Allocator>
void Vector<T, Allocator>::reserve(std::size_t new_cap) {
  if (new_cap > max_size()) {
    throw std::length_error{"Vector reserve capacity"};
  }
  if (new_cap > capacity_) {
    T* elementTemp = allocator_.allocate(new_cap);
    for (std::size_t i = 0; i < size_; ++i) {
      elementTemp[i] = element_[i];
    }
    allocator_.deallocate(element_, capacity_);
    capacity_ = new_cap;
    element_ = elementTemp;
    elementTemp = nullptr;
  }
}

template<class T, class Allocator>
void Vector<T, Allocator>::shrink_to_fit() {
  T* elementTemp = allocator_.allocate(size_);
  for (std::size_t i = 0; i < size_; ++i) {
    elementTemp[i] = element_[i];
  }
  allocator_.deallocate(element_, capacity_);
  capacity_ = size_;
  element_ = elementTemp;
  elementTemp = nullptr;
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear() {
  allocator_.deallocate(element_, capacity_);
  size_ = 0;
  element_ = allocator_.allocate(capacity_);
}

template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, const T& value) {
  int counter = 0;
  bool contains = false;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == pos) {
      contains = true;
      break;
    }
    counter++;
  }
  if (size_ == capacity_) reserve(capacity_ * 2);
  iterator tempPos = &element_[counter];
  if (contains) {
    std::copy(tempPos, end(), tempPos + 1);
    *tempPos = value;
    size_++;
  } else {
    throw std::out_of_range{"insert position does not belong to Vector"};
  }
  return (tempPos);
}

template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, T&& value) {
  int counter = 0;
  bool contains = false;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == pos) {
      contains = true;
      break;
    }
    counter++;
  }
  if (size_ == capacity_) reserve(capacity_ * 2);
  iterator tempPos = &element_[counter];
  if (contains) {
    std::copy(tempPos, end(), tempPos + 1);
    *tempPos = value;
    size_++;
  } else {
    throw std::out_of_range{"insert position does not belong to Vector"};
  }
  return (tempPos);
}

template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, std::size_t count, const T& value) {
  int counter = 0;
  bool contains = false;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == pos) {
      contains = true;
      break;
    }
    counter++;
  }
  if (size_ == capacity_) {
    if (count < size_) reserve(capacity_ * 2);
    else reserve(capacity_ * 2 + count);
  }
  iterator tempPos = &element_[counter];
  if (contains) {
    std::copy(tempPos, end(), tempPos + count);
    std::fill_n(tempPos, count, value);
    size_ += count;
  } else {
    throw std::out_of_range{"insert position does not belong to Vector"};
  }
  return (tempPos);
}


template<class T, class Allocator>
template<typename InputIt/*, typename*/>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, InputIt first, InputIt last) {
  int counter = 0;
  bool contains = false;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == pos) {
      contains = true;
      break;
    }
    counter++;
  }
  int count = 0;
  for (auto i = first; i != last; ++i) {
    count++;
  }
  if (size_ == capacity_) {
    if (count < size_) reserve(capacity_ * 2);
    else reserve(capacity_ * 2 + count);
  }
  iterator tempPos = &element_[counter];
  if (contains) {
    std::copy(tempPos, end(), tempPos + count);
    std::copy(first, last, tempPos);
    size_ += count;
  } else {
    throw std::out_of_range{"insert position does not belong to Vector"};
  }
  return (tempPos);
}


template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::insert(const_iterator pos, std::initializer_list<T> ilist) {
  int counter = 0;
  bool contains = false;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == pos) {
      contains = true;
      break;
    }
    counter++;
  }
  std::size_t count = ilist.size();
  if (size_ == capacity_) {
    if (count < size_) reserve(capacity_ * 2);
    else reserve(capacity_ * 2 + count);
  }
  iterator tempPos = &element_[counter];
  if (contains) {
    std::copy(tempPos, end(), tempPos + count);
    std::copy(ilist.begin(), ilist.end(), tempPos);
    size_ += count;
  } else {
    throw std::out_of_range{"insert position does not belong to Vector"};
  }
  return (tempPos);
}

template<class T, class Allocator>
template<class Args>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::emplace(const_iterator pos, Args&& args) {
  int counter = 0;
  bool contains = false;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == pos) {
      contains = true;
      break;
    }
    counter++;
  }
  if (size_ == capacity_) reserve(capacity_ * 2);
  iterator tempPos = &element_[counter];
  if (contains) {
    std::copy(tempPos, end(), tempPos + 1);
    allocator_.construct(pos, args);
    size_++;
  } else {
    throw std::out_of_range{"emplace position does not belong to Vector"};
  }
  return (tempPos);
}

template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator pos) {
  int counter = 0;
  bool contains = false;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == pos) {
      contains = true;
      break;
    }
    counter++;
  }
  iterator tempPos = &element_[counter];
  if (contains) {
    std::copy(tempPos + 1, end(), tempPos);
    size_--;
  } else {
    throw std::out_of_range{"erase position does not belong to Vector"};
  }
  return (tempPos);
}

template<class T, class Allocator>
typename Vector<T, Allocator>::iterator Vector<T, Allocator>::erase(const_iterator first, const_iterator last) {
  int counter = 0, difference = 0;
  bool containsFirst = false;
  bool containsLast = false;
  iterator tempFirst, tempLast;
  for (const_iterator i = begin(); i != end(); ++i) {
    if (i == first) {
      tempFirst = &element_[counter];
      containsFirst = true;
      difference = counter;
    }
    if (i == last) {
      tempLast = &element_[counter];
      containsLast = true;
      difference = counter - difference;
      difference++;
    }
    counter++;
  }
  if (containsFirst && containsLast) {
    std::copy(tempLast + 1, end(), tempFirst);
    size_ -= difference;
    return (tempLast);
  } else {
    throw std::out_of_range{"erase range does not belong to Vector"};
  }
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(const T& value) {
  if (capacity_ == 0) reserve(1);
  if (size_ == capacity_) reserve(capacity_ * 2);
  allocator_.construct(element_ + size_, value);
  size_++;
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(T&& value) {
  if (capacity_ == 0) reserve(1);
  if (size_ == capacity_) reserve(capacity_ * 2);
  allocator_.construct(element_ + size_, value);
  size_++;
}

template<class T, class Allocator>
template<class Args>
T& Vector<T, Allocator>::emplace_back(Args&& args) {
  if (size_ == capacity_) reserve(capacity_ * 2);
  iterator temp = end();
  allocator_.construct(temp, args);
  size_++;
  return *temp;
}

template<class T, class Allocator>
void Vector<T, Allocator>::pop_back() {
  size_--;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(std::size_t count) {
  if (count > capacity_) reserve(count);
  size_ = count;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(std::size_t count, const T& value) {
  if (count > capacity_) reserve(count);
  std::size_t sizeIncrease = count - size_;
  std::fill_n(end(), sizeIncrease, value);
  size_ = count;
}

template<class T, class Allocator>
void Vector<T, Allocator>::swap(Vector& other) {
  std::swap(other, *this);
}



#endif