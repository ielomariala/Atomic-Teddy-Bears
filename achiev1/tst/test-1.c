#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "testing_functions.h"


int main ()
{
  int c = wallet_tests() + stockex_tests() + queue_tests() + stock_change_tests_loop();
  printf("\n----------------------------\nTotal: %d / 17 tests valides\n",c);
  return 0;
}
