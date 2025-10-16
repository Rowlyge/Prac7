/* Автор: Сокун Михаил
 *    Назначение: демонстрация управления процессами с помощью сигналов
 *       Файл: pulse_simple.c
 *       */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/* Обработчик сигнала SIGINT */
void sigint_handler(int signo) {
	    printf("[pid=%d] Получен SIGINT — завершаюсь\n", getpid());
	        exit(0);
}

/* Обработчик сигнала SIGCONT */
void sigcont_handler(int signo) {
	    printf("[pid=%d] Продолжаю выполнение после SIGCONT\n", getpid());
}

int main() {
	    int pid1, pid2;

	        signal(SIGINT, sigint_handler);
		    signal(SIGCONT, sigcont_handler);

		        pid1 = fork();
			    if (pid1 == 0) {
				            while (1) {
						                printf("[child1 %d] alive\n", getpid());
								            sleep(1);
									            }
					        } else {
							        pid2 = fork();
								        if (pid2 == 0) {
										            while (1) {
												                    printf("[child2 %d] alive\n", getpid());
														                    sleep(1);
																                }
											            } else {
													                sleep(3);
															            printf("[parent] Останавливаю первый процесс\n");
																                kill(pid1, SIGSTOP);
																		            sleep(3);
																			                printf("[parent] Возобновляю первый процесс\n");
																					            kill(pid1, SIGCONT);
																						                sleep(3);
																								            printf("[parent] Завершаю оба процесса\n");
																									                kill(pid1, SIGINT);
																											            kill(pid2, SIGINT);
																												            }
									    }
			        return 0;
}
 
