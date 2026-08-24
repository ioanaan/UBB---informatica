#include "teste.h"
#include "fisierRepo.h"
#include "service.h"

void testGetAll() {
	FisierRepo repo{ "test.txt" };
	Service service{ repo };

	assert(service.getAll().size() >= 0);
}

void testAll() {
	testGetAll();
}