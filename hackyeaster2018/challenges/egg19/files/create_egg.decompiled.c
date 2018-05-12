int __cdecl main(int argc, const char **argv, const char **envp) {
  char *v3; // r12
  size_t v4; // rcx
  size_t v5; // rdx
  _BYTE *v6; // rcx
  char *v7; // rbx
  char *v8; // rdi
  FILE *v9; // rbx
  int result; // eax
  int *v11; // [rsp+0h] [rbp-48h]
  size_t n; // [rsp+8h] [rbp-40h]
  int v13; // [rsp+10h] [rbp-38h]
  int v14; // [rsp+14h] [rbp-34h]
  int v15; // [rsp+18h] [rbp-30h]
  int v16; // [rsp+1Ch] [rbp-2Ch]
  unsigned __int64 v17; // [rsp+28h] [rbp-20h]

  v17 = __readfsqword(0x28u);
  v3 = (char *)malloc(0x3D08uLL);
  memcpy(v3, &c, 0x3D08uLL);
  __printf_chk(1LL, "Enter password: ");
  v11 = 0LL;
  n = 0LL;
  getline((char **)&v11, &n, stdin);
  v4 = n;
  if (n <= 8) {
    if (!n)
      goto LABEL_5;
  } else {
    n = 8LL;
  }
  v5 = 0LL;
  do {
    v6 = (char *)v11 + v5++;
    *v6 = *v6 & 0xDF | 0x40;
    v4 = n;
  } while (n > v5);
LABEL_5:
  v7 = v3;
  v13 = *v11;
  v14 = *(int *)((char *)v11 + 4 % v4);
  v15 = *(int *)((char *)v11 + 8 % v4);
  v16 = *(int *)((char *)v11 + 0xC % v4);
  do {
    v8 = v7;
    v7 += 8;
    d(v8, &v13);
  } while (v7 != v3 + 0x3D08);
  v9 = fopen("egg", "w");
  result = 1;
  if ( v9 ) {
    fwrite(v3, 1uLL, 0x3D08uLL, v9);
    fclose(v9);
    result = 0;
  }
  return result;
}

__int64 __fastcall d(unsigned int *a1, int *a2) {
  unsigned int v2; // ecx
  unsigned int v3; // edx
  int v4; // er11
  int v5; // er10
  int v6; // er9
  int v7; // er8
  signed int v8; // esi
  __int64 result; // rax

  v2 = *a1;
  v3 = a1[1];
  v4 = *a2;
  v5 = a2[1];
  v6 = a2[2];
  v7 = a2[3];
  v8 = 0xC6EF3720;
  do {
    v3 -= (v2 + v8) ^ (v7 + (v2 >> 5)) ^ (v6 + 16 * v2);
    result = (v3 + v8) ^ (v5 + (v3 >> 5)) ^ (v4 + 16 * v3);
    v2 -= result;
    v8 += 0x61C88647;
  } while ( v8 );
  *a1 = v2;
  a1[1] = v3;
  return result;
}