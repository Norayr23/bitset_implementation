#include <cstdint>
#include <cmath>
#ifndef BITVECTOR_H
#define BITVECTOR_H


class BitVector {
 class Reference {
   BitVector* ptr;
 public:
   Reference(BitVector*);
   int currIndex = 0;
   operator bool ();
   Reference& operator= (bool input);  
 }; 
 const short initialSize = 64;
 uint64_t* ptr;
 size_t _size;
 size_t _count;
 Reference ref;
 size_t countOfSubArrays() const;
 public:
   BitVector(const size_t size);
   BitVector(const BitVector& input);
   BitVector& operator= (const BitVector& input);
   Reference& operator[] (const size_t index);
   bool operator[] (const size_t index) const;
   size_t size() const;
   void set(const size_t index);
   void reset(const size_t index);
   bool operator ==(const BitVector& input) const;
   bool operator !=(const BitVector& input) const;
   bool test(size_t index) const;
   bool all() const;
   bool any() const;
   bool none() const;
   size_t count() const;
   BitVector operator&(const int num) const;
   BitVector operator&(const BitVector& input) const;
   BitVector& operator&= (const BitVector& input);
   BitVector& operator&= (const int num);
   BitVector operator|(const int num) const;
   BitVector operator|(const BitVector& input) const;
   BitVector& operator|= (const BitVector& input);
   BitVector& operator|= (const int num);
   BitVector operator^(const int num) const;
   BitVector operator^(const BitVector& input) const;
   BitVector& operator^= (const BitVector& input);
   BitVector& operator^= (const int num);
   BitVector operator~ () const;
   BitVector operator>> (const size_t pos) const;
   BitVector& operator>>= (const size_t pos);
   BitVector operator<< (const size_t pos) const;
   BitVector& operator<<= (const size_t pos);


   
   ~BitVector();

};

#endif

