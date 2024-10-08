#include <sys/types.h>
#include <errno.h>
#include <pthread.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#include <random>
#include <chrono>

using namespace std;

#define PERMISSIONS_FLAG 0660 | IPC_CREAT

#define MUTEX_SEM_KEY 10
#define EMPTY_SEM_KEY 20
#define FULL_SEM_KEY 30

#define MEMORY_1_KEY 40
#define MEMORY_1_SIZE 0

#define MEMORY_2_KEY 50
#define MEMORY_2_SIZE 0

#define MEMORY_ITEMS 5

// struct product
// {
//     char name[30];
//     float mean;
//     float standard_deviation;
//     float item_value;
// };
