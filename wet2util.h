// 
// 234218 Data Structures 1.
// Semester: 2023A (winter).
// Wet Exercise #2.
// 
// Recommended TAB size to view this file: 8.
// 
// The following header file contains necessary types for your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
// 
// DO NOT use the preprocessors in your own code files.
// 

#ifndef WET2_UTIL_H_
#define WET2_UTIL_H_

#include <stdexcept>
#include <iostream>   //TODO::::: REMOVE!!!!!!!!!!!!!!!!!!!

// StatusType
enum struct StatusType {
	SUCCESS          = 0,
	ALLOCATION_ERROR = 1,
	INVALID_INPUT    = 2,
	FAILURE          = 3,
};

// output_t<T>
// The following class is used to support output with status code.
template<typename T>
class output_t {
private:
	// DO NOT access these private fields - may be enforced by verifier.
	const StatusType __status;
	const T __ans;

public:
	output_t() : __status(StatusType::SUCCESS), __ans(T()) { }
	output_t(StatusType status) : __status(status), __ans(T()) { }
	output_t(const T &ans) : __status(StatusType::SUCCESS), __ans(ans) { }
	
	StatusType status() { return __status; }
	T ans() { return __ans; }
};

// Guaranteed for three permutation_t objects p, q, r:
//   (neutral() * p) is the same as: p
//   (p * neutral()) is the same as: p
//   (p.inv() * p) is the same as: neutral()
//   (p * p.inv()) is the same as: neutral()
//   ((p * q) * r) is the same as: p * (q * r)
//   (p * q).inv() is the same as: q.inv() * p.inv()
// 
// Non-Guarnatees:
//   (p * q) is NOT necessarily the same as: q * p
//   (p.inv() * (q * p)) is NOT necessarily the same as: q

class permutation_t {
private:
	// DO NOT access these private fields - may be enforced by verifier.
	enum {
		N = 5
	};
	
	int a[N];
public:
    void print(){                //TODO: REMOVEEEE
        for (int i=0; i <5; ++i){
            std::cout << a[i];
        }
        std::cout << std::endl;
    }
	permutation_t() { for (int i = 0; i < N; ++i) { a[i] = -1; } }
	permutation_t(const int a[N]) { for (int i = 0; i < N; ++i) { this->a[i] = a[i]; } }
	permutation_t(const permutation_t &other) : permutation_t(other.a) { }
	
	static permutation_t neutral() { int a[N]; for (int i = 0; i < N; ++i) { a[i] = i; } return permutation_t(a); }
	
	bool isvalid() const
	{
		bool found[N];
		for (int i = 0; i < N; ++i)
		{
			found[i] = 0;
		}
		
		for (int i = 0; i < N; ++i)
		{
			if (a[i] < 0 || a[i] >= N || found[a[i]])
			{
				return false;
			}
			
			found[a[i]] = true;
		}
		
		return true;
	}
	
	int strength() const
	{
		int s = 0;
		for (int i = 0; i < N; ++i)
		{
			s += (i * 1) * (a[i] + 1);
		}
		
		return s;
	}
	
	permutation_t inv() const
	{
		int res[N];
		for (int i = 0; i < N; ++i)
		{
			res[a[i]] = i;
		}
		return permutation_t(res);
	}
	
	permutation_t operator *(const permutation_t &other) const
	{
		int res[N];
		for (int i = 0; i < N; ++i)
		{
			res[i] = a[other.a[i]];
		}
		return permutation_t(res);
	}
};

#endif // WET2_UTIL_H_
