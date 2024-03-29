#include <stdio.h>
#include <fenv.h>
#include <math.h>
#include <float.h>

#define _show_exc(x)	printf(#x"=%s;", fetestexcept(x) ? "ON" : "OFF")

#pragma STDC FENV_ACCESS ON

void
show_exc (void)
{
  _show_exc (FE_DIVBYZERO);
  _show_exc (FE_INEXACT);
  _show_exc (FE_INVALID);
  _show_exc (FE_OVERFLOW);
  _show_exc (FE_UNDERFLOW);
  puts ("");
}

void
show_round (void)
{
  int r = fegetround ();
  char *rs;
  switch (r)
    {
    case FE_TONEAREST:
      rs = "FE_TONEAREST";
      break;
    case FE_UPWARD:
      rs = "FE_UPWARD";
      break;
    case FE_DOWNWARD:
      rs = "FE_DOWNWARD";
      break;
    case FE_TOWARDZERO:
      rs = "FE_TOWARDZERO";
      break;
    default:
      rs = "unknown";
    }
  printf ("Rounding=%s\n\n", rs);
}

int
main (void)
{
  show_exc ();
  show_round ();
  fenv_t env;
  fegetenv (&env);
  fesetround (FE_TOWARDZERO);
  float x = 1.f, y = 0.f;
  printf ("%f\n", x / y);
  printf ("%f\n", sqrtf (-x));
  show_exc ();
  show_round ();
  feupdateenv (&env);
  show_exc ();
  show_round ();
  fesetenv (&env);
  show_exc ();
  show_round ();
  return 0;
}


/*
line 49: the program exposes statuses of the current floating-point exceptions and rounding settings;
line 52: we save the environment state;
line 53: we change the rounding setting and provoke some exceptions to raise;
line 57: we print the current state;
line 59: we update the environment (raised exceptions remain unchanged)
line 62: we restore the whole previous environment;
line 63: we show the restored environment.

*/