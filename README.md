robowars
========

building boost statically:

  -for win
./b2 toolset=msvc link=static threading=multi runtime-link=static

  - for mac
./b2 toolset=clang cxxflags="-stdlib=libc++" linkflags="-stdlib=libc++" link=static threading=multi runtime-link=static
