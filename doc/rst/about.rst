About
-----

This document provides a basic overview of libctr: what it is, what it is *not*,
what it does, and explains the reasons behind several of its choices. After
reading this, you should have a pretty good idea of whether or not libctr is
what you are looking for - if it *fits the bill*.

Important Notice
----------------

The first and foremost disclaimer about libctr is this:
   libctr is not a catch-all, end-all, be-all solution. Some users will be
   satisfied with libctr, others will be more satisfied with libctru (by 
   smealum), and still other users will be dissatisfied with both. 

There is nothing about libctr that makes it inherently better than libctru, or 
inherently worse. It simply targets a different set of goals.

In particular, because libctr is tailored towards application and game
developers, system kernel-level homebrew like 
https://github.com/Myriachan/libkhax, 
https://github.com/shinyquagsire23/bootstrap, and
https://github.com/StapleButter/Staplehax will never be portable from libctru
to libctr. This is intentional, because libctr intentionally hides a number of
details that libctru exposes directly. This is an architectural design 
tradeoff; by focusing only on what application developers use, we can eliminate
a number of functions/params/values from libctr. This results in more readable
code, better link-time optimizations, easier compile-time static checking, 
and easier maintainability. So the choice was made to exclude certain 
functionality from libctr, even if this does reduce the potential number of 
users and use-cases.

Second, it will be important to remember: libctr tries to be the best at what
it does, but it doesn't try to do anything anything else. Nothing in libctr is
exposed through the public API unless it meets the following criteria:
   1. Is it neccessary?
   2. Will it probably undergo substantial changes very soon?
   3. Is it efficient enough to be used in production quality code?
   4. Is it easy to use correctly, and hard to use incorrectly?
   5. Is it as small as possible, without being any smaller?

Those criteria reflect some of the most desirable characteristics in an API. As
long as they are followed, we can always be positive that *any* changes to
libctr will never hurt it, only add to it. Any pull requests or commits which
publicly expose an API which violates any of those principles will be rejected,
as will any changes to an existing API which cause it to violate a criteria.

