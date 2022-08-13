OBJ_DIR=build/
OBJECT_SERVER=$(OBJ_DIR)server.o
OBJECT_CLIENT=$(OBJ_DIR)client.o
OBJECT_SERVER_THPOOL=$(OBJ_DIR)thpoolserver.o
OBJECT_THPOOL=$(OBJ_DIR)test_threadpool.o
THPOOL_SOURCE=simpleThreadpool/threadpool.c 
THPOOL_TEST_SOURCE=simpleThreadpool/test_threadpool.c 
LIST_SOURCE=list/list.c
RWLOCK_SOURCE=rwlock/rwlock.c
SERVER_SOURCE=socket/server.c
SERVER_THPOOL_SOURCE=Threadpoolsocket/server.c
CLIENT_SOURCE=client.c


CC = gcc
.PHONY: clean
CFLAGS= -pthread -g -O0 -o
all:mkbuild $(OBJECT_SERVER) $(OBJECT_CLIENT) $(OBJECT_SERVER_THPOOL)
$(OBJECT_SERVER) : $(SERVER_SOURCE) 
	$(CC) $(CFLAGS) $@ $^
$(OBJECT_SERVER_THPOOL): $(SERVER_THPOOL_SOURCE) $(THPOOL_SOURCE) $(LIST_SOURCE) $(RWLOCK_SOURCE)
	$(CC) $(CFLAGS) $@ $^
$(OBJECT_CLIENT): $(CLIENT_SOURCE)
	$(CC) $(CFLAGS) $@ $^

threadpool: mkbuild $(OBJECT_THPOOL)
$(OBJECT_THPOOL):$(THPOOL_SOURCE) $(THPOOL_TEST_SOURCE) $(LIST_SOURCE) 
	$(CC) $(CFLAGS) $@ $^
runserver:
	./$(OBJECT_SERVER_THPOOL)
runclient:
	./$(OBJECT_CLIENT)
mkbuild:
	mkdir -p $(OBJ_DIR)
clean:
	rm -rf $(OBJ_DIR) >/dev/null 2>/dev/null || true
	rm -rf time.txt
	