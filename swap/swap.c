#define _GNU_SOURCE

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <syscall.h>

#define PAGE_SIZE 4096

#define VMEM_PAGE_CNT 8
#define RAM_PARGE_CNT 4

#define VMEM_SIZE (VMEM_PAGE_CNT * PAGE_SIZE)
#define RAM_SIZE  (RAM_PARGE_CNT * PAGE_SIZE)

#define handle_error(msg) \
	do { perror(msg); exit(EXIT_FAILURE); } while (0)

char *vmem_base;
char *ram_base;
int memfd;

static int memfd_create(const char *name, unsigned int flags) {
	return syscall(SYS_memfd_create, name, flags);
}

static char *page_align_down(char *mem) {
	return (char *) ((((intptr_t) mem)) & -PAGE_SIZE);
}

static char *page_align_up(char *mem) {
	return page_align_down(mem + PAGE_SIZE - 1);
}

struct Page{
	int isUsed;
	int lastExec;
	char *addr;
};

struct Page schedule[RAM_PARGE_CNT];

void addNewPage(char *p){
	schedule[(int)p].isUsed = 1;
	int i;
	for (i = 0; i < RAM_PARGE_CNT; ++i){
		schedule[i].lastExec += schedule[i].isUsed;
	}
	schedule[(int)p].isUsed = 1;
}

char *findTarget(){
	char *target;
	int max = 0;
	int i;
	for (i = 0; i < RAM_PARGE_CNT; ++i){
		if (schedule[i].isUsed && schedule[i].lastExec > max){
			max = schedule[i].lastExec;
			target = ram_base + i * PAGE_SIZE;
		}
	}
	return target;
}

void access_handler(int signal, siginfo_t *info, void *ctx) {
	char *faulted_addr = info->si_addr;
	char *faulted_page = page_align_down(info->si_addr);
	static int count = 1;
	count = 1 - count;
	char *target_page = findTarget(); //ram_base + count * PAGE_SIZE;
	fprintf(stderr, "%s: faulted_addr=%p faulted_page=%p target_page=%p\n", __func__, faulted_addr, faulted_page, target_page);
	assert((vmem_base <= faulted_addr) && (faulted_addr < (vmem_base + VMEM_SIZE)));

	void *page_map = mmap(faulted_page, PAGE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_FIXED, memfd, target_page - ram_base);
	if (MAP_FAILED == page_map) {
		handle_error("single page mmap");
	}
	assert(page_map == faulted_page);
}

int main(int argc, char *argv[]) {
	const int page_size = sysconf(_SC_PAGE_SIZE);
	assert(PAGE_SIZE == page_size);

	struct sigaction sa = {
		.sa_sigaction = access_handler,
		.sa_flags = SA_SIGINFO,
	};

	sigemptyset(&sa.sa_mask);
	sigaction(SIGSEGV, &sa, NULL);

	memfd = memfd_create("ram", 0);
	if (-1 == memfd) {
		handle_error("memfd");
	}

	if (-1 == ftruncate(memfd, RAM_SIZE)) {
		handle_error("truncate");
	}

	ram_base = mmap(NULL, RAM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, memfd, 0);
	if (MAP_FAILED == ram_base) {
		handle_error("ram mmap");
	}

	vmem_base = mmap(NULL, VMEM_SIZE, PROT_NONE, MAP_SHARED, memfd, 0);
	if (MAP_FAILED == vmem_base) {
		handle_error("ram mmap");
	}

	fprintf(stderr, "vmem_base=%p ram_base=%p\n", vmem_base, ram_base);

	assert(RAM_PARGE_CNT < 26);
	for (int i = 0; i < RAM_PARGE_CNT; ++i) {
		memset(ram_base + i * PAGE_SIZE, 'a' + i, PAGE_SIZE);
		addNewPage(i);
	}

	for (int i = 0; i < VMEM_SIZE; i += PAGE_SIZE) {
		char c = 'Z';
		c = vmem_base[i]; // May segfault!
		fprintf(stderr, "addr=%p c=%c\n", vmem_base + i, c);
		c = vmem_base[i + 1];
		fprintf(stderr, "addr=%p c=%c\n", vmem_base + i + 1, c);
	}

	return 0;
}




