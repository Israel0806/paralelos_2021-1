#include <iostream>
#include <queue>
#include <thread>
#include <omp.h>
#include <random>
#include <time.h>

struct messageMP {
    int value, dest;
    messageMP(int val, int dest) : value(val), dest(dest) {}
};

struct QueueMP {
    std::queue<messageMP> q_p;
    int recibidos; // enqueue
    int retirados; // dequeue
    int done_sending; // threads done sending messages

    QueueMP() {
        recibidos = 0;
        retirados = 0;
        done_sending = 0;
    }
};

bool done(int myRank, int thread_count);
void enqueue(int dest, int msg);
void receiveMessage(int myRank);
void producerConsumer(int num_msg);
void sendMessage(int thread_count, int myRank);

QueueMP* colas;

int main()
{
    srand(time(NULL));
    int thread_count = omp_get_num_threads();
    colas = new QueueMP[thread_count];
    std::cout << thread_count << "\n\n";
#pragma omp parallel num_threads(thread_count)
    {
    producerConsumer(1);
    }

    delete[] colas;
}

void producerConsumer(int num_msg) {
    /// Thread data
    int myRank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    std::cout << "thread_count: " << thread_count << std::endl;

    for (int i = 0; i < num_msg; i++) {
        sendMessage(thread_count, myRank);
        receiveMessage(myRank);
    }
    colas[myRank].done_sending++;

//  #pragma omp barrier

    while (!done(myRank, thread_count))
        receiveMessage(myRank);
}

void enqueue(int dest, int msg) {
    colas[dest].q_p.push(messageMP(msg, dest));
    colas[dest].recibidos++;
}

void sendMessage(int thread_count, int myRank) {
    int msg = rand() % 10 + 1;
    int dest = rand() % thread_count;
#pragma omp critical
    std::cout << "Thread " << myRank << " send a message: " << msg << '\n';
#pragma omp critical
    enqueue(dest, msg);
}

int dequeue(QueueMP *cola, int rank) {
    if (cola[rank].q_p.front().dest == rank) {
        int val = cola[rank].q_p.front().value;
        cola[rank].q_p.pop();
        cola[rank].retirados++;
        return val;
    }
}

void receiveMessage(int myRank) {
    int queueSize = colas[myRank].recibidos - colas[myRank].retirados;
    int msg;
    if (!queueSize)
        return;
    else if (queueSize == 1)
#pragma omp critical
        msg = dequeue(colas, myRank);
    else // mas de 2 mensajes en la cola
        msg = dequeue(colas, myRank);
    std::cout << "Thread " << myRank << " received a message: " << msg << '\n';
}


bool done(int myRank, int thread_count) {
    int queueSize = colas[myRank].recibidos - colas[myRank].retirados;
    return (!queueSize && (colas[myRank].done_sending == thread_count));
}
