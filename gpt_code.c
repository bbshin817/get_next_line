#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 42 // 固定バッファサイズ

// ファイルから1行ずつ読み取る関数
char *read_line(int fd) {
    static char *buffer = NULL;
    // 実際にreadで読み取った値を保持しておく変数
    static ssize_t buffer_size = 0;
    // 実際にreadで読み取ったバイト数を保持しておく変数
    static ssize_t buffer_pos = 0;
    // readで読み取ったテキスト全体を検索する際に、インデックスとして使用する値

    char *line = NULL; // 動的に確保される1行のデータ
    size_t line_size = 0; // 現在の行のサイズ

    // 読み取りバッファが空の場合、最初のメモリ確保
    if (buffer == NULL) {
        buffer = malloc(BUFFER_SIZE);
        if (buffer == NULL) {
            return NULL; // メモリ不足
        }
        buffer_size = read(fd, buffer, BUFFER_SIZE);
        buffer_pos = 0;
        if (buffer_size <= 0) {
            free(buffer);
            buffer = NULL;
            return NULL; // ファイルの終端またはエラー
        }
    }

    // 行を構築するループ
    while (1) {
        // バッファ内のデータを処理
        while (buffer_pos < buffer_size) {
            char c = buffer[buffer_pos++];
            
            // 行用のメモリを確保または拡張
            char *new_line = malloc(line_size + 1 + 1); // +1 for c, +1 for '\0'
            if (new_line == NULL) {
                free(line);
                return NULL; // メモリ不足
            }

            // 既存のデータを新しい領域にコピー
            if (line != NULL) {
                for (size_t i = 0; i < line_size; i++) {
                    new_line[i] = line[i];
                }
                free(line);
            }
            line = new_line;

            // 新しい文字を追加
            line[line_size++] = c;

            // 改行を検出した場合、行を返す
            if (c == '\n') {
                line[line_size] = '\0';
                return line;
            }
        }

        // バッファのデータが尽きた場合、再読み込み
        buffer_size = read(fd, buffer, BUFFER_SIZE);
        buffer_pos = 0;
        if (buffer_size <= 0) {
            break; // ファイルの終端またはエラー
        }
    }

    // 最後の行を返す（改行なしのケース）
    if (line != NULL) {
        line[line_size] = '\0';
    }
    return line;
}