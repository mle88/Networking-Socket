/* 
To compile: gcc -pthread -o test_threads test_threads.cpp
To run: ./test_threads
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *print_message(void *ptr);

int main() {

  pthread_t thread1; 
  pthread_t thread2; 
  
  // The tutorial is written in C, so character array pointers 
  // (const char *message) are used instead of std::string, etc.
  const char *message1 = "Thread 1"; 
  const char *message2 = "Thread 2"; 

  // Create a thread that runs the function `print_message`. Functions run in 
  // threads can recieve a single pointer parameter, in this case `message1`.
  // For our project, we should pass in a pointer to the socket after accepting 
  // a new connection.
  int thread1_return = pthread_create(&thread1, NULL, print_message, (void *) message1);

  // Create another thread that runs the function `print_message` with the parameter `message2`.
  int thread2_return = pthread_create(&thread1, NULL, print_message, (void *) message2);

  // Wait the main thread until `thread1` and `thread2`
  // have finished. Without this, we would `return 0` too fast
  // and never see the messages printed. We could also use usleep 
  // but that's not a good solution.
  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  usleep(3000);

  return 0;
}

void *print_message(void *ptr) {
  /*
  Print a character array

  :param *ptr *ptr: Pointer to the start of a character array 
  :return None:
  */
  char *message;
  message = (char *) ptr;
  printf("%s \n", message);
}

