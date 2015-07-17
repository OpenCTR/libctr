========
Overview
========

This presents an overview of several concepts used in libctr.

Thread-safety
-------------

Concurrent and parallel computing are first-class topics in libctr.
*Everything* should be thread-safe. To make this possible, as well as practical,
libctr does *not* expose any ``init()`` functions to the user. The replacement
makes heavy use of a GCC extension: constructor/destructor attributes. Any
module or service which needs an ``init()`` function should instead declare
an ``init()`` and ``fini()`` function in the source code file. As an example,
consider the file gsp.c: 

.. code-block:: c

   void gspInit() CTR_INIT;
   void gspExit() CTR_FINI;

After the ``init()`` function for a module is called, all other functions should
be completely thread-safe. ``init()`` functions are automatically called by the
CRT0 startup function during program startup, which is the only time the program
can be certain that there is only one thread running.

The ``init()`` function should do only one thing: Create the global context
data.

The ``exit()`` function is optional, though highly recommended. It should
free up any resources allocated, including the global context variable.

It is important to remember this: GCC Constructors/Destructors will only
be called if the file they are declared in is used. As an example, if a
sample program uses the Filesystem API but not the GSP API, the ``init``
function for filesystem will be called, but the ``init`` function for GSP will
*not* be called.

Contexts
--------

A *context* in libctr is a data structure which encapsulates all access to the
data of a particular service or module. Because a context data structure is
thread-safe once allocated, this makes them excellent replacements for global
variables. A context data structure can be shared by as many threads as needed,
provided that the context data was initialized before being passed to any
threads.

Each module has one global context, and can be referenced by using the macro
named ``CTR_<MODULE_NAME>_THIS``. As an example, to refer to the global
filesystem context data, use ``CTR_FS_THIS``.

A context data structure can contain as many data fields as needed. The only
required part is the service handle. This means that every time a new context
data is created for a particular service, a new session for that service is
opened with the kernel. The session will be closed when the context data is
freed.

Although not mandatory, it is strongly encouraged to use atomic operations
to ensure exclusive access, instead of mutex variables. The reason for this is
because atomic operations do not block. An example of using atomic operations
in a context data structure can be found in ``gsp.c``. 

