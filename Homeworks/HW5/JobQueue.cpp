#include "JobQueue.hpp"
#include <iostream>
using namespace std;

JobQueue::JobQueue() {
  queueEnd = 0;
  queueFront = 0;
}

bool JobQueue::isEmpty() {
  if (queueEnd == queueFront && queue[queueEnd] == "") {
    return true;
  }
  return false;
}

bool JobQueue::isFull() {
  if (queueEnd == queueFront && queue[queueEnd] != "") {
    return true;
  }
  return false;
}

void JobQueue::enqueue(std::string job) {
  if (!isFull()) {
    queue[queueEnd] = job;
    queueEnd++;
    queueEnd = queueEnd % 20;
    counter++;
  } 
  else {
    cout << "Queue full, cannot add new job" << endl;
  }
}

void JobQueue::dequeue() {
  if (!isEmpty()) {
    queue[queueFront] = "";
    queueFront++;
    queueFront = queueFront % 20;
    counter--;
  } 
  else {
    cout << "Queue empty, cannot dequeue a job" << endl;
  }
}

std::string JobQueue::peek() {
  if (!isEmpty()) {
    return queue[queueFront];
  } 
  else {
    cout << "Queue empty, cannot peek" << endl;
    return "";
  }
}

int JobQueue::queueSize() {
  return counter;
}