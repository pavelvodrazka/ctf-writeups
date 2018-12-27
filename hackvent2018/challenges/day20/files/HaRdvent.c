__int64 __fastcall sub_88(__int64 a1, __int64 a2, __int64 a3, __int64 a4, __int64 a5, __int64 a6, __int64 a7, __int64 a8, __int64 a9)
{
  __int64 v9; // x27
  __int64 v10; // x30
  __int64 v11; // x25
  __int64 v12; // x26
  __int64 *v13; // x0
  signed __int64 v14; // x1
  _QWORD *i; // x0
  __int64 v16; // x0
  __int64 v17; // x1
  __int64 v19; // [xsp+28h] [xbp-B8h]
  char v20; // [xsp+48h] [xbp-98h]

  v11 = a1;
  v12 = a2;
  v13 = &qword_38240;
  v14 = 51232LL;
  do
  {
    *v13 = 0LL;
    ++v13;
    v14 -= 8LL;
  }
  while ( v14 );
  qword_40638 = (__int64)&a9;
  sub_70D0(v10 - 136, (__int64 *)&unk_315C0);
  sub_7320(v11, v12, v9);
  sub_4EA0(0LL, qword_40640);
  strcpy(&v19, "shuffle*whip$crush%squeeze");                // v19 = key
  sub_10580((__int64)&v20, (__int64 *)&unk_26000, 0x98uLL);  // v20 = ciphertext
  sub_6E0((__int64)&v19, 27LL, (__int64)&v20, 152LL);        // decrypt(key, 27, ciphertext, 152)
  for ( i = (_QWORD *)sub_108F8("\x1B[16;10H%s", &v20); ; i = sub_5010(0LL) )
  {
    v16 = ((__int64 (__fastcall *)(_QWORD *))loc_23D0)(i);
    if ( !(_BYTE)v16 )
      break;
    sub_2C70(v16, v17);
    if ( sub_2BF0(10LL) & 0x400 )
      break;
  }
  sub_4FC0(0LL);
  return 0LL;
}

__int64 __fastcall sub_6E0(__int64 a1, __int64 a2, __int64 a3, __int64 a4)
{
  __int64 v4; // x19
  __int64 result; // x0
  _BYTE *v6; // x19
  unsigned __int8 v7; // w0
  _BYTE *v8; // x14
  __int64 v9; // [xsp+28h] [xbp+28h]

  v4 = a4;
  v9 = a3;
  result = sub_670(a1, a2);      // keysetup(key, key_length)
  if ( v4 )
  {
    v6 = (_BYTE *)(v9 + v4);
    do
    {
      v7 = sub_520();            // drip()
      result = (unsigned __int8)*v8 - (unsigned int)v7;
      *v8 = result;
    }
    while ( v8 + 1 != v6 );
  }
  return result;
}

__int64 sub_520()
{
  int v0; // w4
  int v1; // w2
  __int64 result; // x0

  if ( *off_34298 )
    sub_3F0();
  sub_360();
  v0 = (unsigned __int8)*off_34048;
  v1 = (*(unsigned __int8 *)(off_34260 + (((unsigned __int8)*off_34148 + (unsigned __int8)*off_340E0) & 0xFF))
      + (unsigned __int8)*off_34160) & 0xFF;
  result = *(unsigned __int8 *)(off_34260 + ((*(unsigned __int8 *)(off_34260 + v1) + v0) & 0xFF));
  *off_34148 = *(_BYTE *)(off_34260 + ((*(unsigned __int8 *)(off_34260 + v1) + v0) & 0xFF));
  return result;
}

__int64 __fastcall sub_670(__int64 result, __int64 a2)
{
  unsigned __int8 *v2; // x19
  __int64 v3; // x21
  unsigned int v4; // t1
  char *v5; // x9
  __int64 v6; // x2
  _BYTE *v7; // x8
  _BYTE *v8; // x6
  char *v9; // x5
  char *v10; // x4
  __int64 v11; // x3

  v5 = off_34148;
  v6 = 0LL;
  v7 = (_BYTE *)off_340E0;
  *off_34048 = 0;
  v8 = (_BYTE *)off_34160;
  *v5 = 0;
  v9 = off_34298;
  *v7 = 0;
  v10 = off_340C8;
  *v8 = 0;
  v11 = off_34260;
  *v9 = 0;
  *v10 = 1;
  do
  {
    *(_BYTE *)(v6 + v11) = v6;
    ++v6;
  }
  while ( v6 != 256 );
  if ( a2 )
  {
    v2 = (unsigned __int8 *)result;
    v3 = result + a2;
    do
    {
      v4 = *v2++;
      sub_5B0(v4 & 0xF);
      result = sub_5B0(((unsigned __int64)v4 >> 4) & 0xFF);
    }
    while ( (unsigned __int8 *)v3 != v2 );
  }
  return result;
}

__int64 __fastcall sub_5B0(unsigned __int8 a1)
{
  __int64 (__fastcall **v1)(); // x15
  int v2; // w14
  char *v3; // x18
  int v4; // w2
  __int64 result; // x0
  __int64 v6; // x1
  char *v7; // x3
  char v8; // w4

  v1 = off_34000;
  v2 = a1;
  v3 = off_34298;
  v4 = (unsigned __int8)*off_34298;
  if ( v4 == 128 )
  {
    sub_3F0();
    v4 = (unsigned __int8)*v3;
  }
  result = (v2 - 128) & 0xFF;
  v6 = off_34260;
  v7 = off_34018;
  *(_BYTE *)v1[83] = v4 + 1;
  v8 = *(_BYTE *)(v6 + v4);
  *(_BYTE *)(v6 + v4) = *(_BYTE *)(v6 + (signed int)result);
  *(_BYTE *)(v6 + (signed int)result) = v8;
  *v7 = v8;
  return result;
}

__int64 sub_3F0()
{
  int v0; // w8
  signed int v1; // w4
  signed __int64 v2; // x11
  _BYTE *v3; // x1
  char v4; // w5
  char *v5; // x0
  unsigned int v6; // w2
  unsigned int v7; // w3
  unsigned __int8 *v8; // x8
  _BYTE *v9; // x9
  unsigned __int8 *v10; // x11
  __int64 v11; // x12
  __int64 v12; // x13
  int v13; // w10
  signed int v14; // w2
  unsigned __int8 v15; // w3
  unsigned int v16; // w0
  unsigned int v17; // w1
  __int64 v18; // x12
  int v19; // w8
  _BYTE *v20; // x12
  int v21; // w0
  __int64 result; // x0

  do
    sub_360();
  while ( v0 != 1 );
  v1 = 0;
  v2 = off_34260 + 128LL;
  v3 = (_BYTE *)(off_34260 + 255LL);
  v4 = *off_34018;
  v5 = (char *)off_34260;
  *off_340C8 += 2;
  do
  {
    v6 = (unsigned __int8)*v5;
    v7 = (unsigned __int8)*v3;
    if ( v6 > v7 )
    {
      v4 = *v5;
      v1 = 1;
      *v5 = v7;
      *v3 = v6;
    }
    ++v5;
    --v3;
  }
  while ( v5 != (char *)v2 );
  if ( v1 )
    *off_34018 = v4;
  do
    sub_360();
  while ( v13 != 1 );
  v14 = 0;
  v15 = **(_BYTE **)(v12 + 24);
  **(_BYTE **)(v11 + 200) += 2;
  do
  {
    v16 = *v8;
    v17 = (unsigned __int8)*v9;
    if ( v16 > v17 )
    {
      v15 = *v8;
      v14 = 1;
      *v8 = v17;
      *v9 = v16;
    }
    ++v8;
    --v9;
  }
  while ( v8 != v10 );
  if ( v14 )
    **(_BYTE **)(v12 + 24) = v15;
  do
    sub_360();
  while ( v19 != 1 );
  v20 = *(_BYTE **)(v18 + 200);
  v21 = (unsigned __int8)*v20;
  *off_34298 = 0;
  result = (unsigned int)(v21 + 2);
  *v20 = result;
  return result;
}

__int64 sub_360()
{
  __int64 v0; // x2
  _BYTE *v1; // x5
  _BYTE *v2; // x4
  int v3; // w1
  char *v4; // x7
  int v5; // w6
  int v6; // w3
  int v7; // w0
  __int64 result; // x0

  v0 = off_34260;
  v1 = (_BYTE *)off_34048;
  v2 = (_BYTE *)off_340E0;
  v3 = ((unsigned __int8)*off_34160 + (unsigned __int8)*off_340C8) & 0xFF;
  v4 = off_34018;
  v5 = *(unsigned __int8 *)(off_34260 + v3);
  *off_34160 += *off_340C8;
  v6 = (unsigned __int8)*v1;
  v7 = (unsigned __int8)*v2;
  *v4 = v5;
  LODWORD(v4) = *(unsigned __int8 *)(v0 + ((v5 + v6) & 0xFF));
  LOBYTE(v6) = v3 + v7;
  result = (v7 + (_DWORD)v4) & 0xFF;
  LOBYTE(v4) = *(_BYTE *)(v0 + (signed int)result);
  *v1 = result;
  *(_BYTE *)(v0 + v3) = (_BYTE)v4;
  *(_BYTE *)(v0 + (signed int)result) = v5;
  *v2 = (_BYTE)v4 + v6;
  return result;
}
