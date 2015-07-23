Atomic Overview
===============

This is an overview of the Atomic API.

Overview
--------

The Atomic API is one of the ways that libctr offers support for
concurrency. An *atomic update* is a set of inseparable operations, which makes
it safe to update shared variables, even if they are being used in parallel!

Atomic operations are preferred over mutexes/semaphores whenever possible,
because atomic operations are usually faster, they don't lead to deadlocks,
and they are **not** stateful. The last may be confusing or offsetting to some
developers, but it is actually the most important. See any of the most
important publications and presentations about concurrent/parallel computing,
and you will understand how state in a computer program can *destroy*
concurrency and parallelism.

Using
-----

An atomic function takes the address of a variable, and performs one
operation on that variable (such as adding, subtracting, setting, or comparing).

Developers should take care, when using an atomic variable, to **always**
use the atomic functions only. Once you have decided that a variable should be
atomic, you must never use the standard arithmetic (``+=``, ``-=``, ``*=``,
etc.). You should not even compare it using standard arithmetic, which means
that code such as ``if(x == 5)`` is invalid. You would use 
``if(ctrAtomicRead(&x) == 5)`` instead, as this will be valid even if another
atomic operation is already in progress when you reach the comparison
statement.

