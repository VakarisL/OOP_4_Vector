#ifndef VECTOR_H_
#define VECTOR_H_

#include <memory>
#include <algorithm>
#include <iostream>
#include <stdexcept>

template<class T, class Allocator = std::allocator<T>>
class Vector {
 public:
  //typedef T value_type;
  //typedef Allocator allocator_type;
  //typedef typename allocator_traits<Allocator>::pointer pointer;
  // typedef T& reference;
  // typedef const T& const_reference;

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
  Vector(std::size_t size, const T& value, Allocator alloc = Allocator());
  explicit Vector(std::size_t size, Allocator alloc = Allocator());
  template<typename InputIt, typename = std::_RequireInputIter<InputIt>>
  Vector(InputIt first, InputIt last, Allocator alloc = Allocator()); //works, needs finish TODO
  Vector(const Vector& other, Allocator alloc);
  Vector(Vector&& other) noexcept;
  //Vector(Vector&& other, const Allocator& alloc); (??)
  Vector(std::initializer_list<T>);

  // destructors
  ~Vector() {allocator_.deallocate(element_, capacity_);}

  // operator=
  Vector& operator=(const Vector& other);
  Vector& operator=(Vector&& other);
  Vector& operator=(std::initializer_list<T>);

  // assign
  void assign(std::size_t size, const T& value);
  template<typename InputIt, typename = std::_RequireInputIter<InputIt>>
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
  T& back() {return element_[size_-1];}
  const T& back() const {return element_[size_-1];}

  // data
  T& data() noexcept {return element_;}
  const T& data() const noexcept {return element_;}

  //######### Iterators #########
  // begin/cbegin


  //######### Capacity #########
  int size() const {return size_;}

  //######### Modifiers #########
  // clear
  void clear();


  //######### Non-member Functions #########


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
Vector<T, Allocator>::Vector(std::size_t size, const T& value, Allocator alloc)
  : capacity_(size), size_(size), element_{alloc.allocate(capacity_)} {
  std::fill_n(element_, size, value);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::size_t size, Allocator alloc)
  : capacity_(size), size_(size), element_{alloc.allocate(capacity_)} {
  std::fill_n(element_, size, T());
}

template<class T, class Allocator>
template<typename InputIt, typename>
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
  //std::move(first, last, element_);
  //std::copy(first, last, element_);
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
Vector<T, Allocator>::Vector(std::initializer_list<T> input) : size_{input.size()}, capacity_{input.size()}, element_{allocator_.allocate(capacity_)} {
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
template<typename InputIt, typename>
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
T& Vector<T, Allocator>::at(std::size_t pos){
  if(pos>size_) {
    throw std::out_of_range{"Vector position out of range"};
  }
  return element_[pos];
}

template<class T, class Allocator>
const T& Vector<T, Allocator>::at(std::size_t pos) const{
  if(pos>size_) {
    throw std::out_of_range{"Vector position out of range"};
  }
  return element_[pos];
}




template<class T, class Allocator>
void Vector<T, Allocator>::clear() {
  for (std::size_t i = 0; i < size_; ++i) {
    allocator_.destroy(element_ + i);
  }
  size_ = 0;
}

#endif