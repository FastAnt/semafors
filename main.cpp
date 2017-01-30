#include <iostream>

#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define SEM_NAME "/test.sem"
using namespace std;

int main()
{

    /* Наш именованный семафор */
    sem_t *sema_n;
    int ret,val;

    sem_unlink("/test.sem");
    /*
     * Создаём именованный семафор (O_CREAT) с начальным значением 1
     * (то есть разблокирован)(Если вы хотите создать неименованный
     * семафор, то замените вызов sem_open на sem_init)
     */
    if ((sema_n = sem_open(SEM_NAME, O_CREAT, 0600, 66)) ==
                                              SEM_FAILED){
      perror("sem_open");
      return -1;
    }

    /* Получаем текущее значение семафора */
    sem_getvalue(sema_n, &val);
    printf("semaphore value = %d\n", val);

//    /*
//     * Пробуем получить семафор. Если не получается, используем
//     * блокирующуюся версию. Это сделано только для того, чтобы
//     * показать семантику и sem_trywait, и sem_wait. В реальном
//     * коде не надо делать, как здесь.
//     */
//    if ((ret = sem_trywait(sema_n)) != 0 && errno == EAGAIN)
//      /* permanent wait */
//      sem_wait(sema_n);
//    else if (ret != 0){
//      perror("sem_trywait");
//      return -1;
//    }

//    /*
//     * Семафор захвачен. Работаем с общими данными.
//     */

//    /*
//     * Освобождаем семафор после манипулирования общими данными
//     */
//    if (sem_post(sema_n) != 0)
//      perror("post error");

//    /*
//     * Закрываем и удаляем семафор. (Для неименованных семафоров
//     * замените следующие два вызова на sem_destroy. Для
//     * неименованных семафоров sem_unlink не пригоден)
//     */
//    sem_close(sema_n);
//    sem_unlink(SEM_NAME);
    return 0;

}
