#include <iostream>
#include "Queue.hpp"

int main()
{
	Queue<int> queue;

	queue.push(1);
	queue.push(2);
	queue.push(3);
	queue.push(4);

	queue.pop();
	queue.push(5);
	queue.push(6);
}