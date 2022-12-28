#pragma once

#define CREATE_STATIC_VARIABLE(Ty, Name, Init)	\
	inline Ty& Name##Accessor() const {			\
		static Ty staticValue(Init);			\
		return staticValue;						\
	}											\


#define ACCESS_STATIC_VARIABLE(Name) \
	Name##Accessor()
