About
-----

The first and foremost disclaimer about libctr is this:
   libctr is not a catch-all, end-all, be-all solution. Some users will be
   satisfied with libctr, others will be more satisfied with libctru (by 
   smealum), and still other users will be dissatisfied with both. 

There is nothing about libctr that makes it inherently better than libctru, or 
inherently worse. It simply serves a different croud.

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

