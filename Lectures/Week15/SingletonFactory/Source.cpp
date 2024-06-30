#include "SingletonFactory.h"

int main() {
	SingletonFactory& sf = SingletonFactory::getInstance();

	sf.create();
	sf.create();
	sf.create();
	sf.create();
}