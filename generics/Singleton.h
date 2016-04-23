#pragma once

#include <stdlib.h>
#include <stdio.h>

template <class T>
class Singleton {
public:
	static T* GetInstance() {
		if ( !instance ) {
			printf( "  Creating Singleton...\n" );
			instance = new T;
		}

		return instance;
	}

	static void DestroyInstance() {
		instance = nullptr;
	}

private:
	static T* instance;
};

template <class T> 
T* Singleton<T>::instance = nullptr;