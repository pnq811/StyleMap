#pragma once
#ifndef _ICONSTRAINT_H_
#define _ICONSTRAINT_H_
class IConstraint
{
public:
	typedef enum class Type
	{
		NONE,
		WEIGHT, 
		HEIGHT, 
		WIDTH
	};
	IConstraint(int _id); 
	~IConstraint(); 
	virtual bool check(double _paramater) = 0; 
public: 
	int id; 
	Type type; 
};
#endif //_ICONSTRAINT_H_

