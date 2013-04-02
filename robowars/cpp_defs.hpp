#ifndef __CPP_11_HACKS__
#  define __CPP_11_HACKS__


#  if defined(_MSC_VER)
#    define thread_local __declspec(thread)
#  else
#    define thread_local __thread
#  endif

template <typename T>
void unused_param(T &&)
{ }


#endif //__CPP_11_HACKS__
