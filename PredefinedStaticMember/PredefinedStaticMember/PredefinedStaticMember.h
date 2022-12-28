#pragma once

#define CREATE_STATIC_VARIABLE(Ty, Name)	\
	inline Ty& Name##Accessor() const {		\
		static Ty staticValue;				\
		return staticValue;					\
	}
#define CREATE_STATIC_ARRAY(Ty, N, Name)		\
	inline Ty (&Name##Accessor() const)[N] {	\
		static Ty staticValue[N];				\
		return staticValue;						\
	}

#define ACCESS_STATIC_VARIABLE(Name) \
	Name##Accessor()
