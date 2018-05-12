int __cdecl __noreturn main(int argc, const char **argv, const char **envp) {
  if (argc == 2) {
    pin = atoi(argv[1]);
    mainPrg();
  } else {
    printf(help);
  }
  exit(0);
}

char *mainPrg() {
  char *result; // eax
  char *retaddr; // [esp+4h] [ebp+4h]

  printf(title);
  result = retaddr + 229;
  if (retaddr == (char *)-229)
    result = (char *)checkpin(0);
  return result;
}

int checkpin() {
  int result; // eax

  if (dword_204B >= dword_20AF)
    result = printqr(&qr2);
  else
    result = printqr(&qr1);
  return result;
}

int __cdecl printqr(int a1) {
  int v1; // edi
  int v3; // [esp+0h] [ebp-8h]
  int v4; // [esp+4h] [ebp-4h]

  v3 = 0;
  printf(nl);
  do {
    printf(white);
    v1 = *(_DWORD *)(a1 + 4 * v3) << 6;
    v4 = 0;
    while (1) {
      if (v1 >= 0)
        printf(white);
      else
        printf((const char *)&black);
      if (++v4 == 25)
        break;
      v1 *= 2;
    }
    printf(nl);
    ++v3;
  } while (v3 != 25);
  return printf(nl);
}

void __usercall sub_75B(int a1@<ebp>) {
  int v1; // ebx
  int v2; // ecx
  int v3; // eax
  int v4; // ecx

  v1 = 0;
  v2 = 0;
  do
    v1 += *((_DWORD *)&qr1 + v2++); // sums all int elements of qr1 array
  while (v2 != 25);
  v3 = *((_DWORD *)&qr1 - 1); // loads entered pin which is stored right before qr1
  if (v3 == v1) { // pin == sum(qr1) ?
    v4 = 0;
    do
      *((_DWORD *)&qr1 + v4++ + 25) -= v3; // subtracts pin value from the elements of qr2 (&qr1 + 25 points to qr2)
    while (v4 != 25);
  }
  JUMPOUT(__CS__, *(_DWORD *)(a1 + 4) + 62);
}