#include "good.h"
#include "stockex.h"
#include "queue.h"
#include "utility.h"
#include "testing_functions.h"

int main ()
{
  printf("\n----------------------------\nTotal: %d / 9 tests valides\n",wallet_tests() + stockex_tests() + queue_tests());
  return 0;
}
