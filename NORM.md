# TEAM NORM

## Structure files:
>./Makefile  (setting)
>./config.ini (config files)
./src/main.cpp (for *.cpp)  
./src/ft_utils.cpp (functions without class)  
./inc/Webserv.class.hpp (for *.hpp)  
./inc/tpp/Webserv.template.tpp (for template)  
./inc/ipp/Webserv.template.tpp (for interface)  

## Functions names:
>**ft_function_name**: global function (utils...)  
**fs_function_name**: static function (same file)  
**dg_function_name**: debug/test function (from debug.hpp)

## Class names:
> ClassName

## Methods names:
> getName

## Class variables:
> _private_attribute
> public_attribute
> g_global_attribute

## Struct and enum + typedef
```
e_enum
s_struct
t_typedef
```

## const everywhere
```
<type> const& <function/attribute> const
```
## tab == 4 espaces

## Comment formating
A function should be correctly commented, with brief (function purpose), param (sent parameters), return (returned value)
```c
Simple line comment:
// hello
Multiline comment:
/*
*  @brief	Default constructor of the class Socket.
*               Initialize the socket without any parameters
*  @param	void
*  @return	void
*/
Socket::Socket(void): _fd(-1) {}
```