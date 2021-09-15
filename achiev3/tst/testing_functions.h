#include <getopt.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAX_GOODS 20
#define MAX_PARTY_TIME 1000
#define MAX_TED 20
#define MAX_STOCKEX 100
#define MAX_TRANSAC 100

int wallet_tests();

int stockex_tests();

int queue_tests();

int stock_change_tests(int test);

int stock_change_tests_loop();

int strategy_tests(int test);

int strategy_tests_loop();

int good_rare_tests(int test);

int good_rare_tests_loop();
