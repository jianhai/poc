/*
 *
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define MAX 10
#define MAXLEN 4096

static pthread_t tid[MAX];
static pthread_t prob;

static void* sleepThread(void *arg)
{
	printf("Debug> pid:%d tpid:%ld\n", getpid(), syscall(SYS_gettid));

	sleep(10);

	return NULL;
}

static void * probThread(void *arg)
{
	int fd = 0;
	char buf[MAXLEN];

	printf("Debug> pid:%d tpid:%ld\n", getpid(), syscall(SYS_gettid));

	fd = open("/proc/eip", O_RDONLY);
	if (fd < 0)
		printf("Error open\n");

	memset(buf, 0, MAXLEN);
	read(fd, buf, MAXLEN);

	printf("%s\n", buf);

	close(fd);
	return NULL;
}

int main()
{
	int rc;
	int i;

	for (i=0; i< MAX; i++) {
		rc = pthread_create(&tid[i], NULL, sleepThread, NULL);
		if (rc) {
			printf("Error pthread_create\n");
			return -1;
		}
	}

	rc = pthread_create(&prob, NULL, probThread, NULL);
	if (rc) {
		printf("Error pthread_create\n");
	}

	rc = pthread_join(prob, NULL);
	if (rc) {
		printf("Error pthread_join\n");
	}

	for ( ; i>0; i--) {
		rc = pthread_join(tid[i], NULL);
	}

	return 0;
}
