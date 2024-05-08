#include "testlib.h"
using namespace std;

const int MAXN = 1'000'000;
const int MAXT = 1'000;
const int MAXv = 1'000'000'000;

int main() {
	registerValidation();
  int N = inf.readInt(0, MAXN, "N");
	inf.readSpace();
	int T = inf.readInt(0, MAXT, "T");
	inf.readEoln();

  for (int i = 1; i <= N; i++) {
    inf.readInt(0, MAXv, "a");
    if (i != N) inf.readSpace();
    else inf.readEoln();
  }
  int len = N;
  while (T--) {
    int op = inf.readInt(1, 3, "op");
    inf.readSpace();
    if (op == 1) {
      inf.ensure(len >= 1);
      inf.readInt(1, len, "k");
      len--;
    } else if (op == 2) {
      inf.readInt(0, len, "k");
      inf.readSpace();
      inf.readInt(0, MAXv, "b");
      len++;
    } else if (op == 3) {
      inf.readInt(1, len, "l");
      inf.readSpace();
      inf.readInt(1, len, "r");
    }
    inf.readEoln();
  }

	inf.readEof();
	return 0;
}
