CC :=                   gcc
CFLAGS +=               -Wall -Werror -Wextra
LDFLAGS +=              -Wall -Werror -Wextra

SRC_DIR := ./lib/
OBJ_DIR := ./objects/

SRC :=                  $(wildcard $(SRC_DIR)*.c)
OBJ :=                  $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_PROFILED :=         $(OBJ:.o=_profiled.o)

TEST_DIR :=             ./tests/
TEST_SRC :=             $(wildcard $(TEST_DIR)*.c)
TEST_OBJ :=             $(TEST_SRC:.c=.o) 
TEST_EXEC :=            $(TEST_DIR)tests_s21_decimal.out

TEST_PROFILE_DATA =     $(wildcard $(OBJ_DIR)*.gcda $(OBJ_DIR)*.gcno $(TEST_DIR)*.gcda $(TEST_DIR)*.gcno)

COVERAGE_REPORT_DIR :=  ./coverage/
COVERAGE_FILE :=        coverage.info

LIB :=                  s21_decimal.a

.PHONY: test tests echo clean lint coverage_report gcov_report

all: $(LIB)

echo:
	@echo LIB=$(LIB)
	@echo CFLAGS=$(CFLAGS)
	@echo CC=$(CC)
	@echo SRC=$(SRC)
	@echo OBJ=$(OBJ)
	@echo LDLIBS=$(LDLIBS)
	@echo OBJ_PROFILED=$(OBJ_PROFILED)
	@echo TEST_PROFILE_DATA=$(TEST_PROFILE_DATA)

lint:
	@cp ../materials/linters/CPPLINT.cfg .
	@python3 ../materials/linters/cpplint.py --extension=c $(SRC_DIR)* $(TEST_DIR)*
	@rm CPPLINT.cfg

test: tests

tests: CFLAGS += --coverage -g
tests: LDFLAGS += --coverage
tests: CFLAGS += $(shell pkg-config --cflags-only-I check)
tests: LDLIBS += $(shell pkg-config --libs check)
tests: $(TEST_EXEC)
	@$^

coverage_report: tests
	lcov --capture --directory $(OBJ_DIR) --output-file $(COVERAGE_FILE)

gcov_report: coverage_report
	genhtml $(COVERAGE_FILE) --output-directory $(COVERAGE_REPORT_DIR)

$(LIB): $(OBJ)
	$(AR) -rcs $@ $^

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(OBJ_DIR)%_profiled.o: $(SRC_DIR)%.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(TEST_DIR)%.o: $(TEST_DIR)%.c
	$(CC) -c $(CFLAGS) $^ -o $@

$(TEST_EXEC): $(TEST_OBJ) $(OBJ_PROFILED)
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -rf 	$(OBJ) $(LIB)
	rm -rf $(TEST_OBJ) $(TEST_EXEC) $(TEST_PROFILE_DATA) $(OBJ_PROFILED)
	rm -rf 	$(COVERAGE_FILE) $(COVERAGE_REPORT_DIR)