#ifndef __CPP_11_HACKS__
#  define __CPP_11_HACKS__


#  if defined(_MSC_VER)
#    define thread_local __declspec(thread)
#  else
#    define thread_local __thread
#  endif

#  if !defined(QT_NO_DEBUG) || defined(_DEBUG)
#    define DEBUG
#  endif


template<class... T> void unused_params(T&&...) {}

#endif //__CPP_11_HACKS__
