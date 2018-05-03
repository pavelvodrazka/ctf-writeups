#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define NTHREADS 8 // should be <= 32 (alphabet size)

char *alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ@[\\]^_";
int terminate = 0;

uint32_t data[2] =  { 0xD5B5CB50, 0xFE4F8364 };
uint32_t expected[2] = { 0x474E5089, 0x0A1A0A0D };

inline uint32_t *generate_tea_keys(char *passwd) {
    size_t i, n = 8;
    uint32_t buf[n];
    uint32_t *keys;
    char *c;

    strncpy((char *) buf, passwd, n);
    for (i = 0; i < n; i++) {
        c = (char *) buf + i;
        *c = *c & 0xDF | 0x40;
    }

    keys = (uint32_t *) malloc(4 * sizeof(uint32_t));
    keys[0] = *buf;
    keys[1] = *(uint32_t *) ((char *) buf +  4 % n);
    keys[2] = *(uint32_t *) ((char *) buf +  8 % n);
    keys[3] = *(uint32_t *) ((char *) buf + 12 % n);

    return keys;
}

inline uint32_t *tea_decrypt_block(uint32_t *block, uint32_t *keys) {
    uint32_t v0 = block[0], v1 = block[1];
    uint32_t k0 = keys[0], k1 = keys[1], k2 = keys[2], k3 = keys[3];
    uint32_t *decrypted;

    int32_t i, sum = -957401312;
    for (i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k2) ^ (v0 + sum) ^ ((v0 >> 5) + k3);
        v0 -= ((v1 << 4) + k0) ^ (v1 + sum) ^ ((v1 >> 5) + k1);
        sum += 1640531527;
    }

    decrypted = (uint32_t *) malloc(2 * sizeof(uint32_t));
    decrypted[0] = v0;
    decrypted[1] = v1;

    return decrypted;
}

inline uint32_t *decrypt_first_block(uint32_t* data, char *passwd) {
    uint32_t *keys = generate_tea_keys(passwd);
    uint32_t *decrypted = tea_decrypt_block(data, keys);
    free(keys);
    return decrypted;
}

void *crack_password(void *thread_id) {
    int tid = *((int *) thread_id);
    int c0, c1, c2, c3, c4, c5, c6, c7;
    int n = strlen(alphabet);
    int found = 0;
    unsigned long long cnt = 0;
    char passwd[9] = "????????";
    uint32_t *decrypted;
    time_t start, now;

    printf("thread[%02d] - started\n", tid);

    start = time(0);
    for (c0 = 0; c0 < n; c0++) {
        passwd[0] = alphabet[c0];
        for (c1 = tid; c1 < n; c1 += NTHREADS) {
            passwd[1] = alphabet[c1];
            for (c2 = 0; c2 < n; c2++) {
                passwd[2] = alphabet[c2];
                for (c3 = 0; c3 < n; c3++) {
                    passwd[3] = alphabet[c3];
                    for (c4 = 0; c4 < n; c4++) {
                        passwd[4] = alphabet[c4];
                        for (c5 = 0; c5 < n; c5++) {
                            passwd[5] = alphabet[c5];
                            for (c6 = 0; c6 < n; c6++) {
                                passwd[6] = alphabet[c6];
                                for (c7 = 0; c7 < n; c7++) {
                                    passwd[7] = alphabet[c7];
                                    if (terminate) {
                                        goto terminate;
                                    }

                                    decrypted = decrypt_first_block(data, passwd);
                                    if (decrypted[0] == expected[0] && decrypted[1] == expected[1]) {
                                        terminate = 1;
                                        found = 1;
                                        goto terminate;
                                    }
                                    free(decrypted);

                                    if (cnt % 100000000 == 0 && cnt > 0) {
                                        now = time(0);
                                        printf("thread[%02d] - time: %8.0f secs  |  tried: %8u Mpws  |  speed: %8.2f Mpws/sec  |  current: %s\n",
                                                    tid, difftime(now, start), cnt / 1000000, cnt / difftime(now, start) / 1000000, passwd);
                                    }
                                    cnt++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    terminate:
    if (found) {
        printf("thread[%02d] - found password: %s\n", tid, passwd);
    }
    printf("thread[%02d] - terminated\n", tid);
}

int main() {
    pthread_t threads[NTHREADS];
    int thread_ids[NTHREADS];
    int i;

    printf("alphabet: %s\n", alphabet);
    printf("alphabet size: %d\n", strlen(alphabet));

    printf("spawning %d threads...\n", NTHREADS);
    for (i = 0; i < NTHREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, crack_password, (void *) &thread_ids[i]);
    }
    for (i = 0; i < NTHREADS; i++) {
        pthread_join(threads[i], NULL);
    }

	return 0;
}
