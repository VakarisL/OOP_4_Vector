#ifndef VECTOR_H_
#define VECTOR_H_

template<class T>
class Vector {
  private:
  	int size_;
  	T* element_;
  public:
  	Vector() : size_(0), element_(new T[size_]) {}
    Vector(size_t size,const T& value) : size_(size), element_(new T[size_]) {std::fill_n(element_, size, value);}
    Vector(size_t size) : size_(size), element_(new T[size_]) {}
  	Vector(std::initializer_list<T>);
  	int size() const {return size_;}
  	T element(int i) const {return element_[i];}
  	~Vector() {delete[] element_;}
};

template<class T>
Vector<T>::Vector(std::initializer_list<T> input) : size_(input.size()), element_(new T[size_]){
  for(size_t i=0; i<size_; i++){
    element_[i]=*(input.begin()+i);
  }
}

#endif