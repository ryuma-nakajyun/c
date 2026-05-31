#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void write_file(const char *path, const char *content) {
  FILE *fp = fopen(path, "w");
  if (!fp) {
    perror("ファイル作成失敗");
    return;
  }
  fputs(content, fp);
  fclose(fp);
}

int main(void) {
  const char *root = "c";
  const char *project = "c/myproject";

  // c/
  mkdir(root, 0755);

  // c/myproject/
  mkdir(project, 0755);

  // --- ディレクトリ作成 ---
  char src[256], include[256], build[256], logdir[256];

  snprintf(src, sizeof(src), "%s/src", project);
  snprintf(include, sizeof(include), "%s/include", project);
  snprintf(build, sizeof(build), "%s/build", project);
  snprintf(logdir, sizeof(logdir), "%s/log", project);

  mkdir(src, 0755);
  mkdir(include, 0755);
  mkdir(build, 0755);
  mkdir(logdir, 0755);

  // --- main.c ---
  char main_c[256];
  snprintf(main_c, sizeof(main_c), "%s/src/main.c", project);
  write_file(main_c, "#include <stdio.h>\n"
                     "#include \"logger.h\"\n"
                     "#include \"router.h\"\n"
                     "#include \"handlers.h\"\n\n"
                     "int main(void) {\n"
                     "    log_info(\"system start\");\n"
                     "    route_request(\"/hello\");\n"
                     "    return 0;\n"
                     "}\n");

  // --- logger.c ---
  char logger_c[256] = {0};
  snprintf(logger_c, sizeof(logger_c), "%s/src/logger.c", project);
  write_file(logger_c, "#include <stdio.h>\n"
                       "#include \"logger.h\"\n\n"
                       "void log_info(const char *msg) {\n"
                       "    printf(\"[INFO] %s\\n\", msg);\n"
                       "}\n");

  // --- router.c ---
  char router_c[256] = {0};
  snprintf(router_c, sizeof(router_c), "%s/src/router.c", project);
  write_file(router_c, "#include <stdio.h>\n"
                       "#include \"router.h\"\n"
                       "#include \"handlers.h\"\n\n"
                       "void route_request(const char *path) {\n"
                       "    if (strcmp(path, \"/hello\") == 0) {\n"
                       "        handle_hello();\n"
                       "    } else {\n"
                       "        printf(\"404 Not Found: %s\\n\", path);\n"
                       "    }\n"
                       "}\n");

  // --- handlers.c ---
  char handlers_c[256] = {0};
  snprintf(handlers_c, sizeof(handlers_c), "%s/src/handlers.c", project);
  write_file(handlers_c, "#include <stdio.h>\n"
                         "#include \"handlers.h\"\n"
                         "#include \"logger.h\"\n\n"
                         "void handle_hello(void) {\n"
                         "    log_info(\"handle_hello called\");\n"
                         "    printf(\"Hello World!\\n\");\n"
                         "}\n");

  // --- include/logger.h ---
  char logger_h[256] = {0};
  snprintf(logger_h, sizeof(logger_h), "%s/include/logger.h", project);
  write_file(logger_h, "#ifndef LOGGER_H\n#define LOGGER_H\n\n"
                       "void log_info(const char *msg);\n\n"
                       "#endif\n");

  // --- include/router.h ---
  char router_h[256] = {0};
  snprintf(router_h, sizeof(router_h), "%s/include/router.h", project);
  write_file(router_h, "#ifndef ROUTER_H\n#define ROUTER_H\n\n"
                       "void route_request(const char *path);\n\n"
                       "#endif\n");

  // --- include/handlers.h ---
  char handlers_h[256] = {0};
  snprintf(handlers_h, sizeof(handlers_h), "%s/include/handlers.h", project);
  write_file(handlers_h, "#ifndef HANDLERS_H\n#define HANDLERS_H\n\n"
                         "void handle_hello(void);\n\n"
                         "#endif\n");

  // --- Makefile ---
  char makefile[256] = {0};
  snprintf(makefile, sizeof(makefile), "%s/Makefile", project);
  write_file(makefile, "CC = gcc\n"
                       "CFLAGS = -Iinclude -Wall -O2\n"
                       "TARGET = build/myproject\n"
                       "SRC = $(wildcard src/*.c)\n\n"
                       "$(TARGET): $(SRC)\n"
                       "\t$(CC) $(CFLAGS) -o $@ $^\n\n"
                       "clean:\n"
                       "\trm -f $(TARGET)\n");

  // --- .gitignore ---
  char gitignore[256] = {0};
  snprintf(gitignore, sizeof(gitignore), "%s/.gitignore", project);
  write_file(gitignore, "build/\n"
                        "*.o\n"
                        "*.exe\n"
                        "log/\n");

  printf("以前のプロジェクト構造をできるだけ復元しました。\n");
  return 0;
}
