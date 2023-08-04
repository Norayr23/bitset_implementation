#include <cstdint>
#include <cmath>
#include <string>
#ifndef BITVECTOR_H
#define BITVECTOR_H


class BitVector {

private:

   class Reference {
     BitVector* ptr;
   public:
     Reference(BitVector*);
     int currIndex = 0;
     operator bool ();
     Reference& operator= (bool input);  
   };   
 
public:

   explicit BitVector(const size_t size);
   BitVector(const BitVector& input);
   explicit BitVector (const std::string& str, char one = '1', char zero = '0');
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
   BitVector& flip();
   BitVector& flip(size_t pos);
   std::string to_string(char zero = '0', char one = '1') const;
   unsigned long to_ulong() const;
   unsigned long long to_ullong() const; 
   ~BitVector();

private:

   const short initialSize = 64;
   uint64_t* ptr;
   size_t _size;
   size_t _count;
   Reference ref;
   size_t countOfSubArrays() const; 
     
};

#endif

