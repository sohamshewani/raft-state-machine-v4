CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -pedantic -g
OBJS=src/main.o src/network.o src/storage.o src/state_machine.o src/leader_election.o src/log_compaction.o
TEST_OBJS=tests/test_raft.o tests/test_network.o tests/test_storage.o tests/test_state_machine.o tests/test_leader_election.o tests/test_log_compaction.o
TEST_PROGS=test_raft test_network test_storage test_state_machine test_leader_election test_log_compaction

all: main $(TEST_PROGS)

clean:
	@rm -f $(OBJS) $(TEST_OBJS) $(TEST_PROGS)

main: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lstdc++fs

%: %.cpp $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lstdc++fs

.PHONY: clean
