/*
.data:0000000000603140 ; char key[2]
.data:0000000000603140 key             db 0Ah,0                ; DATA XREF: play_game+5F3↑o
.data:0000000000603140                                         ; play_game+602↑o ...
.data:0000000000603142                 align 20h
.data:0000000000603160 functions_table dq offset error         ; DATA XREF: main+120↑r
.data:0000000000603168                 dq offset set_player_name
.data:0000000000603170                 dq offset print_help
.data:0000000000603178                 dq offset play_game
.data:0000000000603180                 dq offset exit_game
.data:0000000000603180 _data           ends
*/

void __fastcall __noreturn main(__int64 a1, char **a2, char **a3)
{
  FILE *v3; // rdi
  unsigned int choice; // [rsp+Ch] [rbp-14h]
  __int64 (__fastcall *v5)(); // [rsp+10h] [rbp-10h]
  char v6; // [rsp+1Fh] [rbp-1h]

  set_player_name();
  printf("\x1B[H\x1B[J", a2);
  fflush(stdout);
  while ( 1 )
  {
    printf("\x1B[0;0H");
    puts("Choose:");
    puts("[1] Change User");
    puts("[2] Help");
    puts("[3] Play");
    puts("[4] Exit");
    printf("> ");
    fflush(stdout);
    choice = -1;
    __isoc99_scanf("%d", &choice);
    do
      v6 = fgetc(stdin);
    while ( v6 != 10 && v6 != -1 );
    fflush(stdin);
    printf("\x1B[H\x1B[J", &choice);
    printf("\x1B[8;0H");
    v3 = stdout;
    fflush(stdout);
    if ( choice <= 4 )
    {
      v5 = functions_table[choice];
      ((void (__fastcall *)(FILE *))v5)(v3);
    }
    else
    {
      error();
    }
    choice = 0;
  }
}

int error()
{
  printf("Wrong option!");
  return fflush(stdout);
}

int set_player_name()
{
  size_t v1; // [rsp+0h] [rbp-10h]
  char v2; // [rsp+Fh] [rbp-1h]

  printf("\x1B[H\x1B[J");
  printf("Please enter your name:\n> ");
  fflush(stdout);
  fgets(&player_name, 16, stdin);
  if ( !strchr(&player_name, 10) )
  {
    do
      v2 = fgetc(stdin);
    while ( v2 != 10 && v2 != -1 );
  }
  fflush(stdin);
  v1 = strlen(&player_name);
  if ( v1 && *(&player_name + v1 - 1) == 10 )
    *(_BYTE *)(--v1 + 6304240) = 0;
  printf("Welcome %s.\n\n", &player_name, v1);
  fflush(stdout);
  printf("\x1B[H\x1B[J");
  return fflush(stdout);
}

int print_help()
{
  char v1; // [rsp+Fh] [rbp-1h]

  printf("\x1B[H\x1B[J");
  puts("To navigate through the maze use the following commands:");
  puts("  - go <direction>\t(north, south, west, east)");
  puts("  - search");
  puts("  - pick up");
  puts("  - open");
  puts("  - exit\n");
  puts("Press enter to resume to the menue.");
  fflush(stdout);
  do
    v1 = fgetc(stdin);
  while ( v1 != 10 && v1 != -1 );
  fflush(stdin);
  printf("\x1B[H\x1B[J");
  return fflush(stdout);
}

int play_game()
{
  int v1; // eax
  size_t v2; // rax
  signed int v3; // eax
  char v4; // [rsp+Fh] [rbp-21h]
  FILE *stream; // [rsp+10h] [rbp-20h]
  char *s; // [rsp+18h] [rbp-18h]
  char v7; // [rsp+23h] [rbp-Dh]
  signed int v8; // [rsp+24h] [rbp-Ch]
  signed int v9; // [rsp+28h] [rbp-8h]
  signed int i; // [rsp+2Ch] [rbp-4h]

  initialize_random_s1();
  sub_40100D();
  printf("\x1B[H\x1B[J");
  fflush(stdout);
  for ( i = 0; i <= 624; ++i )
  {
    if ( byte_603220[i] == 2 )
    {
      dword_603128 = i % 25;
      dword_60312C = i / 25;
      break;
    }
  }
  v9 = 0;
  while ( 1 )
  {
    while ( 1 )
    {
      sub_40161E();
      printf("\x1B[20;0H");
      printf("Enter your command:\n> ");
      fflush(stdout);
      fgets(command, 16, stdin);
      if ( !strchr(command, 10) )
      {
        do
          v7 = fgetc(stdin);
        while ( v7 != 10 && v7 != -1 );
      }
      fflush(stdin);
      printf("\x1B[H\x1B[J", 10LL);
      puts("\x1B[16;0H");
      if ( !(unsigned int)xored_equals(command, "':+6HB") ) // exit
      {
        printf("\x1B[H\x1B[J", "':+6HB");
        return fflush(stdout);
      }
      if ( !(unsigned int)xored_equals(command, "%-b,-06*HB") ) // go north
      {
        if ( byte_603220[25 * (dword_60312C - 1) + dword_603128] )
        {
          --dword_60312C;
          v9 = 0;
        }
        else
        {
          printf("There is a wall!", "%-b,-06*HB");
        }
        goto LABEL_67;
      }
      if ( !(unsigned int)xored_equals(command, "%-b1-76*HB") ) // go south
      {
        if ( byte_603220[25 * (dword_60312C + 1) + dword_603128] )
        {
          ++dword_60312C;
          v9 = 0;
        }
        else
        {
          printf("There is a wall!", "%-b1-76*HB");
        }
        goto LABEL_67;
      }
      if ( !(unsigned int)xored_equals(command, "%-b5'16HB") ) // go west
      {
        if ( byte_603220[25 * dword_60312C - 1 + dword_603128] )
        {
          --dword_603128;
          v9 = 0;
        }
        else
        {
          printf("There is a wall!", "%-b5'16HB");
        }
        goto LABEL_67;
      }
      if ( !(unsigned int)xored_equals(command, "%-b'#16HB") ) // go east
      {
        if ( byte_603220[25 * dword_60312C + 1 + dword_603128] )
        {
          ++dword_603128;
          v9 = 0;
        }
        else
        {
          printf("There is a wall!", "%-b'#16HB");
        }
        goto LABEL_67;
      }
      if ( !(unsigned int)xored_equals(command, "1'#0!*HB") ) // search
      {
        v9 = 1;
        if ( byte_603220[25 * dword_60312C + dword_603128] == 3 )
        {
          printf("You found a key!", "1'#0!*HB");
        }
        else if ( byte_603220[25 * dword_60312C + dword_603128] == 4 )
        {
          printf("You found a locked chest!", "1'#0!*HB");
        }
        else if ( rand() % 3 )
        {
          puts(off_6030E0);
        }
        else
        {
          v1 = rand();
          puts((&off_6030E0)[v1 % 9]);
        }
        goto LABEL_67;
      }
      if ( (unsigned int)xored_equals(command, "2+!)b72HB") ) // pick up
        break;
      if ( v9 )
      {
        if ( byte_603220[25 * dword_60312C + dword_603128] == 3 )
        {
          printf("You pick up the key: %s", s1);
        }
        else if ( byte_603220[25 * dword_60312C + dword_603128] == 4 )
        {
          printf("This is to heavy! You can't pick up that.", "2+!)b72HB");
        }
        else
        {
          printf("There is nothing you want to pick up!", "2+!)b72HB");
        }
      }
      else
      {
        printf("Maybe you should search first", "2+!)b72HB");
      }
LABEL_67:
      fflush(stdout);
    }
    if ( !(unsigned int)xored_equals(command, "-2',HB") ) // open
      break;
    if ( !(unsigned int)xored_equals(command, "5*-#/+HB") ) // whoami
    {
      printf(&player_name, "5*-#/+HB");
      goto LABEL_67;
    }
    error();
  }
  if ( !v9 )
  {
    printf("Maybe you should search first", "-2',HB");
    goto LABEL_67;
  }
  if ( byte_603220[25 * dword_60312C + dword_603128] != 4 )
  {
    printf("There is nothing you can open!", "-2',HB");
    goto LABEL_67;
  }
  sub_40161E();
  printf("\x1B[20;0H", "-2',HB");
  fflush(stdout);
  v8 = 3;
  while ( 1 )
  {
    v3 = v8--;
    if ( !v3 )
    {
      printf("Next time get the right key!");
      printf("For now get out of here! Quickly!");
      fflush(stdin);
      exit(0);
    }
    printf("The chest is locked. Please enter the key:\n> ");
    fflush(stdout);
    fgets(key, 40, stdin);
    if ( !strchr(key, 10) )
    {
      while ( fgetc(stdin) != 10 ) ;
    }
    fflush(stdin);
    v2 = strlen(s1);
    if ( !strncmp(s1, key, v2) )
      break;
    puts("Sorry but that was the wrong key.");
  }
  printf("\x1B[H\x1B[J", key);
  puts("Congratulation, you solved the maze. Here is your reward:");
  s = (char *)malloc(0x400uLL);
  stream = fopen("egg.txt", "r");
  while ( fgets(s, 1024, stream) )
    printf("%s", s);
  fclose(stream);
  printf("Press enter to return to the menue", 1024LL);
  fflush(stdout);
  do
    v4 = fgetc(stdin);
  while ( v4 != 10 && v4 != -1 );
  fflush(stdin);
  printf("\x1B[H\x1B[J");
  return fflush(stdout);
}

void __noreturn exit_game()
{
  printf("\x1B[H\x1B[J");
  puts("Bye!");
  fflush(stdout);
  exit(0);
}
