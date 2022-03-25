#pragma once

// This is stolen from this genius: https://www.modernescpp.com/index.php/visiting-a-std-variant-with-the-overload-pattern

template<typename... Args_T>
struct Overload : Args_T...
{
    using Args_T::operator()...;
};

template<typename... Args_T> Overload(Args_T...) -> Overload<Args_T...>;
