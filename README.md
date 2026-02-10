*This project has been created as part of the 42 curriculum by mcardoso.*

## Description

The **Philosophers** project is an introduction to the fundamentals of threading and process synchronization. It simulates the classic **Dining Philosophers Problem**, where a number of philosophers sit at a round table with a bowl of spaghetti and a fork between each pair of philosophers.

**The Goal:**
Each philosopher must alternately eat, sleep, and think. To eat, a philosopher needs two forks (one on their left and one on their right). The challenge is to implement a solution that:
- Prevents **deadlock** (all philosophers waiting indefinitely)
- Avoids **data races** (concurrent access to shared resources)
- Ensures philosophers don't starve

This project teaches critical concepts in concurrent programming, including thread creation, mutex locks, and race condition prevention using POSIX threads (pthreads).

## Instructions

### Compilation

To compile the project, simply run:
```bash
make
```

This will create an executable called `philo`.

### Execution

The program takes 4 or 5 arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
1. `number_of_philosophers` - The number of philosophers (and forks)
2. `time_to_die` - Time in milliseconds before a philosopher dies if they haven't eaten
3. `time_to_eat` - Time in milliseconds it takes for a philosopher to eat
4. `time_to_sleep` - Time in milliseconds a philosopher spends sleeping
5. `[number_of_times_each_philosopher_must_eat]` - (Optional) If specified, the simulation stops when all philosophers have eaten at least this many times

**Example:**
```bash
./philo 5 800 200 200
```
This runs a simulation with 5 philosophers who die after 800ms without eating, take 200ms to eat, and sleep for 200ms.

### Cleanup

To remove object files:
```bash
make clean
```

To remove object files and the executable:
```bash
make fclean
```

To recompile everything from scratch:
```bash
make re
```

## Expected Behavior

The program outputs timestamped logs of each philosopher's actions:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
200 3 has taken a fork
200 3 has taken a fork
200 3 is eating
...
```

**Format:** `timestamp_in_ms philosopher_id action`

The simulation should:
- Run indefinitely until a philosopher dies or (if specified) all philosophers have eaten the required number of times
- Display a death message (`X died`) immediately when a philosopher dies
- Not display any messages after a death has occurred
- Have no data races or crashes

## Key Concepts

### Threading
Each philosopher runs as a separate thread, allowing concurrent execution. Threads share the same memory space, which requires careful synchronization.

### Mutexes
Mutexes (mutual exclusion locks) prevent multiple threads from accessing shared resources (forks) simultaneously. Each fork is protected by a mutex.

### Deadlock Prevention
The program prevents deadlock by having even-numbered philosophers grab forks in a different order than odd-numbered philosophers.

### Data Race Prevention
All shared data (death status, meal counts, last meal time) is protected by mutexes to prevent race conditions.

## Testing

### Basic Tests
```bash
# Should not die
./philo 5 800 200 200

# Should die
./philo 4 310 200 100

# Single philosopher (should die)
./philo 1 800 200 200

# With meal limit
./philo 5 800 200 200 7
```

## Resources

### Documentation & Tutorials
- [CodeVault's pthread tutorial series](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) - Comprehensive introduction to POSIX threads
- Linux man pages:
  - `man pthread_create` - Thread creation
  - `man pthread_join` - Waiting for thread termination
  - `man pthread_mutex_init` - Mutex initialization
  - `man pthread_mutex_lock` - Acquiring mutex locks
  - `man pthread_mutex_unlock` - Releasing mutex locks
  - `man gettimeofday` - Getting current time
  - `man usleep` - Microsecond sleep

# Additional "Resources"
- Help from other student

### AI Usage
AI was used in this project for:
- **Code structure consultation** - Discussing optimal data structure design and mutex placement
- **Concept clarification** - Explaining threading concepts, deadlock prevention strategies, and mutex best practices
- **Test case generation** - Creating comprehensive test scenarios with expected outputs

---
