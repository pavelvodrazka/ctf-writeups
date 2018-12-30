/*
hardcoded rabbit cipher key:
DATA:00402171 unk_402171      db  87h ; ‡             ; DATA XREF: sub_401645+285↑o
DATA:00402172                 db    5
DATA:00402173                 db  89h ; ‰
DATA:00402174                 db 0CDh ; Í
DATA:00402175                 db 0A8h ; ¨
DATA:00402176                 db  75h ; u
DATA:00402177                 db  62h ; b
DATA:00402178                 db 0EFh ; ď
DATA:00402179                 db  38h ; 8
DATA:0040217A                 db  45h ; E
DATA:0040217B                 db 0FFh ; ˙
DATA:0040217C                 db 0D1h ; Ń
DATA:0040217D                 db  41h ; A
DATA:0040217E                 db  37h ; 7
DATA:0040217F                 db  54h ; T
DATA:00402180                 db 0D5h ; Ő
*/

void __stdcall sub_401645(HWND hWndParent, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  HANDLE v4; // eax
  _DWORD *v5; // ST34_4
  HGLOBAL v6; // eax
  const void *v7; // eax
  int v8; // ecx
  _BYTE *v9; // esi
  HANDLE v10; // eax

  switch ( Msg )
  {
    case 1u:
      dword_402288 = (int)CreateWindowExA(
                            0x200u,
                            aStatic,
                            0,
                            0x50010081u,
                            12,
                            20,
                            366,
                            20,
                            hWndParent,
                            (HMENU)0x7D0,
                            hWnd,
                            0);
      SetFocus((HWND)dword_402288);
      CreateWindowExA(0x20000u, aButton, aEncrypt, 0x50010000u, 12, 50, 60, 28, hWndParent, (HMENU)0xBB8, hWnd, 0);
      CreateWindowExA(0x20000u, aButton, aExit, 0x50010000u, 318, 50, 60, 28, hWndParent, (HMENU)0xFA0, hWnd, 0);
      sub_401A78(hWndParent);
      ::wParam = (WPARAM)CreateFontA(16, 0, 0, 0, 400, 0, 0, 0, 1u, 0, 0, 0, 0, pszFaceName);
      SendDlgItemMessageA(hWndParent, 2000, 0x30u, ::wParam, 0);
      SendDlgItemMessageA(hWndParent, 3000, 0x30u, ::wParam, 0);
      SendDlgItemMessageA(hWndParent, 4000, 0x30u, ::wParam, 0);
      SetDlgItemTextA(hWndParent, 2000, String);
      break;
    case 0x111u:
      if ( (unsigned __int16)wParam == 3000 )
      {
        v4 = CreateFileA(FileName, 0xC0000000, 3u, 0, 3u, 0, 0);
        if ( v4 == (HANDLE)-1 )
        {
          SetDlgItemTextA(hWndParent, 2000, aErrorCouldNotO);
        }
        else
        {
          hFile = v4;                                                   // flag file handle
          dwBytes = GetFileSize(v4, 0);
          if ( dwBytes % 2 )
            ++dwBytes;
          dword_402270 = GlobalAlloc(0x40u, dwBytes);
          hMem = GlobalLock(dword_402270);
          v5 = hMem;
          ReadFile(hFile, hMem, dwBytes, &NumberOfBytesRead, 0);        // read flag into v5
          CloseHandle(hFile);
          if ( *v5 == 0x474E5089 )                                      // check against PNG magic number
          {
            nNumberOfBytesToWrite = dwBytes >> 1;
            v6 = GlobalAlloc(0x40u, dwBytes >> 1);
            dword_402278 = v6;
            v7 = GlobalLock(v6);
            lpBuffer = v7;
            v8 = 0;
            v9 = hMem;
            while ( v8 != nNumberOfBytesToWrite )
            {                                                           // take only high half-bytes of flag
              *((_BYTE *)v7 + v8) = (v9[2 * v8 + 1] >> 4) | 16 * (v9[2 * v8] >> 4);
              ++v8;                                                     // combine each two of them into a single byte
            }                                                           // and store the result bytes into lpBuffer
            GlobalUnlock(hMem);
            GlobalFree(dword_402270);
            sub_4019F8();                                               // get current filetime and store it into FileTime
            sub_4013D7((int)&unk_4020D1, (unsigned int *)&unk_402171);  // setup hardcoded key
            sub_40121D((int)&unk_4020D1, (int *)&FileTime);             // setup initial vector from FileTime
            sub_401000(&unk_4020D1, lpBuffer, nNumberOfBytesToWrite);   // crypt stripped flag stored in lpBuffer
            v10 = CreateFileA(aFlagEncrypted, 0xC0000000, 3u, 0, 2u, 0, 0);
            if ( v10 == (HANDLE)-1 )                                    // encrypted flag file handle
            {
              SetDlgItemTextA(hWndParent, 2000, aErrorCouldNotW);
            }
            else
            {
              dword_402290 = v10;                                       // write encrypted flag to file
              if ( WriteFile(v10, lpBuffer, nNumberOfBytesToWrite, &NumberOfBytesRead, 0) )
                SetDlgItemTextA(hWndParent, 2000, aSuccessFlagEnc);
            }
          }
          else
          {
            SetDlgItemTextA(hWndParent, 2000, aErrorThisFlagI);
          }
          CloseHandle(dword_402290);
          GlobalUnlock((HGLOBAL)lpBuffer);
          GlobalFree(dword_402278);
        }
      }
      else if ( (unsigned __int16)wParam == 4000 )
      {
        PostQuitMessage(0);
      }
      break;
    case 0x201u:
      PostMessageA(hWndParent, 0xA1u, 2u, lParam);
      break;
    case 2u:
      PostQuitMessage(0);
      break;
    default:
      DefWindowProcA(hWndParent, Msg, wParam, lParam);
      break;
  }
}

LSTATUS sub_4019F8()
{
  RegCreateKeyExA(HKEY_CURRENT_USER, SubKey, 0, 0, 0, 0x4001Fu, 0, &hKey, 0);
  RegQueryInfoKeyA(hKey, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, &FileTime);
  RegCloseKey(hKey);
  FileTimeToSystemTime(&FileTime, &SystemTime);
  SystemTimeToFileTime(&SystemTime, &FileTime);
  return RegDeleteKeyA(HKEY_CURRENT_USER, SubKey);
}

int __cdecl sub_4013D7(int a1, unsigned int *a2)
{
  unsigned int v2; // ebx
  unsigned int v3; // edx
  unsigned int v4; // ebp
  unsigned int v5; // edi
  int v6; // ecx
  int v7; // eax
  signed int v8; // edi
  int result; // eax

  v2 = a2[3];
  v3 = a2[1];
  v4 = *a2;
  v5 = a2[2];
  v6 = *((_QWORD *)a2 + 1) >> 16;
  *(_DWORD *)(a1 + 16) = v5;
  *(_DWORD *)(a1 + 4) = v6;
  *(_DWORD *)a1 = v4;
  *(_DWORD *)(a1 + 12) = (v4 << 16) | (v2 >> 16);
  *(_DWORD *)(a1 + 8) = v3;
  *(_DWORD *)(a1 + 20) = (v4 >> 16) | (v3 << 16);
  *(_DWORD *)(a1 + 24) = v2;
  *(_DWORD *)(a1 + 28) = (v3 >> 16) | (v5 << 16);
  *(_DWORD *)(a1 + 32) = __ROL4__(v5, 16);
  *(_DWORD *)(a1 + 40) = __ROL4__(v2, 16);
  *(_DWORD *)(a1 + 48) = __ROL4__(v4, 16);
  *(_DWORD *)(a1 + 56) = __ROL4__(v3, 16);
  *(_DWORD *)(a1 + 64) = 0;
  *(_DWORD *)(a1 + 36) = v4 ^ (unsigned __int16)(v4 ^ v3);
  *(_DWORD *)(a1 + 44) = v3 ^ (unsigned __int16)(v3 ^ v5);
  v7 = v5 ^ (unsigned __int16)(v5 ^ v2);
  v8 = 4;
  *(_DWORD *)(a1 + 52) = v7;
  *(_DWORD *)(a1 + 60) = v2 ^ (unsigned __int16)(v4 ^ v2);
  do
  {
    sub_4010EC((_DWORD *)a1);
    --v8;
  }
  while ( v8 );
  *(_DWORD *)(a1 + 32) ^= *(_DWORD *)(a1 + 16);
  *(_DWORD *)(a1 + 36) ^= *(_DWORD *)(a1 + 20);
  *(_DWORD *)(a1 + 40) ^= *(_DWORD *)(a1 + 24);
  *(_DWORD *)(a1 + 44) ^= *(_DWORD *)(a1 + 28);
  *(_DWORD *)(a1 + 48) ^= *(_DWORD *)a1;
  *(_DWORD *)(a1 + 52) ^= *(_DWORD *)(a1 + 4);
  *(_DWORD *)(a1 + 56) ^= *(_DWORD *)(a1 + 8);
  *(_DWORD *)(a1 + 60) ^= *(_DWORD *)(a1 + 12);
  result = *(_DWORD *)(a1 + 64);
  *(_OWORD *)(a1 + 68) = *(_OWORD *)a1;
  *(_OWORD *)(a1 + 84) = *(_OWORD *)(a1 + 16);
  *(_OWORD *)(a1 + 100) = *(_OWORD *)(a1 + 32);
  *(_OWORD *)(a1 + 116) = *(_OWORD *)(a1 + 48);
  *(_DWORD *)(a1 + 132) = result;
  return result;
}

int __cdecl sub_40121D(int a1, int *a2)
{
  int v2; // ebx
  _DWORD *v3; // esi
  int v4; // edi
  int v5; // edx
  unsigned int v6; // ecx
  int v7; // edx
  int v8; // eax
  char *v9; // edi
  unsigned int v10; // ecx
  unsigned int v11; // eax
  _DWORD *v12; // esi
  signed int v13; // ebx
  BOOL v14; // eax
  unsigned int v15; // ecx
  unsigned int v16; // eax
  BOOL v17; // eax
  unsigned int v18; // ecx
  unsigned int v19; // eax
  BOOL v20; // eax
  unsigned int v21; // ecx
  unsigned int v22; // eax
  BOOL v23; // eax
  unsigned int v24; // ecx
  unsigned int v25; // eax
  BOOL v26; // eax
  unsigned int v27; // ecx
  unsigned int v28; // eax
  BOOL v29; // eax
  unsigned int v30; // ecx
  unsigned int v31; // eax
  BOOL v32; // eax
  unsigned int v33; // ecx
  unsigned int v34; // eax
  signed int v35; // esi
  int result; // eax
  int v37; // ecx
  int v38; // [esp+Ch] [ebp-24h]
  int v39; // [esp+10h] [ebp-20h]
  int v40[7]; // [esp+14h] [ebp-1Ch]
  signed int v41; // [esp+38h] [ebp+8h]

  v2 = a2[1];
  v3 = (_DWORD *)a1;
  v4 = *a2;
  v5 = a2[1] << 16;
  v6 = ((unsigned int)*a2 >> 16) | a2[1] & 0xFFFF0000;
  v41 = 4;
  v7 = (unsigned __int16)v4 | v5;
  *(_DWORD *)(a1 + 100) = v4 ^ *(_DWORD *)(a1 + 32);
  v3[26] = v6 ^ v3[9];
  v3[27] = v2 ^ v3[10];
  v3[28] = v7 ^ v3[11];
  v8 = v4 ^ *(_DWORD *)(a1 + 48);
  v9 = (char *)(a1 + 68);
  *(_DWORD *)(a1 + 116) = v8;
  v3[30] = v6 ^ v3[13];
  v3[31] = v2 ^ v3[14];
  *(_DWORD *)(a1 + 128) = v7 ^ *(_DWORD *)(a1 + 60);
  *(_OWORD *)v9 = *(_OWORD *)a1;
  *((_OWORD *)v9 + 1) = *(_OWORD *)(a1 + 16);
  do
  {
    v10 = *(_DWORD *)(a1 + 100);
    v11 = v10 + *(_DWORD *)(a1 + 132) + 1295307597;
    v12 = (_DWORD *)(a1 + 68);
    *(_DWORD *)(a1 + 100) = v11;
    v13 = 8;
    v14 = v11 < v10;
    *(_DWORD *)(a1 + 132) = v14;
    v15 = *(_DWORD *)(a1 + 104);
    v16 = v15 + v14 - 749914925;
    *(_DWORD *)(a1 + 104) = v16;
    v17 = v16 < v15;
    *(_DWORD *)(a1 + 132) = v17;
    v18 = *(_DWORD *)(a1 + 108);
    v19 = v18 + v17 + 886263092;
    *(_DWORD *)(a1 + 108) = v19;
    v20 = v19 < v18;
    *(_DWORD *)(a1 + 132) = v20;
    v21 = *(_DWORD *)(a1 + 112);
    v22 = v21 + v20 + 1295307597;
    *(_DWORD *)(a1 + 112) = v22;
    v23 = v22 < v21;
    *(_DWORD *)(a1 + 132) = v23;
    v24 = *(_DWORD *)(a1 + 116);
    v25 = v24 + v23 - 749914925;
    *(_DWORD *)(a1 + 116) = v25;
    v26 = v25 < v24;
    *(_DWORD *)(a1 + 132) = v26;
    v27 = *(_DWORD *)(a1 + 120);
    v28 = v27 + v26 + 886263092;
    *(_DWORD *)(a1 + 120) = v28;
    v29 = v28 < v27;
    *(_DWORD *)(a1 + 132) = v29;
    v30 = *(_DWORD *)(a1 + 124);
    v31 = v30 + v29 + 1295307597;
    *(_DWORD *)(a1 + 124) = v31;
    v32 = v31 < v30;
    *(_DWORD *)(a1 + 132) = v32;
    v33 = *(_DWORD *)(a1 + 128);
    v34 = v33 + v32 - 749914925;
    *(_DWORD *)(a1 + 128) = v34;
    *(_DWORD *)(a1 + 132) = v34 < v33;
    do
    {
      *(_DWORD *)((char *)v12 + (char *)&v39 - v9) = sub_4010E1(*v12 + v12[8]);
      ++v12;
      --v13;
    }
    while ( v13 );
    v35 = 0;
    result = 7;
    do
    {
      *(_DWORD *)&v9[4 * v35] = *(&v39 + v35) + __ROL4__(*(&v39 + result), 16) + __ROL4__(*(&v38 + result), 16);
      v37 = v40[v35] + *(&v39 + result) + __ROL4__(*(&v39 + (((_BYTE)result + 1) & 7)), 8);
      result = ((_BYTE)result + 2) & 7;
      *(_DWORD *)&v9[4 * v35 + 4] = v37;
      v35 += 2;
    }
    while ( v35 < 8 );
    --v41;
  }
  while ( v41 );
  return result;
}

char __cdecl sub_401000(_DWORD *a1, _BYTE *a2, int a3)
{
  _BYTE *v3; // esi
  _DWORD *v4; // edi
  int *v5; // ebx
  int v6; // edx
  int v7; // ebx
  int v8; // ebp
  unsigned int v9; // edi
  int v10; // eax
  int v11; // ecx
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  unsigned int v16; // edx
  int v17; // ecx
  int v18; // ecx
  int v19; // ecx
  unsigned int v21; // [esp+4h] [ebp-10h]
  int v22; // [esp+8h] [ebp-Ch]
  int v23; // [esp+Ch] [ebp-8h]
  int v24; // [esp+10h] [ebp-4h]

  v3 = a2;
  if ( a3 )
  {
    v4 = a1;
    v5 = a1 + 17;
LABEL_3:
    sub_4010EC(v5);
    v6 = *v5;
    v7 = v4[19];
    v8 = v4[21];
    v9 = v4[22];
    v21 = (v9 >> 16) ^ (a1[20] << 16) ^ v6;
    v10 = (v9 << 16) ^ (a1[24] >> 16);
    v11 = a1[24] << 16;
    v4 = a1;
    v22 = v10 ^ v7;
    v12 = v11 ^ (a1[18] >> 16);
    v13 = a3;
    v14 = (a1[20] >> 16) ^ (a1[18] << 16);
    v23 = v12 ^ v8;
    v15 = v14 ^ a1[23];
    v16 = 0;
    v24 = v15;
    while ( v13 )
    {
      LOBYTE(v15) = *((_BYTE *)&v21 + v16);
      *v3 ^= v15;
      v17 = v13 - 1;
      if ( !v17 )
        break;
      LOBYTE(v15) = *((_BYTE *)&v21 + v16 + 1);
      v3[1] ^= v15;
      v18 = v17 - 1;
      if ( !v18 )
        break;
      LOBYTE(v15) = *((_BYTE *)&v21 + v16 + 2);
      v3[2] ^= v15;
      v19 = v18 - 1;
      if ( !v19 )
        break;
      LOBYTE(v15) = *((_BYTE *)&v21 + v16 + 3);
      v13 = v19 - 1;
      v3[3] ^= v15;
      v16 += 4;
      v3 += 4;
      a3 = v13;
      if ( v16 >= 0x10 )
      {
        v5 = a1 + 17;
        if ( v13 )
          goto LABEL_3;
        return v15;
      }
    }
  }
  return v15;
}

int __cdecl sub_4010EC(_DWORD *a1)
{
  _DWORD *v1; // esi
  signed int v2; // ebx
  unsigned int v3; // ecx
  unsigned int v4; // eax
  BOOL v5; // eax
  unsigned int v6; // ecx
  unsigned int v7; // eax
  BOOL v8; // eax
  unsigned int v9; // ecx
  unsigned int v10; // eax
  BOOL v11; // eax
  unsigned int v12; // ecx
  unsigned int v13; // eax
  BOOL v14; // eax
  unsigned int v15; // ecx
  unsigned int v16; // eax
  BOOL v17; // eax
  unsigned int v18; // ecx
  unsigned int v19; // eax
  BOOL v20; // eax
  unsigned int v21; // ecx
  unsigned int v22; // eax
  BOOL v23; // eax
  unsigned int v24; // ecx
  unsigned int v25; // eax
  signed int v26; // esi
  int result; // eax
  int v28; // ecx
  int v29; // [esp+Ch] [ebp-4h]
  int v30; // [esp+10h] [ebp+0h]
  int v31[7]; // [esp+14h] [ebp+4h]

  v1 = a1;
  v2 = 8;
  v3 = a1[8];
  v4 = v3 + a1[16] + 1295307597;
  a1[8] = v4;
  v5 = v4 < v3;
  a1[16] = v5;
  v6 = a1[9];
  v7 = v6 + v5 - 749914925;
  a1[9] = v7;
  v8 = v7 < v6;
  a1[16] = v8;
  v9 = a1[10];
  v10 = v9 + v8 + 886263092;
  a1[10] = v10;
  v11 = v10 < v9;
  a1[16] = v11;
  v12 = a1[11];
  v13 = v12 + v11 + 1295307597;
  a1[11] = v13;
  v14 = v13 < v12;
  a1[16] = v14;
  v15 = a1[12];
  v16 = v15 + v14 - 749914925;
  a1[12] = v16;
  v17 = v16 < v15;
  a1[16] = v17;
  v18 = a1[13];
  v19 = v18 + v17 + 886263092;
  a1[13] = v19;
  v20 = v19 < v18;
  a1[16] = v20;
  v21 = a1[14];
  v22 = v21 + v20 + 1295307597;
  a1[14] = v22;
  v23 = v22 < v21;
  a1[16] = v23;
  v24 = a1[15];
  v25 = v24 + v23 - 749914925;
  a1[15] = v25;
  a1[16] = v25 < v24;
  do
  {
    *(int *)((char *)&v30 + (_DWORD)v1) = sub_4010E1(*v1 + v1[8]);
    ++v1;
    --v2;
  }
  while ( v2 );
  v26 = 0;
  result = 7;
  do
  {
    a1[v26] = *(&v30 + v26) + __ROL4__(*(&v30 + result), 16) + __ROL4__(*(&v29 + result), 16);
    v28 = v31[v26] + *(&v30 + result) + __ROL4__(*(&v30 + (((_BYTE)result + 1) & 7)), 8);
    result = ((_BYTE)result + 2) & 7;
    a1[v26 + 1] = v28;
    v26 += 2;
  }
  while ( v26 < 8 );
  return result;
}

int __cdecl sub_4010E1(unsigned int a1)
{
  return (a1 * (unsigned __int64)a1 >> 32) ^ a1 * a1;
}
