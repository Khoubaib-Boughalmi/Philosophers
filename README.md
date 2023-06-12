# Dining Philosophers Problem

This repository contains the solution for the Dining Philosophers Problem. The problem involves a group of philosophers sitting around a table, where each philosopher needs to alternate between eating and thinking. However, there are a limited number of forks available on the table for them to use. The challenge is to design a program that ensures the philosophers can eat without causing deadlocks or starvation.

## Global Rules

To solve this problem, your program must adhere to the following rules:

- Global variables are forbidden!
- The program should consist of two parts: the mandatory part and the bonus part (if you decide to implement it).
- Both parts must comply with the rules mentioned below.

## Program Arguments

Your program should take the following arguments:

```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

- `number_of_philosophers`: The number of philosophers and also the number of forks on the table.
- `time_to_die` (in milliseconds): If a philosopher doesn't start eating within `time_to_die` milliseconds since the beginning of their last meal or the start of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During this time, they must hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): If specified, the simulation stops when all philosophers have eaten at least this many times. If not specified, the simulation stops when a philosopher dies.

## Philosopher Details

- Each philosopher is assigned a number ranging from 1 to `number_of_philosophers`.
- Philosopher number 1 sits next to philosopher number `number_of_philosophers`. For any other philosopher number N, they sit between philosopher number N - 1 and philosopher number N + 1.

## Logging

The program should generate logs according to the following format:

- Any state change of a philosopher should be formatted as follows:
  - `timestamp_in_ms X has taken a fork`
  - `timestamp_in_ms X is eating`
  - `timestamp_in_ms X is sleeping`
  - `timestamp_in_ms X is thinking`
  - `timestamp_in_ms X died`
- Replace `timestamp_in_ms` with the current timestamp in milliseconds and `X` with the philosopher number.
- Each displayed state message should be distinct and not mixed up with another message.
- A message announcing a philosopher's death should be displayed no more than 10 ms after the philosopher's actual death.

## Data Races and Mutexes

Your program must avoid data races, and to protect the forks' state, you should use a mutex for each fork.

## Chapter V - Mandatory Part

### Program Name

The program should be named `philo`.

### Files to Include

You should include the following files in the `philo/` directory:

- `Makefile`
- `*.h`
- `*.c`

### Makefile Instructions

The `Makefile` should include the following rules:

- `all`: Compiles the program.
- `clean`: Removes object files.
- `fclean`: Removes object files and the executable.
- `re`: Rebuilds the program.

### External Functions

You are allowed to use the following external functions:

- `memset`
- `printf`
- `malloc`
- `free`
- `write`
- `usleep`
- `gettimeofday`
- `pthread_create`
- `pthread_detach`
- `pthread_join`
- `pthread_mutex_init`
- `pthread_mutex_destroy

`
- `pthread_mutex_lock`
- `pthread_mutex_unlock`

### Libft

You are not authorized to use the Libft library.

### Description

This program implements the Dining Philosophers Problem using threads and mutexes. Each philosopher is represented by a separate thread, and mutexes are used to protect the state of the forks.

Please refer to the provided source code for the implementation details.

*Note: This readme file is generated based on the given requirements and may require further modification and enhancement.*

Chapter VI - Bonus Part: Philosophers with Processes and Semaphores

This repository contains the solution for the Bonus Part of the Dining Philosophers Problem. In this version, the program is modified to use processes instead of threads and implements semaphores to manage the availability of forks.
Program Name

The program for the bonus part should be named philo_bonus.
Files to Include

Include the following files in the philo_bonus/ directory:

    Makefile
    *.h
    *.c

Makefile Instructions

The Makefile should include the following rules:

    all: Compiles the program.
    clean: Removes object files.
    fclean: Removes object files and the executable.
    re: Rebuilds the program.

External Functions

You are allowed to use the following external functions:

    memset
    printf
    malloc
    free
    write
    fork
    kill
    exit
    pthread_create
    pthread_detach
    pthread_join
    usleep
    gettimeofday
    waitpid
    sem_open
    sem_close
    sem_post
    sem_wait
    sem_unlink

Libft

You are not authorized to use the Libft library.
Description

The bonus part of the program follows the same argument structure as the mandatory part and complies with the rules mentioned in the Global Rules chapter.

Specific rules for the bonus part are as follows:

    All the forks are placed in the middle of the table.
    There are no states of forks stored in memory. Instead, the number of available forks is represented by a semaphore.
    Each philosopher is implemented as a separate process. However, the main process should not act as a philosopher.

Please refer to the provided source code for the implementation details.

Note: This readme file is generated based on the given requirements and may require further modification and enhancement.