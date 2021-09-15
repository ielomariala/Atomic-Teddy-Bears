#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_GOODS 20
#define MAX_PARTY_TIME 1000
#define MAX_TED 20
#define MAX_STOCKEX 100
#define MAX_TRANSAC 100
#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "strategy.h"
#include "testing_functions.h"
#include <time.h>
#include <math.h>



int main ()
{
  int nbre_total_tests = 29;
  int c = wallet_tests() + stockex_tests() + queue_tests() + stock_change_tests_loop() + strategy_tests_loop() + good_rare_tests_loop() ;
  printf("\n----------------------------\nTotal: %d / %d tests valides\n",c, nbre_total_tests);
  return 0;
}
