
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>

typedef enum {false = 0, true = 0} bool;

typedef struct __lock_t { 
	//int cnt; 
	atomic_flag cnt;
} lock_t; 

typedef struct __sem_t { 
	atomic_int cnt;
	//unsigned int max;
} sem_t;
lock_t 	lock1 = {ATOMIC_VAR_INIT(0)};//ATOMIC_FLAG_INIT;
sem_t 	sem1;;


void simple_lock_lock(lock_t *mutex) 
{ 
	while (atomic_flag_test_and_set(&mutex->cnt)) { 
	   	; // Wait the lock
	}
}

void simple_lock_unlock(lock_t *mutex) 
{ 
	atomic_flag_clear(&mutex->cnt);
}

#if 0
static int test_and_set(int *x)
{
	if (*x == 0) {
		return 1;
	} else {
		*x = 0; 
		return 0;
	}
}

void simple_lock_init(lock_t *mutex) { 
	// 0: lock is available // 1: lock is held 
	mutex->cnt = 1; 
} 

void simple_lock_lock(lock_t *mutex) 
{ 
	while (test_and_set(&mutex->cnt)) { 
	   	; // Wait the lock
	}
}

void simple_lock_unlock(lock_t *mutex) 
{ 
	if (mutex->cnt == 1) {
		printf ("Something is not correct\n");
		return;
	}
	
	mutex->cnt = 1; 
}


#define BUSY -1
int simple_lock_trylock(lock_t *mutex) 
{ 
	if (mutex->cnt == 1) {
		return BUSY;
	} 
	
	mutex->cnt = 1;
	return 0;
}
#endif

void simple_sem_init(sem_t *sem, int n) 
{ 
	atomic_init(&sem->cnt, n);
} 

void simple_sem_p(sem_t *sem) 
{ 
	while (atomic_load(&sem->cnt) == 0) { 
		;  // Wait the lock
	} 

	atomic_fetch_sub(&sem->cnt, 1);
}

void simple_sem_v(sem_t *sem) 
{  
	atomic_fetch_add(&sem->cnt, 1);
}

static void * task1(void *argv)
{
	//simple_lock_lock(&lock1);
	simple_sem_p(&sem1);
	//sam_lock(&sam1);
	printf("hello task %d...\n", *(pthread_t)argv);
	simple_lock_unlock(&lock1);
	//simple_sem_v(&sem1);
	
	return NULL;
}

#if 0
shmid = shmget(AH_TPA_SHM_ID, sizeof(ah_tpa_shm_t), IPC_EXCL);
if ( shmid == -1 ) {
		ah_err("Failed to get TPA shared mem.");
		ah_tpa_v();
		return -1;
}
/* Attaches the shared memory to the process, 
 * get the pointer to the shared mem.
 */
*shm = ( ah_tpa_shm_t *)shmat( shmid, NULL, 0 );
#endif

typedef struct {
	pthread_cond_t 		cond;
	pthread_mutex_t 	mutex;
	uint				N;
} Sam;
Sam 	sam1;

void sam_init(Sam * ps, int N)
{
	pthread_mutex_init(&ps->mutex, NULL);
	pthread_cond_init(&ps->cond, NULL);
	ps->N = N;
}

void sam_deinit(Sam * ps)
{
	pthread_mutex_destroy (&ps->mutex);
	pthread_cond_destroy (&ps->cond);
}

void sam_lock (Sam *ps)
{
	pthread_mutex_lock (&ps->mutex);

	while (ps->N == 0) {
		pthread_cond_wait(&ps->cond, &ps->mutex);
	}
	
	--(ps->N);

	pthread_mutex_unlock (&ps->mutex);
}

void sam_unlock (Sam * ps)
{
	pthread_mutex_lock (&ps->mutex);
	++(ps->N);
	pthread_mutex_unlock (&ps->mutex);

	pthread_cond_signal(&ps->cond);
}



int main ()
{
	pthread_t pid, pid2, pid3;
	
	
	//simple_lock_init( &lock1);
	simple_sem_init (&sem1, 2);
	//sam_init(&sam1, 2);
	
	printf ("Exec mutex ...\n");

	if (0 != pthread_create(&pid, NULL, task1, &pid)) {
		return -1;
	}

	if (0 != pthread_create(&pid, NULL, task1, &pid2)) {
		return -1;
	}
	if (0 != pthread_create(&pid, NULL, task1, &pid3)) {
		return -1;
	}

	//sam_lock(&sam1);
	//simple_lock_lock(&lock1);
	simple_sem_p(&sem1);
	printf("In main ...\n");
	//simple_lock_unlock(&lock1);
	simple_sem_v(&sem1);
	//sam_unlock(&sam1);

	pthread_join(pid, NULL);
	pthread_join(pid2, NULL);
	pthread_join(pid3, NULL);
	
	return 0;
}

