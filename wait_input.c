#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define TIMEOUT 10

volatile sig_atomic_t timeout_flag = 0;

void alarm_handler(int signo) {
	    timeout_flag = 1;
	        printf("\n(Сработал таймер: прошло %d секунд)\n", TIMEOUT);
}

int main(void) {
	    char buf[100];
	        struct sigaction sa;

		    sa.sa_handler = alarm_handler;
		        sigemptyset(&sa.sa_mask);
			    sa.sa_flags = 0;  
			        sigaction(SIGALRM, &sa, NULL);

				    alarm(TIMEOUT);
				        printf("Введите строку (у вас %d секунд): ", TIMEOUT);
					    fflush(stdout);

					        if (fgets(buf, sizeof(buf), stdin) == NULL) {
							        if (timeout_flag)
									            printf("Нет ввода — время ожидания истекло.\n");
								        else
										            printf("Ошибка ввода.\n");
									    } else {
										            buf[strcspn(buf, "\n")] = '\0';
											            printf("Спасибо, вы ввели: %s\n", buf);
												        }

						    return 0;
} 
