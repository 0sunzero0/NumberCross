#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
  // >> input read
  char input_file_name[128];
  char temp[128];
  char *ptr;
  int width = 0;
  int height = 0;


  FILE *fp = fopen("input", "r");

  // input의 height, width를 count
  while((temp[0]=fgetc(fp))!=EOF){
    while(height == 1 && (temp[0]=fgetc(fp))!='\n'){
      if(temp[0]==' ')
        width++;
    }
    if(temp[0]=='\n'){
      height ++;
    }
  }
  width ++;

  int M = height-1;
  int N = width-1;
  int color[M+1][N+1];
  int number[M+1][N+1];

  // 파일 다시 처음으로 읽도록 cursor 이동
  fseek(fp, 0l, SEEK_SET);

  // numberArray에 input 파일에 있는 number를 할당
  int i = 0;
  int j = 0;
  while(fgets(temp, 128, fp) != NULL){
    ptr = strtok(temp, " ");
    while(ptr != NULL){
      number[i][j] = atoi(ptr);
      ptr = strtok(NULL, " ");
      j++;
    }
    j = 0;
    i++;
  }

  // input print
  printf("input\n");
  for(i=0; i <= M; i++){
    for(j=0; j <= N; j++){
      printf("%2d ", number[i][j]);
    }
    printf("\n");
  }

  fclose(fp);

  // >> formula 작성
  FILE *fp2 = fopen("formula", "w");
  // 1. declare number
  for(int i = 0; i <= M; i++){
    for(int j = 0; j <= N; j++){
      if(i == 0 & j == N) continue;
      fprintf(fp2, "(declare-const number_%d_%d Int)\n", i, j);
    }
  }
  // 2. number에 value를 assignment
  for(int i = 0; i <= M; i++){
    for(int j = 0; j <= N; j++){
      if(i == 0 & j == N) continue;
      fprintf(fp2, "(assert (= number_%d_%d %d))\n", i, j, number[i][j]);
    }
  }
  // 3. declare color
  for(int i = 1; i <= M; i++){
    for(int j = 0; j <= N-1; j++){
      fprintf(fp2, "(declare-const color_%d_%d Int)\n", i, j);
    }
  }
  // 4. range number constraints
  for(int i = 1; i <= M; i++){
    for(int j = 0; j <= N-1; j++){
      fprintf(fp2, "(assert (and (<= number_%d_%d 9) (<= 1 number_%d_%d)))\n", i, j, i, j);
    }
  }
  // 5. range color constraints
  for(int i = 1; i <= M; i++){
    for(int j = 0; j <= N-1; j++){
      fprintf(fp2, "(assert (or (= color_%d_%d 1) (= color_%d_%d 0)))\n", i, j, i, j);
    }
  }

  // 6. black constraints
  for(int j = 0; j <= N-1; j++){
    fprintf(fp2, "(assert (= (+ ");
    for(int i = 1; i <= M; i++){
      fprintf(fp2, "(* number_%d_%d color_%d_%d)", i, j, i, j);
    }
    fprintf(fp2, ") number_%d_%d))\n", 0, j);
  }
  // 7. white constraints
  for(int i = 1; i <= M; i++){
    fprintf(fp2, "(assert (= (+ ");
    for(int j = 0; j <= N-1; j++){
      fprintf(fp2, "(* number_%d_%d (- 1 color_%d_%d))", i, j, i, j);
    }
    fprintf(fp2, ") number_%d_%d))\n", i, N);
  }

  fprintf(fp2, "(check-sat)\n(get-model)\n");

  fclose(fp2);

  // >> z3 formula pipe
  char a[128];
  char b[128];
  char c[128];
  char d[128];
  char e[128];
  char buf[128];

  FILE *fp3 = popen("z3 formula", "r");
  fscanf(fp3, "%s", buf);

  if(strcmp(buf, "sat") != 0){
    printf("\nNo Solution.\n");
    return -1;
  }

  fscanf(fp3, "%s", b);

  for(int k = 0; k < M * N; k++){
    fscanf(fp3, "%s %s %s %s %s", a, b, c, d, e);

    ptr = strtok(b, "_");
    ptr = strtok(NULL, "_");
    i = atoi(ptr);
    ptr = strtok(NULL, "_");
    j = atoi(ptr);

    if(strcmp(e, "0)") == 0){
      color[i-1][j] = 0;
    }
    if(strcmp(e, "1)") == 0){
      color[i-1][j] = 1;
    }
  }
  pclose(fp3);

  // >> output write and output print
  FILE *fp4 = fopen("output", "w");
  printf("\noutput");

  for(int i = 0; i <= N; i++){
    for(int j = 0; j < M; j++){
      if(i == 0 || j == 0)  continue;
      fprintf(fp4, "%d ", color[i-1][j]);
      printf("%d ", color[i-1][j]);
    }
    fprintf(fp4, "\n");
    printf("\n");
  }

  fclose(fp4);

  return 0;
}

