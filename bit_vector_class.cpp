#include "bitVector.h"
#include <cstdint>
#include <stdexcept>
#include <limits>
#include <iostream>
#include <cmath>



void print(const BitVector& bv) {
    for (int i = bv.size() - 1; i >= 0; --i) {
        std::cout << bv[i];
    }
    std::cout << std::endl;
}
 

BitVector::Reference::Reference(BitVector* ptr) : ptr(ptr){ }
BitVector::Reference::operator bool() {
    return (static_cast<const BitVector&>(*ptr))[currIndex];
}
BitVector::Reference& BitVector::Reference::operator=(bool input) {
   if (input) {
      ptr -> set(currIndex);
   }
   else {
      ptr -> reset(currIndex);
   }
   return *this;
}

size_t BitVector::countOfSubArrays() const {
   return _size / initialSize <= 1 ? 1 : !(_size % initialSize) ? _size / initialSize : _size / initialSize + 1;
}

BitVector::BitVector(const size_t size) : _size(size), ref(this), _count(0) {
   ptr = new uint64_t[countOfSubArrays()]; 
}
BitVector::BitVector(const BitVector& input) : _size(input.size()), ref(this), _count(input.count()) {
   ptr = new uint64_t[countOfSubArrays()];
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      ptr[i] = input.ptr[i];
   } 
}
BitVector& BitVector::operator= (const BitVector& input) {
  if (input.size() != this -> size()) {
   throw std::invalid_argument("BitVectors should have same size for using operator =");
  }
   this -> _count = input._count;
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      ptr[i] = input.ptr[i];
   }
   return *this; 
}
BitVector::~BitVector() {
    delete [] ptr;
}
bool BitVector::operator[] (const size_t index) const {
    size_t pos = index / initialSize;
    size_t offset = index - (pos * initialSize);
    return ptr[pos] & static_cast<uint64_t>(pow(2, offset));
 }
 BitVector::Reference& BitVector::operator[] (const size_t index) {
   ref.currIndex = index;
   return this -> ref;
 }
 size_t BitVector::size() const {
     return _size;
 }
 void BitVector::set(const size_t index) {
   if (test(index)) {
      return;
    }
    size_t pos = index / initialSize;
    size_t offset = index - (pos * initialSize);
    ++_count;
    ptr[pos] |= static_cast<uint64_t>(pow(2, offset));
 }; 
 void BitVector::reset(const size_t index) {
    if (!test(index)) {
      return;
    }
    size_t pos = index / initialSize;
    size_t offset = index - (pos * initialSize);
    --_count;
    ptr[pos] ^= static_cast<uint64_t>(pow(2, offset));
 }; 
 bool BitVector::operator==(const BitVector& input) const {
   if (this -> size() != input.size()) {
      return false;
   }
   size_t count = size() / initialSize;
   for (size_t i = 0; i <= count; ++i) {
      if (ptr[i] != input.ptr[i]) {
         return false;
      }
   }
   return true;
 }
 bool BitVector::operator !=(const BitVector& input) const {
   return !(*this == input);
 }
 bool BitVector::test(size_t index) const {
   if (index > size()) {
      throw std::out_of_range("std::out_of_range");
   }
   return (static_cast<const BitVector&>(*this))[index];
 }
  bool BitVector::all() const {
   return _size == _count;
  }
  bool BitVector::none() const {
   return _count == 0;
  }
  bool BitVector::any() const {
   return _count != 0;
  }
  size_t BitVector::count() const {
   return _count;
  }
 BitVector BitVector::operator&(const int num) const {
   BitVector tmp(size());
   tmp.ptr[0] = this -> ptr[0] & num;
   return tmp;
  }
BitVector BitVector::operator&(const BitVector& input) const {
   if (this -> size() != input.size()) {
     throw std::invalid_argument("BitVectors should have same size for using operator &");
   }
   BitVector tmp{*this};
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      tmp.ptr[i] &= input.ptr[i];
   }
   return tmp;
  }
BitVector& BitVector::operator&= (const BitVector& input) {
   if (this -> size() != input.size()) {
     throw std::invalid_argument("BitVectors should have same size for using operator &");
   }
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      ptr[i] &= input.ptr[i];
   }
   return *this;
   }
BitVector& BitVector::operator&=(const int num) {
   this -> ptr[0] &= num;
   return *this;
}
BitVector BitVector::operator|(const int num) const {
   BitVector tmp(size());
   tmp.ptr[0] = this -> ptr[0] | num;
   return tmp;
  }
BitVector BitVector::operator|(const BitVector& input) const {
   if (this -> size() != input.size()) {
     throw std::invalid_argument("BitVectors should have same size for using operator &");
   }
   BitVector tmp{*this};
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      tmp.ptr[i] |= input.ptr[i];
   }
   return tmp;
  }
BitVector& BitVector::operator|= (const BitVector& input) {
   if (this -> size() != input.size()) {
     throw std::invalid_argument("BitVectors should have same size for using operator &");
   }
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      ptr[i] |= input.ptr[i];
   }
   return *this;
   }
BitVector& BitVector::operator|=(const int num) {
   this -> ptr[0] |= num;
   return *this;
}
BitVector BitVector::operator^(const int num) const {
   BitVector tmp(size());
   tmp.ptr[0] = this -> ptr[0] ^ num;
   return tmp;
  }
BitVector BitVector::operator^(const BitVector& input) const {
   if (this -> size() != input.size()) {
     throw std::invalid_argument("BitVectors should have same size for using operator &");
   }
   BitVector tmp{*this};
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      tmp.ptr[i] ^= input.ptr[i];
   }
   return tmp;
  }
BitVector& BitVector::operator^= (const BitVector& input) {
   if (this -> size() != input.size()) {
     throw std::invalid_argument("BitVectors should have same size for using operator &");
   }
   for (size_t i = 0; i <= countOfSubArrays(); ++i) {
      ptr[i] ^= input.ptr[i];
   }
   return *this;
   }
BitVector& BitVector::operator^=(const int num) {
   this -> ptr[0] ^= num;
   return *this;
}
 BitVector BitVector::operator~ () const {
   BitVector tmp(_size);
   for (int i = 0; i <= countOfSubArrays(); ++i) {
      tmp.ptr[i] = ~ptr[i]; 
   }
   tmp._count = _size - _count;
   return tmp; 
 }

 BitVector BitVector::operator>> (const size_t pos) const {
   if (pos >= size()) {
      return BitVector(size());
   }
   BitVector tmp(*this);
   for (int i = 0; i < pos && i < size(); ++i) {
      for (int j = 0; j < size(); ++j) {
         if (j == size() - 1) {
            tmp.reset(j);          
         }
         else {
         tmp[j] = tmp.test(j + 1);
         } 
      }
   }
   return tmp;
 }

 BitVector& BitVector::operator>>= (const size_t pos) {
   if (pos >= size()) {
      for (int i = 0; i <= countOfSubArrays(); ++i) {
         ptr[i] = 0;
      }
      _count = 0;      
   }
   else {
      for (int i = 0; i < pos && i < size(); ++i) {
         for (int j = 0; j < size(); ++j) {
            if (j == size() - 1) {
               reset(j);          
            }
            else {
            (*this)[j] = this -> test(j + 1);
            } 
         }
      }
   } 
   return *this;
 }

 BitVector BitVector::operator<< (const size_t pos) const {
   if (pos >= size()) {
      return BitVector(size());
   }
   BitVector tmp(*this);
   for (int i = 0; i < pos && i < size(); ++i) {
      for (int j = size() - 1; j >= 0; --j) {
         if (j == 0) {
            tmp.reset(j);          
         }
         else {
         tmp[j] = tmp.test(j -1);
         } 
      }
   }
   return tmp;
 }

 BitVector& BitVector::operator<<= (const size_t pos) {
   if (pos >= size()) {
      for (int i = 0; i <= countOfSubArrays(); ++i) {
         ptr[i] = 0;
      }
      _count = 0;      
   }
   else {
      for (int i = 0; i < pos && i < size(); ++i) {
         for (int j = size() - 1; j >= 0; --j) {
            if (j == 0) {
               reset(0);          
            }
            else {
            (*this)[j] = this -> test(j - 1);
            } 
         }
      }
   } 
   return *this;
 }
                           
