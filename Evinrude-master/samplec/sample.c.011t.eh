
;; Function main (main, funcdef_no=6, decl_uid=1810, cgraph_uid=6)

main ()
{
  char string[12];
  int D.1814;

  string = "Hello World";
  __builtin_puts (&string);
  D.1814 = 0;
  goto <D.1816>;
  <D.1816>:
  string = {CLOBBER};
  goto <D.1815>;
  <D.1815>:
  return D.1814;
}


