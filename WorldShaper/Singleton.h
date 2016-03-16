#pragma once

template <class T>
class Singleton {
public:
	static T* GetInstance() {
		if ( !instance ) {
			instance = new T;
		}

		return instance;
	}

	static void DestroyInstance() {
		delete instance;
		instance = nullptr;
	}

private:
	static T* instance;
};

template <class T> 
T* Singleton<T>::instance = nullptr;