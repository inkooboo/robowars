robowars
========

building boost statically:


> for win
>> add mingw bin to PATH var then
>> bootstrap.bat
>> b2 toolset=gcc link=static threading=multi runtime-link=static

> for mac
>> ./booststrap.sh
>>./b2 toolset=clang cxxflags="-stdlib=libc++" linkflags="-stdlib=libc++" link=static threading=multi runtime-link=static
