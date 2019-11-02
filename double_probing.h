//Liulan Zheng
//CSCI335 Homework3
#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>


namespace {
template <typename HashedObj>
class DoubleProb : public HashTable<HashedObj> {
	// Internal method to test if a positive number is prime.
	bool IsPrime(size_t n) {
	if( n == 2 || n == 3 )
		return true;
	
	if( n == 1 || n % 2 == 0 )
		return false;
	
	for( int i = 3; i * i <= n; i += 2 )
		if( n % i == 0 )
		return false;
	
	return true;
}


// Internal method to return a prime number at least as large as n.
	int NextPrime(size_t n) {
	if (n % 2 == 0)
		++n;  
	while (!IsPrime(n)) n += 2;  
	return n;
	}
	
};

}  // namespace



// double probing implementation.
template <typename HashedObj>
class HashTableDouble : public HashTable<HashedObj>{
public:
	enum EntryType {ACTIVE, EMPTY, DELETED};
	
	explicit HashTableDouble(size_t size = 101) : array_(NextPrime(size)){ 
		MakeEmpty();
		number_of_collisions_ =0;
	}
	
	bool Contains(const HashedObj & x) const {
		probes_ = 1;
		return IsActive(FindPos(x));
	}
	
	void MakeEmpty() {
		current_size_ = 0;
		for (auto &entry : array_)
		entry.info_ = EMPTY;
	}
	
	bool Insert(const HashedObj & x) {
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
		return false;
		
		array_[current_pos].element_ = x;
		array_[current_pos].info_ = ACTIVE;
		
		// Rehash; see Section 5.5
		if (++current_size_ > array_.size() / 2)
		Rehash();    
		return true;
	}
		
	bool Insert(HashedObj && x) {
		// Insert x as active
		size_t current_pos = FindPos(x);
		if (IsActive(current_pos))
		return false;
		
		array_[current_pos] = std::move(x);
		array_[current_pos].info_ = ACTIVE;
	
		// Rehash; see Section 5.5
		if (++current_size_ > array_.size() / 2)
		Rehash();
	
		return true;
	}
	
	bool Remove(const HashedObj & x) {
		size_t current_pos = FindPos(x);
		if (!IsActive(current_pos))
		return false;
	
		array_[current_pos].info_ = DELETED;
		return true;
	}
	
	size_t GetCurrentSize() const { return current_size_; }
	size_t GetTableSize() const { return array_.size(); }
	int GetCollision() const { return number_of_collisions_; }
	int GetProbe() const { return probes_; }
	
private:        
	struct HashEntry {
		HashedObj element_;
		EntryType info_;
		
		HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
		:element_{e}, info_{i} { }
		
		HashEntry(HashedObj && e, EntryType i = EMPTY)
		:element_{std::move(e)}, info_{ i } {}
	};
    

	std::vector<HashEntry> array_;
	size_t current_size_;
	mutable int number_of_collisions_;
	mutable int probes_;
	
	bool IsActive(size_t current_pos) const
	{ return array_[current_pos].info_ == ACTIVE; }
	
	// Hash function2 for double hashing
	
	size_t HashFunction2(const HashedObj & x) const {
		static std::hash<HashedObj> hf;
		// 13 was chosen for R - (X % R) 
		// since it provides the least number of collisions among other prime numbers
		return  13 - ( hf(x) % 13);
		
	}
	
	
	size_t FindPos(const HashedObj & x) const{
	
		size_t hash_value = InternalHash(x);
		size_t i = 0;
		size_t current_pos = hash_value;
		while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) {
			i++;
			number_of_collisions_++;
			probes_++;
			current_pos = hash_value + i * HashFunction2(x); // Compute ith probe. 
			if (current_pos >= array_.size())
			current_pos -= array_.size();
		}
		return current_pos;
	}
	
	void Rehash() {
		std::vector<HashEntry> old_array = array_;
		
		// Create new double-sized, empty table.
		array_.resize(NextPrime(2 * old_array.size()));
		for (auto & entry : array_)
			entry.info_ = EMPTY;
		
		// Copy table over.
		current_size_ = 0;
		for (auto & entry :old_array)
			if (entry.info_ == ACTIVE)
			Insert(std::move(entry.element_));
	}
		
	size_t InternalHash(const HashedObj & x) const {
		static std::hash<HashedObj> hf;
		return hf(x) % array_.size( );
	}
};

#endif  // DOUBLE_PROBING_H
